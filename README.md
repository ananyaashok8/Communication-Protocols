# Communication Protocols in C

## Overview

This repository contains implementations of common embedded and automotive communication protocols written in C.

The goal of this repository is to learn communication protocols from first principles by designing driver abstractions, implementing protocol behavior, creating hardware-independent test environments, and documenting design decisions.

The projects are developed with a focus on:

* Embedded Systems
* Automotive Software Development
* Driver Development
* Protocol Understanding
* Hardware Abstraction
* Testability
* Code Documentation

---

## Protocols

| Protocol | Status      | Description                                                   |
| -------- | ----------- | ------------------------------------------------------------- |
| CAN      | Implemented | CAN driver abstraction with mock backend and SocketCAN design |
| SPI      | Planned     | SPI master/slave driver abstraction and peripheral simulation |
| I2C      | Planned     | I2C master driver with EEPROM and sensor simulation           |
| UART     | Planned     | UART driver with ring buffer implementation                   |
| LIN      | Planned     | Automotive LIN protocol implementation                        |
| Ethernet | Planned     | Embedded Ethernet communication concepts                      |

---

## Repository Structure

```text
Communication-Protocols/
├── CAN/
├── SPI/
├── I2C/
├── UART/
└── docs/
```

Each protocol directory contains:

```text
include/   Public APIs
src/       Driver implementation
examples/  Example applications
docs/      Design notes and test results
```

---

## Design Philosophy

The primary design goal is to separate:

```text
Application Layer
        ↓
Driver API
        ↓
Platform-Specific Backend
        ↓
Hardware / Simulation
```

This approach improves:

* Portability
* Maintainability
* Testability
* Reusability

and mirrors the architecture commonly used in embedded and automotive software systems.

---

## Current Project: CAN Driver Abstraction

The CAN project implements:

* CAN frame abstraction
* Hardware-independent API
* Mock backend for testing without hardware
* SocketCAN backend design
* Example transmit and receive application
* Design documentation

See:

```text
CAN/README.md
```

for details.

---

## Learning Objectives

Through these projects I aim to develop a practical understanding of:

* Communication protocols
* Embedded C programming
* Driver development
* Automotive software architecture
* Software abstraction layers
* Testing without physical hardware
* Software design documentation

---

## Future Enhancements

* Unit Testing
* GitHub Actions CI/CD
* CAN FD Support
* SPI Flash Simulation
* I2C EEPROM Simulation
* UART Ring Buffer Driver
* AUTOSAR-style Driver Layering

