#ifndef PIPE4_H
#define PIPE4_H

#include <systemc.h>
#include <iostream>

SC_MODULE(Pipe4){

	sc_in<bool> clk;
	sc_in< sc_int<4> > dir_reg_in;
	sc_in< sc_int<4> > data_in;

	sc_out< sc_int<4> > dir_reg_out;
	sc_out< sc_int<4> > data_out;

	sc_int<4> dir_reg;
	sc_int<4> data;

	void receive(){

		data = data_in.read();
		dir_reg = dir_reg_in.read();

	}

	void exit(){

		dir_reg_out.write(dir_reg);
		data_out.write(data);

		std::cout<<"PIPE 4 REPORTING"<<std::endl;

		for(int i = 0; i < 4; i++){

			std::cout<< dir_reg.range(4-(i+1), 4-(i+1));

		}

		std::cout<<"\n";

		for(int i = 0; i < 4; i++){

			std::cout<< data.range(4-(i+1), 4-(i+1));
			
		}

		std::cout<<"\n";

	}

	SC_CTOR(Pipe4){

		SC_METHOD(receive);
			sensitive << clk << dir_reg_in << data_in;

		SC_METHOD(exit);
			sensitive << clk;

	}


};

#endif