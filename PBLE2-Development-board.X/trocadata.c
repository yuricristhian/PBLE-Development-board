/* 
 * File:   trocadata.c
 * Author: isaac
 *
 * Created on 14 de Maio de 2018, 14:58
 */

#include "trocadata.h"
#include "lcd.h"
#include "rtc.h"
#include "delay.h"
#include "texto.h"
//#include "setaalarme.h"
#include "user.h"

#define up 1
#define down 2
#define left 4
#define right 8
#define ok 16
#define cancel 32

void trocaData(void) {

    char estado = 0, acao, fim = 1, dia, mes, ano, i;
    char tx[] = "cancel ";
    lcdCommand(0x80);
    delay(10);
    for (i = 0; i < 7; i++) {
        lcdChar(tx[i]);
        delay(10);
    }
    lcdChar(((rtcGetDate() / 10) % 10) + 48);
    lcdChar((rtcGetDate() % 10) + 48);
    lcdChar('/');
    lcdChar(((rtcGetMonth() / 10) % 10) + 48);
    lcdChar((rtcGetMonth() % 10) + 48);
    lcdChar('/');
    lcdChar(((rtcGetYear() / 10) % 10) + 48);
    lcdChar((rtcGetYear() % 10) + 48);
    delay(10);
    dia = rtcGetDate();
    mes = rtcGetMonth();
    ano = rtcGetYear();
    attData();
    lcdCommand(0xC1);
    while (fim) {
        
        checaAlarme();
        
        
        switch (estado) {

            case 0:
                acao=interacao();
                if (acao == down && rtcGetDate() > 1) {
                    rtcPutDate(rtcGetDate() - 1);
                    attData();
                    delay(50);
                    lcdCommand(0xC1);
                }
                if (acao == up) {
                    if (rtcGetDate() < 31) {
                        if (rtcGetMonth() == 1 || rtcGetMonth() == 3 || rtcGetMonth() == 5 || rtcGetMonth() == 7 || rtcGetMonth() == 8 || rtcGetMonth() == 10 || rtcGetMonth() == 12) {
                            rtcPutDate(rtcGetDate() + 1);
                            attData();
                            delay(50);
                        }
                    }
                    if (rtcGetDate() < 30) {
                        if (rtcGetMonth() == 4 || rtcGetMonth() == 6 || rtcGetMonth() == 9 || rtcGetMonth() == 11) {
                            rtcPutDate(rtcGetDate() + 1);
                            attData();
                            delay(50);
                        }
                    }
                    if (rtcGetMonth() == 2) {
                        if (rtcGetYear() % 4 == 0) {
                            if (rtcGetDate() < 29) {
                                rtcPutDate(rtcGetDate() + 1);
                                attData();
                                delay(50);
                            }
                        }
                        if (rtcGetDate() < 28) {
                            rtcPutDate(rtcGetDate() + 1);
                            attData();
                            delay(50);
                        }
                    }
                    lcdCommand(0xC1);
                }
                if (acao == left) {
                    estado = 2;
                    lcdCommand(0xC7);
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
                    rtcPutDate(dia);
                    rtcPutMonth(mes);
                    rtcPutYear(ano);
                    fim = 0;
                    delay(50);
                }
                break;

            case 1:
                acao=interacao();
                if (acao == down && rtcGetMonth() > 1) {
                    rtcPutMonth(rtcGetMonth() - 1);
                    attData();
                    delay(50);
                    lcdCommand(0xC4);
                }
                if (acao == up && rtcGetMonth()<12) {
                    rtcPutMonth(rtcGetMonth() + 1);
                    attData();
                    delay(50);
                    lcdCommand(0xC4);
                }
                if (acao == left) {
                    estado = 0;
                    lcdCommand(0xC1);
                    delay(50);
                }
                if (acao == right) {
                    estado = 2;
                    lcdCommand(0xC7);
                    delay(50);
                }
                if (acao == ok) {
                    fim = 0;
                    delay(50);
                }
                if (acao == cancel) {
                    rtcPutDay(dia);
                    rtcPutMonth(mes);
                    rtcPutYear(ano);
                    fim = 0;
                    delay(50);
                }
                break;
            case 2:
                acao=interacao();
                if (acao == down) {
                    rtcPutYear(rtcGetYear() - 1);
                    attData();
                    delay(50);
                    lcdCommand(0xC7);
                }
                if (acao == up) {
                    rtcPutYear(rtcGetYear() + 1);
                    attData();
                    delay(50);
                    lcdCommand(0xC7);
                }
                if (acao == left) {
                    estado = 1;
                    lcdCommand(0xC4);
                    delay(50);
                }
                if (acao == right) {
                    estado = 0;
                    lcdCommand(0xC1);
                    delay(50);
                }
                if (acao == ok) {
                    fim = 0;
                    attData();
                    delay(50);
                }
                if (acao == cancel) {
                    rtcPutDay(dia);
                    rtcPutMonth(mes);
                    rtcPutYear(ano);
                    attData();
                    fim = 0;
                    delay(50);
                }
                break;
        }
    }
    lcdCommand(0x01);
    print(5, 0);
    serialSend('\n');
    attData();
}

void attData(void) {
    lcdCommand(0xC0);
    lcdChar(((rtcGetDate() / 10) % 10) + 48);
    lcdChar((rtcGetDate() % 10) + 48);
    lcdChar('/');
    lcdChar(((rtcGetMonth() / 10) % 10) + 48);
    lcdChar((rtcGetMonth() % 10) + 48);
    lcdChar('/');
    lcdChar(((rtcGetYear() / 10) % 10) + 48);
    lcdChar((rtcGetYear() % 10) + 48);
    serialSend(((rtcGetDate() / 10) % 10) + 48);
    serialSend((rtcGetDate() % 10) + 48);
    serialSend('/');
    serialSend(((rtcGetMonth() / 10) % 10) + 48);
    serialSend((rtcGetMonth() % 10) + 48);
    serialSend('/');
    serialSend(((rtcGetYear() / 10) % 10) + 48);
    serialSend((rtcGetYear() % 10) + 48);
    serialSend('\n');
}