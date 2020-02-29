#ifndef ALU_H
#define ALU_H

#include <systemc.h>
#include "Pipe3.h"
#include "Map.h"

SC_MODULE(ALU){

	sc_in< sc_int<4> > inst;
	sc_in< sc_int<4> > op1, op2;
	sc_in<bool> clk;
	sc_out< sc_int<4> > alu_out;

	Pipe3 *pipe3;
	Map *grid;

	sc_signal< sc_int<4> > value_sg;
	
	SC_CTOR(ALU){

		pipe3 =  new Pipe3("pipe3");
		grid = new Map("grid");

		grid -> inst_in(inst);
		grid -> op1(op1);
		grid -> op2(op2);
		grid -> value_out(value_sg);

		pipe3 -> clk(clk);
		pipe3 -> alu(value_sg);
		pipe3 -> alu_result(alu_out);


	}

	
};

#endif