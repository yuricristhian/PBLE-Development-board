/* 
 * File:   lcd.c
 *
 * Modded by Isaac on 17 de Outubro de 2018, 17:17
 */


/*#include "so.h"
#include "io.h"*/
#include "mcc_generated_files/mcc.h"
#include "lcd.h"
//RS = 19 = RC9
//EN = 18 = RB9
//dados RA4 RB4 RB11 RB10
char LCD_RS_PIN = 0xC9;
char line, col;
_Bool rs;
int value;

void soInit(void) {
    BitClr(TRISA, 4);
    BitClr(TRISB, 4);
    BitClr(TRISB, 11);
    BitClr(TRISB, 10);
    BitClr(TRISC, 9);
    BitClr(TRISB, 9);
}

void delayMicro(int a) {
    volatile int i;
    for (i = 0; i < (a * 20); i++);
}

void delayMili(int a) {
    volatile int i;
    for (i = 0; i < a; i++) {
        delayMicro(100);
    }
}
//Gera um clock no enable

void pulseEnablePin() {
    BitSet(PORTB, 9);
    delayMicro(10);
    BitClr(PORTB, 9);
    delayMicro(10);
}
//Envia 4 bits e gera um clock no enable

//void pushNibble(char value, int rs) {
//    pushByte(value);
//    digitalWrite(LCD_RS_PIN, rs);
//    pulseEnablePin();
//}
//Envia 8 bits em dois pacotes de 4

void pushByte(char val) {
    if (BitTst(val, 4))
        BitSet(PORTB, 10);
    else
        BitClr(PORTB, 10);
    if (BitTst(val, 5))
        BitSet(PORTB, 11);
    else
        BitClr(PORTB, 11);
    if (BitTst(val, 6))
        BitSet(PORTB, 4);
    else
        BitClr(PORTB, 4);
    if (BitTst(val, 7))
        BitSet(PORTA, 4);
    else
        BitClr(PORTA, 4);
    pulseEnablePin();
    if (BitTst(val, 0))
        BitSet(PORTB, 10);
    else
        BitClr(PORTB, 10);
    if (BitTst(val, 1))
        BitSet(PORTB, 11);
    else
        BitClr(PORTB, 11);
    if (BitTst(val, 2))
        BitSet(PORTB, 4);
    else
        BitClr(PORTB, 4);
    if (BitTst(val, 3))
        BitSet(PORTA, 4);
    else
        BitClr(PORTA, 4);
    pulseEnablePin();
    BitClr(PORTA, 4);
    BitClr(PORTB, 4);
    BitClr(PORTB, 11);
    BitClr(PORTB, 10);
}
void lcdCommand(char value) {
    BitClr(PORTC, 9);
    pushByte(value);
    delayMili(5);
}

void lcdPosition(int line, int col) {
    if (line == 0) {
        //        BitSet(PORTA, 4);
        //        BitClr(PORTB, 4);
        //        BitClr(PORTB, 11);
        //        BitClr(PORTB, 10);
        //
        //        BitClr(PORTC, 9);
        //        pulseEnablePin();
        //
        //        BitClr(PORTA, 4);
        //        BitClr(PORTB, 4);
        //        BitClr(PORTB, 11);
        //        BitClr(PORTB, 10);
        //
        //        BitClr(PORTC, 9);
        //        pulseEnablePin();
        lcdCommand(0x80 + (col % 16));
    }
    if (line == 1) {
        //        BitSet(PORTA, 4);
        //        BitSet(PORTB, 4);
        //        BitClr(PORTB, 11);
        //        BitClr(PORTB, 10);
        //
        //        BitClr(PORTC, 9);
        //        pulseEnablePin();
        //
        //        BitClr(PORTA, 4);
        //        BitClr(PORTB, 4);
        //        BitClr(PORTB, 11);
        //        BitClr(PORTB, 10);
        //
        //        BitClr(PORTC, 9);
        //        pulseEnablePin();
        lcdCommand(0xC0 + (col % 16));
    }
}

void lcdChar(char value) {
    BitSet(PORTC, 9);
    pushByte(value);
    delayMicro(40);
}
//Imprime um texto (vetor de char)

void lcdString(char msg[]) {
    int i = 0;
    while (msg[i] != 0) {
        lcdChar(msg[i]);
        i++;
    }
}

void lcdNumber(unsigned long int value) {
    int i = 1000000; //Máximo 99.999
    while (i > 0) {
        lcdChar((value / i) % 10 + 48);
        i /= 10;
    }
}
// Rotina de incialização

void lcdInit() {
    BitClr(TRISB, 9);
    BitClr(TRISC, 9);
    BitClr(PORTC, 9);
    soInit();
    delayMili(30);
    // Comunicação começa em estado incerto
    pushByte(0x03);
    delayMili(5);
    pushByte(0x03);
    delayMicro(80);
    pushByte(0x03);
    delayMicro(80);
    // Mudando comunicação para 4 bits
    pushByte(0x02);
    delayMili(10);
    // Configura o display
    lcdCommand(0x28); //8bits, 2 linhas, fonte: 5x8
    lcdCommand(0x08 + 0x04); //display on
    lcdCommand(0x01); //limpar display, voltar p/ posição 0
}
