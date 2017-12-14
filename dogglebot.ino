#include <avr/io.h>
#include <util/delay.h>

/*setting pins for wheels*/
// Wheel 1 (back left)
int wheel1A = PC1;
int wheel1B = PC0;
// Wheel 2 (back right)
int wheel2A = PC5;
int wheel2B = PC4;
// Wheel 3 (front right)
int wheel3A = PD4;
int wheel3B = PD5;
// Wheel 4 (front left)
int wheel4A = PC2;
int wheel4B = PC3;

void setupWheels(){
  DDRC |= (1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3) | (1 << PC4) | (1 << PC5);
  DDRD |= (1 <<  PD4) | (1 << PD5);
}

void moveWheel1(bool reverse){
  if(!reverse)
    PORTC |= (0 << wheel1A) | (1<< wheel1B);
  else
    PORTC |= (1 << wheel1A) | (0<< wheel1B);
}

void moveWheel2(bool reverse){
  if(!reverse)
    PORTD |= (1 << wheel3A) | (0 <<wheel3B);
  else
    PORTD |= (0 << wheel3A) | (1 << wheel3B);
}


void moveWheel3(bool reverse){
  if(!reverse)
    PORTC |= (0 << wheel4A) | (1<< wheel4B);
  else
    PORTC |= (1 << wheel4A) | (0<< wheel4B) ;
}

void moveWheel4(bool reverse){
  if(!reverse)
    PORTC |= (0 << wheel2A) | (1<< wheel2B) ;
  else
    PORTC |= (1 << wheel2A) | (0<< wheel2B) ;
}

void stopWheel1(){
  PORTC |= (0 << wheel1A) | (0<< wheel1B);
}

void stopWheel2(){
  PORTD |= (0 << wheel3A) | (0 <<wheel3B);
}


void stopWheel3(){
  PORTC |= (0 << wheel4A) | (0<< wheel4B);
}

void stopWheel4(){
  PORTC |= (0 << wheel2A) | (0<< wheel2B) ;
}

void moveFoward(){
    moveWheel1(false);
    moveWheel2(false);
    moveWheel3(false);
    moveWheel4(false);
}

void turnLeft(){
    stopWheel1();
    moveWheel2(false);
    stopWheel3();
    moveWheel4(false);
}

void turnRight(){
    moveWheel1(false);
    stopWheel2();
    moveWheel3(false);
    stopWheel4();
}

void reverse(){
    moveWheel1(true);
    moveWheel2(true);
    moveWheel3(true);
    moveWheel4(true);
}

int main(){
 setupWheels();
  
  while(1)
    reverse();
 return 0; 
}
