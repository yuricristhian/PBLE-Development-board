/**
  UART1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    uart1.c

  @Summary
    This is the generated driver implementation file for the UART1 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides implementations for driver APIs for UART1.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.75.1
        Device            :  PIC32MM0032GPL028
    The generated drivers are tested against the following:
        Compiler          :  XC32 v2.10
        MPLAB             :  MPLAB X v5.05
 */

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
 */

/**
  Section: Included Files
 */

#include "serial.h"

/**
  Section: UART1 APIs
 */

void serialInit(void) {
    // Set the UART1 module to the options selected in the user interface.

    // STSEL 1; PDSEL 8N; RTSMD disabled; OVFDIS disabled; ACTIVE disabled; RXINV disabled; WAKE disabled; BRGH enabled; IREN disabled; ON enabled; SLPEN disabled; SIDL disabled; ABAUD disabled; LPBACK disabled; UEN TX_RX; CLKSEL PBCLK; 
    // Data Bits = 8; Parity = None; Stop Bits = 1;
    U1MODE = (0x8008 & ~(1 << 15)); // disabling UART ON bit
    // UTXISEL TX_ONE_CHAR; UTXINV disabled; ADDR 0; MASK 0; URXEN disabled; OERR disabled; URXISEL RX_ONE_CHAR; UTXBRK disabled; UTXEN disabled; ADDEN disabled; 
    U1STA = 0x00;
    // BaudRate = 57600; Frequency = 24000000 Hz; BRG 103; 
    U1BRG = 0x67;

    //Make sure to set LAT bit corresponding to TxPin as high before UART initialization
    U1STASET = _U1STA_UTXEN_MASK;
    U1MODESET = _U1MODE_ON_MASK; // enabling UART ON bit
    U1STASET = _U1STA_URXEN_MASK;
}

uint8_t serialRead(void) {
    if (!(U1STAbits.URXDA == 1)) {
        return false;
    }

    if ((U1STAbits.OERR == 1)) {
        U1STACLR = _U1STA_OERR_MASK;
    }

    return U1RXREG;
}

void serialSend(uint8_t txData) {
    while (U1STAbits.UTXBF == 1) {

    }

    U1TXREG = txData; // Write the data byte to the USART.
}

void serialString(char msg[]) {
    int i = 0;
    while (msg[i] != 0) {
        serialSend(msg[i]);
        i++;
    }
}

uint32_t UART1_StatusGet(void) {
    return U1STA;
}

void serialNumber(unsigned long int number) {
    int i = 1000000; //Máximo 9.999.999
    while (i > 0) {
        serialSend((number / i) % 10 + 48);
        i /= 10;
    }
}

