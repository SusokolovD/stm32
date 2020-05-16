/**
  ******************************************************************************
  * @file    mg90s.h
  * @version V1.0.0
  * @date    16-May-2020
  * @brief   This file contains all the functions prototypes for the mg90s 
  *          servo motor driver.
  * @author  Susokolov Dmitry
  ******************************************************************************
**/ 

#include "stm32f4xx_hal.h"

#define PWMPERIOD   20  //in ms
#define PWMMINUS90  0.5 //in ms
#define PWMZERO     1.5 //in ms
#define PWMPLUS90   2.5 //in ms
#define MINROTATE   -90 //in degree
#define MAXROTATE   90 //in degree
#define ALLROTATE   180 //in degree

void config_mg90s(TIM_HandleTypeDef* htimx);
void mg90s_set_angle(int angle);
void mg90s_test(void);
