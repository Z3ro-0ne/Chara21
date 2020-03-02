#ifndef SUPERTESTBENCH_H
#define SUPERTESTBENCH_H

#include <systemc.h>

SC_MODULE(SuperTestBench){

	sc_in_clk clk;

	void test(){

		for(int i = 0; i > -1; i++){

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