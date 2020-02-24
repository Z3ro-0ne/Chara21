#ifndef PIPE_H
#define PIPE_H

#include <systemc.h>

SC_MODULE(Pipe){

	sc_in<bool> clk;
	sc_in< sc_uint<16> > input;
	sc_uint<16> data;
	sc_out< sc_uint <16> > out;

	void receive(){
		data = input.read();
	} 

	void exit(){
		out.write(data);
	}
	
	SC_CTOR(Pipe){
		SC_METHOD(receive);
		sensitive << clk.pos() << input;

		SC_METHOD(exit);
		sensitive << clk.neg();	
	}
	
};

#endif