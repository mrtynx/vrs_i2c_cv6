#include "hts221.h"

uint8_t dev_addr = 0xBF;

uint8_t hts221_read_byte(uint8_t reg_addr)
{
	uint8_t data = 0;
	return *(i2c_master_read(&data, 1, reg_addr, dev_addr, 0));
}


void hts221_write_byte(uint8_t reg_addr, uint8_t value)
{
	i2c_master_write(value, reg_addr, dev_addr, 0);
}


void hts221_readArray(uint8_t * data, uint8_t reg, uint8_t length)
{
	i2c_master_read(data, length, reg, dev_addr, 1);
}


uint8_t hts221_init(void)
{
	uint8_t status = 1;

	LL_mDelay(100);

	uint8_t who_am_i = hts221_read_byte(HTS221_WHO_AM_I_ADDRESS);

	if(who_am_i == HTS221_WHO_AM_I_VALUE)
	{
		status = 1;
	}
	else
	{
		return 0;
	}

	// Device configuration

	uint8_t ctrl1 = HTS221_CTRL1_POWER_UP | HTS221_CTRL1_FAST_ODR;
	uint8_t avg   = HTS221_AVGT_DEFAULT	| HTS221_AVGH_HI_RES;

	hts221_write_byte(HTS221_CTRL_REG1_ADDRESS, ctrl1);
	hts221_write_byte(HTS221_AV_CONF_ADDRESS , avg);

	return status;
}


double hts221_get_temp()
{
	uint8_t T0_degC_x8, T1_degC_x8, T1_T0_MSB;
	uint8_t t_out_data[2], t0_t1_data[4];
	int16_t T_OUT, T0_OUT, T1_OUT;

	T0_degC_x8 = hts221_read_byte(HTS221_T0_DEG_X8);
	T1_degC_x8 = hts221_read_byte(HTS221_T1_DEG_X8);
	T1_T0_MSB  = hts221_read_byte(HTS221_T0_T1_MSB);

	hts221_readArray(t_out_data, HTS221_T_OUT, 2);
	hts221_readArray(t0_t1_data, HTS221_T0_OUT, 4);

	T_OUT = ((uint16_t)t_out_data[1] << 8 | t_out_data[0]);
	T0_OUT = ((uint16_t)t0_t1_data[1]) << 8 | t0_t1_data[0];
	T1_OUT = ((uint16_t)t0_t1_data[3]) << 8 | t0_t1_data[2];

	double T_DegC;
	double T0_degC = (T0_degC_x8 + (1 << 8) * (T1_T0_MSB & 0x03)) / 8.0;
	double T1_degC = (T1_degC_x8 + (1 << 6) * (T1_T0_MSB & 0x0C)) / 8.0;

	T_DegC = (T0_degC + (T_OUT - T0_OUT) * (T1_degC - T0_degC) / (T1_OUT - T0_OUT));

	return T_DegC;

}

double hts221_get_humidity()
{

	uint8_t H0_rH_x2, H1_rH_x2;
	uint8_t h_out_arr[2], h0_t0_out_arr[2], h1_t0_out_arr[2];
	int16_t H_OUT, H0_T0_OUT, H1_T0_OUT;

	H0_rH_x2 = hts221_read_byte(HTS221_H0_RH_X2);
	H1_rH_x2 = hts221_read_byte(HTS221_H1_RH_X2);

	hts221_readArray(h_out_arr, HTS221_H_OUT, 2);
	hts221_readArray(h0_t0_out_arr, HTS221_H0_T0_OUT, 2);
	hts221_readArray(h1_t0_out_arr, HTS221_H1_T0_OUT, 2);

	H_OUT = ((uint16_t)h_out_arr[1] << 8 | h_out_arr[0]);
	H0_T0_OUT = ((uint16_t)h0_t0_out_arr[1] << 8 | h0_t0_out_arr[0]);
	H1_T0_OUT = ((uint16_t)h1_t0_out_arr[1] << 8 | h1_t0_out_arr[0]);

	double h_out, h0, h1;

	h0 = H0_rH_x2 / 2.0;
	h1 = H1_rH_x2 / 2.0;

	h_out = (h0 + (H_OUT - H0_T0_OUT) * (h1 - h0) / (H1_T0_OUT - H0_T0_OUT));

	return h_out;

}

