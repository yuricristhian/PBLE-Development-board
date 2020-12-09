#include "rtc.h"
#include "delay.h"
int wait;
unsigned long int i;
//Tempo de estabilização
#define DELAY() delay_us(10);

//Funções do pino conectado ao SDA
/*RB13_High()*/
#define SDA_ON()    SDA_IN() 
#define SDA_OFF()   SDA_OUT(); RB13_Low()
#define SDA()       RB13_Get()
#define SDA_IN()    RB13_In()
#define SDA_OUT()   RB13_Out()

//Funções do pino conectado ao SCL
/*RB12_High()*/
#define SCL_ON()    SCL_IN()
#define SCL_OFF()   SCL_OUT(); RB12_Low()
#define SCL()       RB12_Get()
#define SCL_IN()    RB12_In()
#define SCL_OUT()   RB12_Out()

void i2cInit(void) {
    SDA_IN();
    SCL_IN();
}

void RTCinit(void) {
    RTCwrite(0x00, 0xD7); //sec (bit7 deve ser 1 para se ligar o cristal)
    RTCwrite(0x01, 0x59); //min
    RTCwrite(0x02, 0x23); //hora
    RTCwrite(0x03, 0x06); //dia semana
    RTCwrite(0x04, 0x03); //dia
    RTCwrite(0x05, 0x12); //mes
    RTCwrite(0x06, 0x18); //ano
    RTCwrite(0x07, 0x00); //desabilita ocilador externo para usar cristal
}

//Condição de inicio: Rampa de decida no SDA COM SCL ligado

void startC(void) {
    i2cInit();
    DELAY();
    SDA_OFF();
    DELAY();
    SCL_OFF();
    DELAY();
}

//Condição de inicio: Rampa de subida no SCA COM SCL ligado

void stopC(void) {

    SDA_OUT();
    DELAY();
    SCL_IN();
    DELAY();
    SDA_IN();

}

//Pulso de Clock usado para validar 1 bit

void clkPulse(void) {
    SCL_ON();
    while (SCL() == 0);
    DELAY();
    SCL_OFF();
    DELAY();
}

//Quando 1 Byte é recebido deve-se ceder acesso ao pino SDA para o Slave
//Se o byte foi recebido o Slave leva SDA para nível 0, e aguarda um pulso de Clock

void chekAkB(void) {
    SDA_IN(); //Slave controla o estado do pino, Master verifica
    clkPulse();
    DELAY();
}

void writeByte(unsigned char dados) {
    char i;
    for (i = 7; i >= 0; i--) {
        if (BitTst(dados, i)) {
            SDA_ON();
        } else {
            SDA_OFF();
        }
        DELAY()
        clkPulse();
    }
}

unsigned char readByte() {
    char i;
    int dados;
    dados = 0;
    SDA_IN();
    for (i = 8; i >= 0; i--) {
        DELAY();
        if (SDA()) {
            BitSet(dados, i);
        } else {
            BitClr(dados, i);
        }
        clkPulse();
    }
    return dados;
}

void RTCwrite(unsigned char addr, unsigned char dados) {
    startC();
    writeByte(0xDE); //Endereço do RTC e Escrita
    chekAkB(); //Verifica se recebeu 1 Byte
    writeByte(addr); //Posição da memoria
    chekAkB(); //Verifica se recebeu 1 Byte
    writeByte(dados); //Valor a ser escrito
    chekAkB(); //Verifica se recebeu 1 Byte
    stopC();
}

int RTCread(unsigned char addr) {
    int dados;
    startC();
    writeByte(0xDE); //Endereço do RTC e Leitura
    chekAkB(); //Verifica se recebeu 1 Byte
    writeByte(addr); //Posição da memoria
    chekAkB(); //Verifica se recebeu 1 Byte
    startC();
    writeByte(0xDF); // leitura do endereço anterior
    dados = readByte(); //Valor a ser lido
    stopC();
    return (dados&0x00FF);
}

unsigned char rtcGetSeconds(void) {
    unsigned char value;
    value = RTCread(0x00); // endereço dos segundos
    //return (value);
    return ((((value) >> 4)&0x07)*10 + (value & 0x0f)); //&0x07 para se ignorar o bit7
}

void rtcPutSeconds(unsigned char seconds) {
    RTCwrite(0x00, (seconds % 10) | (((seconds / 10) + 8) << 4));
}

unsigned char rtcGetMinutes(void) {
    unsigned char value;
    value = RTCread(0x01);
    return (((value >> 4)&0x07)*10 + (value & 0x0f));
}

void rtcPutMinutes(unsigned char minutes) {
    RTCwrite(0x01, (minutes % 10) | ((minutes / 10) << 4));
}

unsigned char rtcGetHours(void) {
    unsigned char value;
    value = RTCread(0x02);
    return (((value >> 4)&0x07)*10 + (value & 0x0f));
}

void rtcPutHours(unsigned char hours) {
    RTCwrite(0x02, (hours % 10) | (((hours / 10) + 8) << 4));
}

unsigned char rtcGetDate(void) {
    unsigned char value;
    value = RTCread(0x04);
    return (((value >> 4)&0x03)*10 + (value & 0x0f));
}

void rtcPutDate(unsigned char date) {
    RTCwrite(0x04, (date % 10) | ((date / 10) << 4));
}

unsigned char rtcGetMonth(void) {
    unsigned char value;
    value = RTCread(0x05);
    return ((value >> 4)*10 + (value & 0x0f));
}

void rtcPutMonth(unsigned char month) {
    RTCwrite(0x05, (month % 10) | ((month / 10) << 4));
}

unsigned char rtcGetYear(void) {
    unsigned char value;
    value = RTCread(0x06);
    return (((value >> 4)&0x0f)*10 + (value & 0x0f));
}

void rtcPutYear(unsigned char year) {
    RTCwrite(0x06, (year % 10) | ((year / 10) << 4));
}

unsigned char rtcGetDay(void) {
    unsigned char value;
    value = RTCread(0x03);
    return (value&0x07);
    //return (value & 0x0f); // 1..7
}

void rtcPutDay(unsigned char day) {
    RTCwrite(0x03, day | (0x02 << 4));
}

unsigned char rtcCrystal(void) {
    unsigned char crystal;
    crystal = (RTCread(0x07)&0x20); //lê o bit5
}

