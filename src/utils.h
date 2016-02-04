#pragma once
enum bf_token_t{
		inc_ptr 	= '>',
		dec_ptr 	= '<',
		inc_deref 	= '+', 
		dec_deref	= '-',
		beg_loop	= '[',
		end_loop	= ']',
		read_char	= ',',
		put_char	= '.'
};
auto const asm_inc_deref = "inc r16\nst X, r16 ; \"+\"\n\n";
auto const asm_dec_deref = "dec r16\nst X, r16 ; \"-\"\n\n";
auto const asm_put_char = "out 0x18, r16; \".\"\n\n"; //18h is port b
auto const asm_read_char = "in r16, 0x18\nst X, r16; \",\"\n\n"; //might be wrong. check st instruction
auto const asm_dec_ptr = "dec r26\nld r16, X; \"<\"\n\n";
auto const asm_inc_ptr = "inc r26\nld r16, X; \">\"\n\n";


