#ifndef ALU_H
#define ALU_H

#include <systemc.h>
#include "Pipe3.h"
#include "Map.h"

SC_MODULE(ALU){

	sc_in< sc_int<4> > inst, dir;
	sc_in< sc_int<8> > data;
	sc_in_clk clk;
	sc_out< sc_int<8> > alu_out;
	sc_out< sc_int<4> > inst_out, dir_out;

	Pipe3 *pipe3;
	Map *grid;

	sc_signal< sc_int<8> > value_sg;
	sc_signal< sc_int<4> > dir_sg, inst_sg;
	
	SC_CTOR(ALU){

		pipe3 =  new Pipe3("pipe3");
		grid = new Map("grid");

		grid -> inst_in(inst);
		grid -> dir_in(dir);
		grid -> data_in(data);
		grid -> inst_out(inst_sg);
		grid -> dir_out(dir_sg);
		grid -> value_out(value_sg);

		pipe3 -> clk(clk);
		pipe3 -> inst_in(inst_sg);
		pipe3 -> dir_in(dir_sg);
		pipe3 -> alu(value_sg);
		pipe3 -> inst_out(inst_out);
		pipe3 -> dir_out(dir_out);
		pipe3 -> alu_result(alu_out);


	}

	
};

#endif