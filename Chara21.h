#ifndef CHARA21_H
#define CHARA21_H

#include <systemc.h>
#include "./Fetch/Fetch.h"

SC_MODULE(Chara21){

	sc_in_clk clk;
	sc_out< sc_int<12> > out;

	Fetch* fetch;

	SC_CTOR(Chara21){

		fetch = new Fetch("fetch");

		fetch -> clk(clk);
		fetch -> inst(out);

	}

	~Chara21(){

		delete fetch;
	}

};

#endif