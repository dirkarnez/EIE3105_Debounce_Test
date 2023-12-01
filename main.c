#include <avr/io.h>
#include <string.h>

void usart_init()
{
	UCSR0B = (1<<TXEN0) | (1<<RXEN0);
	UCSR0C = (1<<UCSZ00) | (1<<UCSZ01);
	UBRR0L = 0xCF; 
}

void usart_send(unsigned char ch)
{
	while(!(UCSR0A &(1<<UDRE0)));
	UDR0 = ch;
}

void usart_read(unsigned char* ptr_ch)
{
	while(!(UCSR0A & (1<<RXC0)));
	*ptr_ch = UDR0;
}


void print(char* message, size_t length) {
	for (unsigned char i = 0; i <= length; i++) {
		usart_send(*(message + i));
	}
}

int main(void)
{
	DDRB = 0x00;
	
	DDRD = 0xFF;
	PORTD = 0x00;
	
	unsigned char last_state = 0;
	unsigned char current_pb = 0;
	unsigned char previous_pb = 0;
	char o[] = "o\n";
	char f[] = "f\n";

	usart_init();

	while (1) {
		current_pb = PINB;
		
		
		if (((current_pb > 1) && ((previous_pb & 0x10) == 0) )) {
			print(o, strlen(o));

			if (last_state == 0) {
				last_state = 1;
				PORTD = 0xFF;
			} else if (last_state == 1) {
				last_state = 0;
				PORTD = 0x00;
			}
		} else {
			print(f, strlen(f));
		}
		previous_pb = current_pb;
	}
	
	// while (1) {
	// 	current_pb = PINB;
		
		
	// 	if (((current_pb & 0x10) == 0x10) && ((previous_pb & 0x10) == 0x00) ) {
	// 		if (last_state == 0) {
	// 			last_state = 1;
	// 			PORTD = 0xFF;
	// 		} else if (last_state == 1) {
	// 			last_state = 0;
	// 			PORTD = 0x00;
	// 		}
	// 	}
	// 	previous_pb = current_pb;
	// }
}