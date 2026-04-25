/*
 * SDcard.c
 *
 * Created: 07/11/2024 14:16:46
 *  Author: Simon Pope
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "diskio.h"
#include "ff.h"

FATFS fs;		/* Filesystem object for each logical drive */
FIL fp;

void init_sd_card(calibData_t *calibData)
{
	UINT bw;
	FRESULT rc;
	BYTE buff[256];

	/* Mount volume */
	rc = f_mount(&fs,"",0);
	if (rc == FR_OK){
		// Red LED on if mounted
			
		PORTD|=1<<PD5;
		_delay_ms(1000);
		PORTD&=~(1<<PD5);
		_delay_ms(1000);
	}


	/* Open file */
	rc = f_open(&fp,"calibData.txt", FA_WRITE | FA_CREATE_ALWAYS);
	if (rc == FR_OK){
		// Red LED on if opened
	
		PORTD|=1<<PD5;
		_delay_ms(1000);
		PORTD&=~(1<<PD5);
		_delay_ms(1000);
	}
	int len = sprintf(buff, "%d\n %d\n %d\n %d\n %d\n %d\n %d\n %d\n %d\n %d\n %d\n %d\n %d\n %d\n %d\n %d\n %d\n %d\n",
		calibData->dig_T1, calibData->dig_T2, calibData->dig_T3, 
		calibData->dig_P1, calibData->dig_P2, calibData->dig_P3, calibData->dig_P4, calibData->dig_P5, calibData->dig_P6, calibData->dig_P7, calibData->dig_P8, calibData->dig_P9, 
		calibData->dig_H1, calibData->dig_H2, calibData->dig_H3, calibData->dig_H4, calibData->dig_H5, calibData->dig_H6);
	// Write file header
	rc = f_write(&fp, buff, len, &bw);
	
	if (rc == FR_OK) {
		// Green LED on if data written
		PORTD|=1<<PD6;
	}	
	
	// Close file to ensure data is saved
	rc = f_close(&fp);

	rc = f_open(&fp,"dataLog.bin", FA_WRITE | FA_CREATE_ALWAYS);
	if (rc == FR_OK) {
		// Red LED on if data written
		PORTD|=1<<PD5;
	}
	else {
		// Red LED on if file not opened
		PORTD|=1<<PD5;
	}
}

void SD_sample_write(dataLog_t *samples){

	UINT bw;
	FRESULT rc;	
	
	// Write data to file
	rc = f_write(&fp, samples, 16*sizeof(dataLog_t), &bw);
	
	if (rc == FR_OK) {
		// Green LED on if data written
		PORTD|=1<<PD6;
	}
	else {
		// Green LED off if data not written
		PORTD&=~(1<<PD6);
	}
		
}

void fileSync() {
	f_sync(&fp);
}

void fileClose() {
	f_close(&fp);
}

DWORD get_fattime (void)
{
	
	/* Pack date and time into a DWORD variable */
	return	 0;
}