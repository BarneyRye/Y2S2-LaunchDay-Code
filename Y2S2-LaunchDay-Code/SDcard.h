/*
 * SDcard.h
 *
 * Created: 07/11/2024 14:16:26
 *  Author: Simon Pope
 */ 


#ifndef SDCARD_H_
#define SDCARD_H_

#include "datastructs.h"

void    init_sd_card(calibData_t *calibData);
void	SD_sample_write(dataLog_t *data);
void    fileSync();
void    fileClose();
DWORD	get_fattime(void);

#endif /* SDCARD_H_ */