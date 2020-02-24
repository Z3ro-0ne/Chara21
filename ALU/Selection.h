#ifndef SELECTION_H
#define SELECTION_H

#include <systemc.h>

SC_MODULE(Selection){

	sc_in< sc_uint<8> > add_in, sub_in;
	sc_in< sc_uint<2> > choice;

	sc_out< sc_uint<8> > result;

	void operation(){

		switch(choice.read()){

			case 2: result.write(add_in.read());
				break;

			case 3: result.write(sub_in.read());
				break;

			default: result.write(0);
				break;

		}

	}

	SC_CTOR(Selection){

		SC_METHOD(operation);
			sensitive << add_in << sub_in << choice;

	}

};

#endif