//
// Created by nilas on 14/10/2026.
//

#include "edt_uart_logger.h"
#include <string.h>
#include "cmsis_os2.h"

static UART_HandleTypeDef *uart_logger;
static const uint16_t TX_BUFFER_SIZE = 100;
static uint8_t tx_buffer[100] __attribute__((section(".dma_buffer"), aligned(32)));

static osSemaphoreId_t tx_done_sem;

void EDT_USART_LOGGER_Init(UART_HandleTypeDef *huart)
{
  uart_logger = huart;
  tx_done_sem = osSemaphoreNew(1, 1, NULL);
}


void EDT_USART_LOGGER_Transmit_DMA_Blocking(const char *data, const uint16_t size)
{
  if (uart_logger == NULL || tx_done_sem == NULL) return;

  if (osSemaphoreAcquire(tx_done_sem, osWaitForever) != osOK) return;

  size_t n = size;
  if (n > TX_BUFFER_SIZE) n = TX_BUFFER_SIZE;
  memcpy(tx_buffer, data, n);
  if (HAL_UART_Transmit_DMA(uart_logger, tx_buffer, n) != HAL_OK)
  {
    osSemaphoreRelease(tx_done_sem);
  }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart == uart_logger && tx_done_sem != NULL)
  {
    osSemaphoreRelease(tx_done_sem);
  }
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
  if (huart == uart_logger && tx_done_sem != NULL)
  {
    osSemaphoreRelease(tx_done_sem);
  }
}
