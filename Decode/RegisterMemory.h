#ifndef  REGISTERMEMORY_H
#define  REGISTERMEMORY_H

#include "Decode.h"
#include "Register.h"
#include "Pipe2.h"

SC_MODULE(RegisterMemory){

	sc_in< sc_int<12> > instruction_in;
	sc_in_clk clk;
	sc_in< sc_int<4> > dir_WB;
	sc_in< sc_int<8> > data_WB;

	sc_out< sc_int<4> > inst; 
	sc_out< sc_int<4> > dir; 
	sc_out< sc_int<8> > data;

	Register *regis;
	Decode *decode;
	Pipe2 *pipe2;

	sc_signal< sc_int<4> > decode_inst_sg, decode_op1_sg, decode_op2_sg, regis_inst_sg, dir_out_sg;
	sc_signal< sc_int<8> > regis_data1_sg; 

	SC_CTOR(RegisterMemory){

		regis = new Register("regis");
		decode =  new Decode("Decode");
		pipe2 = new Pipe2("Pipe2");

		decode -> inst_in(instruction_in);
		decode -> inst_out(decode_inst_sg);
		decode -> op1(decode_op1_sg);

		regis -> clk(clk);
		regis -> dir_inst(decode_inst_sg);
		regis -> dir1(decode_op1_sg);
		regis -> dir_WB(dir_WB);
		regis -> data_WB(data_WB);
		regis -> inst_out(regis_inst_sg);
		regis -> dir_out(dir_out_sg);
		regis -> data1_out(regis_data1_sg);
				
		pipe2 -> clk(clk);
		pipe2 -> inst_in(regis_inst_sg);
		pipe2 -> data1_in(dir_out_sg);
		pipe2 -> data2_in(regis_data1_sg);
		pipe2 -> inst_out(inst);
		pipe2 -> data1_out(dir);
		pipe2 -> data2_out(data);

	}

};

#endif