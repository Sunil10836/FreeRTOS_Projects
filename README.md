# STM32F446RE FreeRTOS Temperature Monitoring & Queue-Based Logging System
## Overview
This project demonstrates a complete FreeRTOS-based embedded application running on the STM32F446RE microcontroller using register-level programming (No HAL).

The application reads the internal temperature sensor using ADC, processes the temperature in multiple FreeRTOS tasks, and logs periodic temperature data over UART using a queue-based logging architecture.

The project is designed to demonstrate core RTOS concepts including:

 1. Task management
 2. Queue-based inter-task communication
 3. Software timers
 4. Mutex synchronization
 5. Producer-consumer architecture
 6. UART logging system
 7. ADC temperature monitoring
 8. Priority-based scheduling

## Features
| Feature | Description |
|---|---|
| FreeRTOS Tasks | Multiple concurrent tasks |
| Queue Communication | tempQueue + logQueue |
| Software Timer | Periodic logging callback |
| Mutex Protection | UART shared resource protection |
| ADC Temperature Sensor | Internal STM32 temperature sensor |
| Register-Level Programming | No HAL used |
| UART Logging | Serial debug output |
| Clean Architecture | No global temperature sharing |
| Producer-Consumer Design | Queue-based data flow |

## Project Flow

```text
ADC Read
   |
   v
Temperature Conversion
   |
   v
tempQueue Update
   |
   +----------------------+
   |                      |
   v                      v
Controller Task      Timer Callback
                            |
                            v
                      logQueue Send
                            |
                            v
                        Logger Task
                            |
                            v
                           UART
