/* 
 * File:   main.c
 * Author: isaac
 *
 * Created on 11 de Maio de 2018, 19:41
 */
#include "mcc_generated_files/mcc.h"
#include "delay.h"
#include "texto.h"
#include "configuracao.h"
#include "trocadata.h"
#include "trocahora.h"
//#include "setapwm.h"
#include "setaalarme.h"
#include "printadc.h" 
#include "user.h"
#include "rtc.h"
#include "i2c.h"

#define up 1
#define down 2
#define left 4
#define right 8
#define ok 16
#define cancel 32


char idioma, teste123;
static char estado = 0; // =0 se não for para debug
static char acao;
int debug;
int cont, i;

void main(void) {
    SYSTEM_Initialize();
    textoInit();
    lcdCommand(0x01);
    print(2, 0);
    serialSend('\n');
    while (1) {
        checaAlarme();
        switch (estado) {
            case 0:
                //alarme
                acao = interacao();
                if (acao == down) {
                    estado = 2;
                    lcdCommand(0x01);
                    print(5, 0);
                    serialSend('\n');
                    attData();
                }
                if (acao == up) {
                    estado = 5;
                    lcdCommand(0x01);
                    print(8, 0);
                    serialSend('\n');
                }
                if (acao == ok) {
                    lcdCommand(0x01);
                    setaAlarme();
                }
                break;
            case 1:

                break;

            case 2:
                //data
                acao = interacao();
                if (acao == down) {
                    estado = 3;
                    lcdCommand(0x01);
                    print(6, 0);
                    serialSend('\n');
                    attHora();
                }
                if (acao == up) {
                    estado = 0;
                    lcdCommand(0x01);
                    print(2, 0);
                    serialSend('\n');
                }
                if (acao == ok) {
                    delay(100);
                    lcdCommand(0x01);
                    trocaData();
                }
                break;

            case 3:
                //hora
                attHora();
                acao = interacao();
                if (acao == down) {
                    estado = 5;
                    lcdCommand(0x01);
                    print(8, 0);
                    serialSend('\n');
                }
                if (acao == up) {
                    lcdCommand(0x01);
                    estado = 2;
                    print(5, 0);
                    serialSend('\n');
                    attData();
                }
                if (acao == ok) {
                    delay(100);
                    lcdCommand(0x01);
                    trocaHora();
                }
                break;

//            case 4:
//                //pwm
//                attHora();
//                acao = interacao();
//                if (acao == down) {
//                    estado = 5;
//                    lcdCommand(0x01);
//                    print(8, 0);
//                    serialSend('\n');
//                }
//                if (acao == up) {
//                    estado = 3;
//                    lcdCommand(0x01);
//                    print(6, 0);
//                    serialSend('\n');
//                    attHora();
//                }
//                if (acao == ok) {
//                    //delay(100);
//                    lcdCommand(0x01);
//                    //delay(400);
//                    //pwm();
//                }
//                break;

            case 5:
                //print(8, 0); //ADs
                adcPrint();
                acao = interacao();
                if (acao == down) {
                    estado = 0;
                    lcdCommand(0x01);
                    print(2, 0);
                    serialSend('\n');
                }
                if (acao == up) {
                    estado = 3;
                    lcdCommand(0x01);
                    print(6, 0);
                    serialSend('\n');
                    attHora();
                }
                break;
        }
    }
}