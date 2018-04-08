#include "grove_rgb_lcd.h"

GroveLCD GroveLCD_init()
{
    GroveLCD lcd;
    lcd.connected = false;
    lcd.DEVICE_FILE = 0;
    return lcd;
}

void GroveLCD_connect (GroveLCD* lcd)
{
    char filename[11];
    SMBusName (filename);
    int df;
    df = open (filename, O_WRONLY);

    if (df == -1)
    {
        lcd->connected = false;
        return;
    }

    lcd->DEVICE_FILE = df;
    lcd->connected = true;
}

bool GroveLCD_isConnected (GroveLCD* lcd)
{
    return lcd->connected;
}

/**
 * set rgb color
 * if there are writes errors, then it throws exception
 * @param red   8-bit
 * @param green 8-bit
 * @param blue  8-bit
 */
int GroveLCD_setRGB (GroveLCD* lcd, uint8_t  red, uint8_t green, uint8_t blue)
{
    GroveLCD_selectSlave (lcd, DISPLAY_RGB_ADDR);
    int error_sum = 0;
    error_sum += i2c_smbus_write_byte_data (lcd->DEVICE_FILE, 0x00, 0x00);
    error_sum += i2c_smbus_write_byte_data (lcd->DEVICE_FILE, 0x01, 0x00);
    error_sum += i2c_smbus_write_byte_data (lcd->DEVICE_FILE, 0x08, 0xaa);
    error_sum += i2c_smbus_write_byte_data (lcd->DEVICE_FILE, 0x04, red);
    error_sum += i2c_smbus_write_byte_data (lcd->DEVICE_FILE, 0x03, green);
    error_sum += i2c_smbus_write_byte_data (lcd->DEVICE_FILE, 0x02, blue);

    if (error_sum < 0)
    {
        return -1;
    }

    return 0;
}

/**
 * sets the text on the LCD
 * LCD has 16 columns & 2 rows => 32 characters at most
 * @param string of maximum 32 characters
 */
int GroveLCD_setText (GroveLCD* lcd, const char* str)
{
    GroveLCD_selectSlave (lcd, DISPLAY_TEXT_ADDR);
    GroveLCD_sendCommand (lcd, CLEAR_DISPLAY);
    delay (50);
    GroveLCD_sendCommand (lcd, DISPLAY_ON | NO_CURSOR);
    GroveLCD_sendCommand (lcd, ENABLE_2ROWS);
    delay (50);
    int length = strlen (str);
    int error;
    bool already_had_newline;

    for (int i = 0; i < length; i++)
    {
        if (i == 16 || str[i] == '\n')
        {
            if (!already_had_newline)
            {
                already_had_newline = true;
                GroveLCD_sendCommand (lcd, NEW_ROW);

                if (str[i] == '\n')
                {
                    continue;
                }
            }
            else if (str[i] == '\n')
            {
                break;
            }
        }

        error = i2c_smbus_write_byte_data (lcd->DEVICE_FILE, DISPLAY_CHAR, (uint8_t) str[i] );

        if (error < 0)
        {
            return -1;
        }
    }

    return 0;
}

int GroveLCD_sendCommand (GroveLCD* lcd, uint8_t command)
{
    int error = i2c_smbus_write_byte_data (lcd->DEVICE_FILE, PROGRAM_MODE, command);

    if (error < 0)
    {
        return -1;
    }

    return 0;
}

/**
 * the LCD has 2 slaves
 * 1 for the RGB backlight color
 * 1 for the actual text
 * therefore there are 2 adresses
 * @param slave 7-bit address
 */
int GroveLCD_selectSlave (GroveLCD* lcd, uint8_t slave)
{
    int error = ioctl (lcd->DEVICE_FILE, I2C_SLAVE, slave);

    if (error < 0)
    {
        return -1;
    }

    return 0;
}

