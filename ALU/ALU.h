#ifndef ALU_H
#define ALU_H

#include <systemc.h>
#include "Pipe3.h"
#include "Map.h"
//#include "SuperAdder.h"
//#include "Selecter.h"

SC_MODULE(ALU){

	sc_in< sc_int<4> > inst;
	sc_in< sc_int<4> > op1, op2;
	sc_in<bool> clk;
	sc_out< sc_int<4> > alu_out;

	Pipe3 *pipe3;
	Map *grid;
	//SuperAdder *adder;
	//Selecter *mux;

	sc_signal< sc_int<4> > dir_sg, value_sg, bio_sg, cult_sg, emo_sg, result_sg, x_sg, y_sg, exit_sg;
	
	SC_CTOR(ALU){

		pipe3 =  new Pipe3("pipe3");
		grid = new Map("grid");
		//adder = new SuperAdder("adder");
		//mux = new Selecter("mux");

		grid -> inst_in(inst);
		grid -> op1(op1);
		grid -> op2(op2);
		//grid -> add_in(result_sg);
		//grid -> dir_out(dir_sg);
		grid -> value_out(value_sg);
		//grid -> bio_out(bio_sg);
		//grid -> cult_out(cult_sg);
		//grid -> emo_out(emo_sg);
		//grid -> coord_x(x_sg);
		//grid -> coord_y(y_sg);

		/*adder -> dir(dir_sg);
		adder -> value(value_sg);
		adder -> bio(bio_sg);
		adder -> cult(cult_sg);
		adder -> emo(emo_sg);
		adder -> result(result_sg);

		mux -> dir_in(dir_sg);
		mux -> add_in(result_sg);
		mux -> x_in(x_sg);
		mux -> y_in(y_sg);
		mux -> data_out(exit_sg);*/

		pipe3 -> clk(clk);
		pipe3 -> alu(exit_sg);
		pipe3 -> alu_result(alu_out);


	}

	
};

#endif