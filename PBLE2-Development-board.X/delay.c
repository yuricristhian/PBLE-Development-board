/* 
 * File:   Delay.c
 * Author: isaac
 *
 * Created on 11 de Maio de 2018, 13:57
 */
#include "delay.h"

void delay(int tempo) {
    volatile unsigned long int i;
    while (tempo) {
        for (i = 0; i < 2400; i++);
        tempo--;
    }
}

void delay_us(int tempo) {
    unsigned char i;
    while (tempo) {
        for (i = 0; i < 10; i++);
        tempo--;
    }
}
