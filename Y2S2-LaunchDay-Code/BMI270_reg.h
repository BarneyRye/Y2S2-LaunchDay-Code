#ifndef BMI270_REG_H_
#define BMI270_REG_H_

#define BMI270_address (0x68<<1)

#define BMI270_CHIPID 0x00
#define BMI270_CHIPID_VAL 0x24

#define BMI270_SOFTRESET 0x7E
#define BMI270_SOFTRESET_VAL 0xB6

#define BMI270_POWER_CONF 0x7C
#define BMI270_POWER_CONF_VAL 0x00
#define BMI270_INIT_CTRL 0x59
#define BMI270_INIT_CTRL_START 0x00
#define BMI270_INIT_CTRL_END 0x01
#define BMI270_INIT_STATUS 0x21
#define BMI270_INIT_STATUS_VAL 0x01
#define BMI270_POWER_CTRL 0x7D
#define BMI270_POWER_CTRL_VAL 0x0E

#define ACC_CONF_address 0x40
#define ACC_RANGE_address 0x41
#define GYR_CONF_address 0x42
#define GYR_RANGE_address 0x43

#define ACC_ODR_50Hz 0xA7
#define ACC_RANGE_16g 0x03
#define GYR_ODR_50Hz 0xA7
#define GYR_RANGE_2000dps 0x00

#define ACC_X_LSB 0x0C
#define ACC_X_MSB 0x0D
#define ACC_Y_LSB 0x0E
#define ACC_Y_MSB 0x0F
#define ACC_Z_LSB 0x10
#define ACC_Z_MSB 0x11
#define GYR_X_LSB 0x12
#define GYR_X_MSB 0x13
#define GYR_Y_LSB 0x14
#define GYR_Y_MSB 0x15
#define GYR_Z_LSB 0x16
#define GYR_Z_MSB 0x17


#endif /* BMI270_REG_H_ */