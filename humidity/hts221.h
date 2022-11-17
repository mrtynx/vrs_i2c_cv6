#include "main.h"
#include "i2c.h"

// Device registers

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

// Control registers configurations

#define HTS221_CTRL1_POWER_UP					(1 << 7)
#define HTS221_CTRL1_FAST_ODR					(0X3 << 0)

#define HTS221_AVGH_HI_RES						(0x7 << 0)
#define HTS221_AVGT_DEFAULT						(0x3 << 3)

// Calibration registers

#define HTS221_T0_DEG_X8						0X32
#define HTS221_T1_DEG_X8						0X33
#define HTS221_T0_T1_MSB						0X35

#define HTS221_H0_RH_X2							0X30
#define HTS221_H1_RH_X2							0X31

#define HTS221_H0_T0_OUT						0x36
#define HTS221_H1_T0_OUT						0x3A

#define HTS221_T0_OUT							0X3C
#define HTS221_T1_OUT							0X3E

// Output registers

#define HTS221_T_OUT							0X2A
#define HTS221_H_OUT							0x28

// User defined function prototypes

uint8_t hts221_init(void);
uint8_t hts221_read_byte(uint8_t reg_addr);

double hts221_get_temp();
double hts221_get_humidity();

void hts221_write_byte(uint8_t reg_addr, uint8_t value);
void hts221_readArray(uint8_t * data, uint8_t reg, uint8_t length);
