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
#define LOGRATE 50 //HZ

calibData_t calibData;
dataLog_t data[BUFFERSIZE];


int main(void){

    DDRD |= (0x1F << PD3);

    I2C_MasterInit();
    BME280_config(&calibData);
    BMI270_config();
    init_sd_card(&calibData);
    TIM0_init();

    uint32_t startTime = timestamp();
    static uint8_t index = 0;
    static uint32_t logCounts = 0;
    static uint8_t isLogging = 1;
	static uint32_t totalLogs = LOGRATE*(3600/BUFFERSIZE);

    PORTD |= (1<<PD7);
    while (isLogging) {
        while (timestamp()-startTime < (1000/LOGRATE)) { _delay_us(500); }
        startTime += (1000/LOGRATE);
        data[index].timestamp = timestamp();
        BME280_getData(&data[index]);
        BMI270_getData(&data[index]);
        index++;
        if (index >= BUFFERSIZE) {
            SD_sample_write(data);
            index = 0;
			logCounts++;
        }
        if (logCounts % (16*3) == 0) {
            fileSync();
        }
        if (logCounts >= totalLogs) {
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

