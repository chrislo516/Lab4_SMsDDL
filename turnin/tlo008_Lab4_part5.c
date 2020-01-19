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
enum digitLock {start,init,X,Y,Hash,waitY,unlock,lock} digit;
unsigned char comb[3] = {0x01,0x02,0x01};
unsigned char i = 0;

void tick(){
 switch(digit){ 			//Transitions
	case start:		//Initial transition
	    digit = init;
	    PORTB = 0x00;
	break;
	
	case init:
           if(PINA==0x80)
	     PORTB = 0;
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
	    digit = waitY;
	  }else if((PINA==comb[i])&&(PORTB==0x00)&&(i==2)){
	    digit = unlock; break;
	  }else if((PINA==comb[i])&&(PORTB==0x01)&&(i==2)){
	    digit = lock; break;
	  }else if((PINA==0x01)){
	    digit = X; break;
	  }else if((PINA==0x02)){
	    digit = Y; break;	   
          }else{
	    digit = init; break;
	  }
	
	case X:
	  if(PINA==0){
	    digit = waitY;
	  }else if(PINA==0x01){		//still pressing
	    digit = X;
	    i = i-1;
	  }
	break;

	case Y:
	  if(PINA==0){
	    digit = waitY;
	  }else if(PINA==0x02){
	    digit = Y;
            i = i-1;
	  }
	break;

	case unlock:
	  if((PINA&0x80)==0x80){
	   digit = init;
	   i = 0; break;
	  }else{
	   digit = unlock; break;
	  }

	case lock:
	  digit = init;
	  i = 0; 
	break;

	default:
	break;
 }
 switch(digit){

	case start:
	  PORTC = 0x01;
	  i = 0;
          PORTB = 0;
	break;	

	case init:
	  PORTC = 0x02;
	break;

	case Hash:
	  PORTC = 0x03;
	break;

	case waitY:
	  PORTC = 0x04;
	break;
	
	case X:
	  i = i+1;
	  PORTC = 0x05;
	break;
	
	case Y:
	  i = i+1;
	  PORTC = 0x06;
	break;

	case unlock:
	 PORTC = 0x07;
         PORTB = 0x01;
	break;
	
	case lock:
	 PORTC = 0x08;
	 PORTB = 0x00;
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
