#ifndef REGISTERFILE_H
#define REGISTERFILE_H

#include <systemc.h>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
//#include <chrono>
//#include <thread>

SC_MODULE(RegisterFile){

	sc_in< sc_int<4> > instru_in;
	sc_in< sc_int<4> > dir_reg_in;
	sc_in< sc_int<32> > data_in;


	sc_out< sc_int<4> > dir_reg_out;
	sc_out< sc_int<32> > data_out;

	ofstream out_file;

	sc_int<32> storage[32];

	void operation(){

		if(instru_in.read() == 0){//LOAD

			dir_reg_out.write(dir_reg_in.read());
			data_out.write(storage[dir_reg_in.read()]);

		} else {

			if(instru_in.read() == 1){//STORE

				storage[dir_reg_in.read()] = data_in.read();

				switch(dir_reg_in.read()){

					case 1: std::cout<<"Chara's Status: "<<std::endl;
							std::cout<<"*Biological Level: "<<storage[dir_reg_in.read()];
							std::cout<<"\n";
						break;

					case 2: std::cout<<"*Cultural Level: "<<storage[dir_reg_in.read()];
							std::cout<<"\n";
						break;

					case 3: std::cout<<"*Emotional Level: "<<storage[dir_reg_in.read()];
							std::cout<<"\n";
						break;

					case 4: std::cout<<"*Coordenate X: "<<storage[dir_reg_in.read()];
							std::cout<<"\n";
						break;

					case 5: std::cout<<"*Coordenate Y: "<<storage[dir_reg_in.read()];
							std::cout<<"\n\n";
							out_file<<storage[1]<<"//"<<storage[2]<<"//"<<storage[3]<<"//#"<<storage[4]<<"#"<<storage[5]<<"\n";
							//std::this_thread::sleep_for(std__chrono::miliseconds(1000));
							sleep(1);
							if(storage[1] == 0 and storage[2] == 0 and storage[3] == 0){

								std::cout<<"**SIMULATION ENDED**"<<std::endl;
								std::cout<<"CHARA IS DEAD"<<std::endl;
								out_file.close();
								exit(1);

							}

							system("clear");
						
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

		out_file.open("Data.txt");

		SC_METHOD(operation);
			sensitive << instru_in << data_in << dir_reg_in;

	}
	
};

#endif