#include "header.h"
#include <lpc21xx.h>
void i2c_st(void)
{
        PINSEL0 |= 0x50;
        I2CONSET = 1 << 6;
        I2SCLL = I2SCLH = 75;
}

void i2c_send(unsigned char sa, unsigned char mr_addr, unsigned char data)
{
        I2CONSET = 1 << 5;
        I2CONCLR = 1 << 3;
        while(((I2CONSET>>3)&1) == 0);
        I2CONCLR = 1 << 5;

        I2DAT = sa;
        I2CONCLR = 1 << 3;
        while(((I2CONSET>>3)&1) == 0);
        if(I2STAT == 0x20)
        {
                uart0_tx_string("ERROR : SA+W\r\n");
                goto exit;
        }

        I2DAT = mr_addr;
        I2CONCLR = 1 << 3;
        while(((I2CONSET>>3)&1) == 0);
        if(I2STAT == 0x30)
        {
                uart0_tx_string("ERROR : mr_addr\r\n");
                goto exit;
        }

        I2DAT = data;
        I2CONCLR = 1 << 3;
        while(((I2CONSET>>3)&1) == 0);
        if(I2STAT == 0x30)
        {
                uart0_tx_string("ERROR : data\r\n");
                goto exit;
        }

        exit: I2CONSET = 1 << 4;
              I2CONCLR = 1 << 3;
}

unsigned char i2c_read(unsigned char sa, unsigned char mr_addr)
{
        unsigned char temp = 0;
        I2CONSET = 1 << 5;
        I2CONCLR = 1 << 3;
        while(((I2CONSET>>3)&1) == 0);
        I2CONCLR = 1 << 5;

        I2DAT = sa & 0xfe;
        I2CONCLR = 1 << 3;
        while(((I2CONSET>>3)&1) == 0);
        if(I2STAT == 0x20)
        {
                uart0_tx_string("ERROR : SA+W\r\n");
                goto exit;
        }

        I2DAT = mr_addr;
        I2CONCLR = 1 << 3;
        while(((I2CONSET>>3)&1) == 0);
        if(I2STAT == 0x30)
        {
                uart0_tx_string("ERROR : mr_addr\r\n");
                goto exit;
        }
        I2CONSET = 1 << 5;
        I2CONCLR = 1 << 3;
        while(((I2CONSET>>3)&1) == 0);
        I2CONCLR = 1 << 5;

        I2DAT = sa;
        I2CONCLR = 1 << 3;
        while(((I2CONSET>>3)&1) == 0);
        if(I2STAT == 0x48)
        {
                uart0_tx_string("ERROR : SA+R\r\n");
                goto exit;
        }
        I2CONCLR = 1 << 3;
        while(((I2CONSET>>3)&1) == 0);
        temp = I2DAT;

        exit: I2CONSET = 1 << 4;
              I2CONCLR = 1 << 3;
              return temp;
}
void i2c_read_buf(unsigned char sa, unsigned char mr, unsigned char *buf, unsigned char len)
 {
     unsigned char i;
 
    /* START */


    I2CONSET=(1<<5);
     I2CONCLR=(1<<3);
 
    while(((I2CONSET>>3)&1)==0);
 
    I2CONCLR=(1<<5);
 
    /* Slave + Write */
 
     I2DAT=(sa<<1);
 
    I2CONCLR=(1<<3);
  
    while(((I2CONSET>>3)&1)==0);
  
    if(I2STAT!=0x18)
         goto exit;

    /* Register */
  I2DAT=mr;
  I2CONCLR=(1<<3);
    while(((I2CONSET>>3)&1)==0);

    if(I2STAT!=0x28)
        goto exit;

    I2CONSET=(1<<5);

    I2CONCLR=(1<<3);

    while(((I2CONSET>>3)&1)==0);

    I2CONCLR=(1<<5);
 
    /* Slave + Read */

    I2DAT=(sa<<1)|1;

     I2CONCLR=(1<<3);

    while(((I2CONSET>>3)&1)==0);

    if(I2STAT!=0x40)
        goto exit;

  /* Read bytes */
    for(i=0;i<len;i++)
    {
        if(i==(len-1))
        {
            /*
              Last byte
               send NACK
            */
            I2CONCLR=(1<<2);
        }
        else
        {
            /*
               More bytes

               send ACK

            */
            I2CONSET=(1<<2);
        }
        I2CONCLR=(1<<3);
        while(((I2CONSET>>3)&1)==0);
        buf[i]=I2DAT;
    }
exit:
 
    /* STOP */

     I2CONSET=(1<<4);
 
     I2CONCLR=(1<<3);
 
}
 
