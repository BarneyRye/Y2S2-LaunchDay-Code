#ifndef BME280_H_
#define BME280_H_

#include "datastructs.h"

void BME280_config(calibData_t *calibData);
void BME280_getData(dataLog_t *data);

#endif /* BME280_H_ */