#include <lpc21xx.h>
#include "header.h"

void MAX30102_WriteReg(unsigned char reg, unsigned char value)
{
    i2c_send(MAX30102_ADDR, reg, value);
}

unsigned char MAX30102_ReadReg(unsigned char reg)
{
    return i2c_read(MAX30102_ADDR, reg);
}

void MAX30102_Reset(void)
{
    MAX30102_WriteReg(REG_MODE_CONFIG, 0x40);
    while(MAX30102_ReadReg(REG_MODE_CONFIG) & 0x40);
    delay_ms(10);
}

void MAX30102_st(void)
{
    MAX30102_Reset();
    MAX30102_WriteReg(REG_INTR_ENABLE1, 0x00);
    MAX30102_WriteReg(REG_INTR_ENABLE2, 0x00);
    MAX30102_WriteReg(REG_FIFO_WR_PTR, 0x00);
    MAX30102_WriteReg(REG_OVF_COUNTER, 0x00);
    MAX30102_WriteReg(REG_FIFO_RD_PTR, 0x00);
    MAX30102_WriteReg(REG_FIFO_CONFIG, 0x40);
    MAX30102_WriteReg(REG_SPO2_CONFIG, 0x27);
    MAX30102_WriteReg(REG_LED1_PA, 0x24);
    MAX30102_WriteReg(REG_LED2_PA, 0x24);
    MAX30102_WriteReg(REG_MODE_CONFIG, 0x03);
    delay_ms(100);
    MAX30102_ReadReg(REG_INTR_STATUS1);
    MAX30102_ReadReg(REG_INTR_STATUS2);
}

void MAX30102_ReadFIFO(MAX30102_Data *sample)
{
    unsigned char data[6];
    i2c_read_buf(MAX30102_ADDR, REG_FIFO_DATA, data, 6);

    sample->red = (((unsigned int)data[0] << 16) |
                   ((unsigned int)data[1] << 8) |
                   data[2]) & 0x03FFFF;

    sample->ir = (((unsigned int)data[3] << 16) |
                  ((unsigned int)data[4] << 8) |
                  data[5]) & 0x03FFFF;
}
