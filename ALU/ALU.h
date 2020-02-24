#ifndef ALU_H
#define ALU_H

#include <systemc.h>
#include "Adder.h"
#include "Substract.h"
#include "Pipe3.h"
#include "Selecter.h"
#include "Selection.h"

SC_MODULE(ALU){

	sc_in< sc_uint<4> > inst; /*op1,*/
	sc_in< sc_uint<8> > op2, op3;
	sc_in<bool> clk;
	sc_out< sc_uint<8> > alu_out;

	Adder *adder;
	Substract *substract;
	Pipe3 *pipe3;
	Selecter *selecter;
	Selection *selection;

	sc_signal< sc_uint<8> > add_sg, sub_sg, result_sg;
	sc_signal< sc_uint<2> > choice_sg;

	
	SC_CTOR(ALU){

		adder = new Adder("adder");
		substract = new Substract("substract");
		pipe3 =  new Pipe3("pipe3");
		selecter = new Selecter("selecter");
		selection = new Selection("selection");

		selecter -> inst_in(inst);
		selecter -> choice(choice_sg);

		adder -> a_in(op2);
		adder -> b_in(op3);
		adder -> out(add_sg);

		substract -> a_in(op2);
		substract -> b_in(op3);
		substract -> out(sub_sg);

		selection -> add_in(add_sg);
		selection -> sub_in(sub_sg);
		selection -> choice(choice_sg);
		selection -> result(result_sg);

		pipe3 -> clk(clk);
		pipe3 -> alu(result_sg);
		pipe3 -> alu_result(alu_out);


	}

	~ALU(){

		delete substract;
		delete adder;
		delete pipe3;
		delete selection;
		delete selecter;

	}
	
};

#endif