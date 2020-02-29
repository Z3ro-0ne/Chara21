#ifndef SUPERTESTBENCH_H
#define SUPERTESTBENCH_H

#include <systemc.h>

SC_MODULE(SuperTestBench){

	sc_in_clk clk;
	sc_out< sc_int<4> > dir_WB, data_WB;
	sc_in< sc_int<4> > inst_out, dir_out, data_out;

	void test(){

		for(int i = 0; i < 100; i++){

			dir_WB.write(0);
			data_WB.write(0);
			wait();

		}

		sc_stop();

	}

	SC_CTOR(SuperTestBench){

		SC_THREAD(test);
			sensitive << clk;

	}

};

#endif