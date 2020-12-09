/* 
 * File:   setaalarme.c
 * Author: isaac
 *
 * Created on 16 de Maio de 2018, 17:11
 */

#include "setaalarme.h"
#include "texto.h"

#include "lcd.h"
#include "delay.h"

//#include "pwm.h"
#include "user.h"

#define up 1
#define down 2
#define left 4
#define right 8
#define ok 16
#define cancel 32

int piso1 = 0, piso2 = 0, teto1 = 4000, teto2 = 4000, teto, piso;
char cont;
unsigned int adcVal;
char error = 0;

void setaAlarme(void) {
    char acao;
    char fim = 1;

    print(10, 0);
    print(11, 1);
    serialSend('\n');
    while (fim) {
        acao = interacao();
        if (acao == up) {
            fim = 0;
            lcdCommand(0x01);
            delay(50);
            setaAlarme1();
        }
        if (acao == down) {
            fim = 0;
            lcdCommand(0x01);
            delay(50);
            setaAlarme2();
        }
        if (acao == cancel) {
            fim = 0;
            lcdCommand(0x01);
            print(2, 0);
        }
    }
}

void setaAlarme1(void) {
    char estado = 0, acao, fim = 1;
    teto = teto1;
    piso = piso1;
    while (fim) {
        checaAlarme();
        print(9, 0);
        serialSend('\n');
        lcdCommand(0xC2);
        lcdChar((((piso1) / 1000) % 10 + 48));
        lcdChar((((piso1) / 100) % 10 + 48));
        lcdChar((((piso1) / 10) % 10 + 48));
        lcdChar(((piso1) % 10 + 48));
        serialSend((((piso1) / 1000) % 10 + 48));
        serialSend((((piso1) / 100) % 10 + 48));
        serialSend((((piso1) / 10) % 10 + 48));
        serialSend(((piso1) % 10 + 48));
        lcdCommand(0xC8);
        lcdChar((((teto1) / 1000) % 10 + 48));
        lcdChar((((teto1) / 100) % 10) + 48);
        lcdChar((((teto1) / 10) % 10) + 48);
        lcdChar(((teto1) % 10) + 48);
        serialSend(' ');
        serialSend((((teto1) / 1000) % 10 + 48));
        serialSend((((teto1) / 100) % 10 + 48));
        serialSend((((teto1) / 10) % 10 + 48));
        serialSend(((teto1) % 10 + 48));
        serialSend('\n');
        switch (estado) {
            case 0:
                lcdCommand(0xC3);
                delay(50);
                acao = interacao();
                if (acao == down && piso1 > 0 && piso1 <= teto1) {
                    piso1--;
                }
                if (acao == up && piso1 < 4095 && piso1 < teto1) {
                    piso1++;
                }
                if (acao == left) {
                    estado = 1;
                    delay(50);
                }
                if (acao == right) {
                    estado = 1;
                    delay(50);
                }
                if (acao == ok) {
                    fim = 0;
                    delay(50);
                }
                if (acao == cancel) {
                    piso1 = piso;
                    teto1 = teto;
                    fim = 0;
                    delay(50);
                }
                break;

            case 1:
                lcdCommand(0xCD);
                delay(50);
                acao = interacao();
                if (acao == down && teto1 > 0 && teto1 > piso1) {
                    teto1--;
                }
                if (acao == up && teto1 < 4096) {
                    teto1++;
                }
                if (acao == left) {
                    estado = 0;
                    delay(50);
                }
                if (acao == right) {
                    estado = 0;
                    delay(50);
                }
                if (acao == ok) {

                    fim = 0;
                    delay(50);
                }
                if (acao == cancel) {
                    piso1 = piso;
                    teto1 = teto;
                    fim = 0;
                    delay(50);
                }
                break;
        }
    }
    lcdCommand(0x01);
}

void setaAlarme2(void) {
    char estado = 0, acao, fim = 1;
    teto = teto2;
    piso = piso2;
    while (fim) {
        checaAlarme();
        print(9, 0);
        serialSend('\n');
        lcdCommand(0xC2);
        lcdChar((((piso2) / 1000) % 10 + 48));
        lcdChar((((piso2) / 100) % 10 + 48));
        lcdChar((((piso2) / 10) % 10 + 48));
        lcdChar(((piso2) % 10 + 48));
        serialSend((((piso2) / 1000) % 10 + 48));
        serialSend((((piso2) / 100) % 10 + 48));
        serialSend((((piso2) / 10) % 10 + 48));
        serialSend(((piso2) % 10 + 48));
        lcdCommand(0xC8);
        lcdChar((((teto2) / 1000) % 10 + 48));
        lcdChar((((teto2) / 100) % 10) + 48);
        lcdChar((((teto2) / 10) % 10) + 48);
        lcdChar(((teto2) % 10) + 48);
        serialSend(' ');
        serialSend((((teto2) / 1000) % 10 + 48));
        serialSend((((teto2) / 100) % 10 + 48));
        serialSend((((teto2) / 10) % 10 + 48));
        serialSend(((teto2) % 10 + 48));
        serialSend('\n');
        switch (estado) {
            case 0:
                lcdCommand(0xC4);
                delay(50);
                acao = interacao();
                if (acao == down && piso2 > 0 && piso2 <= teto2) {
                    piso2--;
                }
                if (acao == up && piso2 < 4096 && piso2 < teto2) {
                    piso2++;

                }
                if (acao == left) {
                    estado = 1;
                    delay(50);
                }
                if (acao == right) {
                    estado = 1;
                    lcdCommand(0xC4);
                    delay(50);
                }
                if (acao == ok) {
                    fim = 0;
                    delay(50);
                }
                if (acao == cancel) {
                    piso2 = piso;
                    teto2 = teto;
                    fim = 0;
                    delay(50);
                }
                break;

            case 1:
                lcdCommand(0xCE);
                delay(50);
                acao = interacao();
                if (acao == down && teto2 > 0 && teto2 > piso2) {
                    teto2--;
                }
                if (acao == up && teto2 < 4096) {
                    teto2++;
                }
                if (acao == left) {
                    estado = 0;
                    delay(50);
                }
                if (acao == right) {
                    estado = 0;

                    delay(50);
                }
                if (acao == ok) {

                    fim = 0;
                    delay(50);
                }
                if (acao == cancel) {
                    piso2 = piso;
                    teto2 = teto;
                    fim = 0;
                    delay(50);
                }
                break;
        }
    }
    lcdCommand(0x01);
}

void checaAlarme(void) {
    ADC1_ChannelSelect(0x0);
    if (adcRead() <= piso1 || adcRead() >= teto1) {
        error = 1;
        ativaAlarm(error);
    }
    ADC1_ChannelSelect(0x1);
    if (adcRead() <= piso2 || adcRead() >= teto2) {
        error = 2;
        ativaAlarm(error);
    }
    error = 0;
}

void ativaAlarm(char erro) {

    if (erro == 1) {
        lcdCommand(0x01);
        print(12, 0);
        print(13, 1);
        serialSend('\n');
        serialSend(' ');
        attData();
        serialSend(' ');
        attHora();
        serialSend('\n');
        lcdCommand(0xCB);
        adcVal = adcRead();
        lcdChar(((adcVal / 1000) % 10) + 48);
        lcdChar(((adcVal / 100) % 10) + 48);
        lcdChar(((adcVal / 10) % 10) + 48);
        lcdChar((adcVal % 10) + 48);
        serialSend('\n');
        serialSend(((adcVal / 1000) % 10) + 48);
        serialSend(((adcVal / 100) % 10) + 48);
        serialSend(((adcVal / 10) % 10) + 48);
        serialSend((adcVal % 10) + 48);
        //        pwmInit();
        //        pwmFrequency(1000);
        //        pwmSet1(50);
        while (reChecaAlarme());
    }
    if (erro == 2) {
        lcdCommand(0x01);
        print(12, 0);
        print(14, 1);
        serialSend('\n');
        serialSend(' ');
        attData();
        serialSend(' ');
        attHora();
        serialSend('\n');
        lcdCommand(0xCB);
        ADC1_ChannelSelect(0x1);
        adcVal = adcRead();
        lcdChar(((adcVal / 1000) % 10) + 48);
        lcdChar(((adcVal / 100) % 10) + 48);
        lcdChar(((adcVal / 10) % 10) + 48);
        lcdChar((adcVal % 10) + 48);
        serialSend('\n');
        serialSend(((adcVal / 1000) % 10) + 48);
        serialSend(((adcVal / 100) % 10) + 48);
        serialSend(((adcVal / 10) % 10) + 48);
        serialSend((adcVal % 10) + 48);
        //        pwmInit();
        //        pwmFrequency(1000);
        //        pwmSet1(50);
        while (reChecaAlarme());
    }
    //    BitSet(TRISC, 1);
    //    BitSet(TRISC, 2);
}

char reChecaAlarme(void) {

    ADC1_ChannelSelect(0x0);
    adcVal = adcRead();
    if (adcVal <= piso1 || adcVal >= teto1) {
        print(12, 0);
        print(13, 1);
        ADC1_ChannelSelect(0x0);
        lcdCommand(0xCB);
        adcVal = adcRead();
        lcdChar(((adcVal / 1000) % 10) + 48);
        lcdChar(((adcVal / 100) % 10) + 48);
        lcdChar(((adcVal / 10) % 10) + 48);
        lcdChar((adcVal % 10) + 48);
        serialSend('\n');
        serialSend(((adcVal / 1000) % 10) + 48);
        serialSend(((adcVal / 100) % 10) + 48);
        serialSend(((adcVal / 10) % 10) + 48);
        serialSend((adcVal % 10) + 48);
        //        pwmInit();
        //        pwmFrequency(1000);
        //        pwmSet1(50);
        return error;
    }
    ADC1_ChannelSelect(0x1);
    adcVal = adcRead();
    if (adcVal <= piso2 || adcVal >= teto2) {
        print(12, 0);
        print(14, 1);
        ADC1_ChannelSelect(0x1);
        lcdCommand(0xCB);
        adcVal = adcRead();
        lcdChar(((adcVal / 1000) % 10) + 48);
        lcdChar(((adcVal / 100) % 10) + 48);
        lcdChar(((adcVal / 10) % 10) + 48);
        lcdChar((adcVal % 10) + 48);
        serialSend('\n');
        serialSend(((adcVal / 1000) % 10) + 48);
        serialSend(((adcVal / 100) % 10) + 48);
        serialSend(((adcVal / 10) % 10) + 48);
        serialSend((adcVal % 10) + 48);
        return error;
    }
    error = 0;
    lcdCommand(0x01);
    return error;
}

void setapiso1(unsigned int a) {
    if (a < teto1)
        piso1 = a;
}

void setapiso2(unsigned int b) {
    if (b < teto2)
        piso2 = b;
}

void setateto1(unsigned int c) {
    if (c > piso1)
        teto1 = c;
}

void setateto2(unsigned int d) {
    if (d > piso2)
        teto2 = d;
}