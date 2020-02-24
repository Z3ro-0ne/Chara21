#include <iostream>
#include <systemc.h>
#include <RegisterMemory.h>
#include <TestBench.h>

int sc_main(int argc, char* argv[]){

	sc_time PERIOD(10,SC_NS);
	sc_time DELAY(10,SC_NS);
	sc_clock clock("clock",PERIOD,0.5,DELAY,true);

	RegisterMemory rg("rg");
	TestBench tb("tb");

	sc_signal< sc_uint <16> > instruction_in, instruction_og;
	sc_signal< sc_uint <4> > inst, data1, data2, data3;
	//sc_signal<bool> activate_writing;

	rg.instruction_in(instruction_in);
	rg.inst(inst);
	rg.data1(data1);
	rg.data2(data2);
	rg.data3(data3);
	rg.instruction_og(instruction_og);
	rg.clk(clock);


	tb.instruction_in(instruction_in);
	tb.inst(inst);
	tb.data1(data1);
	tb.data2(data2);
	tb.data3(data3);
	tb.instruction_og(instruction_og);
	tb.clk(clock);

	sc_start();

	return 0;
}