#include <lpc21xx.h>
#include <stdio.h>
#include "header.h"


unsigned char eeprom_addr = 0;
void EEPROM_LogData(float temp,float light,unsigned char oxygen)
{
    unsigned int temp_store;
    unsigned int light_store;

    temp_store  = (unsigned int)(temp * 100);
    light_store = (unsigned int)(light * 100);

    i2c_send(EEPROM_ID, eeprom_addr++, temp_store & 0xFF);
    delay_ms(10);

    i2c_send(EEPROM_ID, eeprom_addr++, (temp_store >> 8) & 0xFF);
    delay_ms(10);

    i2c_send(EEPROM_ID, eeprom_addr++, light_store & 0xFF);
    delay_ms(10);

    i2c_send(EEPROM_ID, eeprom_addr++, (light_store >> 8) & 0xFF);
    delay_ms(10);

    i2c_send(EEPROM_ID, eeprom_addr++, oxygen);
    delay_ms(10);

    if(eeprom_addr >= 250)
        eeprom_addr = 0;
}

void EEPROM_ReadRecord(unsigned int start_addr)
{
    unsigned int temp_store;
    unsigned int light_store;
    unsigned char oxygen;

    float temp;
    float light;

    char s[50];

    temp_store  = i2c_read(EEPROM_ID,start_addr);
    temp_store |= (i2c_read(EEPROM_ID,start_addr+1) << 8);

    light_store  = i2c_read(EEPROM_ID,start_addr+2);
    light_store |= (i2c_read(EEPROM_ID,start_addr+3) << 8);

    oxygen = i2c_read(EEPROM_ID,start_addr+4);

    temp  = temp_store / 100.0;
    light = light_store / 100.0;

    sprintf(s,"Temp   : %.2f C\r\n",temp);
    uart0_tx_string(s);

    sprintf(s,"Light  : %.2f %%\r\n",light);
    uart0_tx_string(s);

    sprintf(s,"Oxygen : %d %%\r\n",oxygen);
    uart0_tx_string(s);

    uart0_tx_string("---------------------\r\n");
}
void EEPROM_ReadAllRecords(void)
{
    unsigned int addr;
    char s[40];
    int rec_no = 1;

    uart0_tx_string("\r\n");
    uart0_tx_string("===== EEPROM RECORDS =====\r\n");

    for(addr = 0; addr < eeprom_addr; addr += 5)
    {
        sprintf(s,"\r\nRecord %d\r\n",rec_no++);
        uart0_tx_string(s);

        EEPROM_ReadRecord(addr);

        delay_ms(100);
    }

    uart0_tx_string("===== END OF RECORDS =====\r\n");
}
