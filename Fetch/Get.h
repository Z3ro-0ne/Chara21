#ifndef GET_H
#define GET_H

#include <iostream>
#include <systemc.h>
#include <fstream>

SC_MODULE(Get){

	sc_in<bool> clk;
	sc_out< sc_uint<16> > read;
	ifstream isa_file;

	void fetch(){

		std::string line;
		sc_uint <16> aux;
		std::getline(isa_file, line);
		
		for(int i = 0; i < 16 ; i++){

			aux[i] = line[16-(i+1)]-'0';

		}

		read.write(aux);

	}

	SC_CTOR(Get){

		isa_file.open("ISA.txt");
		SC_METHOD(fetch);
			sensitive << clk.neg();

	}


};

#endif