# Distributed ICU Patient Monitoring Network

> **Original project:** [thiru-vasan/Distributed-ICU-Patient-Monitoring-Network](https://github.com/thiru-vasan/Distributed-ICU-Patient-Monitoring-Network)  
> **Original author shown in the source repository:** Thirumalai Vasan K

## Project Overview

This project presents a Distributed ICU Patient Monitoring Network based on the Controller Area Network (CAN) protocol. It is intended to collect patient-related sensor readings at a transmitter node, send the data to a receiver node, store received readings in EEPROM, and display the data on a PC through UART.

The source repository describes a monitoring flow involving temperature, light-level and oxygen-related readings, CAN communication between two controller nodes, EEPROM storage, and serial logging using Tera Term 5.

## Project Objectives

- Collect patient-related sensor data.
- Transfer data between Node A (transmitter) and Node B (receiver) using CAN.
- Store received sensor data in EEPROM.
- Display received data on a PC through UART.
- Capture serial output using Tera Term 5 and maintain a log file.

## System Architecture

1. **Node A – Transmitter:** Collects sensor readings and transmits data over CAN.
2. **Node B – Receiver:** Receives CAN data, stores data in EEPROM, and sends output to a PC over UART.
3. **PC – Monitoring:** Displays serial data in Tera Term 5 and can save the session as a log file.

## Repository File Guide

The descriptions below are based on the filenames and the project README in the original repository. Confirm each source file's implementation before relying on it.

| File | Description |
|---|---|
| `DATA STORAGE CENTRE.uvproj` | Keil uVision project file for the data-storage/receiver-side project. |
| `Patient Room.uvproj` | Keil uVision project file for the patient-room/transmitter-side project. |
| `EEPROM.c` | C source file for EEPROM-related operations. |
| `Startup.s` | ARM startup assembly file used during controller startup. |
| `adc_driver.c` | ADC driver source file, likely used to acquire analog sensor readings. |
| `can_driver.c` | CAN controller driver source file for CAN communication. |
| `delay.c` | Delay utility functions. |
| `header.h` | Shared declarations, macros, and header definitions used by the project. |
| `i2c_driver.c` | I2C communication driver source file. |
| `main_rx.c` | Main application source for the CAN receiver node. |
| `main_tx.c` | Main application source for the CAN transmitter node. |
| `max.c` | Source file associated with the MAX-series sensor module; inspect the code to confirm the exact device and functions. |
| `spo2.c` | Source file for SpO2-related processing or sensor handling. |
| `uart_driver.c` | UART serial communication driver source file. |
| `README.md` | Project overview, objectives, architecture, requirements, and working principle. |

## Hardware Mentioned in the Original README

- Node A controller
- Node B controller
- Temperature sensor
- LDR sensor
- Oxygen sensor
- CAN interface
- UART interface
- EEPROM memory
- Computer

## Software / Tools Mentioned

- Embedded C firmware
- Keil uVision project files
- Tera Term 5
- Flash Magic
- Cloud drive for log-file storage

## Communication Interfaces

- **CAN:** Communication between the transmitter and receiver nodes.
- **I2C:** Sensor or peripheral communication where supported by the hardware.
- **UART:** Serial output from the receiver to a PC.

## Example Output

The original README gives this illustrative output:

```text
PATIENT DATA
TEMP LEVEL: 28 C
LIGHT LEVEL: 60%
OXYG LEVEL: 99%
```

These are example values, not validated clinical measurements.

## Important Notes

- This is an educational embedded-systems project, not a certified medical device.
- Do not use it for diagnosis, treatment, or real patient monitoring.
- Check the controller model, pin connections, clock settings, sensor wiring, CAN bit rate, and EEPROM layout before building or running the firmware.
- The repository includes Keil `.uvproj` project files; open the appropriate project in a compatible Keil uVision installation.
- Preserve the original author's credit when reusing or adapting the source. If you make changes, document them clearly in your own repository.

## Credits

The original repository is by **Thirumalai Vasan K**:

https://github.com/thiru-vasan/Distributed-ICU-Patient-Monitoring-Network

If this repository is a fork or adapted copy, retain the upstream link and describe your own contributions separately.
