/*
 * my_I2C.h
 *
 * Created: 07/08/2024 12:50:05
 *  Author: Simon Pope
 */ 

#ifndef MY_I2C_H_
#define MY_I2C_H_

void I2C_MasterInit(void);

void I2C_start(void);

void I2C_stop(void);

void I2C_MasterTransmitAddress(char D_Addr, char R_Addr);

void I2C_MasterTransmitData(char T_Data);

char I2C_MasterReceiveData(char D_Addr);

void I2C_MasterTransmitByte(char D_Addr, char R_Addr, char T_Data);

char I2C_MasterReceiveByte(char D_Addr, char R_Addr);

#endif /* MY_I2C_H_ */