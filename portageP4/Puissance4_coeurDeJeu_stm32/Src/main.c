/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include<stdio.h>
#include"debug.h"
#include"game_p4.h"
#include<stdlib.h>
#include<stdint.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include"queue.h"
#include"leds_control.h"
#include<string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
//Game pads controls
typedef enum {
	PAD_1 = 49,
	PAD_2 = 50,
	DOWN_PAD = 100,
	LEFT_PAD = 108,
	RIGHT_PAD = 114,
	UP_PAD = 117
} Pads_controls;

//Pad command Identifier
typedef enum {
	NO_PAD, PAD_1_COMMAND, PAD_2_COMMAND
} Pad_Identifier;

// Victory type command enum.
typedef enum {
	LINE_VICTORY, COL_VICTORY, RIGHT_DIAG_VICTORY, LEFT_DIAG_VICTORY
} Display_victory_command;

//Game mode enum.
typedef enum {
	NUMBERS, CONNECT_4
} Display_mode_command;

//Game Status enum.
typedef enum {
	RESET, PLAY, GAME_END
} Display_status_command;

//Game move commands enum.
typedef enum {
	DOWN_COMMAND, UP_COMMAND, LEFT_COMMAND, RIGHT_COMMAND, NEXT_PLAYER_COMMAND
} Move_command;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
// ASCII and OFFSETS regulators.
#define LED_PANEL_OFFSET 1
#define TOP_ROW_OFFSET 1

#define WRITE_QUEUE_BUFFER_SIZE 8
#define READ_BUTTON_BUFFER_SIZE 4
#define READ_QUEUE_BUFFER_SIZE 3
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ETH_HandleTypeDef heth;

UART_HandleTypeDef huart3;

PCD_HandleTypeDef hpcd_USB_OTG_FS;

/* USER CODE BEGIN PV */
//Global Static Vars, inter-thread communication.
static struct Queue* read_queue;
static struct Queue* write_queue;
static pthread_t thread_id;
static pthread_t write_thread_id_set;
//static pthread_t write_thread_id_blink;

static victory_infos_struct victory_infos;

//Defined colors table of structs.
static led colors[7] = { { COLOR_ON, COLOR_OFF, COLOR_OFF }, { COLOR_OFF,
		COLOR_ON,
		COLOR_OFF }, { COLOR_OFF, COLOR_OFF, COLOR_ON }, { COLOR_ON,
				COLOR_ON, COLOR_ON }, { COLOR_ON, COLOR_OFF, COLOR_ON }, { COLOR_ON,
						COLOR_ON, COLOR_OFF }, { COLOR_OFF, COLOR_OFF, COLOR_OFF } };

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ETH_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_USB_OTG_FS_PCD_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

//Send message through queues, inter-thread communication.
void SendMessage(Queue_id queue, char* message, int message_length) {

	if (queue == QUEUE_READ) {
		if (message_length <= READ_QUEUE_BUFFER_SIZE) {
			add_to_Queue(read_queue, message);
			sem_post(&read_queue->semaphore);
			printf("Message sent.\n");
		} else
			printf("Send message Failed ! Buffer Overflow !\n");
	} else if (queue == QUEUE_WRITE) {
		if (message_length <= WRITE_QUEUE_BUFFER_SIZE) {
			add_to_Queue(write_queue, message);
			sem_post(&write_queue->semaphore);
			printf("Message sent.\n");
		} else
			printf("Send message Failed ! Buffer Overflow !\n");
	} else
		printf("Send message Failed ! Queue unidentified !\n");
}

//Receive message through queues, inter-thread communication.
int ReceiveMessage(Queue_id queue, char* message, int message_length) {
	if (queue == QUEUE_WRITE) {
		if (message_length >= WRITE_QUEUE_BUFFER_SIZE) {
			//sem_wait(&write_queue->semaphore);
			int status = del_from_Queue(write_queue, message);
			//printf("Message received.\n");
			return status;
		} else {
			printf("Receive message failed ! Buffer Overflow !\n");
			return -1;
		}
	} else if (queue == QUEUE_READ) {
		if (message_length >= READ_QUEUE_BUFFER_SIZE) {
			sem_wait(&read_queue->semaphore);
			del_from_Queue(read_queue, message);
			printf("Message received.\n");
			return 0;
		} else {
			printf("Receive message failed ! Buffer Overflow !\n");
			return -1;
		}
	}
	printf("Receive message failed ! Queue unidentified !\n");
	return -1;
}

//Input reading and decoding thread handler.
void *thread_handler_read(void* args) {
	char button_read[READ_BUTTON_BUFFER_SIZE];
	int error;
	char command[READ_QUEUE_BUFFER_SIZE];

	while (1) {
		//Get input.
		error = readbutton(button_read, (READ_BUTTON_BUFFER_SIZE + 1));
		if (error != 0)
			printf("%d\n", error);

		//Debug input print.
		if (button_read[3] == DOWN_PAD)
			printf("Button press read: %d %d %d %d\n", button_read[0],
					button_read[1], button_read[2], button_read[3]);

		//Process input.
		if (button_read[3] == DOWN_PAD && button_read[2] == UP_PAD) {
			if (button_read[1] == PAD_1) {
				command[0] = UP_COMMAND;
				command[1] = PAD_1_COMMAND;
			} else if (button_read[1] == PAD_2) {
				command[0] = UP_COMMAND;
				command[1] = PAD_2_COMMAND;
			}
		} else if (button_read[3] == DOWN_PAD && button_read[2] == DOWN_PAD) {
			if (button_read[1] == PAD_1) {
				command[0] = DOWN_COMMAND;
				command[1] = PAD_1_COMMAND;
			} else if (button_read[1] == PAD_2) {
				command[0] = DOWN_COMMAND;
				command[1] = PAD_2_COMMAND;
			}
		} else if (button_read[3] == DOWN_PAD && button_read[2] == LEFT_PAD) {
			if (button_read[1] == PAD_1) {
				command[0] = LEFT_COMMAND;
				command[1] = PAD_1_COMMAND;
			} else if (button_read[1] == PAD_2) {
				command[0] = LEFT_COMMAND;
				command[1] = PAD_2_COMMAND;
			}
		} else if (button_read[3] == DOWN_PAD && button_read[2] == RIGHT_PAD) {
			if (button_read[1] == PAD_1) {
				command[0] = RIGHT_COMMAND;
				command[1] = PAD_1_COMMAND;
			} else if (button_read[1] == PAD_2) {
				command[0] = RIGHT_COMMAND;
				command[1] = PAD_2_COMMAND;
			}
		} else
			continue;

		//Send processed command to read queue.
		SendMessage(QUEUE_READ, command, READ_QUEUE_BUFFER_SIZE);
	}
	pthread_detach(pthread_self());
	pthread_exit(NULL);
	return 0;
}

void *thread_handler_app(void* args) {

	//Game initializations.
	initialize_victory_struct();
	debug_setlevel(2);
	gp4_init();
	int restart = 0;
	move_t move;
	move.player = 1;
	char tmp_message[WRITE_QUEUE_BUFFER_SIZE];
	char tmp_command[READ_QUEUE_BUFFER_SIZE];
	while (1) {
		if (restart != 0) {
			initialize_victory_struct();
			gp4_init();
			restart = 0;
			move.player = 1;
			sleep(1);
		}
		while (1) {
			//Wait message from reading queue.
			ReceiveMessage(QUEUE_READ, tmp_command, READ_QUEUE_BUFFER_SIZE);
			printf("App handler received: %d %d\n", tmp_command[0], tmp_command[1]);

			//Process message from reading queue.

			//If DOWN button is pushed.
			if (tmp_command[0] == DOWN_COMMAND && tmp_command[1] == move.player) {
				move = gp4_play_token();
				tmp_message[0] = CONNECT_4;
				tmp_message[1] = PLAY;
				tmp_message[2] = DOWN_COMMAND;
				tmp_message[3] = move.player_color;
				tmp_message[4] = move.beg.l;
				tmp_message[5] = move.beg.c;
				tmp_message[6] = move.end.l;
				tmp_message[7] = move.end.c;
				SendMessage(QUEUE_WRITE, tmp_message, WRITE_QUEUE_BUFFER_SIZE);
				sleep(1);
				victory_infos = gp4_check_winner();
				if (victory_infos.game_end != 0) {
					break;
				}
				move = gp4_next_player();
				tmp_message[0] = CONNECT_4;
				tmp_message[1] = PLAY;
				tmp_message[2] = NEXT_PLAYER_COMMAND;
				tmp_message[3] = move.player_color;
				tmp_message[4] = move.beg.l;
				tmp_message[5] = move.beg.c;
				tmp_message[6] = move.end.l;
				tmp_message[7] = move.end.c;
				SendMessage(QUEUE_WRITE, tmp_message, WRITE_QUEUE_BUFFER_SIZE);
				continue;
				//If LEFT button is pushed.
			} else if (tmp_command[0] == LEFT_COMMAND
					&& tmp_command[1] == move.player) {
				move = gp4_move_left();
				tmp_message[0] = CONNECT_4;
				tmp_message[1] = PLAY;
				tmp_message[2] = LEFT_COMMAND;
				tmp_message[3] = move.player_color;
				tmp_message[4] = move.beg.l;
				tmp_message[5] = move.beg.c;
				tmp_message[6] = move.end.l;
				tmp_message[7] = move.end.c;
				SendMessage(QUEUE_WRITE, tmp_message, WRITE_QUEUE_BUFFER_SIZE);
				continue;
				//If RIGHT button is pushed.
			} else if (tmp_command[0] == RIGHT_COMMAND
					&& tmp_command[1] == move.player) {
				move = gp4_move_right();
				tmp_message[0] = CONNECT_4;
				tmp_message[1] = PLAY;
				tmp_message[2] = RIGHT_COMMAND;
				tmp_message[3] = move.player_color;
				tmp_message[4] = move.beg.l;
				tmp_message[5] = move.beg.c;
				tmp_message[6] = move.end.l;
				tmp_message[7] = move.end.c;
				SendMessage(QUEUE_WRITE, tmp_message, WRITE_QUEUE_BUFFER_SIZE);
				continue;
			}
		}
		//Victory processing
		if (victory_infos.game_end == 1) {
			printf("Game end : %d\nWinner: %d\nVictory Type : %d\n",
					victory_infos.game_end, victory_infos.winner_player,
					victory_infos.victory_type);
			printf("Coordonnées du jeton de victoire: Ligne %d Colonne %d\n",
					victory_infos.victory_token_coord[0] + 1,
					victory_infos.victory_token_coord[1] + 1);
			printf(
					"Alignement victorieux:\nJeton 1: Ligne %d Colonne %d\nJeton 2: Ligne %d Colonne %d\nJeton 3: Ligne"
					" %d Colonne %d\nJeton 4: Ligne %d Colonne %d\n",
					victory_infos.victory_line_tokens_coord[0][0] + 1,
					victory_infos.victory_line_tokens_coord[0][1] + 1,
					victory_infos.victory_line_tokens_coord[1][0] + 1,
					victory_infos.victory_line_tokens_coord[1][1] + 1,
					victory_infos.victory_line_tokens_coord[2][0] + 1,
					victory_infos.victory_line_tokens_coord[2][1] + 1,
					victory_infos.victory_line_tokens_coord[3][0] + 1,
					victory_infos.victory_line_tokens_coord[3][1] + 1);
			printf("\n");
			//Victory Blink coordinates processing.
			if (victory_infos.victory_type == HORIZONTAL) {
				tmp_message[2] = LINE_VICTORY;
			} else if (victory_infos.victory_type == VERTICAL) {
				tmp_message[2] = COL_VICTORY;
			} else if (victory_infos.victory_type == RIGHT_DIAGONAL) {
				tmp_message[2] = RIGHT_DIAG_VICTORY;
			} else if (victory_infos.victory_type == LEFT_DIAGONAL) {
				tmp_message[2] = LEFT_DIAG_VICTORY;
			}
			tmp_message[0] = CONNECT_4;
			tmp_message[1] = GAME_END;
			tmp_message[3] = move.player_color;
			tmp_message[4] = victory_infos.victory_line_tokens_coord[0][0];
			tmp_message[5] = victory_infos.victory_line_tokens_coord[0][1];
			tmp_message[6] = victory_infos.victory_line_tokens_coord[3][0];
			tmp_message[7] = victory_infos.victory_line_tokens_coord[3][1];
			SendMessage(QUEUE_WRITE, tmp_message, WRITE_QUEUE_BUFFER_SIZE);
		} else if (victory_infos.game_end == 2) {
			printf("Draw. Game Over.\n");
		}
		sleep(60);
		//Emptying Grid (turn leds off).
		tmp_message[0] = CONNECT_4;
		tmp_message[1] = RESET;
		tmp_message[2] = 0;
		tmp_message[3] = 0;
		tmp_message[4] = 0;
		tmp_message[5] = 0;
		tmp_message[6] = 0;
		tmp_message[7] = 0;
		SendMessage(QUEUE_WRITE, tmp_message, WRITE_QUEUE_BUFFER_SIZE);
		sleep(5);
		restart += 1;
	}
	pthread_detach(pthread_self());
	pthread_exit(NULL);
	return 0;
}

//Led panel controlling handler and blinking handler. 2 THREADS !.
void *thread_handler_write(void* args) {
	int receive_count = 1;
	char tmp_message_write[8];
	tmp_message_write[3] = 1;
	setLedColor(1, 1, colors[GREEN].RValue, colors[GREEN].GValue,
			colors[GREEN].BValue);
	while (1) {
		//if (pthread_self() == write_thread_id_set) {
		//Wait message from writing queue.
		if (ReceiveMessage(QUEUE_WRITE, tmp_message_write,
				WRITE_QUEUE_BUFFER_SIZE) == 0) {
			printf("Write handler received: %d %d %d %d %d %d %d %d\n",
					tmp_message_write[0], tmp_message_write[1],
					tmp_message_write[2], tmp_message_write[3],
					tmp_message_write[4], tmp_message_write[5],
					tmp_message_write[6], tmp_message_write[7]);

			if (tmp_message_write[0] == CONNECT_4) {

				//Console Display
				gp4_display();
				//Empty grid condition.
				if (tmp_message_write[1] == RESET) {
					for (int row = 2; row < 8; row++) {
						for (int col = 1; col < 8; col++) {
							setLedColor(row, col, colors[BLACK].RValue,
									colors[BLACK].GValue, colors[BLACK].BValue);
						}
					}
					break;
				}
				receive_count += 1;
				if (tmp_message_write[1] == PLAY) {
					//If DOWN button pressed. Validation animation.
					if (tmp_message_write[2] == DOWN_COMMAND) {
						printf("VALIDATION\n");
						receive_count = 0;
						for (int row = 2;
								row <= (tmp_message_write[6] + LED_PANEL_OFFSET);
								row++) {
							setLedColor(row - 1,
									(tmp_message_write[7] + LED_PANEL_OFFSET),
									colors[BLACK].RValue, colors[BLACK].GValue,
									colors[BLACK].BValue);
							setLedColor(row,
									(tmp_message_write[7] + LED_PANEL_OFFSET),
									colors[(int) tmp_message_write[3]].RValue,
									colors[(int) tmp_message_write[3]].GValue,
									colors[(int) tmp_message_write[3]].BValue);
							usleep(150000);
						}
						//If LEFT or RIGHT button pressed. Side move animation.
					} else if (tmp_message_write[2] == LEFT_COMMAND
							|| tmp_message_write[2] == RIGHT_COMMAND) {
						setLedColor(1,
								(tmp_message_write[5] + LED_PANEL_OFFSET),
								colors[BLACK].RValue, colors[BLACK].GValue,
								colors[BLACK].BValue);
						setLedColor(1,
								(tmp_message_write[7] + LED_PANEL_OFFSET),
								colors[(int) tmp_message_write[3]].RValue,
								colors[(int) tmp_message_write[3]].GValue,
								colors[(int) tmp_message_write[3]].BValue);
						//Next Player animation, change color and replace play token.
					} else if (tmp_message_write[2] == NEXT_PLAYER_COMMAND) {
						setLedColor(1,
								(tmp_message_write[7] + LED_PANEL_OFFSET),
								colors[(int) tmp_message_write[3]].RValue,
								colors[(int) tmp_message_write[3]].GValue,
								colors[(int) tmp_message_write[3]].BValue);
					}
					//Line victory blink.
				} else if (tmp_message_write[1] == GAME_END) {
					if (tmp_message_write[2] == LINE_VICTORY) {
						receive_count = 0;
						for (int count = 0; count < 30; count++) {
							for (int col = (tmp_message_write[5]
															  + LED_PANEL_OFFSET);
									col
									<= (tmp_message_write[7]
														  + LED_PANEL_OFFSET);
									col++) {
								setLedColor(
										tmp_message_write[4] + LED_PANEL_OFFSET
										+ TOP_ROW_OFFSET, col,
										colors[BLACK].RValue,
										colors[BLACK].GValue,
										colors[BLACK].BValue);
							}
							sleep(1);
							for (int col = (tmp_message_write[5]
															  + LED_PANEL_OFFSET);
									col
									<= (tmp_message_write[7]
														  + LED_PANEL_OFFSET);
									col++) {
								setLedColor(
										tmp_message_write[4] + LED_PANEL_OFFSET
										+ TOP_ROW_OFFSET, col,
										colors[(int) tmp_message_write[3]].RValue,
										colors[(int) tmp_message_write[3]].GValue,
										colors[(int) tmp_message_write[3]].BValue);
							}
							sleep(1);
						}
						//Column victory blink.
					} else if (tmp_message_write[2] == COL_VICTORY) {
						receive_count = 0;
						for (int count = 0; count < 30; count++) {
							for (int row = (tmp_message_write[4]
															  + LED_PANEL_OFFSET + TOP_ROW_OFFSET);
									row
									<= (tmp_message_write[6]
														  + LED_PANEL_OFFSET
														  + TOP_ROW_OFFSET); row++) {
								setLedColor(row,
										tmp_message_write[5] + LED_PANEL_OFFSET,
										colors[BLACK].RValue,
										colors[BLACK].GValue,
										colors[BLACK].BValue);
							}
							sleep(1);
							for (int row = (tmp_message_write[4]
															  + LED_PANEL_OFFSET + TOP_ROW_OFFSET);
									row
									<= (tmp_message_write[6]
														  + LED_PANEL_OFFSET
														  + TOP_ROW_OFFSET); row++) {
								setLedColor(row,
										tmp_message_write[5] + LED_PANEL_OFFSET,
										colors[(int) tmp_message_write[3]].RValue,
										colors[(int) tmp_message_write[3]].GValue,
										colors[(int) tmp_message_write[3]].BValue);
							}
							sleep(1);
						}
						//Right diagonal victory blink.
					} else if (tmp_message_write[2] == RIGHT_DIAG_VICTORY) {
						receive_count = 0;
						int win_row, win_col;
						for (int count = 0; count < 30; count++) {
							win_row = tmp_message_write[4] + LED_PANEL_OFFSET
									+ TOP_ROW_OFFSET;
							win_col = tmp_message_write[5] + LED_PANEL_OFFSET;
							for (int tokens = 0; tokens < 4; tokens++) {
								setLedColor(win_row, win_col,
										colors[BLACK].RValue,
										colors[BLACK].GValue,
										colors[BLACK].BValue);
								win_row++, win_col++;
							}
							sleep(1);
							win_row = tmp_message_write[4] + LED_PANEL_OFFSET
									+ TOP_ROW_OFFSET;
							win_col = tmp_message_write[5] + LED_PANEL_OFFSET;
							for (int tokens = 0; tokens < 4; tokens++) {
								setLedColor(win_row, win_col,
										colors[(int) tmp_message_write[3]].RValue,
										colors[(int) tmp_message_write[3]].GValue,
										colors[(int) tmp_message_write[3]].BValue);
								win_row++, win_col++;
							}
							sleep(1);
						}
						//Left diagonal victory blink.
					} else if (tmp_message_write[2] == LEFT_DIAG_VICTORY) {
						receive_count = 0;
						int win_row, win_col;
						for (int count = 0; count < 30; count++) {
							win_row = tmp_message_write[4] + LED_PANEL_OFFSET
									+ TOP_ROW_OFFSET;
							win_col = tmp_message_write[5] + LED_PANEL_OFFSET;
							for (int tokens = 0; tokens < 4; tokens++) {
								setLedColor(win_row, win_col,
										colors[BLACK].RValue,
										colors[BLACK].GValue,
										colors[BLACK].BValue);
								win_row--, win_col++;
							}
							sleep(1);
							win_row = tmp_message_write[4] + LED_PANEL_OFFSET
									+ TOP_ROW_OFFSET;
							win_col = tmp_message_write[5] + LED_PANEL_OFFSET;
							for (int tokens = 0; tokens < 4; tokens++) {
								setLedColor(win_row, win_col,
										colors[(int) tmp_message_write[3]].RValue,
										colors[(int) tmp_message_write[3]].GValue,
										colors[(int) tmp_message_write[3]].BValue);
								win_row--, win_col++;
							}
							sleep(1);
						}
					}
				}
			}
			//Play token blinking thread. receive_count is used to sync/stop blinking when necessary.
		} else {			// if (pthread_self() == write_thread_id_blink) {
			if (receive_count > 0) {
				setLedColor(1, (tmp_message_write[7] + LED_PANEL_OFFSET),
						colors[(int) tmp_message_write[3]].RValue,
						colors[(int) tmp_message_write[3]].GValue,
						colors[(int) tmp_message_write[3]].BValue);
				usleep(250000);
				setLedColor(1, (tmp_message_write[7] + LED_PANEL_OFFSET),
						colors[BLACK].RValue, colors[BLACK].GValue,
						colors[BLACK].BValue);
				usleep(250000);
			} else
				usleep(500000);
		}
	}
	pthread_detach(pthread_self());
	pthread_exit(NULL);
	return 0;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ETH_Init();
  MX_USART3_UART_Init();
  MX_USB_OTG_FS_PCD_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

		openLink();
		read_queue = create_Queue();
		write_queue = create_Queue();

		pthread_create(&thread_id, NULL, thread_handler_read, (void*) &thread_id);
		pthread_create(&write_thread_id_set, NULL, thread_handler_write,
				(void*) &write_thread_id_set);
		//pthread_create(&write_thread_id_blink, NULL, thread_handler_write,
		//		(void*) &write_thread_id_blink);
		pthread_create(&thread_id, NULL, thread_handler_app, (void*) &thread_id);
		pthread_join(thread_id, NULL);
		printf("Fin du programme.");
		closeLink();

		return 0;
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ETH Initialization Function
  * @param None
  * @retval None
  */
static void MX_ETH_Init(void)
{

  /* USER CODE BEGIN ETH_Init 0 */

  /* USER CODE END ETH_Init 0 */

  /* USER CODE BEGIN ETH_Init 1 */

  /* USER CODE END ETH_Init 1 */
  heth.Instance = ETH;
  heth.Init.AutoNegotiation = ETH_AUTONEGOTIATION_ENABLE;
  heth.Init.PhyAddress = LAN8742A_PHY_ADDRESS;
  heth.Init.MACAddr[0] =   0x00;
  heth.Init.MACAddr[1] =   0x80;
  heth.Init.MACAddr[2] =   0xE1;
  heth.Init.MACAddr[3] =   0x00;
  heth.Init.MACAddr[4] =   0x00;
  heth.Init.MACAddr[5] =   0x00;
  heth.Init.RxMode = ETH_RXPOLLING_MODE;
  heth.Init.ChecksumMode = ETH_CHECKSUM_BY_HARDWARE;
  heth.Init.MediaInterface = ETH_MEDIA_INTERFACE_RMII;

  /* USER CODE BEGIN MACADDRESS */
    
  /* USER CODE END MACADDRESS */

  if (HAL_ETH_Init(&heth) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ETH_Init 2 */

  /* USER CODE END ETH_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief USB_OTG_FS Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_OTG_FS_PCD_Init(void)
{

  /* USER CODE BEGIN USB_OTG_FS_Init 0 */

  /* USER CODE END USB_OTG_FS_Init 0 */

  /* USER CODE BEGIN USB_OTG_FS_Init 1 */

  /* USER CODE END USB_OTG_FS_Init 1 */
  hpcd_USB_OTG_FS.Instance = USB_OTG_FS;
  hpcd_USB_OTG_FS.Init.dev_endpoints = 4;
  hpcd_USB_OTG_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_OTG_FS.Init.dma_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_OTG_FS.Init.Sof_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.vbus_sensing_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.use_dedicated_ep1 = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_OTG_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_OTG_FS_Init 2 */

  /* USER CODE END USB_OTG_FS_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : USER_Btn_Pin */
  GPIO_InitStruct.Pin = USER_Btn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD1_Pin LD3_Pin LD2_Pin */
  GPIO_InitStruct.Pin = LD1_Pin|LD3_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = USB_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USB_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_OverCurrent_Pin */
  GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
