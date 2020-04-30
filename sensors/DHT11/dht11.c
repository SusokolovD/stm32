/**
  ******************************************************************************
  * @file    dht11.c
  * @version V1.0.0
  * @date    08-May-2017
  * @brief   dht11 module driver.
  * @author  Susokolov Dmitry
  ******************************************************************************
**/

#include "dht11.h"

struct dht11_t Dht11 = {0,0,0,0,0}; 
GPIO_InitTypeDef GPIO_InitStruct;
/**
  * @brief  reading DHT11 sensor.
	* @retval value 8 bit humidity(MSB) and value 8 bit temperature(LSB).
  */
uint16_t read_dht11 (void)
{
	Dht11.crc = 0, Dht11.data = 0;
	/*configure PORT, Pin5 for writing DHT11*/
	//HAL_GPIO_DeInit(GPIO_PORT_DHT, GPIO_PIN_DHT);
	GPIO_InitStruct.Pin = GPIO_PIN_DHT;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIO_PORT_DHT, &GPIO_InitStruct);
	/*start ipulse 18ms for DHT11*/
	HAL_GPIO_WritePin (GPIO_PORT_DHT, GPIO_PIN_DHT, GPIO_PIN_RESET);
	HAL_Delay(DELAY_SI_DHT11);
	HAL_GPIO_WritePin (GPIO_PORT_DHT, GPIO_PIN_DHT, GPIO_PIN_SET);
	/*reset PORT parameters*/
	HAL_GPIO_DeInit(GPIO_PORT_DHT, GPIO_PIN_DHT);
	/*configure PORT, Pin5 for reading DHT11*/
	GPIO_InitStruct.Pin = GPIO_PIN_DHT;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIO_PORT_DHT, &GPIO_InitStruct);
	/*wait for ending host signal*/
	if (wait_for_reading(GPIO_PIN_RESET) == NO_CONN) return NO_CONN;
	/*wait for slave signal DHT11*/	
	if (wait_for_reading(GPIO_PIN_SET) == NO_CONN) return NO_CONN;
	if (wait_for_reading(GPIO_PIN_RESET) == NO_CONN) return NO_CONN;
	/*read 4 byte data temperature and humidity*/
	for(uint8_t i = 0; i < 32; i++)
	{
		Dht11.lowlvl_cnt = 0, Dht11.highlvl_cnt = 0; Dht11.err_cnt = 0;	
		if (wait_for_reading(GPIO_PIN_SET) == NO_CONN) return NO_CONN;
		if (wait_for_reading(GPIO_PIN_RESET) == NO_CONN) return NO_CONN;
		if (Dht11.lowlvl_cnt > Dht11.highlvl_cnt)
		{
			Dht11.data |= 0 << (31-i);
		}
		else
		{
			Dht11.data |= 1 << (31-i);
		}
	}
	/*read crc(amount of transferred bytes)*/
	for(uint8_t i = 0; i < 8; i++)
	{
		Dht11.lowlvl_cnt = 0, Dht11.highlvl_cnt = 0; Dht11.err_cnt = 0;	
		if (wait_for_reading(GPIO_PIN_SET) == NO_CONN) return NO_CONN;
		if (wait_for_reading(GPIO_PIN_RESET) == NO_CONN) return NO_CONN;
		if (Dht11.lowlvl_cnt > Dht11.highlvl_cnt)
		{
			Dht11.crc |= 0 << (7-i);
		}
		else
		{
			Dht11.crc |= 1 << (7-i);
		}
	}
	/*checking validation of data*/
	if (((uint8_t)(Dht11.data>>8)+((uint8_t)((Dht11.data >> 24)))) == Dht11.crc)
	{
		return ((uint8_t)((Dht11.data >> 24))) + ((uint8_t)(Dht11.data >> 8) << 8);
	}	
	else return CRC_ERR;
	
}

/**
  * @brief  reading one impulse DHT11 sensor.
  * @param  state: where GPIO_PIN_RESET determines the reading of high-level loops
  *                      GPIO_PIN_SET 	determines the reading of low-level loops.
	* @retval NO_CONN: signal level did not change for the number of cycles MAX_CNT_ND
  *					READ_OK: reading passed normally.
  */
static
uint8_t wait_for_reading (uint8_t state)
{
	while (HAL_GPIO_ReadPin(GPIO_PORT_DHT, GPIO_PIN_DHT) != state)
	{
		if (state ==  GPIO_PIN_RESET)
		{
			Dht11.highlvl_cnt++;
		}
		else
		{
			Dht11.lowlvl_cnt++;
		}				
		Dht11.err_cnt++;
		if (Dht11.err_cnt > MAX_CNT_ND)
		{
			Dht11.err_cnt = 0;
			return NO_CONN;
		}
	}
	Dht11.err_cnt = 0;
	return READ_OK;
}
