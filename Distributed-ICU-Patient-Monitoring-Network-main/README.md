# Distributed-ICU-Patient-Monitoring-Network
This project presents a Distributed ICU Patient Monitoring Network based on the CAN protocol. The system continuously monitors important parameters and transmits them reliably to a central monitoring station, the proposed system improves monitoring efficiency and supports better patient care in ICU environments

# Distributed ICU Patient Monitoring Network

## 1. Project Overview
Brief description of the Distributed ICU Patient Monitoring Network and its purpose.

## 2. Project Objectives
- To monitor patient-related sensor data.
- To transmit data between Node A and Node B using CAN protocol.
- To store sensor data in EEPROM memory.
- To display received data through UART communication.
- To capture and store serial data using Tera Term 5.
- To maintain a log file in cloud storage.

## 3. System Architecture
Describe the overall architecture of the project.

### Node A – Transmitter
- Sensor data collection.
- CAN data transmission.

### Node B – Receiver
- CAN data reception.
- EEPROM data storage.
- UART data transmission to PC.

### PC – Data Monitoring
- UART data displayed in Tera Term 5.
- Complete serial data captured into one file.
- Log file uploaded to cloud drive.

## 4. Hardware Requirements
- Node A Controller
- Node B Controller
- Temperature Sensor
- LDR Sensor
- Oxygen Sensor
- CAN Interface
- UART Interface
- EEPROM Memory
- Computer

## 5. Software Requirements
- Embedded C / Firmware
- Tera Term 5
- Flash magic
- Cloud Drive

## 6. Communication Protocols
- CAN Protocol
- I2C Protocol
- UART Communication
  
## 7. Working Principle
1. Sensors collect patient monitoring data.
2. Sensors to provide to Node A using some Protocol
3. Node A transmits data to Node B through CAN.
4. Node B receives and stores the data in EEPROM.
5. Node B sends data to the PC through UART.
6. Tera Term 5 displays the received data.
7. Tera Term 5 captures all serial data into a single log file.
8. The log file is stored in a cloud drive.

## 8. Sample Output
```text
PATIENT DATA
TEMP LEVEL: 28 C
LIGHT LEVEL: 60%
OXYG LEVEL: 99%
```

## 9. Advantages
- Real-time data communication.
- EEPROM-based data storage.
- CAN and I2C-based node communication.
- UART-based monitoring.
- Centralized serial data logging.
- Cloud-based log file storage.

## 10. Future Enhancements
- Add timestamp-based data logging.
- Improve data security.
- Add more sensors to monitoring patient.

## 14. Author
Thirumalai Vasan K
