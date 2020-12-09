///* 
// * File:   interact.h
// * Author: isaac
// *
// * Created on 22 de Agosto de 2018, 14:24
// */
//
//
#include "mcc_generated_files/mcc.h"
//#include "keypad.h"
#include "user.h"
//#include "setaalarme.h"
//#include "delay.h"

unsigned char str[30], i = 0, fim = 0, car, act = 0, pos;
char dado = 0;
char start = 0;
unsigned char wait;
unsigned int valores = 0, mult = 1, time;
short int temp;

char interacao(void) {
    while (wait < 253) {
        car = serialRead();
        if (car) {
            serialSend(car);
            if (car == '@') {
                fim = 0;
                start = 1;
                pos = 0;
                wait = 0;
            }
            if (car == '#' && start) {
                fim = pos;
                dado = 1;
                start = 0;
                for(i=0; i<13; i++){
                    serialString("srt:");
                    serialSend(str[i]);
                }
            }
            str[pos] = car;
            if (pos < 12) {
                pos++;
            } else {
                pos = 0;
            }
        } else {
            ADC1_ChannelSelect(0x4);
            ADC1_Start();
            for (time = 0; time < 10000; time++);
            ADC1_Stop();
            while (!ADC1_IsConversionComplete()) {
                ADC1_Tasks();
            }
            temp = ADC1_ConversionResultGet();
            if (temp >= 4000)
                return 0;
            if (temp >= 2035 && temp <= 2055)
                return 2;
            if (temp >= 2720 && temp <= 2740)
                return 8;
            if (temp >= 3060 && temp <= 3080)
                return 16;
            if (temp >= 3265 && temp <= 3285)
                return 32;
            if (temp <= 10)
                return 1;
            delay(100);
        }
        if (dado == 1) {
            if (str[1] == 'C' || str[1] == 'c') {
                serialSend('C');
                config();
            }
            if (str[1] == 'I' || str[1] == 'i') {
                info();
                serialSend('I');
            }
            if (str[1] == 'R' || str[1] == 'r') {
                rstPgm();
                serialSend('R');
            }
            dado = 0;
            fim = 0;
            i = 0;
            for (i = 0; i < 30; i++)
                str[i] = 0;
            return 0;
        }
        if (!start) {
            dado = 0;
            fim = 0;
            i = 0;
            act = checaNav();
            return act;
        }
        wait++;
    }
    return 0;
}

void config(void) {
    //trata o valor desejado
    for (i = (fim-1); i >= 2; i--) {
        if (str[i] == '0' || str[i] == '1' || str[i] == '2' || str[i] == '3' || str[i] == '4' || str[i] == '5' || str[i] == '6' || str[i] == '7' || str[i] == '8' || str[i] == '9') {
            valores += (mult * (str[i] - 48));
            mult = mult * 10;
        }
    }
    serialSend(' ');
    serialNumber(valores);
    serialSend(' ');
    mult = 1;
    //    configura o novo valor no local desejado
    if (str[2] == 'a' || str[2] == 'A') {
        if (str[3] == 'P' || str[3] == 'p') {
            if (valores >= 0 && valores < 4095) {
            }
            setapiso1(valores);
        }
        if (str[3] == 'T' || str[3] == 't') {

            if (valores > 0 && valores <= 4095) {
            }
            setateto1(valores);
        }
        valores = 0;
    } else {
        if (str[2] == 'B' || str[2] == 'b') {
            if (str[3] == 'P' || str[3] == 'p') {

                if (valores >= 0 && valores < 4095) {
                }
                setapiso2(valores);
            }
            if (str[3] == 'T' || str[3] == 't') {

                if (valores > 0 && valores <= 4095) {
                }
                setateto2(valores);
            }
        } else {
            if (str[2] == 'H' || str[2] == 'h') {
                rtcPutHours(((str[3] - 48)*10) + (str[4] - 48));
                rtcPutMinutes(((str[5] - 48)*10) + (str[6] - 48));
                rtcPutSeconds(((str[7] - 48)*10) + (str[8] - 48));
            } else {
                if (str[2] == 'D' || str[2] == 'd') {
                rtcPutDate(((str[3] - 48)*10) + (str[4] - 48));
                rtcPutMonth(((str[5] - 48)*10) + (str[6] - 48));
                rtcPutYear(((str[7] - 48)*10) + (str[8] - 48));
                } else {
                    if (str[2] == 'p' || str[2] == 'p') {

                    } else {
                        if (str[2] == 'I' || str[2] == 'i') {

                        } else {
                            if (str[2] == 'S' || str[2] == 's') {

                            }
                        }
                    }
                }
            }
        }
        valores = 0;
    }
}

void info(void) {
    if (str[2] == 'A' || str[2] == 'a') {

    } else {
        if (str[2] == 'T' || str[2] == 't') {

        } else {
            if (str[2] == 'P' || str[2] == 'p') {

            } else {
                if (str[2] == 'L' || str[2] == 'l') {

                }
            }
        }
    }
}

char checaNav() {
    if (car == 'W' || car == 'w')
        return 1;
    if (car == 'S' || car == 's')
        return 2;
    if (car == 'A' || car == 'a')
        return 4;
    if (car == 'D' || car == 'd')
        return 8;
    if (car == 'Y' || car == 'y')
        return 16;
    if (car == 'N' || car == 'n')
        return 32;
    return 0;
}

void rstPgm(void) {

}
