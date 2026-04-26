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

    while (1) {

    }
}

