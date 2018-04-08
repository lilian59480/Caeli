// Copyright Dexter Industries, 2016
// http://dexterindustries.com/grovepi

#ifndef GROVEPI_H
#define GROVEPI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <linux/i2c.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdint.h>

#define G_INPUT 0
#define G_OUTPUT 1
#define G_LOW false
#define G_HIGH true

void SMBusName (char* smbus_name);



// default address of GrovePi set as default argument
bool initGrovePi();
void setGrovePiAddress (uint8_t addr);
bool writeBlock (uint8_t command, uint8_t pin_number, uint8_t opt1, uint8_t opt2);
bool writeByte (uint8_t byte_val);
bool readBlock (uint8_t* data_block);
uint8_t readByte();

void delay (unsigned int milliseconds);
bool pinMode (uint8_t pin, uint8_t mode);
bool digitalWrite (uint8_t pin, bool value);
uint8_t digitalRead (uint8_t pin);
bool analogWrite (uint8_t pin, uint8_t value);
int analogRead (uint8_t pin);
int ultrasonicRead (uint8_t pin);

#endif
