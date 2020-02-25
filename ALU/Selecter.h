#ifndef SELECTER_H
#define SELECTER_H

#include <systemc.h>

SC_MODULE(Selecter){

	sc_in< sc_int<4> > dir_in, add_in, x_in, y_in;
	sc_out< sc_int<4> > data_out;

	void choice(){

		switch(dir_in.read()){

			case 4: data_out.write(x_in.read());
				break;

			case 5: data_out.write(y_in.read());
				break;

			default: data_out.write(add_in.read());
				break;

		}
	}

	SC_CTOR(Selecter){

		SC_METHOD(choice);
			sensitive << dir_in << add_in << x_in << y_in;

	}

};

#endif