#ifndef DECODE_H
#define DECODE_H

#include <iostream>

using namespace std;

SC_MODULE(Decode){

	sc_in< sc_uint<16> > inst_in;
	sc_out< sc_uint<4> > inst_out, /*op1,*/ op2, op3;
	//sc_out< sc_uint<16> > instruction;

	void fragment(){

		inst_out.write(inst_in.read().range(15,12));
		//op1.write(inst_in.read().range(11,8));
		op2.write(inst_in.read().range(7,4));
		op3.write(inst_in.read().range(3,0));
		//instruction.write(inst_in.read());


	}

	SC_CTOR(Decode){
		SC_METHOD(fragment);
			sensitive << inst_in;
	}
	
};

#endif
