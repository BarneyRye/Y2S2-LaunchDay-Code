/*
 * SDcard.c
 *
 * Created: 07/11/2024 14:16:46
 *  Author: Simon Pope
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "datastructs.h"
#include "diskio.h"
#include "ff.h"

FATFS fs;		/* Filesystem object for each logical drive */
FIL fp;

void init_sd_card(calibData_t *calibData)
{
	UINT bw;
	FRESULT rc;

	/* Mount volume */
	rc = f_mount(&fs,"",0);
	if (rc == FR_OK){
		// Red LED on if mounted
			
		PORTD|=1<<PD5;
		_delay_ms(1000);
		PORTD&=~(1<<PD5);
		_delay_ms(1000);
	}


	/* Open file and write calibration struct as raw binary */
	rc = f_open(&fp,"calibData.bin", FA_WRITE | FA_CREATE_ALWAYS);
	if (rc == FR_OK){
		// Red LED on if opened
	
		PORTD|=1<<PD5;
		_delay_ms(1000);
		PORTD&=~(1<<PD5);
		_delay_ms(1000);
	}
	rc = f_write(&fp, calibData, sizeof(calibData_t), &bw);

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