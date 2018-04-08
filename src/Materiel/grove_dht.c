#include "grove_dht.h"

/**
 * returns via its parameters the temperature and humidity
 * this function is NaN-proof
 * it always gives "accepted" values
 *
 * if bad values are read, then it will retry reading them
 * and check if they are okay for a number of [MAX_RETRIES] times
 * before throwing a [runtime_error] exception
 *
 * @param temp     in Celsius degrees
 * @param humidity in percentage values
 */
void DHT_getSafeData (GroveDHT* dht, float* temp, float* humidity)
{
    int current_retry  = 0;
    DHT_getUnsafeData (dht, temp, humidity); // read data from GrovePi once

    // while values got are not okay / accepteed
    while ( (isnan (*temp) || isnan (*humidity) || !DHT_areGoodReadings (*temp, *humidity) )
            && current_retry < MAX_RETRIES)
    {
        // reread them again
        current_retry += 1;
        DHT_getUnsafeData (dht, temp, humidity);
    }

}

/**
 * function for returning via its arguments the temperature & humidity
 * it's not recommended to use this function since it might throw
 * some NaN or out-of-interval values
 *
 * use it if you come with your own implementation
 * or if you need it for some debugging
 *
 * @param temp     in Celsius degrees
 * @param humidity in percentage values
 */
void DHT_getUnsafeData (GroveDHT* dht, float* temp, float* humidity)
{
    writeBlock (DHT_TEMP_CMD, dht->pin, dht->module,0);
    readByte();
    uint8_t data_block[33];
    readBlock (data_block);
    *temp = DHT_fourBytesToFloat (data_block + 1);
    *humidity = DHT_fourBytesToFloat (data_block + 5);
}

/**
 * function for converting 4 unsigned bytes of data
 * into a single float
 * @param  byte_data array to hold the 4 data sets
 * @return           the float converted data
 */
float DHT_fourBytesToFloat (uint8_t* byte_data)
{
    float output;

    memcpy(&output,byte_data,4);
    
    return output;
}

bool DHT_areGoodReadings (float temp, float humidity)
{
    return (temp > -100.0 && temp < 150.0 && humidity >= 0.0 && humidity <= 100.0);
}
