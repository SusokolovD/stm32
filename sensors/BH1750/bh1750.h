#ifndef BH1750_h
#define BH1750_h

/**
  ******************************************************************************
  * @file    dht11.h
  * @version V1.0.0
  * @date    08-May-2017
  * @brief   This file contains all the functions prototypes for the BH1750 
  *          module driver.
  * @author  Susokolov Dmitry
  ******************************************************************************
**/ 
	
#include "stm32f1xx_hal.h"

#define ADDR 0x23<<1
#define MODE_H2 0x11

uint16_t read_bh1750(void);

#endif
