#include "uart.h"

#include "uart.h"
#include <avr/pgmspace.h>

const uint8_t asciiNumbers[] PROGMEM = {0x30, 0x31, 0x32, 0x33, 0x34,
                                        0x35, 0x36, 0x37, 0x38, 0x39};

void uartSend(uint8_t data) {
  while (!(UCSR0A & (1 << UDRE0)))
    ;
  UDR0 = data;
}

long pow(uint8_t base, uint8_t exponent) {
  long number = base;
  for (uint8_t i = 1; i < exponent; i++) number *= base;
  return number;
}

uint32_t pow_unsigned(uint8_t base, uint8_t exponent) {
  uint32_t number = base;
  for (uint8_t i = 1; i < exponent; i++) number *= base;
  return number;
}

void uart::init() {
  // 2400 bauds.
  UBRR0H = 0;
  UBRR0L = 0xCF;

  // allow reception and transmission via UART0
  UCSR0A = 0;
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);
  // 8 bits, 1 stop bits, none parity
  UCSR0C = (0 << USBS0) | (3 << UCSZ00) | (0 << UPM00) | (0 << UMSEL00);
}

void uart::print(const char *c, const uint8_t size) {
  for (uint8_t i = 0; i < size; i++) {
    uartSend(c[i]);
  }
}

void uart::print(const char *c) {
  uint8_t i = 0;
  while (c[i] != '\0') {
    uartSend(c[i]);
    i++;
  }
}

uint8_t uart::readData(){
  while ( !(UCSR0A & (1<<RXC0)) );
  /* Get and return received data from buffer */
  return UDR0;
}

void uart::print(const char c) { uartSend(c); }

void uart::print(const int n) {
  uint8_t size = 1;
  int num = n;
  if (n < 0) {
    num *= -1;
    uartSend('-');
  }
  uint8_t rem;
  while (pow(10, size) <= num) {
    size++;
  }
  uint8_t digits[size];
  for (uint8_t i = 0; i < size; i++) {
    rem = num % 10;
    num = num / 10;
    digits[i] = pgm_read_byte(&asciiNumbers[rem]);
  }
  for (int i = (size - 1); i >= 0; i--) {
    uartSend(digits[i]);
  }
}

void uart::print(const uint8_t n) { print((int)n); }

void uart::print(const long n) {
  uint8_t size = 1;
  long num = n;
  if (n < 0) {
    num *= -1;
    uartSend('-');
  }
  uint8_t rem;
  while (pow(10, size) <= num) {
    size++;
  }
  uint8_t digits[size];
  for (uint8_t i = 0; i < size; i++) {
    rem = num % 10;
    num = num / 10;
    digits[i] = pgm_read_byte(&asciiNumbers[rem]);
  }
  for (int i = (size - 1); i >= 0; i--) {
    uartSend(digits[i]);
  }
}

void uart::print(const uint16_t n) { print((long)n); }

void uart::print(const uint32_t n) {
  uint8_t size = 1;
  uint32_t num = n;
  if (n < 0) {
    num *= -1;
    uartSend('-');
  }
  uint8_t rem;
  while (pow_unsigned(10, size) <= num) {
    size++;
  }
  uint8_t digits[size];
  for (uint8_t i = 0; i < size; i++) {
    rem = num % 10;
    num = num / 10;
    digits[i] = pgm_read_byte(&asciiNumbers[rem]);
  }
  for (int i = (size - 1); i >= 0; i--) {
    uartSend(digits[i]);
  }
}

void uart::println() { uartSend('\n'); }

void uart::clear(){
  uart::print("\033[2J\033[;H");
}
