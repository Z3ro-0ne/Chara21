#ifndef ALU_H
#define ALU_H

#include <systemc.h>
#include "Pipe3.h"
#include "Map.h"
#include "SuperAdder.h"

SC_MODULE(ALU){

	sc_in< sc_int<4> > inst;
	sc_in< sc_int<4> > op1, op2;
	sc_in<bool> clk;
	sc_out< sc_int<4> > alu_out;

	Pipe3 *pipe3;
	Map *grid;
	SuperAdder *adder;

	sc_signal< sc_int<4> > dir_sg, value_sg, bio_sg, cult_sg, emo_sg, result_sg;
	
	SC_CTOR(ALU){

		pipe3 =  new Pipe3("pipe3");
		grid = new Map("grid");
		adder = new SuperAdder("adder+");

		grid -> inst_in(inst);
		grid -> op1(op1);
		grid -> op2(op2);
		grid -> dir_out(dir_sg);
		grid -> value_out(value_sg);
		grid -> bio_out(bio_sg);
		grid -> cult_out(cult_sg);
		grid -> emo_out(emo_sg);

		adder -> dir(dir_sg);
		adder -> value(value_sg);
		adder -> bio(bio_sg);
		adder -> cult(cult_sg);
		adder -> emo(emo_sg);
		adder -> result(result_sg);

		pipe3 -> clk(clk);
		pipe3 -> alu(result_sg);
		pipe3 -> alu_result(alu_out);


	}

	~ALU(){

		delete pipe3;
		delete grid;
		delete adder;

	}
	
};

#endif