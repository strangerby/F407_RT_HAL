/*
 * @Author: your name
 * @Date: 2020-10-15 15:55:17
 * @LastEditTime: 2020-10-15 15:59:00
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \F407_RT_HAL\RT-Thread\bsp\core_delay.c
 */
#include "core_delay.h"

HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{

    DEM_CR |= (uint32_t)DEM_CR_TRCENA;

/* DWT CYCCNT 寄存器计数清 0 */
    DWT_CYCCNT = (uint32_t)0u;

/* 使能 Cortex-M DWT CYCCNT 寄存器 */
    DWT_CR |= (uint32_t)DWT_CR_CYCCNTENA;

    return HAL_OK;
}

/**
* @brief 读取当前时间戳
* @param 无
* @retval 当前时间戳，即 DWT_CYCCNT 寄存器的值
*/
uint32_t CPU_TS_TmrRd(void)
{
return ((uint32_t)DWT_CYCCNT);
}

/**
* @brief 读取当前时间戳
* @param 无
* @retval 当前时间戳，即 DWT_CYCCNT 寄存器的值
*/
uint32_t HAL_GetTick(void)
{
return ((uint32_t)DWT_CYCCNT*1000/SysClockFreq);
}

/**
* @brief 采用 CPU 的内部计数实现精确延时， 32 位计数器
* @param us : 延迟长度，单位 1 us
* @retval 无
* @note 使用本函数前必须先调用 CPU_TS_TmrInit 函数使能计数器，
或使能宏 CPU_TS_INIT_IN_DELAY_FUNCTION
最大延时值为 8 秒，即 8*1000*1000
*/
void CPU_TS_Tmr_Delay_US(uint32_t us)
{
    uint32_t ticks;
    uint32_t told,tnow,tcnt=0;

 /* 在函数内部初始化时间戳寄存器， */
    #if (CPU_TS_INIT_IN_DELAY_FUNCTION)
 /* 初始化时间戳并清零 */
    HAL_InitTick(5);
    #endif

    ticks = us * (GET_CPU_ClkFreq() / 1000000); /* 需要的节拍数 */
    tcnt = 0;
    told = (uint32_t)CPU_TS_TmrRd(); /* 刚进入时的计数器值 */

    while (1) {
        tnow = (uint32_t)CPU_TS_TmrRd();
        if (tnow != told) {
 /* 32 位计数器是递增计数器 */
            if (tnow > told) {
                tcnt += tnow - told;
            }
 /* 重新装载 */
            else {
                tcnt += UINT32_MAX - told + tnow;
            }

                told = tnow;

 /*时间超过/等于要延迟的时间,则退出 */
                if (tcnt >= ticks)break;
        }
    }
}

