#ifndef  REGISTERMEMORY_H
#define  REGISTERMEMORY_H

#include "Decode.h"
#include "Cache.h"
#include "Pipe2.h"
#include "Mux.h"

SC_MODULE(RegisterMemory){

	sc_in< sc_uint<16> > instruction_in;
	sc_in<bool> clk;
	sc_in< sc_uint<4> > dir_WB;
	sc_in< sc_uint<8> > data_WB;

	sc_out< sc_uint<4> > inst; /*data1,*/ 
	sc_out< sc_uint<8> > data2, data3;
	//sc_out< sc_uint<16> > instruction_og;

	Cache *cache;
	Decode *decode;
	Pipe2 *pipe2;
	Mux *mux1, *mux2;

	sc_signal< sc_uint<4> > decode_inst_sg, /*decode_op1_sg,*/ decode_op2_sg, decode_op3_sg, cache_inst_sg;
	sc_signal< sc_uint<8> >  /*cache_data1_sg,*/ cache_data2_sg, cache_data3_sg, data_out_sg1, data_out_sg2;
	//sc_signal< sc_uint<16> > sg1, sg2;

	SC_CTOR(RegisterMemory){

		cache = new Cache("Cache");
		decode =  new Decode("Decode");
		pipe2 = new Pipe2("Pipe2");
		mux1 = new Mux("Mux1");
		mux2 = new Mux("Mux2");
		

		decode -> inst_in(instruction_in);
		decode -> inst_out(decode_inst_sg);
		//decode -> op1(decode_op1_sg);
		decode -> op2(decode_op2_sg);
		decode -> op3(decode_op3_sg);
		//decode -> instruction(sg1);

		cache -> clk(clk);
		cache -> dir_inst(decode_inst_sg);
		//cache -> dir1(decode_op1_sg);
		cache -> dir_WB(dir_WB);
		cache -> data_WB(data_WB);
		cache -> dir2(decode_op2_sg);
		cache -> dir3(decode_op3_sg);
		cache -> inst_out(cache_inst_sg);
		//cache -> data1_out(cache_data1_sg);
		cache -> data2_out(cache_data2_sg);
		cache -> data3_out(cache_data3_sg);
		//cache -> instruction(sg1);
		//cache -> chain(sg2);

		mux1 -> dir_WB(dir_WB);
		mux1 -> dir_op(decode_op2_sg);
		mux1 -> data_WB(data_WB);
		mux1 -> data_op(cache_data2_sg);
		mux1 -> data_out(data_out_sg1);

		mux2 -> dir_WB(dir_WB);
		mux2 -> dir_op(decode_op3_sg);
		mux2 -> data_WB(data_WB);
		mux2 -> data_op(cache_data3_sg);
		mux2 -> data_out(data_out_sg2);

		pipe2 -> clk(clk);
		pipe2 -> inst_in(cache_inst_sg);
		//pipe2 -> data1_in(cache_data1_sg);
		pipe2 -> data2_in(data_out_sg1);
		pipe2 -> data3_in(data_out_sg2);
		pipe2 -> inst_out(inst);
		//pipe2 -> data1_out(data1);
		pipe2 -> data2_out(data2);
		pipe2 -> data3_out(data3);
		//pipe2 -> chain(sg2);
		//pipe2 -> instruction(instruction_og);

	}

};

#endif