#ifndef MAP_H
#define MAP_H

#include <systemc.h>
#include <stdlib.h>
#include "Entity.h"

struct COORD {
	sc_int<16> x;
	sc_int<16> y;
};

void createMap(Entity **node, int x, int y);
COORD moveBio(Entity **node, int x, int y);
COORD moveEmo(Entity **node, int x, int y);
COORD moveCult(Entity **node, int x, int y);

SC_MODULE(Map){

	sc_in< sc_int<4> > inst_in, op1, op2;
	sc_out< sc_int<4> > dir_out, value_out, bio_out, cult_out, emo_out;

	Entity **Grid;
	COORD pos;
	int x, y, look;
	sc_int<4> bio, emo, cult;
	bool flag;

	void alteration(){

		if(inst_in.read() == 2){

			dir_out.write(op1.read());
			value_out.write(op2.read());
			bio_out.write(Grid[pos.x][pos.y].getBioTerm());
			cult_out.write(Grid[pos.x][pos.y].getCultTerm());
			emo_out.write(Grid[pos.x][pos.y].getEmoTerm());

		}

		if(inst_in.read() == 3){//SE BUSCA EL VALOR MAS BAJO PARA DECIDIR QUE ESTIMULACION BUSCAR

			if((bio <= emo) and (bio <= cult)){

			look = 1;

		} else if((cult <= emo) and (cult <= emo)){

			look = 2;

		} else if((emo <= bio) and (emo <= cult)){

			look = 3;

		}

		switch(look){

			case 1: pos = moveBio(Grid, x, y);//SE MUEVE A UNA ENTIDAD ALTA EN BIOLOGICO
				break;

			case 2: pos = moveCult(Grid, x, y);//SE MUEVE A UNA ENTIDAD ALTA EN CULTURA
				break;

			case 3: pos = moveEmo(Grid, x, y);//SE MUEVE A UNA ENTIDAD ALTA EN EMOCION
				break;

			}


		}

	}

	SC_CTOR(Map){

		pos.x = 0;
		pos.y = 0;
		x = 9;
		y = 9;
		flag = true;

		if(flag == true){

			createMap(Grid, x, y);
			flag = false;

		}

		SC_METHOD(alteration);
			sensitive << inst_in << op1 << op2;


	}

	~Map(){

		for(int i = 0; i < x; i++){

			delete[] Grid[i];

		}

		delete[] Grid;


	}


};

COORD moveBio(Entity **node, int x, int y){

	sc_int<4> max = -10;
	int aux = 0;
	COORD pos;

	for(int i = 0; i < x; i++){

		for(int j = 0; j < y; j++){

			if((node[i][j].getBioTerm() >= max) and (node[i][j].getAvailable() == true)){

				pos.x = i;
				pos.y = j;
				max = node[i][j].getBioTerm();

			}

		}
	}

	aux = node[pos.x][pos.y].getTimes();
	node[pos.x][pos.y].setAvailable(false);
	node[pos.x][pos.y].setTimes(aux++);

	if(node[pos.x][pos.y].getTimes() == 2){

		node[pos.x][pos.y].setAvailable(true);
		node[pos.x][pos.y].setTimes(0);

	}

	return pos;

}

COORD moveCult(Entity **node, int x, int y){

	sc_int<4> max = -10;
	int aux = 0;
	COORD pos;

	for(int i = 0; i < x; i++){

		for(int j = 0; j < y; j++){

			if((node[i][j].getCultTerm() >= max) and (node[i][j].getAvailable() == true)){

				pos.x = i;
				pos.y = j;
				max = node[i][j].getCultTerm();

			}

		}
	}

	aux = node[pos.x][pos.y].getTimes();
	node[pos.x][pos.y].setAvailable(false);
	node[pos.x][pos.y].setTimes(aux++);

	if(node[pos.x][pos.y].getTimes() == 2){

		node[pos.x][pos.y].setAvailable(true);
		node[pos.x][pos.y].setTimes(0);

	}

	return pos;

}

COORD moveEmo(Entity **node, int x, int y){

	sc_int<4> max = -10;
	int aux = 0;
	COORD pos;

	for(int i = 0; i < x; i++){

		for(int j = 0; j < y; j++){

			if((node[i][j].getEmoTerm() >= max) and (node[i][j].getAvailable() == true)){

				pos.x = i;
				pos.y = j;
				max = node[i][j].getEmoTerm();

			}

		}
	}

	aux = node[pos.x][pos.y].getTimes();
	node[pos.x][pos.y].setAvailable(false);
	node[pos.x][pos.y].setTimes(aux++);

	if(node[pos.x][pos.y].getTimes() == 2){

		node[pos.x][pos.y].setAvailable(true);
		node[pos.x][pos.y].setTimes(0);

	}

	return pos;

}

void createMap(Entity **node, int x, int y){

	node = new Entity* [x];

		for(int j = 0; j < x; j++){

			node[j] = new Entity[y];
	
		}

	srand((unsigned)time(NULL));	
	int data1, data2, data3;

	for(int i = 0; i < x; i++){

		for(int j = 0; j < y; j++){

			data1 = (-10) + rand()%((10+1)-(-10));
			node[i][j].setBioTerm(data1);

			data2 = (-10) + rand()%((10+1)-(-10));
			node[i][j].setCultTerm(data2);

			data3 = (-10) + rand()%((10+1)-(-10));
			node[i][j].setEmoTerm(data3);         


		}

	}

}

#endif