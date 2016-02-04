#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <fstream>
#include <sstream>
#include <streambuf>


#include "utils.h"


std::string read_entire_file(const std::string &filename){
	std::ifstream t(filename);
	std::stringstream buffer;
	buffer << t.rdbuf();
	return buffer.str();
}

void compile(const std::string bf_program, 
				std::vector<std::string> &asm_program,
			   	const std::map<std::string,std::string> &options){
		
	std::stack<int> jump_label_nums;	//stack for [ and ] instructions
	//auto curr_inst = bf_program.begin(); //iterator over instructions
	auto label_num = 1;					//counter for label numbers to avoid conflicts

	//data register option
	if(options.count("data_reg")){
		asm_program.push_back("clr " + options.at("data_reg") + "\n");
	
	} else {
		asm_program.push_back("clr r16\n");
	}

	
	if(options.count("memory_addr")){
		asm_program.push_back("ldi r26, " + options.at("memory_addr") + "\n");
	
	} else {
		asm_program.push_back("ldi r26, 0x60\n");
	}

	asm_program.push_back("main:\n");


	for(const auto &curr_inst : bf_program){
			switch(curr_inst){
				case inc_ptr:
					asm_program.push_back(asm_inc_ptr);
					break;

				case dec_ptr:
					asm_program.push_back(asm_dec_ptr);
					break;

				case inc_deref:
					asm_program.push_back(asm_inc_deref);
					break;

				case dec_deref:
					asm_program.push_back(asm_dec_deref);
					break;

				case beg_loop:
					{
					const auto end_label = "loop_label_end" + std::to_string(label_num); 
					const auto beg_label = "loop_label" + std::to_string(label_num);
					asm_program.push_back("cpi r16,0\nbreq " + end_label + "\n");
					asm_program.push_back(beg_label + ":\n\n");
					jump_label_nums.push(label_num);
					++label_num;
					}
					break;

				case end_loop:
					{
					const auto curr_label_num = jump_label_nums.top();
					jump_label_nums.pop();
					const auto beg_label = "loop_label" + std::to_string(curr_label_num);
					const auto end_label = "loop_label_end" + std::to_string(curr_label_num);
					asm_program.push_back("cpi r16, 0\nbrne " + beg_label + "\n");
					asm_program.push_back(end_label + ":\n");
					}
					break;

				case read_char:
					asm_program.push_back(asm_read_char);
					break;

				case put_char:
					asm_program.push_back(asm_put_char);
					break;
			}
	}

}


//ASM Notes:
//X will contain current data pointer (data space of 256 bytes) 
//Address space starts at 0x025F
//Note that x is r26:r27 with r26 being low byte
//R16 contains value at current data pointer. (updated every time the data pointer changes)
//
//
//

int main(int argc, char **argv){

	const auto bf_program = read_entire_file("main.bf");
	std::vector<std::string> asm_program;	//holds each equiv instruction of the bf

	std::map<std::string,std::string> options = {{"data_reg","r16"}};

	compile(bf_program,asm_program,options);

	for(auto const& instr: asm_program) {
		std::cout << instr;
	} 

	return 0;
}
