#include "header.h"
#include <stdio.h>

struct CAN1_MSG r1;

int main()
{
        unsigned int adcout0, adcout1,count=10;
        unsigned char oxygen;
        float temp, vout, v2;
        char s[50];
        can1_st();
	      i2c_st();
        uart0_st(9600);
	      uart0_tx_string("**************************\r\n");
        uart0_tx_string(" DATA ROOM \r\n");
	      uart0_tx_string("**************************\r\n");

        while(count>0)
        {
                can1_rx(&r1);
                if(r1.rtr == 0)
                {
                        adcout0 = (r1.byteA & 0x3ff);
                        adcout1 = ((r1.byteA >> 10) & 0x3ff);
                        oxygen = ((r1.byteA >> 20) & 0xff);
                        uart0_tx_string("\r\n                       \r\n");
                        uart0_tx_string(" PATIENT DATA MONITOR  \r\n");
                        uart0_tx_string("Patient data\r\n");

                        vout = (adcout0 * 3.3) / 1023;
                        temp = -((vout - 0.5) / 0.01);
                        sprintf(s, "Temp : %.2f ^C \r\n", temp);
                        uart0_tx_string(s);

                        v2 = (adcout1 * 3.3) / 1023 * 100;
                        sprintf(s, "Light : %.2f %%\r\n", v2);
                        uart0_tx_string(s);

                        sprintf(s, "Oxygen  : %d %%\r\n", oxygen);
                        uart0_tx_string(s);
									      EEPROM_LogData(temp,v2,oxygen);
                        delay_ms(300);
									count--;
                }
                else
                {
                        uart0_tx_string("remote-frame received\r\n");
                }
        }
				    uart0_tx_string("\r\n");
            uart0_tx_string("===== EEPROM DATA =====\r\n");
				EEPROM_ReadAllRecords();
}
