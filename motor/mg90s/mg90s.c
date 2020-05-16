/**
  ******************************************************************************
  * @file    mg90s.c
  * @version V1.0.0
  * @date    16-May-2020
  * @brief   mg90s servo driver.
  * @author  Susokolov Dmitry
  ******************************************************************************
**/

#include "mg90s.h"

TIM_HandleTypeDef htim;
float min, mid, max, step;

/**
  * @brief  set PWM timer structure.
  * @param  htimx: pointer on timer structure.
  */
void config_mg90s(TIM_HandleTypeDef* htimx)
{
  uint32_t period;
  htim = *htimx;
  period = htim.Init.Period;
  min = PWMMINUS90/PWMPERIOD*period;
  mid = PWMZERO/PWMPERIOD*period;
  max = PWMPLUS90/PWMPERIOD*period;
  step = (max - min)/ALLROTATE; 
}

/**
  * @brief  set servo on the position.
  * @param  angle: position from -90 to 90 degree.
  */
void mg90s_set_angle(int angle)
{
  if(angle >= MINROTATE && angle <= MAXROTATE)
  {
    __HAL_TIM_SetCompare(&htim, TIM_CHANNEL_4, (uint16_t)(mid + (angle * step)));
  }
}

/**
  * @brief  test servo from -90 to 90 degree.
  */
void mg90s_test(void)
{
  for (int i = -90; i < 90; i++)
  {
    HAL_Delay(5);
    mg90s_set_angle(i);
  }
  HAL_Delay(1000);
  for (int i = 90; i > -90; i--)
  {
    HAL_Delay(5);
    mg90s_set_angle(i);
  }
  HAL_Delay(1000);
}
