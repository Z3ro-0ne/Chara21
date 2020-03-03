#ifndef PIPE_H
#define PIPE_H

#include <systemc.h>
#include <iostream>
#include <iomanip>

SC_MODULE(Pipe){

	sc_in_clk clk;
	sc_in< sc_int<8> > input;
	sc_int<8> data;
	sc_out< sc_int <8> > out;

	void receive(){

		data = input.read();

	} 

	void exit(){

		out.write(data);

		/*std::cout<<"PIPE 1 REPORTING"<<std::endl;

		for(int i = 0; i < 12; i++){

			std::cout<<out.read().range(12-(i+1),12-(i+1));

		}

		std::cout<<"\n";*/

	}
	
	SC_CTOR(Pipe){
		SC_METHOD(receive);
		sensitive << clk;

		SC_METHOD(exit);
		sensitive << clk;	
	}
	
};

#endif