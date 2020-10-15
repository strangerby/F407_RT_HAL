/*
 * @Author: your name
 * @Date: 2020-10-15 15:55:09
 * @LastEditTime: 2020-10-15 15:58:44
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \F407_RT_HAL\RT-Thread\bsp\core_delay.h
 */
#ifndef __CORE_DELAY_H__
#define __CORE_DELAY_H__

#include "stm32f4xx.h"

#define  DWT_CR      *(volatile unsigned int *)0xE0001000
#define  DWT_CYCCNT  *(volatile unsigned int *)0xE0001004
#define  DEM_CR      *(volatile unsigned int *)0xE000EDFC
#define  DBGMCU_CR   *(volatile unsigned int *)0xE0042004
#define  DEM_CR_TRCENA                   (1 << 24)
#define  DWT_CR_CYCCNTENA                (1 <<  0)




#define GET_CPU_ClkFreq() HAL_RCC_GetSysClockFreq()
#define SysClockFreq (168000000)

#define CPU_TS_INIT_IN_DELAY_FUNCTION 1

uint32_t CPU_TS_TmrRd(void);
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority);
//使用以下函数前必须先调用 CPU_TS_TmrInit 函数使能计数器，或使能宏
void CPU_TS_Tmr_Delay_US(uint32_t us);
#define HAL_Delay(ms) CPU_TS_Tmr_Delay_US(ms*1000)
#define CPU_TS_Tmr_Delay_S(s) CPU_TS_Tmr_Delay_MS(s*1000




#endif