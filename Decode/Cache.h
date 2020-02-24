#ifndef CACHE_H
#define CACHE_H

#include <systemc.h>
#include <iomanip>

SC_MODULE(Cache){

	sc_in< sc_uint<4> >dir_inst, /*dir1,*/ dir2, dir3;
	//sc_in< sc_uint<16> >instruction;
	sc_in< sc_uint<4> > dir_WB;
	sc_in< sc_uint<8> > data_WB;
	//sc_out< sc_uint<16> >chain; 
	//sc_in< sc_uint<4> > inst_cache, data1_cache, data2_cache, data3_cache;
	sc_out< sc_uint<4> > inst_out;
	sc_out< sc_uint<8> > /*data1_out,*/ data2_out, data3_out; 

	sc_uint<64> storage[512];

	sc_in<bool> clk;
	//sc_in<bool> activate_writing;

	void read(){

		if(true){
			
			inst_out = dir_inst;
			//data1_out = storage[dir1.read()];
			data2_out = storage[dir2.read()];
			data3_out = storage[dir3.read()];
			//chain = storage[instruction.read()];
		
		}

	}

	void write(){

		if(true /*and activate_writing.read()*/){

			//storage[dir_inst.read()] = dir_inst.read();
			//storage[dir1.read()] = dir1.read();
			storage[dir2.read()] = dir2.read();
			storage[dir3.read()] = dir3.read();
			//storage[instruction.read()] = instruction.read();
			storage[dir_WB.read()] = data_WB;

		}

	}

	SC_CTOR(Cache){

		SC_METHOD(read);
			sensitive << clk;
		SC_METHOD(write);
			sensitive << clk;

	}

};

#endif
