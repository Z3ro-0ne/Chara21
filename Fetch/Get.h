#ifndef GET_H
#define GET_H

#include <iostream>
#include <systemc.h>
#include <fstream>

SC_MODULE(Get){

	sc_in<bool> clk;
	sc_out< sc_int<12> > read;
	ifstream isa_file;

	void fetch(){

		std::string line;
		sc_int <12> aux;
		std::getline(isa_file, line);
		
		for(int i = 0; i < 12 ; i++){

			aux[i] = line[12-(i+1)]-'0';

		}

		//AQUI IRIA LA CONDICIONAL DE REPETIR..AKA...MOVER EL PUNTERO DEL ARCHIVO AL PUNTO DONDE SE MODIFICAN LOS TERMOMETROS

		read.write(aux);

	}

	SC_CTOR(Get){

		isa_file.open("ISA.txt");
		SC_METHOD(fetch);
			sensitive << clk;

	}


};

#endif