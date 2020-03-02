#ifndef DATAMEMORY_H
#define DATAMEMORY_H

#include <systemc.h>
#include "Pipe4.h"
#include "Decoder2.h"
#include "RegisterFile.h"

SC_MODULE(DataMemory){

	sc_in< sc_int<8> > alu_result;
	sc_in< sc_int<4> > inst_in, dir_in;
	sc_in_clk clk;

	sc_out< sc_int<4> > register_dir_WB;
	sc_out< sc_int<8> > data_WB;

	
	RegisterFile *reg_file;
	Pipe4 *pipe4;

	sc_signal< sc_int<4> > sg1;
	sc_signal< sc_int<8> > sg2;

	SC_CTOR(DataMemory){

		reg_file = new RegisterFile("reg_file");
		pipe4 = new Pipe4("pipe4");

		reg_file -> instru_in(inst_in);
		reg_file -> dir_reg_in(dir_in);
		reg_file -> data_in(alu_result);
		reg_file -> dir_reg_out(sg1);
		reg_file -> data_out(sg2);

		pipe4 -> clk(clk);
		pipe4 -> dir_reg_in(sg1);
		pipe4 -> data_in(sg2);
		pipe4 -> dir_reg_out(register_dir_WB);
		pipe4 -> data_out(data_WB);

	}
	

};

#endif