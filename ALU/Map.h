#ifndef MAP_H
#define MAP_H

#include <systemc.h>
#include <stdlib.h>
#include "Entity.h"

struct COORD {
	sc_int<32> x;
	sc_int<32> y;
};

void createMap(int x, int y);
void moveBio(int x, int y);
void moveEmo(int x, int y);
void moveCult(int x, int y);
sc_int<8> Tired(sc_int<8> a, sc_int<8> b);
sc_int<8> Bored(sc_int<8> a, sc_int<8> b);
sc_int<8> Anxiety(sc_int<8> value, sc_int<8> bio, sc_int<8> cult, sc_int<8> emo);

Entity **Grid;
COORD pos;
sc_int<8> bio, emo, cult;

SC_MODULE(Map){

	sc_in< sc_int<4> > inst_in, dir_in;
	sc_in< sc_int<32> > data_in;
	sc_out< sc_int<4> > inst_out, dir_out;
	sc_out< sc_int<32> > value_out;

	int x , y, look;

	void alteration(){

		if(inst_in.read() == 2){

			switch(dir_in.read()){

				case 1: value_out.write(Tired(data_in.read(), Grid[pos.x][pos.y].getBioTerm()));
						bio = Tired(data_in.read(), Grid[pos.x][pos.y].getBioTerm());
						inst_out.write(inst_in.read());
						dir_out.write(dir_in.read());
						/*std::cout<<"case 1"<<std::endl;
						std::cout<<bio<<std::endl;
						std::cout<<value_out.read()<<std::endl;*/
					break;

				case 2: value_out.write(Bored(data_in.read(),Grid[pos.x][pos.y].getCultTerm()));
						cult = Bored(data_in.read(),Grid[pos.x][pos.y].getCultTerm());
						inst_out.write(inst_in.read());
						dir_out.write(dir_in.read());
						/*std::cout<<"case 2"<<std::endl;
						std::cout<<cult<<std::endl;
						std::cout<<value_out.read()<<std::endl;*/
					break;

				case 3: value_out.write(Anxiety(data_in.read(),Grid[pos.x][pos.y].getBioTerm(),Grid[pos.x][pos.y].getCultTerm(),Grid[pos.x][pos.y].getEmoTerm()));
						emo = Anxiety(data_in.read(),Grid[pos.x][pos.y].getBioTerm(),Grid[pos.x][pos.y].getCultTerm(),Grid[pos.x][pos.y].getEmoTerm());
						inst_out.write(inst_in.read());
						dir_out.write(dir_in.read());
						/*std::cout<<"case 3"<<std::endl;
						std::cout<<emo<<std::endl;
						std::cout<<value_out.read()<<std::endl;*/
					break;

				case 4: value_out.write(pos.x);
						inst_out.write(inst_in.read());
						dir_out.write(dir_in.read());
						/*std::cout<<"case 4"<<std::endl;
						std::cout<<pos.x<<std::endl;
						std::cout<<value_out.read()<<std::endl;*/
					break;

				case 5: value_out.write(pos.y);
						inst_out.write(inst_in.read());
						dir_out.write(dir_in.read());
						/*std::cout<<"case 5"<<std::endl;
						std::cout<<pos.y<<std::endl;
						std::cout<<value_out.read()<<std::endl;*/
					break;


				}

		} else if(inst_in.read() == 3){//SE BUSCA EL VALOR MAS BAJO PARA DECIDIR QUE ESTIMULACION BUSCAR

				if((bio <= emo) and (bio <= cult)){

				look = 1;

			} else if((cult <= emo) and (cult <= bio)){

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

			} else if(inst_in.read() == 4){//CREACION DEL MAPA

						x = 10;
						y = 10;
						createMap(x, y);
						pos.x = 0;
						pos.y = 0;
			} else{

				value_out.write(data_in.read());
				dir_out.write(dir_in.read());
				inst_out.write(inst_in.read());
				
			}

		}


	SC_CTOR(Map){

		SC_METHOD(alteration);
			sensitive << inst_in << dir_in << data_in;

	}


};

void moveBio(int x, int y){

	sc_int<8> max;
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

	sc_int<8> max;
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

	sc_int<8> max;
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

sc_int<8> Tired(sc_int<8> value, sc_int<8> bio){

	sc_int<8> aux;

	aux = value + bio;

	if(aux > 10){

		aux = 10;

	} 

	if(aux > 0){

		aux = aux - 1;

	}  

	if(aux < 0) {

		aux = 0;

	}

	return aux;

}

sc_int<8> Bored(sc_int<8> value, sc_int<8> cult){

	sc_int<8> aux;

	aux = value + cult;

	if(aux > 10){

	aux = 10;

	} 

	if(aux > 0){

		aux = aux - 1;

	}  

	if(aux < 0) {

		aux = 0;

	}

	return aux;

}

sc_int<8> Anxiety(sc_int<8> value, sc_int<8> bio, sc_int<8> cult, sc_int<8> emo){

	sc_int<8> desire;
	sc_int<8> aux;

	desire = 10;

	aux = value + emo;

	if(aux > 10){

		aux = 10;

	}

	if(((desire - bio) >= 1) and ((desire - bio < 3))){

		if(aux > 0){

			aux = aux - 1;

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

				aux = aux - 1;

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

		if(aux < 0){

			aux = 0;

		}

		return aux;

	}


#endif