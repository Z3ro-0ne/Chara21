#ifndef REGISTERFILE_H
#define REGISTERFILE_H

#include <systemc.h>

SC_MODULE(RegisterFile){

	sc_in< sc_uint<4> > instru_in;
	sc_in< sc_uint<4> > dir_reg_in;
	sc_in< sc_uint<8> > dir_data_in;
	sc_in< sc_uint<8> > data_in;

	sc_out< sc_uint<4> > dir_reg_out;
	sc_out< sc_uint<8> > data_out;

	sc_uint<64> storage[512];

	void operation(){

		if(instru_in.read() == 0){//LOAD

			dir_reg_out.write(dir_reg_in.read());
			data_out.write(storage[dir_data_in.read()]);

		} else {

			if(instru_in.read() == 1){//STORE

				storage[dir_data_in.read()] = data_in.read();

			} else {

				if((instru_in.read() == 2) or (instru_in.read() == 3)){ //ADD SUB

					dir_reg_out.write(dir_reg_in.read());
					data_out.write(data_in.read());

				}

			}

		}

	}

	SC_CTOR(RegisterFile){

		SC_METHOD(operation);
			sensitive << instru_in << dir_data_in << data_in << dir_reg_in;

	}
	
};

#endif