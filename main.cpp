#include <systemc.h>
#include <iostream>
#include "Chara21.h"
#include "TESTBENCH.h"

int sc_main(int argv, char* argc[]){

	sc_time PERIOD(10,SC_NS);//SC_PS SC_SEC . . .
	sc_time DELAY(10,SC_NS);	
	sc_clock clock("clock",PERIOD,0.5,DELAY,true);

	Chara21 bc("bc");
	TESTBENCH tb("tb");

	//sc_signal< sc_int<4> > out1_sg, out2_sg;

	bc.CLK(clock);
	//bc.out1(out1_sg);
	//bc.out2(out2_sg);

	//tb.CLK(clock);
	tb.clk(clock);
	//tb.out1(out1_sg);
	//tb.out2(out2_sg);

	sc_start();

	return 0;

}