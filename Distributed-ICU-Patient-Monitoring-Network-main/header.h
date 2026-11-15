#ifndef HEADER_H
#define HEADER_H

// UART
extern void uart0_st(unsigned int baud);
extern void uart0_tx(unsigned char data);
extern void uart0_tx_string(char *ptr);
extern void uart0_integer(int num);
extern void uart0_rx_string(unsigned char *ptr, int len);

// Delay
extern void delay_ms(unsigned int ms);

// I2C
extern void i2c_st(void);
extern void i2c_send(unsigned char sa, unsigned char mr, unsigned char data);
extern unsigned char i2c_read(unsigned char sa, unsigned char mr);
extern void i2c_read_buf(unsigned char sa, unsigned char mr, unsigned char *buf, unsigned char len);

// ADC
void adc_st(void);
unsigned int adc_read(unsigned char);

// CAN
struct CAN1_MSG {
        unsigned int id;
        unsigned int byteA;
        unsigned int byteB;
        unsigned char rtr;
        unsigned char dlc;
        unsigned char ff; //ide
};

extern void can1_rx(struct CAN1_MSG *ptr);
extern void can1_tx(struct CAN1_MSG v);
extern void can1_st(void);

#endif

#ifndef __MAX30102_H__
#define __MAX30102_H__

#include "header.h"

#define REG_TEMP_INT      0x1F
#define REG_TEMP_FRAC     0x20
#define REG_TEMP_CONFIG   0x21

/* I2C Address */
#define MAX30102_ADDR          0x57

/* Registers */
#define REG_INTR_STATUS1       0x00
#define REG_INTR_STATUS2       0x01
#define REG_INTR_ENABLE1       0x02
#define REG_INTR_ENABLE2       0x03

#define REG_FIFO_WR_PTR        0x04
#define REG_OVF_COUNTER        0x05
#define REG_FIFO_RD_PTR        0x06
#define REG_FIFO_DATA          0x07
#define REG_FIFO_CONFIG        0x08

#define REG_MODE_CONFIG        0x09
#define REG_SPO2_CONFIG        0x0A

#define REG_LED1_PA            0x0C
#define REG_LED2_PA            0x0D

#define REG_REV_ID             0xFE
#define REG_PART_ID            0xFF

typedef struct
{
    unsigned int red;
    unsigned int ir;
} MAX30102_Data;

/* Driver API */
void MAX30102_st(void);
void MAX30102_Reset(void);
void MAX30102_WriteReg(unsigned char reg, unsigned char value);
unsigned char MAX30102_ReadReg(unsigned char reg);
void MAX30102_ReadFIFO(MAX30102_Data *sample);
unsigned char MAX30102_GetWritePointer(void);
unsigned char MAX30102_GetReadPointer(void);
void MAX30102_DumpRegisters(void);

#endif

#ifndef __SPO2_H__
#define __SPO2_H__

#include "header.h"

#define SPO2_SAMPLE_SIZE 100

void SpO2_st(void);
void SpO2_Process(unsigned int red, unsigned int ir);
unsigned char Get_SpO2(void);

#endif

//EEPROM

#define EEPROM_ID 0x50


extern void EEPROM_LogData(float temp,float light,unsigned char oxygen);
extern void EEPROM_ReadRecord(unsigned int start_addr);
extern void EEPROM_ReadAllRecords(void);
