#ifndef ADDER_H
#define ADDER_H

#include <systemc.h>

SC_MODULE(Adder){

	sc_in< sc_uint<8> > a_in,b_in;
	sc_out< sc_uint<8> > out;

	void add(){

		out = a_in.read() + b_in.read();

	}

	SC_CTOR(Adder){

		SC_METHOD(add);
			sensitive << a_in << b_in;

	}

};


#endif