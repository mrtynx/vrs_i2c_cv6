#include "main.h"
#include "i2c.h"

#define LPS25HB_I2C_DEV_ADDRESS_READ			0xBB
#define LPS25HB_I2C_DEV_ADDRESS_WRITE			0XBA

#define LPS25HB_REF_P_XL						0X08
#define LPS25HB_REF_P_L							0X09
#define LPS25HB_REF_P_H							0X0A

#define LPS25HB_WHO_AM_I_ADDRESS				0X0F
#define LPS25HB_WHO_AM_I_VALUE					0XBD

#define LPS25HB_RES_CONF						0X10

#define LPS25HB_CTRL_REG1						0X20
#define LPS25HB_CTRL_REG2						0X21
#define LPS25HB_CTRL_REG3						0X22
#define LPS25HB_CTRL_REG4						0X23

#define LPS25HB_INTERRUPT_CFG					0X24
#define LPS25HB_INT_SOURCE						0X25

#define LPS25HB_STATUS_REG						0X27

#define LPS25HB_PRESS_OUT_XL					0X28
#define LPS25HB_PRESS_OUT_L						0X29
#define LPS25HB_PRESS_OUT_H						0X2A

#define LPS25HB_TEMP_OUT_L						0X2B
#define LPS25HB_TEMP_OUT_H						0X2C

#define LPS25HB_FIFO_CTRL						0X2E
#define LPS25HB_FIFO_STATUS						0X2F

#define LPS25HB_THS_P_L							0X30
#define LPS25HB_THS_P_H							0X31

#define LPS25HB_RPDS_L							0X39
#define LPS25HB_RPDS_H							0X3A

// Control configuration

#define LPS25HB_POWER_ON						(1 << 7)
#define LPS25HB_ODR_FAST						(0x4 << 4)

uint8_t lps25hb_init(void);
uint8_t lps25hb_read_byte(uint8_t reg_addr);

double lps25hb_get_pressure();
double lps25hb_get_altitude(double P, double T);
double lps25hb_get_delta_z(double initial_altitude, double P, double T);

void lps25hb_write_byte(uint8_t reg_addr, uint8_t value);
void lps25hb_readArray(uint8_t * data, uint8_t reg, uint8_t length);
