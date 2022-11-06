#include "main.h"
#include "i2c.h"

#define HTS221_I2C_DEV_ADDRESS_READ				0xBF
#define HTS221_I2C_DEV_ADDRESS_WRITE			0XBE

#define HTS221_WHO_AM_I_ADDRESS					0X0F
#define HTS221_WHO_AM_I_VALUE 					0XBC

#define HTS221_AV_CONF_ADDRESS 					0X10
#define HTS221_AV_CONF_VALUE 					0X1B

#define HTS221_CTRL_REG1_ADDRESS 				0X20
#define HTS221_CTRL_REG2_ADDRESS 				0X21
#define HTS221_CTRL_REG3_ADDRESS 				0X22

#define HTS221_STATUS_REG_ADDRESS 				0X27

#define HTS221_HUMIDITY_OUT_L_ADDRESS			0X28
#define HTS221_HUMIDITY_OUT_H_ADDRESS 			0X29

#define HTS221_TEMP_OUT_L_ADDRESS 				0X2A
#define HTS221_TEMP_OUT_H_ADDRESS 				0X2B


uint8_t hts221_init(void);
uint8_t hts221_read_byte(uint8_t reg_addr);

int8_t hts221_get_temp();

void hts221_write_byte(uint8_t reg_addr, uint8_t value);
void hts221_readArray(uint8_t * data, uint8_t reg, uint8_t length);
