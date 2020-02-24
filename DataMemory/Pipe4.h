#ifndef PIPE4_H
#define PIPE4_H

#include <systemc.h>

SC_MODULE(Pipe4){

	sc_in<bool> clk;
	sc_in< sc_uint<4> > dir_reg_in;
	sc_in< sc_uint<8> > data_in;

	sc_out< sc_uint<4> > dir_reg_out;
	sc_out< sc_uint<8> > data_out;

	sc_uint<4> dir_reg;
	sc_uint<8> data;

	void receive(){

		data = data_in.read();
		dir_reg = dir_reg_in.read();

	}

	void exit(){

		dir_reg_out.write(dir_reg);
		data_out.write(data);

	}

	SC_CTOR(Pipe4){

		SC_METHOD(receive);
			sensitive << clk << dir_reg_in << data_in;

		SC_METHOD(exit);
			sensitive << clk;

	}


};

#endif