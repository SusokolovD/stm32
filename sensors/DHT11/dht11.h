/**
  ******************************************************************************
  * @file    dht11.h
  * @version V1.0.0
  * @date    08-May-2017
  * @brief   This file contains all the functions prototypes for the dht11 
  *          module driver.
  * @author  Susokolov Dmitry
  ******************************************************************************
**/ 
	
#include "stm32f1xx_hal.h"

#define READ_OK 0
#define NO_CONN 1
#define CRC_ERR 2
#define MAX_CNT_ND 1000
#define GPIO_PIN_DHT GPIO_PIN_8
#define GPIO_PORT_DHT GPIOB
#define DELAY_SI_DHT11 18

struct dht11_t {
	uint8_t crc;			/*variable for crc(amount of transferred bytes) data*/
	uint32_t data;			/*variable for 4 byte data temperature and humidity*/
	uint32_t lowlvl_cnt;	/*variable for cicle count of low level*/
	uint32_t highlvl_cnt;	/*variable for cicle count of high level*/
	uint16_t err_cnt;		/*variable for cicle count of no data*/
};

uint16_t read_dht11(void);
