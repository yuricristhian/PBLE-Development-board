#include "i2c.h"
#include "delay.h"
#include "mcc_generated_files/mcc.h"
//Fun��es do pino conectado ao SDA
/*RB13_High()*/
#define SDA_ON()    SDA_IN() 
#define SDA_OFF()   SDA_OUT(); RB13_Low()
#define SDA()       RB13_Get()
#define SDA_IN()    RB13_In()
#define SDA_OUT()   RB13_Out()

//Fun��es do pino conectado ao SCL
/*RB12_High()*/
#define SCL_ON()    SCL_IN()
#define SCL_OFF()   SCL_OUT(); RB12_Low()
#define SCL()       RB12_Get()
#define SCL_IN()    RB12_In()
#define SCL_OUT()   RB12_Out()

void i2cInit(void) {
    SDA_IN();
    SCL_IN();
    delay(1);
}

// Hardware-specific support functions that MUST be customized:
#define I2CSPEED 10

void I2C_delay(void) {
    
    delay_us(3);
}

unsigned char read_SCL(void) // Set SCL as input and return current level of line, 0 or 1
{
    SCL_IN();
    return !!SCL();
}

unsigned char read_SDA(void) // Set SDA as input and return current level of line, 0 or 1
{
    SDA_IN();
    return !!SDA();

}

void clear_SCL(void) // Actively drive SCL signal low
{
    SCL_OUT();
    SCL_OFF();
}

void clear_SDA(void) // Actively drive SDA signal low
{
    SDA_OUT();
    SDA_OFF();
}

unsigned char started = 0; // global data

void i2c_start(void) {
    //se j? estiver iniciado, prepara para reenviar o bit de start
    if (started) {
        read_SDA();
        I2C_delay();
        while (read_SCL() == 0); // Clock stretching
        // Repeated start setup time, minimum 4.7us
        I2C_delay();
    }
    if (read_SDA() == 0) {
        //Houve problema de comunica??o
    }
    // SCL is high, set SDA from 1 to 0.
    clear_SDA();
    I2C_delay();
    clear_SCL();
    started = 1;
}

void i2c_stop(void) {
    // set SDA to 0
    clear_SDA();
    I2C_delay();
    while (read_SCL() == 0); // Clock stretching
    I2C_delay();
    if (read_SDA() == 0) {
        //      arbitration_lost();
    }
    I2C_delay();
    started = 0;
}

void i2c_write_bit(unsigned char bit) {
    if (bit) {
        read_SDA();
    } else {
        clear_SDA();
    }
    I2C_delay();
    while (read_SCL() == 0); // Clock stretching
    if (bit && read_SDA() == 0) {
        //Houve problema de comunica??o
    }
    I2C_delay();
    clear_SCL();
    I2C_delay();
}

unsigned char i2c_read_bit(void) {
    unsigned char bit;
    read_SDA();
    I2C_delay();
    while (read_SCL() == 0); // Clock stretching
    bit = read_SDA();
    I2C_delay();
    clear_SCL();
    I2C_delay();
    return bit;
}

// Write a byte to I2C bus. Return 0 if ack by the slave.

unsigned char i2cWriteByte(unsigned char send_start, unsigned char send_stop, unsigned char byte) {
    unsigned char bit;
    unsigned char nack;
    if (send_start) {
        i2c_start();
    }
    for (bit = 0; bit < 8; bit++) {
        i2c_write_bit((byte & 0x80) != 0);
        byte <<= 1;
    }
    nack = i2c_read_bit();
    if (send_stop) {
        i2c_stop();
    }
    return nack;
}

// Read a byte from I2C bus

unsigned char i2cReadByte(unsigned char nack, unsigned char send_stop) {
    unsigned char byte = 0;
    unsigned bit;
    for (bit = 0; bit < 8; bit++) {
        byte = (byte << 1) | i2c_read_bit();
    }
    i2c_write_bit(nack);
    if (send_stop) {
        i2c_stop();
    }
    return byte;
}