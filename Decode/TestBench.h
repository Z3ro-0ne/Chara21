#ifndef TESTBENCH_H
#define TESTBENCH_H

#include <systemc.h>
#include <iostream>



SC_MODULE(TestBench){

	sc_out< sc_uint<16> > instruction_in;
	sc_in<bool> clk;

	sc_in< sc_uint<4> > inst, data1, data2, data3;
	sc_in< sc_uint<16> > instruction_og;

	void test(){

		instruction_in.write(1);//0000000000000001

		wait();
		instruction_in.write(2);//0000000000000010
		
		wait();
		instruction_in.write(105);
		
		wait();
		instruction_in.write(4);

		wait();
		instruction_in.write(200);

		output();

		wait();
		output();

		wait();
		output();

		wait();
		output();

		wait();
		output();

		sc_stop();

	}


	void output(){

		std::cout<<"inst_in || inst || op1 || op2 || op3"<<std::endl;

		for(int i = 15; i >= 0; i--){

			std::cout<<instruction_og.read().range(i,i);

		}

		std::cout<<" || ";

		for(int i = 3; i >= 0; i--){

			std::cout<<inst.read().range(i,i);

		}

		std::cout<<" || ";

		for(int i = 3; i >= 0; i--){

			std::cout<<data1.read().range(i,i);
			
		}

		std::cout<<" || ";


		for(int i = 3; i >= 0; i--){

			std::cout<<data2.read().range(i,i);
			
		}

		std::cout<<" || ";

		for(int i = 3; i >= 0; i--){

			std::cout<<data3.read().range(i,i);
			
		}

		std::cout<<"\n\n";
	
	}

	SC_CTOR(TestBench){

		SC_THREAD(test)
			sensitive << clk;
			
	}

};

#endif
