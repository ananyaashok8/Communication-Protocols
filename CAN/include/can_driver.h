#ifndef CAN_DRIVER_H
#define CAN_DRIVER_H

#include <stdint.h>

#define CAN_MAX_DATA_LEN 8

typedef struct {
    uint32_t id;
    uint8_t dlc;
    uint8_t data[CAN_MAX_DATA_LEN];
} CanFrame;

typedef struct {
    int socket_fd;
} CanDriver;

int Can_Init(CanDriver *driver, const char *interface_name);
int Can_Send(CanDriver *driver, const CanFrame *frame);
int Can_Receive(CanDriver *driver, CanFrame *frame);
void Can_Deinit(CanDriver *driver);

#endif