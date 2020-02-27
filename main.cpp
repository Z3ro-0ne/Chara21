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

	sc_signal< sc_int<12> > out_sg;

	bc.clk(clock);
	bc.out(out_sg);
	//bc.out2(out2_sg);

	//tb.CLK(clock);
	tb.clk(clock);
	tb.out(out_sg);
	//tb.out2(out2_sg);

	sc_start();

	return 0;

}