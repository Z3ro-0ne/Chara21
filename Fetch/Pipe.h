#ifndef PIPE_H
#define PIPE_H

#include <systemc.h>

SC_MODULE(Pipe){

	sc_in<bool> clk;
	sc_in< sc_int<12> > input;
	sc_int<12> data;
	sc_out< sc_int <12> > out;

	void receive(){
		data = input.read();
	} 

	void exit(){
		out.write(data);
	}
	
	SC_CTOR(Pipe){
		SC_METHOD(receive);
		sensitive << clk << input;

		SC_METHOD(exit);
		sensitive << clk;	
	}
	
};

#endif