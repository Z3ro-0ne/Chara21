#ifndef TESTBENCH_H
#define TESTBENCH_H

#include <systemc.h>
#include <iostream>

	
SC_MODULE(TestBench){

	sc_out< sc_uint<4> > inst, op1, op2, op3;
	sc_in<bool> clk;
	sc_in< sc_uint<8> > alu_out;

	void test(){

		inst.write(0);
		op1.write(0);
		op2.write(1);
		op3.write(1);

		wait();

		wait();

		wait();

		wait();
		output();

		inst.write(1);
		op1.write(0);
		op2.write(2);
		op3.write(1);
		
		wait();

		wait();

		wait();

		wait();
		output();	

		sc_stop();
	}

	void output(){

		std::cout<< inst.read() << "||" << op2.read() << "+" << op3.read() << "=" << alu_out.read() << std::endl;
	
	}

	SC_CTOR(TestBench){

		SC_THREAD(test);
			sensitive << clk;
	}

};


#endif