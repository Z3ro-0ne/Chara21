#ifndef PIPE4_H
#define PIPE4_H

#include <systemc.h>
#include <iostream>

SC_MODULE(Pipe4){

	sc_in_clk clk;
	sc_in< sc_int<4> > dir_reg_in;
	sc_in< sc_int<32> > data_in;

	sc_out< sc_int<4> > dir_reg_out;
	sc_out< sc_int<32> > data_out;

	sc_int<4> dir_reg;
	sc_int<32> data;

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
			sensitive << clk;

		SC_METHOD(exit);
			sensitive << clk;

	}


};

#endif