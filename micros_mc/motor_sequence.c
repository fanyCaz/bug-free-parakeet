/***************************************************

* Nombre:                                          *

* Eduardo Salazar Treviño                          *

* Estefanía Cáceres Pérez                          *

* Hora clase: M4-M6                                *

* Día: Jueves                                      *

* N° de lista: 3,28                                *

* N° de Equipo: 15                                 *

* Dispositivo: ATMEGA328P                          *

* Rev: 1                                           *

* Propósito de la actividad:                       *

*   Examen de medio curso de Controladores y       * 
*   Microcontroladores Programables                *
*                                                  *

*                            Fecha: 24/09/21       *

***************************************************/ 
#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>
#include <stdbool.h>
//--Inputs
#define PUSH0 PINB4
#define PUSH1 PINB5
#define STOP PINB6
#define BUTTONS PINB
//--Outputs

//Display
#define SEGA PORTD0
#define SEGB PORTD1
#define SEGC PORTD2
#define SEGD PORTD3
#define SEGE PORTD4
#define SEGF PORTD5
#define SEGG PORTD6

#define STOPLIGHT PORTD = 0x38
#define ANTICLOCKLIGHT PORTD = 0x76
#define PROCLOCKLIGHT PORTD = 0x66
#define SECUENCELIGHT PORTD = 0x6D

//Motor
#define OUTM1  PORTB0
#define OUTM2  PORTB1
#define OUTMEN PORTB2

#define OUTM1_ON   PORTB |= _BV(OUTM1)
#define OUTM1_OFF  PORTB &=~_BV(OUTM1)
#define OUTM2_ON   PORTB |= _BV(OUTM2)
#define OUTM2_OFF  PORTB &=~_BV(OUTM2)
#define OUTMEN_ON  PORTB |= _BV(OUTMEN)
#define OUTMEN_OFF PORTB &=~_BV(OUTMEN)

//Main conditions
#define TURNEDOFF       !presionado(PINB4) && !presionado(PINB5)
#define COUNTERCLOCK    !presionado(PINB4) && presionado(PINB5)
#define PROCLOCK        presionado(PINB4)  && !presionado(PINB5)
#define SEQUENCE        presionado(PINB4)  && presionado(PINB5)
//if any other button is not pressed
#define ANYBTNNOTPUSHED !presionado(PINB4) || !presionado(PINB5)
#define STOPPED         presionado(PINB6)

//--Functions
void init_ports(void);
bool presionado(char boton);

int main(void)
{
    init_ports();
    while (1)
    {
        //SEQUENCE 00 - STOPPED
        if (TURNEDOFF)
        {
            OUTM1_OFF;
            OUTM2_OFF;
            OUTMEN_OFF;
            STOPLIGHT;
        }
        //SEQUENCE 01 - CCW
        else if (COUNTERCLOCK)
        {
            if (STOPPED)
            {
                OUTM1_OFF;
                OUTM2_OFF;
                OUTMEN_OFF;
            }else{
                OUTM1_OFF;
                OUTM2_ON;
                OUTMEN_ON;
                ANTICLOCKLIGHT;
            }
        }
        //SEQUENCE 10 - CW
        else if (PROCLOCK)
        {
            if (STOPPED)
            {
                OUTM1_OFF;
                OUTM2_OFF;
                OUTMEN_OFF;
            }else{
                OUTM1_ON;
                OUTM2_OFF;
                OUTMEN_ON;
                PROCLOCKLIGHT;
            }
        }
        //SEQUENCE 11 - LEFT RIGHT ON REPEAT
        else if (SEQUENCE)
        {   
            int i = 0;
            while (i < 250)
            {
                if(ANYBTNNOTPUSHED){
                    i = 251;
                    break;
                }
                if (STOPPED){
                    OUTM1_OFF;
                    OUTM2_OFF;
                    OUTMEN_OFF;
                }else{
                    SECUENCELIGHT;
                    OUTM1_OFF;
                    OUTM2_ON;
                    OUTMEN_ON;
                    i++;
                }
            }
            i = 0;
            while (i < 250)
            {
                if(ANYBTNNOTPUSHED){
                    i = 251;
                    break;
                }
                if (STOPPED){
                    OUTM1_OFF;
                    OUTM2_OFF;
                    OUTMEN_OFF;
                }else{
                    SECUENCELIGHT;
                    OUTM1_ON;
                    OUTM2_OFF;
                    OUTMEN_ON;
                    i++;
                }
            }
        }
    }
}
void init_ports(void)
{
    //Inputs
    DDRB  &= ~(_BV(PUSH0) | _BV(PUSH1) | _BV(STOP)); //Son Entradas
    PORTB |=  (_BV(PUSH0) | _BV(PUSH1) | _BV(STOP)); //Pull up
    //Outputs
    DDRB  |=  ( _BV(OUTM1) | _BV(OUTM2) | _BV(OUTMEN)); //Son salidas
    PORTB &= ~( _BV(OUTM1) | _BV(OUTM2) | _BV(OUTMEN)); // Apagadas (source)
    DDRD |= (SEGA) | _BV(SEGB) | _BV(SEGC) | _BV(SEGD) | _BV(SEGE) | _BV(SEGF) | _BV(SEGG);
    PORTD &= ~(_BV(SEGA) | _BV(SEGB) | _BV(SEGC) | _BV(SEGD) | _BV(SEGE) | _BV(SEGF) | _BV(SEGG));
}

bool presionado(char boton){
    if (bit_is_clear(BUTTONS, boton))
    {
        _delay_ms(10);
        if (bit_is_clear(BUTTONS, boton))
        {
            return true;
        }
    }
    return false;
}