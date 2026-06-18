#include "can_driver.h"

#include <stdio.h>          // Used for printing Linux error messages perror()
#include <string.h>         
#include <unistd.h>         // Needed for Linux system calls

#include <net/if.h>         // "What is the interface index of vcan0?"
#include <sys/ioctl.h>      // ioctl = ask kernel for device information
#include <sys/socket.h>     

#include <linux/can.h>
#include <linux/can/raw.h>

int Can_Init(CanDriver *driver, const char *interface_name)
{
    struct sockaddr_can addr;
    struct ifreq ifr;

    if (driver == NULL || interface_name == NULL) {
        return -1;
    }           // to avoid false initialization of the driver

    driver->socket_fd = socket(PF_CAN, SOCK_RAW, CAN_RAW);

    if (driver->socket_fd < 0) {
        perror("socket");
        return -1;
    }           //  return positive integer if socket allocation was successful


    /*
    Memory: strncpy

    ifr
    ┌─────────────┐
    │ "vcan0"     │
    └─────────────┘    
    */
    strncpy(ifr.ifr_name, interface_name, IFNAMSIZ - 1);
    ifr.ifr_name[IFNAMSIZ - 1] = '\0';

    /*
    Memory becomes: ioctl

    ifr
    ├─ ifr_name    = "vcan0"
    └─ ifr_ifindex = 5      
    
    */

    if (ioctl(driver->socket_fd, SIOCGIFINDEX, &ifr) < 0) {
        perror("ioctl");
        close(driver->socket_fd);
        return -1;
    }

    memset(&addr, 0, sizeof(addr));

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    /*
    Kernel now connects: bind()

    socket fd 3
        ↓
      vcan0    
    */
    if (bind(driver->socket_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(driver->socket_fd);
        return -1;
    }

    return 0;
}

int Can_Send(CanDriver *driver, const CanFrame *frame)
{
    struct can_frame linux_frame;

    if (driver == NULL || frame == NULL) {
        return -1;
    }

    if (frame->dlc > CAN_MAX_DATA_LEN) {
        return -1;
    }

    memset(&linux_frame, 0, sizeof(linux_frame));

    linux_frame.can_id = frame->id;
    linux_frame.can_dlc = frame->dlc;

    memcpy(linux_frame.data, frame->data, frame->dlc);

    if (write(driver->socket_fd, &linux_frame, sizeof(linux_frame)) != sizeof(linux_frame)) {
        perror("write");
        return -1;
    }

    return 0;
}

int Can_Receive(CanDriver *driver, CanFrame *frame)
{
    struct can_frame linux_frame;

    if (driver == NULL || frame == NULL) {
        return -1;
    }

    if (read(driver->socket_fd, &linux_frame, sizeof(linux_frame)) < 0) {
        perror("read");
        return -1;
    }

    frame->id = linux_frame.can_id;
    frame->dlc = linux_frame.can_dlc;

    memcpy(frame->data, linux_frame.data, frame->dlc);

    return 0;
}

void Can_Deinit(CanDriver *driver)
{
    if (driver != NULL && driver->socket_fd >= 0) {
        close(driver->socket_fd);
        driver->socket_fd = -1;
    }
}