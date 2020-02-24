#include <systemc.h>
#include <micro_BC.h>

int sc_main(int argv, char* argc[]){

	sc_time PERIOD(10,SC_NS);//SC_PS SC_SEC . . .
	sc_time DELAY(10,SC_NS);	
	sc_clock clock("clock",PERIOD,0.5,DELAY,true);

	micro_BC M("M");

	M.CLK(clock);

	sc_start();

	return 0;

}