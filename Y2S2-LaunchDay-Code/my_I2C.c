/*
 * my_I2C.c
 *
 * Created: 07/08/2024 12:49:50
 *  Author: Simon Pope
 */ 

#include <avr/io.h>

void I2C_MasterInit(void)
{
	// prescalar = 1 (TWPS 00 - doesn't need changing)
	// TWBR = 12  0x0C to give 400kHz
	// SDA PC4 (A4/D18); SCL PC5 (A5/D19)
	
	TWSR = 0x00;	// Sets the two prescalar bits (bits 0 and 1 of TWSR) to 0 to give a bit rate prescalar of 1
	TWBR = 0x0C;  // TWBR = 12  (0x0C) to give 400kHz
	TWCR = (1<<TWEN); // Enable the I2C bus by setting bit 2 of the control register

}

void I2C_start(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);
}

void I2C_stop(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void I2C_MasterTransmitAddress(char D_Addr, char R_Addr)
{
	TWDR = D_Addr;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);
	
	TWDR = R_Addr;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);
}

void I2C_MasterTransmitData(char T_Data)
{
	TWDR = T_Data;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);
}

char I2C_MasterReceiveData(char D_Addr)
{	
	TWDR = D_Addr|1;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);

	TWCR = (1<<TWINT)|(1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);
	return TWDR;
}

void I2C_MasterTransmitByte(char D_Addr, char R_Addr, char T_Data)
{
	I2C_start();
	I2C_MasterTransmitAddress(D_Addr,R_Addr);
	I2C_MasterTransmitData(T_Data);
	I2C_stop();
}

char I2C_MasterReceiveByte(char D_Addr, char R_Addr)
{
	char R_Data;
	I2C_start();
	I2C_MasterTransmitAddress(D_Addr,R_Addr);
	I2C_start();
	R_Data = I2C_MasterReceiveData(D_Addr);
	I2C_stop();
	return R_Data;
}