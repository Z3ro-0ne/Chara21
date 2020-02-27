#ifndef REGISTER_H
#define REGISTER_H

#include <systemc.h>
#include <iomanip>

SC_MODULE(Register){

	sc_in< sc_int<4> >dir_inst, dir1, dir2;
	sc_in< sc_int<4> > dir_WB;
	sc_in< sc_int<4> > data_WB; 
	sc_out< sc_int<4> > inst_out;
	sc_out< sc_int<4> > data1_out /*data2_out*/; 

	sc_int<12> storage[32];

	sc_in<bool> clk;

	void read(){
			
		inst_out = dir_inst;
		data1_out = storage[dir1.read()];
		//data2_out = storage[dir2.read()];
		

	}

	void write(){

		storage[dir1.read()] = dir2.read();
		//storage[dir2.read()] = dir2.read();
		storage[dir_WB.read()] = data_WB.read();

	}

	SC_CTOR(Register){

		SC_METHOD(read);
			sensitive << clk;
		SC_METHOD(write);
			sensitive << clk;

	}

};

#endif
