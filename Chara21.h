#ifndef CHARA21_H
#define CHARA21_H

#include <systemc.h>
#include "./Fetch/Fetch.h"
#include "./Decode/RegisterMemory.h"
#include "./ALU/ALU.h"
#include "./DataMemory/DataMemory.h"

SC_MODULE(Chara21){

	sc_in_clk clk;

	Fetch* fetch;
	RegisterMemory* decode;
	ALU *alu;
	DataMemory *data_mem;

	sc_signal< sc_int<8> > fetch_sg; 
	sc_signal< sc_int<4> > inst_sg, dir_sg, dir_WB, sg1, sg2;
	sc_signal< sc_int<32> > data_sg, alu_sg, data_WB;

	SC_CTOR(Chara21){

		fetch = new Fetch("fetch");
		decode = new RegisterMemory("decode");
		alu = new ALU("alu");
		data_mem = new DataMemory("data_mem");

		fetch -> clk(clk);
		fetch -> inst(fetch_sg);

		decode -> clk(clk);
		decode -> instruction_in(fetch_sg);
		decode -> dir_WB(dir_WB);
		decode -> data_WB(data_WB);
		decode -> inst(inst_sg);
		decode -> dir(dir_sg);
		decode -> data(data_sg);

		alu -> clk(clk);
		alu -> inst(inst_sg);
		alu -> dir(dir_sg);
		alu -> data(data_sg);
		alu -> inst_out(sg1);
		alu -> dir_out(sg2);
		alu -> alu_out(alu_sg);

		data_mem -> clk(clk);
		data_mem -> inst_in(sg1);
		data_mem -> dir_in(sg2);		
		data_mem -> alu_result(alu_sg);
		data_mem -> register_dir_WB(dir_WB);
		data_mem -> data_WB(data_WB);

	}

};

#endif