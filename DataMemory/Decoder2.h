#ifndef DECODER2_H
#define DECODER2_H

#include <systemc.h>

SC_MODULE(Decoder2){

	sc_in< sc_int<12> > inst_in;

	sc_out< sc_int<4> > inst_out;
	sc_out< sc_int<4> > dir_reg;

	SC_CTOR(Decoder2){

		SC_METHOD(Split);
			sensitive << inst_in;

	}

	void Split(){

		inst_out.write(inst_in.read().range(11,8));
		dir_reg.write(inst_in.read().range(7,4));

	}

};

#endif