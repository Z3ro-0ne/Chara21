#ifndef PIPE3_H
#define PIPE3_H

#include <systemc.h>
#include <iostream>

SC_MODULE(Pipe3){

	sc_in< sc_int<32> > alu;
	sc_in< sc_int<4> > inst_in, dir_in;
	sc_in_clk clk;

	sc_out< sc_int<32> > alu_result;
	sc_out< sc_int<4> > dir_out, inst_out;

	sc_int<32> data, dir, inst;

	void receive(){

		data = alu.read();
		dir = dir_in.read();
		inst = inst_in.read();


	}

	void exit(){

		alu_result.write(data);
		dir_out.write(dir);
		inst_out.write(inst);

		/*std::cout<<"PIPE 3 REPORTING"<<std::endl;

		std::cout<<alu_result<<std::endl;

		for(int i = 0; i < 4; i++){

			std::cout<<alu_result.read().range(4-(i+1),4-(i+1));

		}

		std::cout<<"\n";*/

	}

	SC_CTOR(Pipe3){

		SC_METHOD(receive);
			sensitive << clk;
		SC_METHOD(exit);
			sensitive << clk;
	}

};

#endif