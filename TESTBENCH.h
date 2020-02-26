#ifndef TESTBENCH_H
#define TESTBENCH_H

#include <systemc.h>
#include <iostream>

SC_MODULE(TESTBENCH){

	sc_out<bool> CLK;
	sc_in<bool> clk;
	sc_in< sc_int<4> > out1, out2;

	void test(){

		CLK.write(clk);

		for(int i = 0; i < 11; i++){

			wait();

		}

		for(int i = 0; i < 4; i++){

			std::cout<<out1.read().range(4-(i+1), 4-(i+1));

		}

		std::cout<<"\t";

		for(int i = 0; i < 4; i++){

			std::cout<<out2.read().range(4-(i+1), 4-(i+1));
			
		}

		sc_stop();
	}

	SC_CTOR(TESTBENCH){

		SC_THREAD(test);
			sensitive << CLK;

	}

};

#endif