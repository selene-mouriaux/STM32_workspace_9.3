/*
 * leds_control.h
 *
 *  Created on: Oct 14, 2020
 *      Author: silvanas
 */

#ifndef _LEDS_CONTROL
#define _LEDS_CONTROL

#include "cmsis_os2.h"

#define SIZE_OF_LED_COMMAND_BUFFER (10)
#define SIZE_OF_PLAYER_COMMAND_BUFFER (5)

typedef enum {
  LCRC_OK,
  LCRC_ERROR_SERIAL_OPEN,  // Check simulator status - impossible to open serial link
  LCRC_ERROR_SERIAL_WRITE, // Check simulator status - impossible to write on serial link
  LCRC_ERROR_SERIAL_READ,
  LCRC_ERROR_SERIAL_CLOSE, // Check simulator status - impossible to close serial link
  LCRC_ERROR_COL,          // COL must be between 1 and 7
  LCRC_ERROR_ROW,          // ROW must be between 1 and 7
  LCRC_ERROR_RGB_VALUE,    // Value of red, green and blue must be less or equal to 255
} LedControlReturnCode ;

osMessageQueueId_t inputs_queueHandle;
osMessageQueueId_t outputs_queueHandle;

/**
 * @brief Send command to a led
 *
 * To turn off led, set red, green, blue to 0
 *
 * @param row Row number of led to control [1..7]
 * @param col Column number of led to control [1..7]
 * @param red Red value of RGB code
 * @param green Green value of RGB code
 * @param blue Blue value of RGB code
 *
 * @return LCRC_OK if everything works correctly, else LCRC_ERROR_* corresponding
 *         of error encounter
 */
LedControlReturnCode setLedColor(const unsigned int row,
                                 const unsigned int col,
                                 const unsigned int red,
                                 const unsigned int green,
                                 const unsigned int blue);

char readbutton(char *pReadData, char DataSize);

LedControlReturnCode openLink();
LedControlReturnCode closeLink();

#endif
