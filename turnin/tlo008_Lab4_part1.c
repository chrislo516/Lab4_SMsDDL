/*	Author: Macbook
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
enum stateLEDs {startState,init,s0,waitS0,s1,waitS1} stateLED;

void tick(){
 switch(stateLED){			//Transitions
	case startState:		//Initial transition
	    stateLED = init;
	    PORTB = 0x01;
	break;
	
	case init:
	    stateLED = waitS0;
	break;

	case waitS0:
	  if(((PINA&0X01)==0x01)){	//button pressed
	    stateLED = s1;
	  }else if(((PINA&0X01)==0x00)){
	    stateLED = waitS0;
	  }
	break;
	
	case s0:
	  if(((PINA&0X01)==0x01)){      //button pressed
            stateLED = s0;
          }else if(((PINA&0X01)==0x00)){
            stateLED = waitS0;
          }
	break;

	case s1:
	 if(((PINA&0X01)==0x01)){      //button pressed
            stateLED = s1;
          }else if(((PINA&0X01)==0x00)){
            stateLED = waitS1;
          }     
        break;

	case waitS1:
          if(((PINA&0X01)==0x01)){      //button pressed
            stateLED = s0;
          }else if(((PINA&0X01)==0x00)){
            stateLED = waitS1;
          }
	break;
	
	default:
	break;
 }
 switch(stateLED){

	case s0:
	 PORTB = 0x01;
	break;	

	case waitS0:
	break;

	case s1:
	 PORTB = 0x02;
	break;

	case waitS1:
        break;
	
	default:
	break;
 }
}


int main(void) {
    /* Insert DDR and PORT initializations */
    	DDRA = 0x00 ; PORTA = 0xFF;
	DDRB = 0xFF ; PORTB = 0x00;
    /* Insert your solution below */
    while (1) {
	  tick(); 
    }
    return 1;
}
