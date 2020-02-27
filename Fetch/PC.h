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

		if(isa_file.eof()){

			isa_file.seekg(72, ios::beg);
			
		}

		
		for(int i = 0; i < 12 ; i++){

			aux[i] = line[12-(i+1)]-'0';

		}

		std::cout<<"PC REPORTING"<<std::endl;
		for(int i = 0; i < 12; i++){

			std::cout<< aux.range(12-(i+1),12-(i+1));

		}

		read.write(aux);

		std::cout<<"\n";


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