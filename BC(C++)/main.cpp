#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "BC.h"
#include "Entity.h"

struct COORD {
	int x;
	int y;
};

void fillMap(Entity **node, int x, int y);
COORD moveBio(Entity **node, int x, int y);
COORD moveEmo(Entity **node, int x, int y);
COORD moveCult(Entity **node, int x, int y);

Entity **Node;

int main(){

	COORD coord;
	BC Chara;
	int x = 9,y = 9;
	bool sim = true;

	coord.x = 0;
	coord.y = 0;

	Node = new Entity* [x];//CREACION DEL MAPA

	for(int j = 0; j < x; j++){

		Node[j] = new Entity[y];
	
	}
	
	fillMap(Node, x, y);

	int look = 1;

	while(sim == true){//INICIO DE LA SIMULACION

		Chara.setBio(Chara.getBio() + Node[coord.x][coord.y].getBioTerm());
		Chara.setCult(Chara.getCult() + Node[coord.x][coord.y].getCultTerm());
		Chara.setEmo(Chara.getEmo() + Node[coord.x][coord.y].getEmoTerm());

		Chara.Tired();
		Chara.Bored();
		Chara.Anxiety();

		//AQUI SE DECIDE CUAL TERMOMETRO TIENE MAS PRIORIDAD A LA HORA DE MOVERSE A UNA NUEVA ENTIDAD
		if((Chara.getBio() <= Chara.getEmo()) and (Chara.getBio() <= Chara.getCult())){

			look = 1;

		} else if((Chara.getCult() <= Chara.getEmo()) and (Chara.getCult() <= Chara.getBio())){

			look = 2;

		} else if((Chara.getEmo() <= Chara.getBio()) and (Chara.getEmo() <= Chara.getCult())){

			look = 3;

		}

		switch(look){

			case 1: coord = moveBio(Node, x, y);//SE MUEVE A UNA ENTIDAD ALTA EN BIOLOGICO
				break;

			case 2: coord = moveCult(Node, x, y);//SE MUEVE A UNA ENTIDAD ALTA EN CULTURA
				break;

			case 3: coord = moveEmo(Node, x, y);//SE MUEVE A UNA ENTIDAD ALTA EN EMOCION
				break;

		}

		Chara.setX(coord.x);//"MOVIMIENTO" EN SI
		Chara.setY(coord.y);

		std::cout<<"\nEstado de Chara:\n\n";
		std::cout<<"Coordenada X: "<<Chara.getX()<<std::endl;
		std::cout<<"Coordenada Y: "<<Chara.getY()<<std::endl;
		std::cout<<"Status Biologico: "<<Chara.getBio()<<std::endl;
		std::cout<<"Status Cultural: "<<Chara.getCult()<<std::endl;
		std::cout<<"Status Emocional: "<<Chara.getEmo()<<std::endl;

		sleep(1);

		if((Chara.getBio() == 0) and (Chara.getEmo() == 0) and (Chara.getCult() == 0)){

			sim = false;
			std::cout<<"ALLAHU AKHBAR!!!!"<<std::endl;
			std::cout<<"*explodes violently*"<<std::endl;

		}//POR SI CHARA MUERE A MITAD DE CAMINO :V


	}


	for(int i = 0; i < x; i++){

		delete[] Node[i];

	}

	delete[] Node;

	return 0;

}

void fillMap(Entity **node, int x, int y){

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

COORD moveBio(Entity **node, int x, int y){

	int max = -10;
	int aux = 0;
	COORD pos;

	for(int i = 0; i < x; i++){

		for(int j = 0; j < y; j++){

			if((node[i][j].getBioTerm() >= max) and (node[i][j].getAvailable() == true)){

				pos.x = i;
				pos.y = j;
				max = node[i][j].getBioTerm();

			} else if(node[i][j].getAvailable() == false){

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

	int max = -10;
	int aux = 0;
	COORD pos;

	for(int i = 0; i < x; i++){

		for(int j = 0; j < y; j++){

			if((node[i][j].getCultTerm() >= max) and (node[i][j].getAvailable() == true)){

				pos.x = i;
				pos.y = j;
				max = node[i][j].getCultTerm();

			} else if(node[i][j].getAvailable() == false){

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

	int max = -10;
	int aux = 0;
	COORD pos;

	for(int i = 0; i < x; i++){

		for(int j = 0; j < y; j++){

			if((node[i][j].getEmoTerm() >= max) and (node[i][j].getAvailable() == true)){

				pos.x = i;
				pos.y = j;
				max = node[i][j].getEmoTerm();

			} else if(node[i][j].getAvailable() == false){

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
