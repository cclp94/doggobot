#include <avr/io.h>
#include <util/delay.h>

/*setting pins for wheels*/
// Wheel 1 (back right)
int wheel1A = PC1;
int wheel1B = PC0;
// Wheel 2 (back left)
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

void moveFoward(){
    PORTC |= (0 << wheel1A) | (1<< wheel1B) | (0 << wheel2A) | (1<< wheel2B) | (0 << wheel4A) | (1<< wheel4B);
    PORTD |= (1 << wheel3A) | (0 <<wheel3B);
}

int main(){
 setupWheels();
  
  while(1)
    moveFoward();
 return 0; 
}
