#ifndef PIPE3_H
#define PIPE3_H

#include <systemc.h>

SC_MODULE(Pipe3){

	sc_in< sc_uint<8> > alu;
	sc_in<bool> clk;

	sc_out< sc_uint<8> > alu_result;

	sc_uint<4> data;

	void receive(){

		data = alu.read();

	}

	void exit(){

		alu_result = data;

	}

	SC_CTOR(Pipe3){

		SC_METHOD(receive);
			sensitive << clk;
		SC_METHOD(exit);
			sensitive << clk;
	}

};

#endif