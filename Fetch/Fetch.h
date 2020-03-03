#ifndef FETCH_H
#define FETCH_H

#include <systemc.h>
#include <fstream>
#include "Pipe.h"
#include "PC.h"

SC_MODULE(Fetch){

	ifstream isa_file;
	sc_in_clk clk;
	sc_out< sc_int<8> > inst;

	Pipe *pipe;
	PC *pc;

	sc_signal< sc_int<8> > sg1;

	SC_CTOR(Fetch){

		pipe = new Pipe("pipe");
		pc = new PC("pc");

		pc -> clk(clk);
		pc -> read(sg1);

		pipe -> clk(clk);
		pipe -> input(sg1);
		pipe -> out(inst);

	}
	

};


#endif  