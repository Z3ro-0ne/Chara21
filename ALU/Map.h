#ifndef MAP_H
#define MAP_H

#include <systemc.h>
#include <stdlib.h>
#include "Entity.h"

struct COORD {
	sc_int<16> x = 0;
	sc_int<16> y = 0;
};

void createMap(Entity **node, int x, int y);
COORD moveBio(Entity **node, int x, int y);
COORD moveEmo(Entity **node, int x, int y);
COORD moveCult(Entity **node, int x, int y);
sc_int<4> Tired(sc_int<4> a, sc_int<4> b);
sc_int<4> Bored(sc_int<4> a, sc_int<4> b);
sc_int<4> Anxiety(sc_int<4> value, sc_int<4> bio, sc_int<4> cult, sc_int<4> emo);


SC_MODULE(Map){

	sc_in< sc_int<4> > inst_in, op1, op2;
	//sc_in< sc_int<4> > add_in;
	sc_out< sc_int<4> > /*dir_out,*/ value_out/*, bio_out, cult_out, emo_out, coord_x, coord_y*/;

	Entity **Grid;
	COORD pos;
	int x = 9, y = 9, look;
	sc_int<4> bio, emo, cult;
	bool flag = true;

	void alteration(){

		if(inst_in.read() == 2){

			/*dir_out.write(op1.read());
			value_out.write(op2.read());
			bio_out.write(Grid[pos.x][pos.y].getBioTerm());
			cult_out.write(Grid[pos.x][pos.y].getCultTerm());
			emo_out.write(Grid[pos.x][pos.y].getEmoTerm());
			coord_x.write(pos.x);
			coord_y.write(pos.y);

			switch(op1.read()){

				case 1: bio = add_in.read();
					break;

				case 2: cult = add_in.read();
					break;

				case 3: emo = add_in.read();
					break;

			}*/

			//dir_out.write(op1.read());

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

		if(flag == true){

			createMap(Grid, x, y);
			flag = false;

		}

		SC_METHOD(alteration);
			sensitive << inst_in << op1 << op2;


	}

	/*~Map(){

		for(int i = 0; i < x; i++){

			delete Grid[i];

		}

		delete Grid;


	}*/


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

			} else if(node[i][j].getAvailable == false){

				aux = node[i][j].getTimes();
				aux = aux+1;
				node[i][j].setTimes(aux);

				if(aux == 3){

					node[i][j].setAvailable(true);

				}

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

			} else if(node[i][j].getAvailable == false){

				aux = node[i][j].getTimes();
				aux = aux+1;
				node[i][j].setTimes(aux);

				if(aux == 3){

					node[i][j].setAvailable(true);

				}

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

			} else if(node[i][j].getAvailable == false){

				aux = node[i][j].getTimes();
				aux = aux+1;
				node[i][j].setTimes(aux);

				if(aux == 3){

					node[i][j].setAvailable(true);

				}

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