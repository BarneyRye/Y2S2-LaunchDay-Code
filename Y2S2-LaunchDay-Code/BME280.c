#define F_CPU 16000000UL
#include <util/delay.h>

#include "BME280.h"
#include "BME280_reg.h"
#include "my_I2C.h"

void BME280_config(calibData_t *calibData) {
    I2C_MasterTransmitByte(BME280_ADDR, BME280_RESET, BME280_RESET_VALUE);
    _delay_ms(100);
    char id = I2C_MasterReceiveByte(BME280_ADDR, BME280_ID);
    if (id != BME280_ID_VALUE) {
        PORTD |= (1<<PD4);
        return;
    }
    BME_getComp(calibData);

    I2C_MasterTransmitByte(BME280_ADDR, BME280_CTRL_HUM, BME280_H_OSRS_1);
    I2C_MasterTransmitByte(BME280_ADDR, BME280_CTRL_MEAS, BME280_T_OSRS_1 | BME280_P_OSRS_1 | BME280_MODE_NORMAL);
    I2C_MasterTransmitByte(BME280_ADDR, BME280_CONFIG, BME280_T_SB_0_5 | BME280_FILTER_OFF);
    id = I2C_MasterReceiveByte(BME280_ADDR, BME280_ID);
    if (id != BME280_ID_VALUE) {
        PORTD |= (1<<PD4);
        return;
    }
}

void BME280_getData(dataLog_t *data) {
    data->pressure = (I2C_MasterReceiveByte(BME280_ADDR, BME280_PRESS_MSB)<<8) | I2C_MasterReceiveByte(BME280_ADDR, BME280_PRESS_LSB);
    data->temperature = (I2C_MasterReceiveByte(BME280_ADDR, BME280_TEMP_MSB)<<8) | I2C_MasterReceiveByte(BME280_ADDR, BME280_TEMP_LSB);
    data->humidity = (I2C_MasterReceiveByte(BME280_ADDR, BME280_HUM_MSB)<<8) | I2C_MasterReceiveByte(BME280_ADDR, BME280_HUM_LSB);

}

static void BME_getComp(calibData_t *calibData) {
    calibData->dig_T1 = I2C_MasterReceiveByte(BME280_ADDR, BME280_CALIB00);
    calibData->dig_T1 |= (I2C_MasterReceiveByte(BME280_ADDR, BME280_CALIB00+1)<<8);
    calibData->dig_T2 = I2C_MasterReceiveByte(BME280_ADDR, BME280_CALIB00+2);
    calibData->dig_T2 |= (I2C_MasterReceiveByte(BME280_ADDR, BME280_CALIB00+3)<<8);
    calibData->dig_T3 = I2C_MasterReceiveByte(BME280_ADDR, BME280_CALIB00+4);
    calibData->dig_T3 |= (I2C_MasterReceiveByte(BME280_ADDR, BME280_CALIB00+5)<<8);
    calibData->dig_P1 = I2C_MasterReceiveByte(BME280_ADDR, BME280_CALIB00+6);
    calibData->dig_P1 |= (I2C_MasterReceiveByte(BME280_ADDR, BME280_CALIB00+7)<<8);
    calibData->dig_P2 = I2C_MasterReceiveByte(BME280_ADDR, BME280_CALIB00+8);
    calibData->dig_P2 |= (I2C_MasterReceiveByte(BME280_ADDR, BME280_CALIB00+9)<<8);
    calibData->dig_P3 = I2C_MasterReceiveByte(BME280_ADDR, BME280_CALIB00+10);
    calibData->dig_P3 |= (I2C_MasterReceiveByte(BME280_ADDR, BME280_CALIB00+11)<<8);
    calibData->dig_P4 = I2C_MasterReceiveByte(BME280_ADDR, BME280_CALIB00+12);
    calibData->dig_P4 |= (I2C_MasterReceiveByte(BME280_ADDR, BME280_CALIB00+13)<<8);
    calibData->dig_P5 = I2C_MasterReceiveByte(BME280_ADDR, BME280_CALIB00+14);
    calibData->dig_P5 |= (I2C_MasterReceiveByte(BME280_ADDR, BME280_CALIB00+15)<<8);
    calibData->dig_P6 = I2C_MasterReceiveByte(BME280_ADDR, BME280_CALIB00+16);
    calibData->dig_P6 |= (I2C_MasterReceiveByte(BME280_ADDR, BME280_CALIB00+17)<<8);
    calibData->dig_P7 = I2C_MasterReceiveByte(BME280_ADDR, BME280_CALIB00+18);
    calibData->dig_P7 |= (I2C_MasterReceiveByte(BME280_ADDR, BME280_CALIB00+19)<<8);
    calibData->dig_P8 = I2C_MasterReceiveByte(BME280_ADDR, BME280_CALIB00+20);
    calibData->dig_P8 |= (I2C_MasterReceiveByte(BME280_ADDR, BME280_CALIB00+21)<<8);
    calibData->dig_P9 = I2C_MasterReceiveByte(BME280_ADDR, BME280_CALIB00+22);
    calibData->dig_P9 |= (I2C_MasterReceiveByte(BME280_ADDR, BME280_CALIB00+23)<<8);
    calibData->dig_H1 = I2C_MasterReceiveByte(BME280_ADDR, BME280_CALIB00+25);
    calibData->dig_H2 = I2C_MasterReceiveByte(BME280_ADDR, BME280_CALIB26);
    calibData->dig_H2 |= (I2C_MasterReceiveByte(BME280_ADDR, BME280_CALIB26+1)<<8);
    calibData->dig_H3 = I2C_MasterReceiveByte(BME280_ADDR, BME280_CALIB26+2);
    calibData->dig_H4 = I2C_MasterReceiveByte(BME280_ADDR, BME280_CALIB26+3);
    calibData->dig_H4 |= (I2C_MasterReceiveByte(BME280_ADDR, BME280_CALIB26+4)<<4);
    calibData->dig_H5 = I2C_MasterReceiveByte(BME280_ADDR, BME280_CALIB26+5);
    calibData->dig_H5 |= (I2C_MasterReceiveByte(BME280_ADDR, BME280_CALIB26+4)>>4);
    calibData->dig_H6 = I2C_MasterReceiveByte(BME280_ADDR, BME280_CALIB26+6);
}
    