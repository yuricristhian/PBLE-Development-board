/* 
 * File:   trocahora.c
 * Author: isaac
 *
 * Created on 14 de Maio de 2018, 16:51
 */

#include "trocahora.h"
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

void trocaHora(void) {

    char estado = 0, acao, fim = 1, hora, minuto, segundo, i;
    char tx[] = "cancel ";
    lcdCommand(0x80);
    delay(10);
    for (i = 0; i < 7; i++) {
        lcdChar(tx[i]);
        delay(10);
    }
    lcdChar(((rtcGetHours() / 10) % 10) + 48);
    lcdChar((rtcGetHours() % 10) + 48);
    lcdChar(':');
    lcdChar(((rtcGetMinutes() / 10) % 10) + 48);
    lcdChar((rtcGetMinutes() % 10) + 48);
    lcdChar(':');
    lcdChar(((rtcGetSeconds() / 10) % 10) + 48);
    lcdChar((rtcGetSeconds() % 10) + 48);
    delay(10);
    hora = rtcGetHours();
    minuto = rtcGetMinutes();
    segundo = rtcGetSeconds();
    attHora();
    lcdCommand(0xC1);
    while (fim) {


        //checaAlarme();


        switch (estado) {
            case 0:
                lcdCommand(0xC1);
                acao = interacao();
                mudaHora();
                lcdCommand(0xC1);
                delay(100);
                if (acao == down && rtcGetHours() > 0) {
                    rtcPutHours(rtcGetHours() - 1);
                    attHora();
                    lcdCommand(0xC1);
                }
                if (acao == up && rtcGetHours() < 23) {
                    rtcPutHours(rtcGetHours() + 1);
                    attHora();
                    lcdCommand(0xC1);
                }
                if (acao == left) {
                    estado = 2;

                }
                if (acao == right) {
                    estado = 1;

                }
                if (acao == ok) {
                    fim = 0;
                }
                if (acao == cancel) {
                    rtcPutHours(hora);
                    rtcPutMinutes(minuto);
                    fim = 0;
                }
                break;

            case 1:
                lcdCommand(0xC4);
                acao = interacao();
                mudaHora();
                lcdCommand(0xC4);
                delay(100);
                if (acao == down && rtcGetMinutes() > 0) {
                    rtcPutMinutes(rtcGetMinutes() - 1);
                    attHora();
                    lcdCommand(0xC4);
                }
                if (acao == up && rtcGetMinutes() < 59) {
                    rtcPutMinutes(rtcGetMinutes() + 1);
                    attHora();
                    lcdCommand(0xC4);
                }
                if (acao == left) {
                    estado = 0;
                }
                if (acao == right) {
                    estado = 2;
                }
                if (acao == ok) {
                    fim = 0;
                }
                if (acao == cancel) {
                    rtcPutHours(hora);
                    rtcPutMinutes(minuto);
                    fim = 0;
                }
                break;
            case 2:
                lcdCommand(0xC7);
                acao = interacao();
                mudaHora();
                lcdCommand(0xC7);
                delay(100);
                if (acao == down && rtcGetSeconds() > 0) {
                    rtcPutSeconds(rtcGetSeconds() - 1);
                    attHora();
                    lcdCommand(0xC7);
                }
                if (acao == up && rtcGetSeconds() < 59) {
                    rtcPutSeconds(rtcGetSeconds() + 1);
                    attHora();
                    lcdCommand(0xC7);
                }
                if (acao == left) {
                    estado = 1;
                    lcdCommand(0xC4);
                }
                if (acao == right) {
                    estado = 0;
                    lcdCommand(0xC1);
                }
                if (acao == ok) {
                    fim = 0;
                }
                if (acao == cancel) {
                    rtcPutHours(hora);
                    rtcPutMinutes(minuto);
                    fim = 0;
                }
                break;
        }
    }
    lcdCommand(0x01);
    print(6, 0);
    serialSend('\n');
}

void attHora(void) {
    lcdCommand(0xC0);
    lcdChar(((rtcGetHours() / 10) % 10) + 48);
    lcdChar((rtcGetHours() % 10) + 48);
    lcdChar(':');
    lcdChar(((rtcGetMinutes() / 10) % 10) + 48);
    lcdChar((rtcGetMinutes() % 10) + 48);
    lcdChar(':');
    lcdChar(((rtcGetSeconds() / 10) % 10) + 48);
    lcdChar((rtcGetSeconds() % 10) + 48);
    serialSend(((rtcGetHours() / 10) % 10) + 48);
    serialSend((rtcGetHours() % 10) + 48);
    serialSend(':');
    serialSend(((rtcGetMinutes() / 10) % 10) + 48);
    serialSend((rtcGetMinutes() % 10) + 48);
    serialSend(':');
    serialSend(((rtcGetSeconds() / 10) % 10) + 48);
    serialSend((rtcGetSeconds() % 10) + 48);
    serialSend('\n');
}

void mudaHora(void) {
    char tx[] = "cancel ";
    char h;
    lcdCommand(0x80);
    for (h = 0; h < 7; h++) {
        lcdChar(tx[h]);
    }
    lcdChar(((rtcGetHours() / 10) % 10) + 48);
    lcdChar((rtcGetHours() % 10) + 48);
    lcdChar(':');
    lcdChar(((rtcGetMinutes() / 10) % 10) + 48);
    lcdChar((rtcGetMinutes() % 10) + 48);
    lcdChar(':');
    lcdChar(((rtcGetSeconds() / 10) % 10) + 48);
    lcdChar((rtcGetSeconds() % 10) + 48);

    serialSend(((rtcGetHours() / 10) % 10) + 48);
    serialSend((rtcGetHours() % 10) + 48);
    serialSend(':');
    serialSend(((rtcGetMinutes() / 10) % 10) + 48);
    serialSend((rtcGetMinutes() % 10) + 48);
    serialSend(':');
    serialSend(((rtcGetSeconds() / 10) % 10) + 48);
    serialSend((rtcGetSeconds() % 10) + 48);
    serialSend('\n');
}