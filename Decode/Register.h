#ifndef REGISTER_H
#define REGISTER_H

#include <systemc.h>
#include <iomanip>

SC_MODULE(Register){

	sc_in< sc_int<4> >dir_inst, dir1, dir_WB;
	sc_in< sc_int<32> > data_WB; 
	sc_out< sc_int<4> > dir_out, inst_out;
	sc_out< sc_int<32> > data1_out; 

	sc_int<32> storage[32];

	sc_in_clk clk;

	void read(){
			
		data1_out.write(storage[dir1.read()]);

		dir_out.write(dir1.read());

		inst_out.write(dir_inst.read());

		/*std::cout<<"REGISTER REPORTING"<<std::endl;

		for(int i = 0; i < 4; i++){

			std::cout<<dir_inst.read().range(4-(i+1),4-(i+1));

		}

		std::cout<<"\t";

		for(int i = 0; i < 4; i++){

			std::cout<<dir_out.read().range(4-(i+1),4-(i+1));
			
		}

		std::cout<<"\t";

		for(int i = 0; i < 4; i++){

			std::cout<< data1_out.read().range(4-(i+1),4-(i+1));
			
		}

		std::cout<<"\n";*/

	}

	void write(){

		storage[dir_WB.read()] = data_WB.read();

	}

	SC_CTOR(Register){

		SC_METHOD(read);
			sensitive << clk;
		SC_METHOD(write);
			sensitive << clk << dir_inst << dir1 << dir_WB << data_WB;

	}

};

#endif
