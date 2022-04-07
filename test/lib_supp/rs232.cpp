#include <memoire_24.h>

void initialisationUART ( void ) {

// 2400 bauds. Nous vous donnons la valeur des deux

// premiers registres pour vous éviter des complications.

UBRR0H = 0;

UBRR0L = 0xCF;

// permettre la réception et la transmission par le UART0

UCSR0A = 0 ;

UCSR0B |= (1 << RXEN0) | (1 << TXEN0); //RXEN0 pas utile pour le moment, mais utile ulterieurement

// Format des trames: 8 bits, 1 stop bits, sans parité

UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); 

}

void USART_Transmit( unsigned char donnee )
{
/* Wait for empty transmit buffer */
while ( !( UCSR0A & (1<<UDRE0)) )
;
/* Put data into buffer, sends the data */
UDR0 = donnee;
}

unsigned char USART_Receive( void )
{
/* Wait for data to be received */
while ( !(UCSR0A & (1<<RXC0)) )
;
/* Get and return received data from buffer */
return UDR0;
}