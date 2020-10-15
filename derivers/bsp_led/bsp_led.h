/*
 * @Author: your name
 * @Date: 2020-10-15 16:52:48
 * @LastEditTime: 2020-10-15 17:09:29
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \F407_RT_HAL\derivers\bsp_led\bsp_led.h
 */
#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#include "main.h"

#define     LED2_PORT       GPIOA
#define     LED2_PIN        GPIO_PIN_6
#define     LED3_PORT       GPIOA
#define     LED3_PIN        GPIO_PIN_7

enum LED { 
    LED2 = 2,
    LED3 = 3

};

void bsp_led_toggle(uint8_t LED_num);
void bsp_led_init(void);


#endif // !__BSP_LED_H__