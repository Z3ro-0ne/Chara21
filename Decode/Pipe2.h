#ifndef PIPE2_H
#define PIPE2_H

#include <systemc.h>
#include <iostream>

SC_MODULE(Pipe2){

	sc_in_clk clk;
	sc_in< sc_int<4> > inst_in, data1_in;
	sc_in< sc_int<8> > data2_in;
	sc_out< sc_int<4> > inst_out, data1_out; 
	sc_out< sc_int<8> > data2_out;

	sc_int <4> load_inst, load_data1; 
	sc_int <8> load_data2;

	void receive(){

		load_inst = inst_in;
		load_data1 = data1_in;
		load_data2 = data2_in;

	}

	void exit(){

		inst_out.write(load_inst);
		data1_out.write(load_data1);
		data2_out.write(load_data2);

		/*std::cout<<"PIPE 2 REPORTING"<<std::endl;

		for(int i = 0; i < 1; i++){

			//std::cout<<inst_out.read().range(4-(i+1),4-(i+1));
			std::cout<<inst_out.read();

		}

		std::cout<<"\t";

		for(int i = 0; i < 1; i++){

			//std::cout<<data1_out.read().range(4-(i+1),4-(i+1));
			std::cout<<data1_out.read();
			
		}

		std::cout<<"\t";

		for(int i = 0; i < 1; i++){

			//std::cout<<data2_out.read().range(4-(i+1),4-(i+1));
			std::cout<<data2_out.read();
			
		}

		std::cout<<"\n";*/

	}

	SC_CTOR(Pipe2){

		SC_METHOD(receive);
			sensitive << clk.pos();
		SC_METHOD(exit);
			sensitive << clk.neg();

	}

};

#endif