/* 
 * File:   texto.c
 * Author: isaac
 *
 * Created on 11 de Maio de 2018, 20:18
 */
#include "mcc_generated_files/mcc.h"
#include "delay.h"
#include "configuracao.h"
#include "texto.h"

unsigned char caracter;
unsigned char idioma2;
unsigned char textos [16][16];

char txt(void) {
    return idioma2;
}

void textoInit(void) {

    idioma2 = txIdioma();

    if (idioma2 == 0) {

        unsigned char PT1[] = "   Bem vindo!  "; //00
        unsigned char PT2[] = "NavegueCom ^<v>"; //01
        unsigned char PT3[] = "     Alarme    "; //02
        unsigned char PT4[] = "   ^  <  v  >  "; //03
        unsigned char PT6[] = "      Data     "; //05
        unsigned char PT7[] = "      Hora     "; //06
        unsigned char PT8[] = "      PWM      "; //07
        unsigned char PT9[] = "      ADCs      "; //08
        unsigned char PT10[] = "  Piso:  Teto:"; //09
        unsigned char PT11[] = " Alarme 1: ^/w"; //010
        unsigned char PT12[] = " Alarme 2: v/s"; //011
        unsigned char PT13[] = "  Problema no "; //012
        unsigned char PT14[] = "Alarme 1      "; //013
        unsigned char PT15[] = "Alarme 2      "; //014

        //Salva os textos em uma matriz
        for (caracter = 0; caracter < 15; caracter++) {
            textos[0][caracter] = PT1[caracter];
        }
        for (caracter = 0; caracter < 15; caracter++) {
            textos[1][caracter] = PT2[caracter];
        }

        for (caracter = 0; caracter < 15; caracter++) {
            textos[2][caracter] = PT3[caracter];
        }
        for (caracter = 0; caracter < 15; caracter++) {
            textos[3][caracter] = PT4[caracter];
        }
        for (caracter = 0; caracter < 15; caracter++) {
            textos[5][caracter] = PT6[caracter];
        }
        for (caracter = 0; caracter < 15; caracter++) {
            textos[6][caracter] = PT7[caracter];
        }
        for (caracter = 0; caracter < 15; caracter++) {
            textos[7][caracter] = PT8[caracter];
        }
        for (caracter = 0; caracter < 15; caracter++) {
            textos[8][caracter] = PT9[caracter];
        }
        for (caracter = 0; caracter < 15; caracter++) {
            textos[9][caracter] = PT10[caracter];
        }
        for (caracter = 0; caracter < 15; caracter++) {
            textos[10][caracter] = PT11[caracter];
        }
        for (caracter = 0; caracter < 15; caracter++) {
            textos[11][caracter] = PT12[caracter];
        }
        for (caracter = 0; caracter < 15; caracter++) {
            textos[12][caracter] = PT13[caracter];
        }
        for (caracter = 0; caracter < 15; caracter++) {
            textos[13][caracter] = PT14[caracter];
        }
        for (caracter = 0; caracter < 15; caracter++) {
            textos[14][caracter] = PT15[caracter];
        }
    }
    if (idioma2 == 1) {

        unsigned char EN1[] = "   Welcome!!!  "; //00
        unsigned char EN2[] = " ^<v> ToSelect "; //01
        unsigned char EN3[] = "     Alarm     "; //02
        unsigned char EN4[] = "   ^  <  v  >  "; //03
        unsigned char EN6[] = "       Date     "; //05
        unsigned char EN7[] = "       Hour     "; //06
        unsigned char EN8[] = "       PWM      "; //07
        unsigned char EN9[] = "      ADCs      "; //08
        unsigned char EN10[] = "Lower: Higher:"; //09
        unsigned char EN11[] = " Alarm 1: ^/w "; //010
        unsigned char EN12[] = " Alarm 2: v/s "; //011
        unsigned char EN13[] = "  Problem at  "; //012
        unsigned char EN14[] = "Alarm 1       "; //013
        unsigned char EN15[] = "Alarm 2       "; //014

        //Salva os textos em uma matriz
        for (caracter = 0; caracter < 15; caracter++) {
            textos[0][caracter] = EN1[caracter];
        }
        for (caracter = 0; caracter < 15; caracter++) {
            textos[1][caracter] = EN2[caracter];
        }

        for (caracter = 0; caracter < 15; caracter++) {
            textos[2][caracter] = EN3[caracter];
        }
        for (caracter = 0; caracter < 15; caracter++) {
            textos[3][caracter] = EN4[caracter];
        }
        for (caracter = 0; caracter < 15; caracter++) {
            textos[5][caracter] = EN6[caracter];
        }
        for (caracter = 0; caracter < 15; caracter++) {
            textos[6][caracter] = EN7[caracter];
        }
        for (caracter = 0; caracter < 15; caracter++) {
            textos[7][caracter] = EN8[caracter];
        }
        for (caracter = 0; caracter < 15; caracter++) {
            textos[8][caracter] = EN9[caracter];
        }
        for (caracter = 0; caracter < 15; caracter++) {
            textos[9][caracter] = EN10[caracter];
        }
        for (caracter = 0; caracter < 15; caracter++) {
            textos[10][caracter] = EN11[caracter];
        }
        for (caracter = 0; caracter < 15; caracter++) {
            textos[11][caracter] = EN12[caracter];
        }
        for (caracter = 0; caracter < 15; caracter++) {
            textos[12][caracter] = EN13[caracter];
        }
        for (caracter = 0; caracter < 15; caracter++) {
            textos[13][caracter] = EN14[caracter];
        }
        for (caracter = 0; caracter < 15; caracter++) {
            textos[14][caracter] = EN15[caracter];
        }
    }
    print(0, 0);
    serialSend('\n');
    delay(500);
    print(1, 1);
    serialSend('\n');
    delay(2000);
}

void print(char texto, char linha) {

    //Printa o texto escolhido
    if (linha == 0) {
        lcdPosition(0, 0);
        delay(10);
        for (caracter = 0; caracter < 14; caracter++) {
            lcdChar(textos[texto][caracter]);
            serialSend(textos[texto][caracter]);
            delay(10);
        }
    }
    if (linha == 1) {
        lcdPosition(1, 0);
        delay(10);
        for (caracter = 0; caracter < 14; caracter++) {
            lcdChar(textos[texto][caracter]);
            serialSend(textos[texto][caracter]);
            delay(10);
        }
    }
}