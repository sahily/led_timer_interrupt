/*
 * led_timer_interrupt.c
 *
 * Created: 4/7/2019 2:11:54 PM
 * Author : Sahil S. Mahajan
 * Description: Blinks LED using timer interrupt
 *
 */

#include <REG51F.H>

void init(void);
void configureTimer0(void);
void enableInterrupt(void);
void resetTimer0(void);

#define TRIGGER 10          //the number of timer overflow iterations before turning LED on/off
sbit pin = P0^7;

unsigned int x;             //used for the timer overflow iterations




void main()
{
    init();
    configureTimer0();
    enableInterrupt();
    while(1);
}


/* -----------------
 * Function: init
 * -----------------
 *
 * initializes system and variables
 *
 */

void init(void)
{
    P0 = 0x00;      //clear display
    x = 0;  
}


/* -----------------
 * Function: configureTimer0
 * -----------------
 *
 * sets up Timer 0 and enables timer interrupt
 *
 */

void configureTimer0(void)
{
    TMOD = 0x01;            //use Timer 0 in 16-bit Timer operating mode
    resetTimer0();          //load timer0 start value
    TR0 = 1;                //start Timer 0
    ET0 = 1;                //enable Timer 0 overflow interrupt
}


/* -----------------
 * Function: enableInterrupt
 * -----------------
 *
 * enables all interrupts that has their individual interrupt bit enabled
 *
 */

void enableInterrupt(void)
{
    EA = 1;
}


/* -----------------
 * Function: resetTimer0
 * -----------------
 *
 * loads Timer 0's 16 bit count register with start value
 *
 */

void resetTimer0(void)
{
    TH0 = 0x4C;
    TL0 = 0x00;     
}


/* --------------------------------------
 * Interrupt Service Routine: Timer 0 Interrupt
 * --------------------------------------
 *
 * Runs each time timer 0 interrupt is generated 
 *
 * resets Timer 0's count register to start value, and complements LED pin when certain number of iterations has been reached
 *
 */

void isr_t0() interrupt 1
{
    resetTimer0();
    x++;
    if(x==TRIGGER)
    {
        pin = ~pin;
        x = 0;
    }
}