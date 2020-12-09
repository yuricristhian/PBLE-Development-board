/* 
 * File:   adcprint.c
 * Author: isaac
 *
 * Created on 16 de Maio de 2018, 19:10
 */

#include "lcd.h"
#include "delay.h"
#include "texto.h"
#include "printadc.h"

int i;
unsigned int cont;

void adcPrint(void) {
    serialSend('\n');
    lcdPosition(1, 0);
    ADC1_ChannelSelect(0xB);
    ADC1_Start();
    //Provide Delay
    for (i = 0; i < 1000; i++);
    ADC1_Stop();
    while (!ADC1_IsConversionComplete()) {
        ADC1_Tasks();
    }
    cont = ADC1_ConversionResultGet();
    lcdNumber(cont);
    lcdChar(' ');
    lcdChar(' ');
    serialNumber(cont);
    serialSend(' ');
    serialSend(' ');
    delay(10);
    ADC1_ChannelSelect(0x4);
    ADC1_Start();
    //Provide Delay
    for (i = 0; i < 1000; i++);
    ADC1_Stop();
    while (!ADC1_IsConversionComplete()) {
        ADC1_Tasks();
    }
    cont = ADC1_ConversionResultGet();
    lcdNumber(cont);
    serialNumber(cont);
    serialSend(' ');
    serialSend(' ');
    delay(10);
    lcdPosition(0, 0);
    ADC1_ChannelSelect(0x1);
    ADC1_Start();
    //Provide Delay
    for (i = 0; i < 1000; i++);
    ADC1_Stop();
    while (!ADC1_IsConversionComplete()) {
        ADC1_Tasks();
    }
    cont = ADC1_ConversionResultGet();
    lcdNumber(cont);
    lcdChar(' ');
    lcdChar(' ');
    serialNumber(cont);
    serialSend(' ');
    serialSend(' ');
    delay(10);
    ADC1_ChannelSelect(0x0);
    ADC1_Start();
    //Provide Delay
    for (i = 0; i < 1000; i++);
    ADC1_Stop();
    while (!ADC1_IsConversionComplete()) {
        ADC1_Tasks();
    }
    cont = ADC1_ConversionResultGet();
    lcdNumber(cont);
    serialNumber(cont);
    serialSend(' ');
    serialSend(' ');
    delay(10);
}
