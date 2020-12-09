/* 
 * File:   configuracao.c
 * Author: isaac
 *
 * Created on 11 de Maio de 2018, 21:38
 */
#include "mcc_generated_files/mcc.h"
#include "delay.h"
#include "configuracao.h"
#include "user.h"

int txIdioma(void) {
    char i;
    char acao = 0;
    char idioma = 3;
    char escolhaidioma[] = "PT= ^/w  EN= v/s";
    lcdCommand(0x01);
    delay(10);
    lcdString(escolhaidioma);
    serialString(escolhaidioma);
    delay(10);
    if (i == 8) {
        lcdCommand(0xC0);
    }

    while (!acao) {
        acao = interacao();
        if (acao == 1) {
            idioma = 0;
            serialSend('\n');
        } else {
            if (acao == 2) {
                idioma = 1;
                serialSend('\n');
            } else {
                acao = 0;
            }
        }
    }
    lcdCommand(0x01);
    return idioma;
}