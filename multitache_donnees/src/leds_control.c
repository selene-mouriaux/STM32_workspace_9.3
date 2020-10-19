#include "leds_control.h"

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#ifdef TEST_HEADER
  #include TEST_HEADER
#endif

#ifndef NUMFER_OF_LEDS_PER_RING
  #define NUMBER_OF_LEDS_PER_RING 24
#endif

#ifndef MAX_ROW
  #define MAX_ROW 7
#endif

#ifndef MAX_COL
  #define MAX_COL 7
#endif

#ifndef LC_OPEN
  #define LC_OPEN open
#endif

#ifndef LC_WRITE
  #define LC_WRITE write
#endif

#ifndef LC_CLOSE
  #define LC_CLOSE close
#endif

#ifndef LC_READ
  #define LC_READ read
#endif

#ifndef LC_SERIAL_PATH
  #define LC_SERIAL_PATH "/tmp/puissance4/serial/ttyS1"
#endif

#define SIZE_OF_LED_COMMAND_BUFFER (10)
#define SIZE_OF_PLAYER_COMMAND_BUFFER (5)

/**
 * @brief encode number between 0 and 15 in its hexadecimal representation
 *
 * @param i Number to encode
 * @return [0-9A-F] if 0 < i < 16; X otherwise
 */
static inline unsigned char toHexaHalfByte(const unsigned char i) {
  if (i < 9) {
    return '0' + i;
  }
  else if (i < 16) {
    return 'A' + (i - 10);
  }
  else {
    return 'X';
  }
}

/**
 * @brief encode byte in its hexadecimal representation
 *
 * @param buffer Buffer to store result, should be at least size 2
 * @param byte Byte to encode
 */
static inline void encodeByte(char * const buffer, const unsigned char byte) {
  buffer[0] = toHexaHalfByte((byte >> 4) & 0x0F);
  buffer[1] = toHexaHalfByte(byte & 0x0F);
}

/**
 * @brief compute buffer to control led through serial link
 *
 * @param buffer Buffer to fill. Buffer must have enough memory: (4 + (nb leds per ring)*3) bytes
 * @param row Row number of led to control [1..7]
 * @param col Column number of led to control [1..7]
 * @param red Red value of RGB code
 * @param green Green value of RGB code
 * @param blue Blue value of RGB code
 */
static void computeMessage(char * const buffer,
		const unsigned char row,
		const unsigned char col,
		const unsigned char red,
		const unsigned char green,
		const unsigned char blue) {

	buffer[0] = 'R';

	buffer[1] = toHexaHalfByte(row);
	buffer[2] = toHexaHalfByte(col);
	encodeByte(&(buffer[3]), red);
	encodeByte(&(buffer[5]), green);
	encodeByte(&(buffer[7]), blue);

	buffer[SIZE_OF_LED_COMMAND_BUFFER - 1] = '\n';
}


static int fd = -1;

LedControlReturnCode openLink() {
  fd = LC_OPEN("/tmp/puissance4/serial/ttyS1", O_RDWR);

  return fd == -1 ? LCRC_ERROR_SERIAL_OPEN : LCRC_OK;
}

LedControlReturnCode closeLink() {
  if (LC_CLOSE(fd) != 0)
    return LCRC_ERROR_SERIAL_CLOSE;

  fd = -1;
  return LCRC_OK;
}

LedControlReturnCode setLedColor(const unsigned int row, 
    const unsigned int col, 
    const unsigned int red, 
    const unsigned int green, 
    const unsigned int blue) {
  if (row > MAX_ROW || row == 0)
    return LCRC_ERROR_ROW;

  if (col > MAX_COL || col == 0)
    return LCRC_ERROR_COL;

  if (red > 255 || green > 255 || blue > 255)
    return LCRC_ERROR_RGB_VALUE;

  if (fd == -1)
    return LCRC_ERROR_SERIAL_OPEN;

  const unsigned int finalRow = row - 1;
  const unsigned int finalCol = col - 1;

  unsigned char buffer[SIZE_OF_LED_COMMAND_BUFFER] = { 0 };
  computeMessage(buffer, finalRow, finalCol, red, green, blue);

  const ssize_t nbOfWrittenBytes = LC_WRITE(fd, buffer, SIZE_OF_LED_COMMAND_BUFFER);

  if (nbOfWrittenBytes != SIZE_OF_LED_COMMAND_BUFFER) {
    return LCRC_ERROR_SERIAL_WRITE;
  }

  return LCRC_OK;
}

char readbutton(char *pReadData, char DataSize)
{
  if (fd == -1)
    return LCRC_ERROR_SERIAL_OPEN;

  unsigned char buffer[SIZE_OF_PLAYER_COMMAND_BUFFER] = { 0 };

  const ssize_t nbOfReadBytes = LC_READ(fd, buffer, SIZE_OF_PLAYER_COMMAND_BUFFER);

  if (nbOfReadBytes != SIZE_OF_PLAYER_COMMAND_BUFFER) {
    return LCRC_ERROR_SERIAL_READ;
  }

  if(nbOfReadBytes<=DataSize)
  {
    memcpy(pReadData,buffer,nbOfReadBytes);
  }
  return LCRC_OK;
}
