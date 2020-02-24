#ifndef MICRO_BC_H
#define MICRO_BC_H

#include <systemc.h>
#include "./Fetch/Fetch.h"
#include "./Decode/RegisterMemory.h"
#include "./ALU/ALU.h"
#include "./DataMemory/DataMemory.h"

SC_MODULE(micro_BC){

	sc_in<bool> CLK;

	Fetch *fetch;
	RegisterMemory *reg_memory;
	ALU *alu;
	DataMemory *data_memory;

	sc_signal< sc_int<12> > fetch_out_sg;
	sc_signal< sc_int<4> >  data_WB_sg, alu_sg, reg_memory_data1, reg_memory_data2;
	sc_signal< sc_int<4> > dir_WB_sg, reg_memory_inst; 

	SC_CTOR(micro_BC){

		fetch = new Fetch("fetch");
		reg_memory = new RegisterMemory("reg_memory");
		alu = new ALU("alu");
		data_memory = new DataMemory("data_memory");

		fetch -> clk(CLK);
		fetch -> inst(fetch_out_sg);

		reg_memory -> clk(CLK);
		reg_memory -> instruction_in(fetch_out_sg);
		reg_memory -> dir_WB(dir_WB_sg);
		reg_memory -> data_WB(data_WB_sg);
		reg_memory -> inst(reg_memory_inst);
		reg_memory -> data1(reg_memory_data1);
		reg_memory -> data2(reg_memory_data2);

		alu -> clk(CLK);
		alu -> inst(reg_memory_inst);
		alu -> op1(reg_memory_data1);
		alu -> op2(reg_memory_data2);
		alu -> alu_out(alu_sg);

		data_memory -> clk(CLK);
		data_memory -> instruction_og(fetch_out_sg);
		data_memory -> alu_result(alu_sg);
		data_memory -> register_dir_WB(dir_WB_sg);
		data_memory -> data_WB(data_WB_sg);


	}

};

#endif