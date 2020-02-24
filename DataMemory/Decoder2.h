#ifndef DECODER2_H
#define DECODER2_H

#include <systemc.h>

SC_MODULE(Decoder2){

	sc_in< sc_uint<16> > inst_in;

	sc_out< sc_uint<4> > inst_out;
	sc_out< sc_uint<4> > dir_reg;
	sc_out< sc_uint<8> > dir_data;

	SC_CTOR(Decoder2){

		SC_METHOD(Split);
			sensitive << inst_in;

	}

	void Split(){

		inst_out.write(inst_in.read().range(15,12));
		dir_reg.write(inst_in.read().range(11,8));
		dir_data.write(inst_in.read().range(7,0));

	}

};

#endif