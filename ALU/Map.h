#ifndef MAP_H
#define MAP_H

#include <systemc.h>
#include <stdlib.h>
#include "Entity.h"

struct COORD {
	sc_int<16> x;
	sc_int<16> y;
};

void createMap(int x, int y);
void moveBio(int x, int y);
void moveEmo(int x, int y);
void moveCult(int x, int y);
sc_int<4> Tired(sc_int<4> a, sc_int<4> b);
sc_int<4> Bored(sc_int<4> a, sc_int<4> b);
sc_int<4> Anxiety(sc_int<4> value, sc_int<4> bio, sc_int<4> cult, sc_int<4> emo);

Entity **Grid;
COORD pos;

SC_MODULE(Map){

	sc_in< sc_int<4> > inst_in, op1, op2;
	sc_out< sc_int<4> > value_out;

	int x , y, look;
	sc_int<4> bio, emo, cult;

	void alteration(){

		if(inst_in.read() == 2){

			switch(op1.read()){

				case 1: value_out.write(Tired(op2.read(), Grid[pos.x][pos.y].getBioTerm()));
						bio = Tired(op2.read(), Grid[pos.x][pos.y].getBioTerm());
					break;

				case 2: value_out.write(Bored(op2.read(),Grid[pos.x][pos.y].getCultTerm()));
						cult = Bored(op2.read(),Grid[pos.x][pos.y].getCultTerm());
					break;

				case 3: value_out.write(Anxiety(op2.read(),Grid[pos.x][pos.y].getBioTerm(),Grid[pos.x][pos.y].getCultTerm(),Grid[pos.x][pos.y].getEmoTerm()));
						emo = Anxiety(op2.read(),Grid[pos.x][pos.y].getBioTerm(),Grid[pos.x][pos.y].getCultTerm(),Grid[pos.x][pos.y].getEmoTerm());
					break;

				case 4: value_out.write(pos.x);
					break;

				case 5: value_out.write(pos.y);
					break;


				}

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

			case 1: moveBio(x, y);//SE MUEVE A UNA ENTIDAD ALTA EN BIOLOGICO
				break;

			case 2: moveCult(x, y);//SE MUEVE A UNA ENTIDAD ALTA EN CULTURA
				break;

			case 3: moveEmo(x, y);//SE MUEVE A UNA ENTIDAD ALTA EN EMOCION
				break;

			}

		}

		if(inst_in.read() == 4){

			x = 9;
			y = 9;
			createMap(x, y);
			pos.x = 0;
			pos.y = 0;


		}

	}

	SC_CTOR(Map){

		SC_METHOD(alteration);
			sensitive << inst_in << op1 << op2;

	}


};

void moveBio(int x, int y){

	sc_int<4> max;
	max = -10;
	int aux;
	aux = 0;

	for(int i = 0; i < x; i++){

		for(int j = 0; j < y; j++){

			if((Grid[i][j].getBioTerm() >= max) and (Grid[i][j].getAvailable() == true)){

				pos.x = i;
				pos.y = j;
				max = Grid[i][j].getBioTerm();

			} else if(Grid[i][j].getAvailable() == false){

				aux = Grid[i][j].getTimes();
				aux = aux+1;
				Grid[i][j].setTimes(aux);

				if(aux == 3){

					Grid[i][j].setAvailable(true);

				}

			} 

		}

	}

	aux = Grid[pos.x][pos.y].getTimes();
	Grid[pos.x][pos.y].setAvailable(false);
	Grid[pos.x][pos.y].setTimes(aux++);

	if(Grid[pos.x][pos.y].getTimes() == 2){

		Grid[pos.x][pos.y].setAvailable(true);
		Grid[pos.x][pos.y].setTimes(0);

	}


}

void moveCult(int x, int y){

	sc_int<4> max;
	max = -10;
	int aux;
	aux = 0;

	for(int i = 0; i < x; i++){

		for(int j = 0; j < y; j++){

			if((Grid[i][j].getCultTerm() >= max) and (Grid[i][j].getAvailable() == true)){

				pos.x = i;
				pos.y = j;
				max = Grid[i][j].getCultTerm();

			} else if(Grid[i][j].getAvailable() == false){

				aux = Grid[i][j].getTimes();
				aux = aux+1;
				Grid[i][j].setTimes(aux);

				if(aux == 3){

					Grid[i][j].setAvailable(true);

				}

			} 

		}

	}

	aux = Grid[pos.x][pos.y].getTimes();
	Grid[pos.x][pos.y].setAvailable(false);
	Grid[pos.x][pos.y].setTimes(aux++);

	if(Grid[pos.x][pos.y].getTimes() == 2){

		Grid[pos.x][pos.y].setAvailable(true);
		Grid[pos.x][pos.y].setTimes(0);

	}


}

void moveEmo(int x, int y){

	sc_int<4> max;
	max = -10;
	int aux;
	aux = 0;

	for(int i = 0; i < x; i++){

		for(int j = 0; j < y; j++){

			if((Grid[i][j].getEmoTerm() >= max) and (Grid[i][j].getAvailable() == true)){

				pos.x = i;
				pos.y = j;
				max = Grid[i][j].getEmoTerm();

			} else if(Grid[i][j].getAvailable() == false){

				aux = Grid[i][j].getTimes();
				aux = aux+1;
				Grid[i][j].setTimes(aux);

				if(aux == 3){

					Grid[i][j].setAvailable(true);

				}

			} 

		}

	}

	aux = Grid[pos.x][pos.y].getTimes();
	Grid[pos.x][pos.y].setAvailable(false);
	Grid[pos.x][pos.y].setTimes(aux++);

	if(Grid[pos.x][pos.y].getTimes() == 2){

		Grid[pos.x][pos.y].setAvailable(true);
		Grid[pos.x][pos.y].setTimes(0);

	}


}

void createMap(int x, int y){

	Grid = new Entity* [x];

		for(int j = 0; j < x; j++){

			Grid[j] = new Entity[y];
	
		}

	srand((unsigned)time(NULL));	
	int data1, data2, data3;

	for(int i = 0; i < x; i++){

		for(int j = 0; j < y; j++){

			data1 = (-10) + rand()%((10+1)-(-10));
			Grid[i][j].setBioTerm(data1);

			data2 = (-10) + rand()%((10+1)-(-10));
			Grid[i][j].setCultTerm(data2);

			data3 = (-10) + rand()%((10+1)-(-10));
			Grid[i][j].setEmoTerm(data3);         


		}

	}

}

sc_int<4> Tired(sc_int<4> value, sc_int<4> bio){

	sc_int<4> aux;

	aux = value + bio;

	if(aux > 10){

		aux = 10;

	} 

	if(aux > 0){

		aux--;

	} else {

		aux = 0;

	}

	return aux;

}

sc_int<4> Bored(sc_int<4> value, sc_int<4> cult){

	sc_int<4> aux;

	aux = value + cult;

	if(aux > 10){

	aux = 10;

	} 

	if(aux > 0){

		aux--;

	} else {

		aux = 0;

	}

	return aux;

}

sc_int<4> Anxiety(sc_int<4> value, sc_int<4> bio, sc_int<4> cult, sc_int<4> emo){

	sc_int<4> desire;
	sc_int<4> aux;

	desire = 10;

	aux = value + emo;

	if(aux > 10){

		aux = 10;

	}

	if(((desire - bio) >= 1) and ((desire - bio < 3))){

		if(aux > 0){

			aux--;

		}

	} else if(((desire - bio) >= 3) and ((desire - bio) < 6)){

			if(aux > 0){

				aux = aux - 3;

				if(aux < 0){

					aux = 0;

				}

			}

		} else if(((desire - bio) >= 5) and ((desire - bio) < 9)){

			if(aux > 0){

				aux = aux - 5;

				if(aux < 0){

					aux = 0;

				}

			}

		}

		if(((desire - cult) >= 1) and ((desire - cult) < 3)){

			if(aux > 0){

				aux--;

			}

		} else if(((desire - cult) >= 3) and ((desire - cult) < 6)){

			if(aux > 0){

				aux = aux - 3;

				if(aux < 0){

					aux = 0;

				}

			}

		} else if(((desire - cult) >= 6) and ((desire - cult) < 9)){

			if(aux > 0){

				aux = aux - 5;

				if(aux < 0){

					aux = 5;

				}

			}

		}

		return aux;

	}


#endif