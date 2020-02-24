#ifndef FETCH_H
#define FETCH_H

#include <systemc.h>
#include <fstream>
#include "Pipe.h"
#include "Get.h"

SC_MODULE(Fetch){

	ifstream isa_file;
	sc_in<bool> clk;
	sc_out< sc_int<12> > inst;

	Pipe *pipe;
	Get *get;

	sc_signal< sc_int<12> > sg1;

	SC_CTOR(Fetch){

		pipe = new Pipe("pipe");
		get = new Get("get");

		get -> clk(clk);
		get -> read(sg1);

		pipe -> clk(clk);
		pipe -> input(sg1);
		pipe -> out(inst);

	}

	~Fetch(){

		delete pipe;
		delete get;
	}

};


#endif  