#include "lps25hb.h"
#include <math.h>


uint8_t lps25hb_read_byte(uint8_t reg_addr)
{
	uint8_t data = 0;
	return *(i2c_master_read(&data, 1, reg_addr, LPS25HB_I2C_DEV_ADDRESS_READ, 0));
}


void lps25hb_write_byte(uint8_t reg_addr, uint8_t value)
{
	i2c_master_write(value, reg_addr, LPS25HB_I2C_DEV_ADDRESS_READ, 0);
}


void lps25hb_readArray(uint8_t * data, uint8_t reg, uint8_t length)
{
	i2c_master_read(data, length, reg, LPS25HB_I2C_DEV_ADDRESS_READ, 1);
}


uint8_t lps25hb_init(void)
{
	uint8_t status = 1;

	LL_mDelay(100);

	uint8_t who_am_i = lps25hb_read_byte(LPS25HB_WHO_AM_I_ADDRESS);

	if(who_am_i == LPS25HB_WHO_AM_I_VALUE)
	{
		status = 1;
	}
	else
	{
		return 0;
	}

	// Device configuration
	uint8_t ctrl1 = LPS25HB_POWER_ON | LPS25HB_ODR_FAST;
	uint8_t res = ~(0x3 << 0);

	lps25hb_write_byte(LPS25HB_CTRL_REG1, ctrl1);
//	lps25hb_write_byte(LPS25HB_RES_CONF, res);

	return status;
}


double lps25hb_get_pressure()
{
	uint8_t pres_arr[3];
	int32_t PRES = 0;
	double pres_out;

	lps25hb_readArray(pres_arr, LPS25HB_PRESS_OUT_XL, 3);

	PRES = ((uint32_t)pres_arr[2] << 16 | pres_arr[1] << 8 | pres_arr[0]);

	pres_out = PRES / 4069.0;

	return pres_out;

}

// Aj ked tato funkcia nie je zavisla od konkretneho senzora, rozhodol som sa dat ju sem...
double lps25hb_get_altitude(double P, double T)
{
	return (pow(1013.25/P,1/5.257) - 1) * (T + 273.15) / 0.0065;

}

double lps25hb_get_delta_z(double initial_altitude, double P, double T)
{
	return initial_altitude - lps25hb_get_altitude(P, T);
}
