#ifndef F_CPU
#define F_CPU 16000000UL
#endif

//Define BAUD rate
#define BAUD 57600
#include <util/setbaud.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Configuring UART Communication in order to send data to the serial monitor
void Serial_init(void)
{
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

#if USE_2X
    UCSR0A |= _BV(U2X0);
#else
    UCSR0A &= ~(_BV(U2X0));
#endif
    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */
}

void Serial_write(unsigned char c)
{
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
}

void SPI_init(){
  // SET MISO as output
  DDRB |= (1 << PB4);
  // Enable MOSI, SS and SCK as input
   DDRB &= ~((1 << PB2)|(1 << PB3)|(1 << PB5));
   // Enable SPI and SPI interrupt
  SPCR |= (1<<SPE)|(1<<SPIE);
  // Not master
  SPCR &= ~(1<<MSTR);

  // Global SPI function
  sei();
}

/*Interrupt when SPI communication is received*/
ISR(SPI_STC_vect)
{
  cli();
  // command is stored in SPDR
  unsigned char command = SPDR;
  command &= ~(1 << 7); 
  processCommand(command);
  sei();
}  

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

// commands
const unsigned char WALK = 1;
const unsigned char WALK_BACK = 31;
const unsigned char STOP = 15;
const unsigned char TURNL = 3;
const unsigned char TURNR = 7;

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

void stopWheels(){
    stopWheel1();
    stopWheel2();
    stopWheel3();
    stopWheel4();
}

void processCommand(unsigned char command){
  switch(command){
    case WALK:
      Serial_write('w');
      moveFoward();
      break;
    case WALK_BACK:
      Serial_write('b');
      reverse();
      break;
    case STOP:
      Serial_write('s');
      stopWheels();
      break;
    case TURNL:
      Serial_write('l');
      turnLeft();
      break;
    case TURNR:
      Serial_write('r');
      turnRight();
      break;
  }
}

int main(){
 Serial_init();
 SPI_init();
 setupWheels();
  
  while(1);
 return 0; 
}
