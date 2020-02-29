#ifndef PC_H
#define PC_H

#include <iostream>
#include <systemc.h>
#include <fstream>
#include <iomanip>
#include <string>

SC_MODULE(PC){

	sc_in_clk clk;
	sc_out< sc_int<12> > read;
	ifstream isa_file;

	void fetch(){

		std::string line;
		sc_int <12> aux;
		std::getline(isa_file, line);

		/*if(isa_file.eof()){

			isa_file.seekg(132, ios::beg);
			
		}*/

		
		for(int i = 0; i < 12 ; i++){

			aux[i] = line[12-(i+1)]-'0';

		}

		if(aux.range(11,8) == 4){// JUMP

			isa_file.seekg(120, ios::beg);

		}

		read.write(aux);

	}

	SC_CTOR(PC){

		isa_file.open("ISA.txt");
		SC_METHOD(fetch);
			sensitive << clk.neg();

	}

	~PC(){

		isa_file.close();
	}


};

#endif