#ifndef TESTBENCH_H
#define TESTBENCH_H

#include <systemc.h>
#include <iostream>

SC_MODULE(TestBench){

	sc_out< sc_uint<16> > instruction_og;
	sc_out< sc_uint<8> > alu_result;
	sc_in<bool> clk;

	sc_in< sc_uint<4> > register_dir_WB;
	sc_in< sc_uint<8> > data_WB;

	void output(){

		std::cout<< instruction_og.read() << "||" << alu_result.read() << "||" << register_dir_WB.read() << "||" << data_WB.read() << std::endl;		

	}

	void test(){

		std::cout << "INST || DATA_IN || REGISTER_DIR || DATA_OUT " << std::endl;

		instruction_og.write(2321);//0000100100010001
		
		wait();
		output();

		instruction_og.write(4600);//0001000111111000

		wait();
		output();

		instruction_og.write(9034);//0010001101001010
		
		wait();
		output();

		instruction_og.write(504);//0000000111111000

		wait();
		output();

		sc_stop();

	}

	SC_CTOR(TestBench){

		SC_THREAD(test);
			sensitive << clk;

	}

};

#endif