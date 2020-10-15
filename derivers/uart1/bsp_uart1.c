/*
 * @Author: your name
 * @Date: 2020-10-15 16:02:27
 * @LastEditTime: 2020-10-15 17:38:40
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \F407_RT_HAL\derivers\uart1\bsp_uart1.c
 */

#include "bsp_uart1.h"
#include "rtthread.h"

USART_HandleTypeDef uart1_handler = {0};

void bsp_uart1_init(uint32_t BaudRate)
{
    uart1_handler.Instance = USART1;
    uart1_handler.Init.BaudRate = BaudRate;
    uart1_handler.Init.Mode = USART_MODE_TX_RX;
    uart1_handler.Init.Parity = USART_PARITY_NONE;
    uart1_handler.Init.WordLength = USART_WORDLENGTH_8B;
    uart1_handler.Init.StopBits = USART_STOPBITS_1;

    HAL_USART_Init(&uart1_handler);
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    if(huart->Instance == USART1) {
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_USART1_CLK_ENABLE();
        //__HAL_RCC_SYSCFG_CLK_ENABLE();


        GPIO_InitStruct.Pin = GPIO_PIN_9;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_10;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }



}


void rt_hw_console_output(const char *str)
{
    rt_size_t i = 0, size = 0;
    char a = '\r';

    size = rt_strlen(str);
    for (i = 0; i < size; i++)
    {
        if (*(str + i) == '\n')
        {
            HAL_UART_Transmit(&uart1_handler, (uint8_t *)&a, 1, 1);
        }
        HAL_UART_Transmit(&uart1_handler, (uint8_t *)(str + i), 1, 1);
    }
}
