#ifndef SUPERADDER_H
#define SUPERADDER_H

#include <systemc.h>

sc_int<4> Tired(sc_int<4> a, sc_int<4> b);
sc_int<4> Bored(sc_int<4> a, sc_int<4> b);
sc_int<4> Anxiety(sc_int<4> value, sc_int<4> bio, sc_int<4> cult, sc_int<4> emo);

SC_MODULE(SuperAdder){

	sc_in< sc_int<4> > dir, value, bio, emo, cult;
	sc_out< sc_int<4> > result;

	void SuperAdd(){

		switch(dir.read()){

			case 1: result.write(Tired(value, bio)); 
				break;

			case 2: result.write(Bored(value, cult));
				break;

			case 3: result.write(Anxiety(value, bio, cult, emo));
				break;

			default: result.write(value.read());
				break;

		}

	}

	SC_CTOR(SuperAdder){

		SC_METHOD(SuperAdd);
			sensitive << dir << value << bio << emo << cult;

	}

};

sc_int<4> Tired(sc_int<4> value, sc_int<4> bio){

	sc_int<4> aux;

	aux = value + bio;

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