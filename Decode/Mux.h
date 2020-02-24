#ifndef MUX_H
#define MUX_H

#include <systemc.h>

SC_MODULE(Mux){

	sc_in< sc_uint<4> > dir_WB, dir_op;
	sc_in< sc_uint<8> > data_WB, data_op;

	sc_out< sc_uint<8> > data_out;

	void compare(){

		if(dir_WB.read() == dir_op.read()){

			data_out.write(data_WB);

		} else {

			data_out.write(data_out.read());
		}

	}

	SC_CTOR(Mux){

		SC_METHOD(compare);
			sensitive << dir_WB << dir_op;
			
	}

};

#endif