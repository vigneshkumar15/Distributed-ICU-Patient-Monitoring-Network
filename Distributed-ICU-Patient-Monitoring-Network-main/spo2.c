#include <lpc21xx.h>
#include "header.h"

#define BUFFER_SIZE 50

static unsigned int red_buf[BUFFER_SIZE];
static unsigned int ir_buf[BUFFER_SIZE];
static unsigned char index = 0;
static unsigned char spo2 = 0;

void SpO2_st(void)
{
    unsigned char i;
    index = 0;
    spo2 = 0;
    for(i = 0; i < BUFFER_SIZE; i++)
    {
        red_buf[i] = 0;
        ir_buf[i] = 0;
    }
}

void SpO2_Process(unsigned int red, unsigned int ir)
{
    unsigned char i;
    unsigned int red_dc = 0;
    unsigned int ir_dc = 0;
    unsigned int red_ac = 0;
    unsigned int ir_ac = 0;
    float R;
    float value;
    red_buf[index] = red;
    ir_buf[index] = ir;
    index++;
    if(index < BUFFER_SIZE)
        return;
    index = 0;

    for(i = 0; i < BUFFER_SIZE; i++)
    {
        red_dc += red_buf[i];
        ir_dc += ir_buf[i];
    }

    red_dc /= BUFFER_SIZE;
    ir_dc /= BUFFER_SIZE;

    for(i = 0; i < BUFFER_SIZE; i++)
    {
        if(red_buf[i] > red_dc)
            red_ac += red_buf[i] - red_dc;
        else
            red_ac += red_dc - red_buf[i];

        if(ir_buf[i] > ir_dc)
            ir_ac += ir_buf[i] - ir_dc;
        else
            ir_ac += ir_dc - ir_buf[i];
    }
    red_ac /= BUFFER_SIZE;
    ir_ac /= BUFFER_SIZE;

    if(red_dc == 0 || ir_dc == 0)
        return;

    if(red_ac == 0 || ir_ac == 0)
        return;

    R = ((float)red_ac / red_dc) / ((float)ir_ac / ir_dc);
    value = 110.0f - 25.0f * R;

    if(value > 100.0f)
        value = 100.0f;
    if(value < 0.0f)
        value = 0.0f;

    spo2 = (unsigned char)value;
}

unsigned char Get_SpO2(void)
{
    return spo2;
}
