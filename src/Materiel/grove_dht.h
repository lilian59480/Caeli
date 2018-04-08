#ifndef GROVE_DHT_H
#define GROVE_DHT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <math.h>

#include "grovepi.h"

#define BLUE_MODULE 0
#define WHITE_MODULE 1

#define DHT_TEMP_CMD 40
#define MAX_RETRIES 3

typedef struct
{
    uint8_t module;
    uint8_t pin;
} GroveDHT;

void DHT_getSafeData (GroveDHT* dht, float* temp, float* humidity);
void DHT_getUnsafeData (GroveDHT* dht, float* temp, float* humidity);

float DHT_fourBytesToFloat (uint8_t* data);
bool DHT_areGoodReadings (float temp, float humidity);

#endif
