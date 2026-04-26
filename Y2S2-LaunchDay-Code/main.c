/*
 * Y2S2-LaunchDay-Code.c
 *
 * Created: 25/04/2026 11:35:30
 * Author : Barney
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "datastructs.h"
#include "timer.h"
#include "my_I2C.h"
#include "SDcard.h"
#include "BME280.h"
#include "BME280_reg.h"
#include "BMI270.h"
#include "BMI270_reg.h"

#define BUFFERSIZE 16

calibData_t calibData;
dataLog_t data[BUFFERSIZE];


int main(void){

    TIM0_init();
    i2C_init();
    BME280_config(&calibData);
    BMI270_config();
    init_SD_card(&calibData);

    uint32_t startTime = timestamp();
    static uint8_t index = 0;
    static uint32_t logCounts = 0;
    static uint8_t isLogging = 1;

    while (isLogging) {
        while (timestamp()-startTime < (1000/50)) { _delay_us(500); }
        data[index].timestamp = timestamp();
        BME280_readData(&data[index]);
        BMI270_readData(&data[index]);
        index++;
        logCounts++;
        if (index >= BUFFERSIZE) {
            SD_sample_write(data);
            index = 0;
        }
        if (logCounts % (16*3) == 0) {
            fileSync();
        }
        if (logCounts >= (50 * 60 *60)) {
            fileClose();
            isLogging = 0;
        }
    }
    while(1) {
        PORTD |= (1 << PD7);
        _delay_ms(250);
        PORTD &= ~(1 << PD7);
        _delay_ms(750);
    }
}

