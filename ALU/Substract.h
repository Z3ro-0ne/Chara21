#ifndef SUBSTRACT_H
#define SUBSTRACT_H

#include <systemc.h>

SC_MODULE(Substract){

	sc_in< sc_uint<8> > a_in,b_in;
	sc_out< sc_uint<8> > out;

	void sub(){

		out = a_in.read() - b_in.read();

	}

	SC_CTOR(Substract){

		SC_METHOD(sub);
			sensitive << a_in << b_in;

	}

};


#endif