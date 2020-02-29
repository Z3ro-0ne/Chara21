#ifndef REGISTER_H
#define REGISTER_H

#include <systemc.h>
#include <iomanip>

SC_MODULE(Register){

	sc_in< sc_int<4> >dir_inst, dir1, dir2, dir_WB, data_WB; 
	sc_out< sc_int<4> > data1_out, dir_out, inst_out; 

	sc_int<12> storage[32];

	sc_in<bool> clk;

	void read(){
			
		data1_out.write(storage[dir1.read()]);

		if(dir1.read() == dir_WB.read()){

			dir_out.write(dir_WB.read());

		} else {

			dir_out.write(dir1.read());

		}

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

		storage[dir1.read()] = dir2.read();
		storage[dir_WB.read()] = dir_WB.read();

	}

	SC_CTOR(Register){

		SC_METHOD(read);
			sensitive << clk.neg();
		SC_METHOD(write);
			sensitive << clk.pos() << dir_inst << dir1 << dir2 << dir_WB << data_WB;

	}

};

#endif
