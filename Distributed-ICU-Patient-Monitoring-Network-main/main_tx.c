#include <LPC21xx.h>
#include "header.h"

MAX30102_Data sensor;
short int ir_filtered;
struct CAN1_MSG v1;

int main(void)
{
        unsigned int temp, ldr;
        unsigned char oxygen;
        unsigned char count = 0;
        can1_st();
        adc_st();
        uart0_st(9600);
        i2c_st();
        delay_ms(100);

        uart0_tx_string("\r\n");
        uart0_tx_string("***********PATIENT ROOM**********\r\n");

        MAX30102_st();
        SpO2_st();

        v1.id = 0x234;
        v1.rtr = 0; //data-frame
        v1.dlc = 4;
        v1.byteA = 0;
        v1.byteB = 0;

        while(1)
        {
                MAX30102_ReadFIFO(&sensor);
                SpO2_Process(sensor.red, sensor.ir);

                count++;
                if(count >= 50)
                {
                        count = 0;
                        uart0_tx_string("----------------------\r\n");
                        uart0_tx_string("RED=");
                        uart0_integer(sensor.red);
                        uart0_tx_string("\r\nIR=");
                        uart0_integer(sensor.ir);
                        uart0_tx_string("\r\nSpO2=");
                        uart0_integer(Get_SpO2());
                        uart0_tx_string("\r\n");

                        temp = adc_read(0);
                        ldr = adc_read(1);

                        temp = temp & 0x3ff;
                        ldr = ldr & 0x3ff;
                        oxygen = Get_SpO2();

                        v1.byteA = (temp | (ldr << 10) | (oxygen << 20));
                        can1_tx(v1);
                }
                delay_ms(100);
        }
}
