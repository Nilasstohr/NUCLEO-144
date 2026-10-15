//
// Created by nilas on 14/10/2026.
//

#ifndef NUCLEO_144_HOST_EDT_UART_LOGGER_H
#define NUCLEO_144_HOST_EDT_UART_LOGGER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

void EDT_USART_LOGGER_Init(UART_HandleTypeDef *huart);
void EDT_USART_LOGGER_Transmit(const char *data, uint16_t size);
void EDT_USART_LOGGER_Transmit_DMA_Blocking(const char *data, uint16_t size);
#ifdef __cplusplus
}
#endif

#endif //NUCLEO_144_HOST_EDT_UART_LOGGER_H
