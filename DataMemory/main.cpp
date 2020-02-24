#include <systemc.h>
#include <TestBench.h>
#include <DataMemory.h>

int sc_main(int argc, char* argv[]){

	sc_time PERIOD(10,SC_NS);
	sc_time DELAY(10,SC_NS);
	sc_clock clock("clock",PERIOD,0.5,DELAY,true);

	TestBench tb("tb");
	DataMemory dm("dm");

	sc_signal< sc_uint<16> > instruction_og;
	sc_signal< sc_uint<8> > alu_result, data_WB;
	sc_signal< sc_uint<4> > register_dir_WB;

	dm.instruction_og(instruction_og);
	dm.alu_result(alu_result);
	dm.register_dir_WB(register_dir_WB);
	dm.data_WB(data_WB);
	dm.clk(clock);

	tb.instruction_og(instruction_og);
	tb.alu_result(alu_result);
	tb.register_dir_WB(register_dir_WB);
	tb.data_WB(data_WB);
	tb.clk(clock);

	sc_start();

	return 0;

}	
