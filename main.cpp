#include <systemc.h>
#include <iostream>
#include "Chara21.h"
#include "SuperTestBench.h"

int sc_main(int argv, char* argc[]){

	sc_time PERIOD(10,SC_NS);//SC_PS SC_SEC . . .
	sc_time DELAY(10,SC_NS);	
	sc_clock clock("clock",PERIOD,0.5,DELAY,true);

	Chara21 bc("bc");
	SuperTestBench tb("tb");

	sc_signal< sc_int<4> > inst_sg, dir_sg, data_sg, data_WB_sg, dir_WB_sg;

	bc.clk(clock);
	bc.inst_out(inst_sg);
	bc.dir_out(dir_sg);
	bc.data_out(data_sg);
	bc.data_WB(data_WB_sg);
	bc.dir_WB(dir_WB_sg);

	tb.clk(clock);
	tb.inst_out(inst_sg);
	tb.dir_out(dir_sg);
	tb.data_out(data_sg);
	tb.data_WB(data_WB_sg);
	tb.dir_WB(dir_WB_sg);

	sc_start();

	return 0;

}