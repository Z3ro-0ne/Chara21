#ifndef  REGISTERMEMORY_H
#define  REGISTERMEMORY_H

#include "Decode.h"
#include "Register.h"
#include "Pipe2.h"
#include "Mux.h"

SC_MODULE(RegisterMemory){

	sc_in< sc_int<12> > instruction_in;
	sc_in<bool> clk;
	sc_in< sc_int<4> > dir_WB;
	sc_in< sc_int<4> > data_WB;

	sc_out< sc_int<4> > inst; 
	sc_out< sc_int<4> > data1, data2;

	Register *regis;
	Decode *decode;
	Pipe2 *pipe2;
	Mux *mux1/*, *mux2*/;

	sc_signal< sc_int<4> > decode_inst_sg, decode_op1_sg, decode_op2_sg, regis_inst_sg;
	sc_signal< sc_int<4> > regis_data1_sg /*regis_data2_sg*/, data_out_sg1 /*data_out_sg2*/;

	SC_CTOR(RegisterMemory){

		regis = new Register("regis");
		decode =  new Decode("Decode");
		pipe2 = new Pipe2("Pipe2");
		mux1 = new Mux("Mux1");
		//mux2 = new Mux("Mux2");
		

		decode -> inst_in(instruction_in);
		decode -> inst_out(decode_inst_sg);
		decode -> op1(decode_op1_sg);
		decode -> op2(decode_op2_sg);

		regis -> clk(clk);
		regis -> dir_inst(decode_inst_sg);
		regis -> dir_WB(dir_WB);
		regis -> data_WB(data_WB);
		regis -> dir1(decode_op1_sg);
		regis -> dir2(decode_op2_sg);
		regis -> inst_out(regis_inst_sg);
		regis -> data1_out(regis_data1_sg);
		//regis -> data2_out(regis_data2_sg);

		mux1 -> dir_WB(dir_WB);
		mux1 -> dir_op(decode_op1_sg);
		mux1 -> data_WB(data_WB);
		mux1 -> data_op(regis_data1_sg);
		mux1 -> data_out(data_out_sg1);

		/*mux2 -> dir_WB(dir_WB);
		mux2 -> dir_op(decode_op2_sg);
		mux2 -> data_WB(data_WB);
		mux2 -> data_op(regis_data2_sg);
		mux2 -> data_out(data_out_sg2);*/

		pipe2 -> clk(clk);
		pipe2 -> inst_in(regis_inst_sg);
		pipe2 -> data1_in(decode_op1_sg);
		pipe2 -> data2_in(data_out_sg1);
		pipe2 -> inst_out(inst);
		pipe2 -> data1_out(data1);
		pipe2 -> data2_out(data2);

	}

};

#endif