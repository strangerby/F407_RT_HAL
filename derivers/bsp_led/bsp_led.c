/*
 * @Author: your name
 * @Date: 2020-10-15 16:52:44
 * @LastEditTime: 2020-10-15 21:23:47
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \F407_RT_HAL\derivers\bsp_led\bsp_led.c
 */

#include "bsp_led.h"

void bsp_led_init(void)
{
    GPIO_InitTypeDef GPIO_InitSturuct = {0};

    GPIO_InitSturuct.Pin = LED2_PIN;
    GPIO_InitSturuct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitSturuct.Pull = GPIO_PULLUP;
    GPIO_InitSturuct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED2_PORT, &GPIO_InitSturuct);

    GPIO_InitSturuct.Pin = LED3_PIN;
    GPIO_InitSturuct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitSturuct.Pull = GPIO_PULLUP;
    GPIO_InitSturuct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED3_PORT, &GPIO_InitSturuct);
}


void bsp_led_toggle(uint8_t LED_num)
{
    switch(LED_num)
    {
        case LED2 :
            HAL_GPIO_TogglePin(LED2_PORT, LED2_PIN); break;
        case LED3 :
            HAL_GPIO_TogglePin(LED3_PORT, LED3_PIN); break;
    }

}

