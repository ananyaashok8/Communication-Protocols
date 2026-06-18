#include "can_driver.h"

#include <stdio.h>
#include <string.h>

#define MOCK_CAN_QUEUE_SIZE 16

static CanFrame mock_queue[MOCK_CAN_QUEUE_SIZE];
static int write_index = 0;
static int read_index = 0;
static int frame_count = 0;

int Can_Init(CanDriver *driver, const char *interface_name)
{
    if (driver == NULL || interface_name == NULL) {
        return -1;
    }

    driver->socket_fd = 1;

    write_index = 0;
    read_index = 0;
    frame_count = 0;

    printf("Mock CAN initialized on interface: %s\n", interface_name);

    return 0;
}

int Can_Send(CanDriver *driver, const CanFrame *frame)
{
    if (driver == NULL || frame == NULL) {
        return -1;
    }

    if (frame->dlc > CAN_MAX_DATA_LEN) {
        return -1;
    }

    if (frame_count >= MOCK_CAN_QUEUE_SIZE) {
        printf("Mock CAN queue full\n");
        return -1;
    }

    mock_queue[write_index] = *frame;
    write_index = (write_index + 1) % MOCK_CAN_QUEUE_SIZE;
    frame_count++;

    return 0;
}

int Can_Receive(CanDriver *driver, CanFrame *frame)
{
    if (driver == NULL || frame == NULL) {
        return -1;
    }

    if (frame_count == 0) {
        printf("No CAN frame available\n");
        return -1;
    }

    *frame = mock_queue[read_index];
    read_index = (read_index + 1) % MOCK_CAN_QUEUE_SIZE;
    frame_count--;

    return 0;
}

void Can_Deinit(CanDriver *driver)
{
    if (driver != NULL) {
        driver->socket_fd = -1;
    }

    printf("Mock CAN deinitialized\n");
}
