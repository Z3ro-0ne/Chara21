#ifndef SELECTER_H
#define SELECTER_H

#include <systemc.h>

SC_MODULE(Selecter){

	sc_in< sc_uint<4> > inst_in;
	sc_out< sc_uint<2> > choice;

	void selection(){

		if(inst_in.read() == 2){

			choice.write(2);

		} else {

			if(inst_in.read() == 3){

				choice.write(3);

			} else {

				choice.write(0);
				
			}

		}

	}

	SC_CTOR(Selecter){

		SC_METHOD(selection);
			sensitive << inst_in;

	}


};

#endif