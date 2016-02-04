#include <avr/io.h>
#include <stdlib.h>


int main(void){
	uint8_t *data = (uint8_t*) malloc(100 * sizeof(uint8_t));
	
	asm("nop\nnop\nnop");

	volatile int i;
	for(i = 0; i < 101; ++i){
		i++;
	}

	asm("nop\nnop\nnop");

	free(data);



	return 0;
}
