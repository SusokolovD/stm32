/**
  ******************************************************************************
  * @file    bh1750.c
  * @version V1.0.0
  * @date    08-May-2017
  * @brief   BH1750 module driver.
  * @author  Susokolov Dmitry
  ******************************************************************************
**/

#include "bh1750.h"

extern I2C_HandleTypeDef hi2c1;

/**
  * @brief  reading BH1750 sensor.
  * @param  delay: Pause before reading in ms.
	* @retval value 8 bit humidity(MSB) and value 8 bit temperature(LSB).
  */
uint16_t read_bh1750 (void)
{
	uint16_t lux = 0;
	HAL_I2C_Master_Transmit(&hi2c1, ADDR, (uint8_t *)MODE_H2, 1, 200);
	HAL_I2C_Master_Receive(&hi2c1, ADDR, (uint8_t *)&lux, 2, 200);
	return lux;
}

