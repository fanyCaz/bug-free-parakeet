/*
 * FRM_compuertas.c
 *
 * Created: 09/09/2021 10:19:59 a. m.
 * Author : GC-PC
 */ 
#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>
//--Inputs
#define PUSH0 PINB4
#define PUSH1 PINB5
#define STOP PINB6
#define read_PUSH0 bit_is_clear(PINB,PUSH0)
#define read_PUSH1 bit_is_clear(PINB,PUSH1)
#define read_STOP bit_is_clear(PINB, STOP)
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
#define APAGADO      !read_PUSH0 && !read_PUSH1
#define COUNTERCLOCK !read_PUSH0 && read_PUSH1
#define PROCLOCK     read_PUSH0 && !read_PUSH1
#define SEQUENCE     read_PUSH0 && read_PUSH1
#define STOPPED read_STOP

//--Funciones
void init_ports(void);
int main(void)
{
    init_ports();
    while (1) 
    {
		
        //APAGADO
        if (APAGADO)
        {
			if (STOPPED)
			{
				OUTM1_OFF;
				OUTM2_OFF;
				OUTMEN_OFF;
			}else{
				OUTM1_OFF;
				OUTM2_OFF;
				OUTMEN_OFF;
				STOPLIGHT;
			}
        }
        //CCW
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
        //CCW
		
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
		
        //DETENIDO
        else if (SEQUENCE)
        {   int i = 0;
			while (i < 250)
			{
				if (STOPPED)
				{
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
				_delay_ms(20);
			}
// 			SECUENCELIGHT;
//             OUTM1_OFF;
//             OUTM2_ON;
//             OUTMEN_ON;
// 			_delay_ms(5000);
			//for i delay 20 milisegundos cuantas i
			i = 0;
			while (i < 250)
			{
				if (STOPPED)
				{
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
				_delay_ms(20);
			}
// 			OUTM1_ON;
// 			OUTM2_OFF;
// 			OUTMEN_ON;
// 			_delay_ms(5000);
			
        }
    }//FIN while
}//FIN main
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
