#include "can_driver.h"

#include <stdio.h>

static void Print_Frame(const CanFrame *frame)
{
    printf("Received CAN Frame\n");
    printf("ID  : 0x%X\n", frame->id);
    printf("DLC : %d\n", frame->dlc);
    printf("Data: ");

    for (int i = 0; i < frame->dlc; i++) {
        printf("%02X ", frame->data[i]);
    }

    printf("\n");
}

int main(void)
{
    CanDriver driver;
    CanFrame tx_frame;
    CanFrame rx_frame;

    if (Can_Init(&driver, "vcan0") != 0) {
        printf("CAN initialization failed\n");
        return 1;
    }

    tx_frame.id = 0x123;
    tx_frame.dlc = 4;
    tx_frame.data[0] = 0x10;
    tx_frame.data[1] = 0x22;
    tx_frame.data[2] = 0x33;
    tx_frame.data[3] = 0x44;

    if (Can_Send(&driver, &tx_frame) != 0) {
        printf("CAN send failed\n");
        Can_Deinit(&driver);
        return 1;
    }

    printf("CAN frame sent successfully\n");
    printf("Waiting for received CAN frame...\n");

    if (Can_Receive(&driver, &rx_frame) != 0) {
        printf("CAN receive failed\n");
        Can_Deinit(&driver);
        return 1;
    }

    Print_Frame(&rx_frame);

    Can_Deinit(&driver);

    return 0;
}