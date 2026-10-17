//
// Created by nilas on 16/10/2026.
//

#ifndef NUCLEO_144_HOST_EDT_CAN_H
#define NUCLEO_144_HOST_EDT_CAN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "fdcan.h"

typedef struct {
    char data[8];
    uint32_t Identifier;
    uint32_t DataLength;
}edt_can_rx_message_t;

typedef void (*can_rx_callback_t)(const FDCAN_RxHeaderTypeDef *header, const uint8_t *data);

void EDT_FDCAN_Init(FDCAN_HandleTypeDef * hfdcan, can_rx_callback_t rx_callback);
void EDT_FDCAN_Transmit_Loopback_testing();
#ifdef __cplusplus
}
#endif


#endif //NUCLEO_144_HOST_EDT_CAN_H
