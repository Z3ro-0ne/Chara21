#ifndef REGISTERFILE_H
#define REGISTERFILE_H

#include <systemc.h>

SC_MODULE(RegisterFile){

	sc_in< sc_int<4> > instru_in;
	sc_in< sc_int<4> > dir_reg_in;
	sc_in< sc_int<8> > data_in;

	sc_out< sc_int<4> > dir_reg_out;
	sc_out< sc_int<8> > data_out;

	sc_int<8> storage[32];

	void operation(){

		if(instru_in.read() == 0){//LOAD

			dir_reg_out.write(dir_reg_in.read());
			data_out.write(storage[dir_reg_in.read()]);

		} else {

			if(instru_in.read() == 1){//STORE

				storage[dir_reg_in.read()] = data_in.read();

				switch(dir_reg_in.read()){

					case 1: std::cout<<"Bio: "<<storage[dir_reg_in.read()];
							std::cout<<"\n";
						break;

					case 2: std::cout<<"Cult: "<<storage[dir_reg_in.read()];
							std::cout<<"\n";
						break;

					case 3: std::cout<<"Emo: "<<storage[dir_reg_in.read()];
							std::cout<<"\n";
						break;

					case 4: std::cout<<"X: "<<storage[dir_reg_in.read()];
							std::cout<<"\n";
						break;

					case 5: std::cout<<"Y: "<<storage[dir_reg_in.read()];
							std::cout<<"\n\n";
						break;

					default: break;
				}

			} else {

				if((instru_in.read() == 2) or (instru_in.read() == 3) or(instru_in.read() == 4) or (instru_in.read() == 5)){ //ADD MOVE CREATEMAP JUMP

					dir_reg_out.write(dir_reg_in.read());
					data_out.write(data_in.read());

				}

			}

		}

	}

	SC_CTOR(RegisterFile){

		SC_METHOD(operation);
			sensitive << instru_in << data_in << dir_reg_in;

	}
	
};

#endif