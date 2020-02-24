#ifndef TESTBENCH_H
#define TESTBENCH_H

#include <systemc.h>
#include <iostream>
#include <iomanip>

SC_MODULE(TestBench){

	sc_in< sc_int<12> > out;
	sc_in< sc_int<12> > inst;
	sc_in<bool> clk;

	void output(){

		for(int i = 0; i < 12 ; i++){

			std::cout << inst.read().range(12-(i+1), 12-(i+1));
		}

		std::cout << " | ";

		for(int i = 0; i < 12 ; i++){

			std::cout << out.read().range(12-(i+1), 12-(i+1));
		}

		std::cout << " | " << clk.read() <<std::endl;

	}

	void test(){

		std::cout <<"Pipe Entrance    | Pipe Exit        | CLK" << std::endl;

		for(int i = 0; i < 5 ; i++){

			wait();
			output();

		}

		sc_stop();

	}

	SC_CTOR(TestBench){

		SC_THREAD(test);
		sensitive << clk.pos();

	}

};

#endif