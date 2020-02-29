#ifndef CHARA21_H
#define CHARA21_H

#include <systemc.h>
#include "./Fetch/Fetch.h"
#include "./Decode/RegisterMemory.h"

SC_MODULE(Chara21){

	sc_in_clk clk;
	sc_in< sc_int<4> > dir_WB, data_WB;
	sc_out< sc_int<4> > inst_out, dir_out, data_out;

	Fetch* fetch;
	RegisterMemory* decode;

	sc_signal< sc_int<12> > fetch_sg; 
	sc_signal< sc_int<4> > dir_WB_sg, data_WB_sg;

	SC_CTOR(Chara21){

		fetch = new Fetch("fetch");
		decode = new RegisterMemory("decode");

		fetch -> clk(clk);
		fetch -> inst(fetch_sg);

		decode -> clk(clk);
		decode -> instruction_in(fetch_sg);
		decode -> dir_WB(dir_WB);
		decode -> data_WB(data_WB);
		decode -> inst(inst_out);
		decode -> data1(dir_out);
		decode -> data2(data_out);


	}

};

#endif