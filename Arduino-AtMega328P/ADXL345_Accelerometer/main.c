/*---------------------------------------------------------------------------*/
/* Getting the ADXL345 accelerometer readings and printing on serial moniotr.*/
/*---------------------------------------------------------------------------*/

/*------------------------------- Libraries ---------------------------------*/
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include "I2C.h"
#include "ADXL345.h"
#include "uart.h"    

/*-------------------------------- Macros -----------------------------------*/
#define F_CPU 16000000UL // CPU clock freq is independent clock prescaler.
#define BAUD_RATE 9600
#define BAUD_PRESCALER ((F_CPU / (BAUD_RATE * 16UL)) - 1)

// string formatting for the itoa() function:
#define HEX_FORMAT 16
#define DEC_FORMAT 10
#define OCT_FORMAT 8

/*------------------------------- Variables ----------------------------------*/
// temporary storage for raw data read from a sensor, two bytes per axis:
uint8_t accelBuf[6];
// int16_t accelX, accelY, accelZ;
// float accelBuf[6];
float accelX, accelY, accelZ;

char tempStr[8]; // temp storage for a formatted string from itoa().

/*------------------------------ Subroutines ---------------------------------*/
void configure_Hardware() {
  UART_init(BAUD_PRESCALER); // Initialize the UART.

  i2c_init(400000UL); // Initialize the I2C bus.

  // Initialize and power up the accelerometer.
  adxl345_setDataFormat(ADXL_DATA_FORMAT_FULL_RES | ADXL_DATA_FORMAT_RANGE_02); // full resolution, +/-16g
  adxl345_setBWRate(ADXL_BW_RATE_0012);  // data rate 12.5Hz
  adxl345_setPowerControl(ADXL_POWER_CTL_MEASURE);
}
void floatToString(float value, char* buffer, int decimalPlaces) {
    int intPart = (int)value;
    int fracPart = (int)((value - intPart) * 100);  // Multiply by 100 to get two decimal places

    if (fracPart < 0) {
        fracPart = -fracPart;  // Make sure the fractional part is positive
    }
};

/*--------------------------------- Main -------------------------------------*/
int main(void) {
  configure_Hardware();

  while(1) { // read the sensor data:
    adxl345_getAccelData(accelBuf);

    // accelX = (int16_t)accelBuf[1] << 8;
    // accelX += (float)(int16_t)accelBuf[0];
    // accelX /= 24.8;
    
    accelX = (float)(((int16_t)accelBuf[1] << 8) + (int16_t)accelBuf[0]) / 24.8;

    UART_putstring("X: ");
    // UART_putstring(itoa(accelX, tempStr, DEC_FORMAT));
 
    floatToString(accelX, tempStr, 2);  // 2 decimal places
    UART_putstring(tempStr);
    UART_putstring("\r\n");
    _delay_ms(400);


    accelY = (int16_t)accelBuf[3] << 8;
    accelY += (int16_t)accelBuf[2];
    UART_putstring("Y: ");
    UART_putstring(itoa(accelY, tempStr, DEC_FORMAT));
    UART_putstring("\r\n");
    _delay_ms(400);

    accelZ = (int16_t)accelBuf[5] << 8;
    accelZ += (int16_t)accelBuf[4];
    UART_putstring("Z: ");
    UART_putstring(itoa(accelZ, tempStr, DEC_FORMAT));
    UART_putstring("\r\n");
    UART_putstring("\r\n");
    UART_putstring("----------------------------------\r\n");
    _delay_ms(400);
  }
}