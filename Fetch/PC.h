#ifndef PC_H
#define PC_H

#include <iostream>
#include <systemc.h>
#include <fstream>
#include <iomanip>
#include <string>

SC_MODULE(PC){

	sc_in_clk clk;
	sc_out< sc_int<8> > read;
	ifstream isa_file;

	void fetch(){

		std::string line;
		sc_int <8> aux;
		std::getline(isa_file, line);
		
		for(int i = 0; i < 8 ; i++){

			aux[i] = line[8-(i+1)]-'0';

		}

		if(aux.range(7,4) == 5){// JUMP

			isa_file.seekg(88, ios::beg);

		}

		read.write(aux);

	}

	SC_CTOR(PC){

		isa_file.open("ISA.txt");
		SC_METHOD(fetch);
			sensitive << clk;

	}

	~PC(){

		isa_file.close();
	}


};

#endif