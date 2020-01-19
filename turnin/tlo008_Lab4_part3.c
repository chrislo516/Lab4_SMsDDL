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
enum digitLock {start,init,Hash,waitY,unlock} digit;

void tick(){
 switch(digit){ 			//Transitions
	case start:		//Initial transition
	    digit = init;
	    PORTB = 0x00;
	break;
	
	case init:
	  if(PINA==0x04){	//PA2 button pressed
	    digit = Hash; break;
	  }else{
	    digit = init; break;
	  }

	case Hash:
	  if(PINA==0x04) { 
	    digit = Hash; break; 
	  }else if(PINA==0x00){
	    digit = waitY; break;
	  }else{
	    digit = init; break;
	  }

	case waitY:
          if((PINA==0x04)||(PINA==0)){
	    digit = waitY; break;
	  }else if(PINA==0x02){
	    digit = unlock; break;
	  }else{
	    digit = init; break;
	  } 
	
	case unlock:
	  if((PINA&0x80)==0x80){
	   digit = start; break;
	  }else{
	   digit = unlock; break;
	  }

	default:
	break;
 }
 switch(digit){

	case start:
	  PORTC = 0x01;
	break;	

	case init:
	  PORTC = 0x02;
	break;

	case Hash:
	  PORTC = 0x03;
	break;

	case waitY:
	  PORTC = 0x04
	break;
	
	case unlock:
	 PORTC = 0x05;
	 PORTB = 0x01;
	break;

	default:
	break;
 }
}


int main(void) {
    /* Insert DDR and PORT initializations */
    	DDRA = 0x00 ; PORTA = 0xFF;
	DDRB = 0xFF ; PORTB = 0x00;
	DDRC = 0xFF ; PORTC = 0x00;
    /* Insert your solution below */
    while (1) {
	  tick(); 
    }
    return 1;
}
