#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "BME280.h"
#include "BME280_reg.h"
#include "my_I2C.h"

static void BME_getComp(calibData_t *calibData);

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
    uint8_t msb, lsb;
    msb = (uint8_t)I2C_MasterReceiveByte(BME280_ADDR, BME280_PRESS_MSB);
    lsb = (uint8_t)I2C_MasterReceiveByte(BME280_ADDR, BME280_PRESS_LSB);
    data->pressure = ((uint32_t)msb << 8) | lsb;
    msb = (uint8_t)I2C_MasterReceiveByte(BME280_ADDR, BME280_TEMP_MSB);
    lsb = (uint8_t)I2C_MasterReceiveByte(BME280_ADDR, BME280_TEMP_LSB);
    data->temp     = ((uint32_t)msb << 8) | lsb;
    msb = (uint8_t)I2C_MasterReceiveByte(BME280_ADDR, BME280_HUM_MSB);
    lsb = (uint8_t)I2C_MasterReceiveByte(BME280_ADDR, BME280_HUM_LSB);
    data->humidity = ((uint32_t)msb << 8) | lsb;
}

static void BME_getComp(calibData_t *calibData) {
    uint8_t b0, b1;
#define RD(reg) ((uint8_t)I2C_MasterReceiveByte(BME280_ADDR, (reg)))
#define RD16U(reg) ((uint16_t)(RD(reg)) | ((uint16_t)RD((reg)+1) << 8))
#define RD16S(reg) ((int16_t)RD16U(reg))
    calibData->dig_T1 = RD16U(BME280_CALIB00);
    calibData->dig_T2 = RD16S(BME280_CALIB00+2);
    calibData->dig_T3 = RD16S(BME280_CALIB00+4);
    calibData->dig_P1 = RD16U(BME280_CALIB00+6);
    calibData->dig_P2 = RD16S(BME280_CALIB00+8);
    calibData->dig_P3 = RD16S(BME280_CALIB00+10);
    calibData->dig_P4 = RD16S(BME280_CALIB00+12);
    calibData->dig_P5 = RD16S(BME280_CALIB00+14);
    calibData->dig_P6 = RD16S(BME280_CALIB00+16);
    calibData->dig_P7 = RD16S(BME280_CALIB00+18);
    calibData->dig_P8 = RD16S(BME280_CALIB00+20);
    calibData->dig_P9 = RD16S(BME280_CALIB00+22);
    calibData->dig_H1 = RD(BME280_CALIB00+25);
    calibData->dig_H2 = RD16S(BME280_CALIB26);
    calibData->dig_H3 = RD(BME280_CALIB26+2);
    b0 = RD(BME280_CALIB26+3);
    b1 = RD(BME280_CALIB26+4);
    calibData->dig_H4 = (int16_t)(((uint16_t)b0 << 4) | (b1 & 0x0F));
    b0 = RD(BME280_CALIB26+5);
    calibData->dig_H5 = (int16_t)(((uint16_t)b0 << 4) | (b1 >> 4));
    calibData->dig_H6 = (int8_t)RD(BME280_CALIB26+6);
#undef RD
#undef RD16U
#undef RD16S
}
    