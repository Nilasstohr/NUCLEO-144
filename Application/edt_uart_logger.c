//
// Created by nilas on 14/10/2026.
//

#include "edt_uart_logger.h"
#include <string.h>

static UART_HandleTypeDef *uart_logger;
static volatile uint8_t transmit_complete = 1;
static const uint16_t TX_BUFFER_SIZE = 100;
static uint8_t tx_buffer[100] __attribute__((section(".dma_buffer"), aligned(32)));

static uint8_t EDT_UART_LOGGER_IsTransmitComplete(void);

void EDT_USART_LOGGER_Init(UART_HandleTypeDef *huart)
{
  uart_logger = huart;
}

void EDT_USART_LOGGER_Transmit(const char *data, const uint16_t size)
{
  if (uart_logger != NULL)
  {
      HAL_UART_Transmit(uart_logger, (const uint8_t *)data, size, HAL_MAX_DELAY);
  }
}

void EDT_USART_LOGGER_Transmit_IT(const char *data, const uint16_t size)
{
  if (uart_logger != NULL)
  {
    if(EDT_UART_LOGGER_IsTransmitComplete())
    {
      HAL_UART_Transmit_IT(uart_logger, (const uint8_t *)data, size);
    }
  }
}

void EDT_USART_LOGGER_Transmit_DMA(const char *data, const uint16_t size)
{
  if (uart_logger != NULL)
  {
    if(EDT_UART_LOGGER_IsTransmitComplete())
    {
      size_t n = size;
      if (n > TX_BUFFER_SIZE) n = TX_BUFFER_SIZE;
      memcpy(tx_buffer, data, n);
      HAL_UART_Transmit_DMA(uart_logger,tx_buffer, n);
    }
  }
}

void HAL_UART_TxCpltCallback(const UART_HandleTypeDef *huart)
{
  if (huart->Instance == uart_logger->Instance)
  {
    transmit_complete = 1;
  }
}

static uint8_t EDT_UART_LOGGER_IsTransmitComplete(void) {
  if(transmit_complete) {
    transmit_complete = 0;
    return 1;
  }
  return 0;
}