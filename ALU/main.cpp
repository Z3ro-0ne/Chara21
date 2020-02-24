#include <iostream>
#include <systemc.h>
#include <ALU.h>
#include <TestBench.h>

int sc_main(int argc, char* argv[]){

	sc_time PERIOD(10,SC_NS);
	sc_time DELAY(10,SC_NS);
	sc_clock clock("clock",PERIOD,0.5,DELAY,true);

	ALU alu("alu");
	TestBench tb("tb");

	sc_signal< sc_uint<4> > inst, op1, op2, op3;
	sc_signal< sc_uint<8> > alu_out;

	alu.inst(inst);
	alu.op1(op1);
	alu.op2(op2);
	alu.op3(op3);
	alu.alu_out(alu_out);
	alu.clk(clock);


	tb.inst(inst);
	tb.op1(op1);
	tb.op2(op2);
	tb.op3(op3);
	tb.alu_out(alu_out);
	tb.clk(clock);

	sc_start();

	return 0;
}