#ifndef DECODE_H
#define DECODE_H

#include <iostream>

using namespace std;

SC_MODULE(Decode){

	sc_in< sc_int<8> > inst_in;
	sc_out< sc_int<4> > inst_out, op1;

	void fragment(){

		inst_out.write(inst_in.read().range(7,4));
		op1.write(inst_in.read().range(3,0));

	}

	SC_CTOR(Decode){
		SC_METHOD(fragment);
			sensitive << inst_in;
	}
	
};

#endif
