Problem statement:
Build a portable CAN communication driver abstraction in C that allows an application to send and receive CAN frames without depending directly on one specific hardware controller.



Design Flow chart:

Application
    ↓
Your CAN abstraction
    ↓
SocketCAN backend
    ↓
vcan0 virtual CAN bus


Architecture:

can_driver_project
│
├── include
│   └── can_driver.h        public API
│
├── src
│   └── can_socketcan.c     Linux SocketCAN backend
│
├── examples
│   └── main.c              demo application
│
└── Makefile



code deisgn:

Application
    |
    | calls Can_Send(), Can_Receive()
    v
CAN Driver API
    |
    | hides Linux-specific details
    v
SocketCAN Implementation
    |
    | uses Linux socket(), bind(), read(), write()
    v
vcan0 Virtual CAN Bus
