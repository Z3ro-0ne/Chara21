#ifndef PC_H
#define PC_H

#include <iostream>
#include <systemc.h>
#include <fstream>

SC_MODULE(PC){

	sc_in<bool> clk;
	sc_out< sc_int<12> > read;
	ifstream isa_file;
	//int pc = 0;

	void fetch(){

		std::string line;
		sc_int <12> aux;
		std::getline(isa_file, line);

		//pc++;

		if(isa_file.eof()){

			isa_file.seekg(72, ios::beg);
			
		}

		std::cout<<line<<std::endl;
		
		for(int i = 0; i < 12 ; i++){

			aux[i] = line[12-(i+1)]-'0';

		}

		//AQUI IRIA LA CONDICIONAL DE REPETIR..AKA...MOVER EL PUNTERO DEL ARCHIVO AL PUNTO DONDE SE MODIFICAN LOS TERMOMETROS

		read.write(aux);

		std::cout<<"PC REPORTING"<<std::endl;
		for(int i = 0; i < 12; i++){

			std::cout<< aux.range(12-(i+1),12-(i+1));

		}

		std::cout<<"\n";


	}

	SC_CTOR(PC){

		isa_file.open("ISA.txt");
		SC_METHOD(fetch);
			sensitive << clk;

	}


};

#endif