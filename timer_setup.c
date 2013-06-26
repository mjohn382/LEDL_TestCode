#include <msp430.h>
#include <string.h>
#include <stdio.h>
#include "uart.h"
#include "ctl.h"


void timersetup(void){
//setting up timer (create more comments that will reference pictures and give more details to exactly what is happening.)
TACTL = TASSEL_1 | ID_3; // using ACLK for timer, dividing timer by 8 timer is ~4KHz , 
//since the timer is opperating at ~4KHz, the timer can count to 4000 to make the frequncy of ~1Hz
TACCR0 = 4000;
TACCR1 = 3750; 
TACCTL1 = OUTMOD_3 ; //

P2SEL |= BIT3;//this bit is the visual output pin that shows the high out pin from the timer
P2DIR |= BIT3;//

TACTL |= MC_1; // in up mode counts to TACCR0,
}


void timersetup4kHz(void){
//setting up timer (create more comments that will reference pictures and give more details to exactly what is happening.)
TACTL = TASSEL_1 | ID_0; // using ACLK for timer, dividing timer by 1 timer is ~32KHz , 
//since the timer is opperating at ~32KHz, the timer can count to  to make the frequncy of ~4000Hz
TACCR0 = 8;
TACCR1 = 6; 
TACCTL1 = OUTMOD_3 ; //

P2SEL |= BIT3;//this bit is the visual output pin that shows the high out pin from the timer
P2DIR |= BIT3;//

TACTL |= MC_1; // in up mode counts to TACCR0,
}


//The following three functions I pulled from Jesse Code, If these are used all timer functions have to be used in continuous mode
//use majority function so the timer
//can be read while it is running
short readTA(void){
  int a=TAR,b=TAR,c=TAR;
  return (a&b)|(a&c)|(b&c);
}

//setup timer A to run off 32.768kHz xtal
void init_timerA(void){
  //setup timer A 
  TACTL=TASSEL_1|ID_0|TACLR;//AClK|divide the clock by 1 ~32 kHz
  //init CCR0 for tick interrupt
  TACCR0=32;
  TACCTL0=CCIE; 
  TACCR1=4;
  TACCTL1=CCIE|OUTMOD_4;
}

//start timer A in continuous mode
void start_timerA(void){
//start timer A
  TACTL|=MC_2;
}

//================[Time Tick interrupt]=========================
void task_tick(void) __ctl_interrupt[TIMERA0_VECTOR]{
  //set rate to 1024Hz
  TACCR0+=32;
  //increment timer
  ctl_increment_tick_from_isr();
}


void task_tick_forADC(void) __ctl_interrupt[TIMERA1_VECTOR]{
  switch(TAIV){
  case TAIV_TACCR1:
  //set rate to 8000Hz to change this later on, change the 4 to approperaite time interval
  TACCR1+=16000;
  //increment timer
  break;
}

}
