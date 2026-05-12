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

static uint8_t filename_index = 0;

FATFS fs;		/* Filesystem object for each logical drive */
FIL fp;

static void getFilename(uint8_t *index) {
	FRESULT res;
	char temp[20];
	for (uint8_t i = 0; i <= 99; i++) {
		snprintf(temp, sizeof(temp), "dataLog%02d.bin", i);
		res = f_open(&fp, temp, FA_CREATE_NEW | FA_WRITE);
		if (res == FR_OK) {
			*index = i;
			f_close(&fp);
			break;
		}
	}
}

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

	getFilename(&filename_index);
	/* Open file and write calibration struct as raw binary */
	char filename[20];
	snprintf(filename, sizeof(filename), "calibData%02d.bin", filename_index);
	rc = f_open(&fp,filename, FA_WRITE | FA_CREATE_ALWAYS);
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

	snprintf(filename, sizeof(filename), "dataLog%02d.bin", filename_index);
	rc = f_open(&fp,filename, FA_OPEN_EXISTING | FA_WRITE);
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