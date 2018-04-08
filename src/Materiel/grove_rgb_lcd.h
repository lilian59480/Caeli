#ifndef GROVE_RGB_LCD_H
#define GROVE_RGB_LCD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdint.h>

#include "grovepi.h"

typedef struct
{
    uint8_t DEVICE_FILE;
    bool connected;
} GroveLCD;

#define DISPLAY_RGB_ADDR 0x62
#define DISPLAY_TEXT_ADDR 0x3e

#define CLEAR_DISPLAY 0x01
#define DISPLAY_ON 0x08
#define NO_CURSOR 0x04
#define ENABLE_2ROWS 0x28
#define PROGRAM_MODE 0x80
#define NEW_ROW 0xc0
#define DISPLAY_CHAR 0x40

GroveLCD GroveLCD_init();
void GroveLCD_connect (GroveLCD* lcd);
bool GroveLCD_isConnected (GroveLCD* lcd);
int GroveLCD_setRGB (GroveLCD* lcd, uint8_t  red, uint8_t green, uint8_t blue);
int GroveLCD_setText (GroveLCD* lcd, const char* str);
int GroveLCD_sendCommand (GroveLCD* lcd, uint8_t command);
int GroveLCD_selectSlave (GroveLCD* lcd, uint8_t slave);

#endif

