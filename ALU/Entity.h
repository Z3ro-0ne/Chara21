#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <systemc.h>

class Entity{

	private:
		sc_int<8> bio_term;
		sc_int<8> cult_term;
		sc_int<8> emo_term;
		int times;
		bool available;

	public:

		Entity(){

			bio_term = 0;
			cult_term = 0;
			emo_term = 0;
			times = 0;
			available = true;

		}

		Entity(sc_int<8> b, sc_int<8> c, sc_int<8> e, int t, bool a){

			bio_term = b;
			cult_term = c;
			emo_term = e;
			times = t;
			available = a;

		}

		void setBioTerm(sc_int<8> b){

			bio_term = b;

		}

		void setCultTerm(sc_int<8> c){

			cult_term = c;

		}

		void setEmoTerm(sc_int<8> e){

			emo_term = e;

		}

		void setTimes(int t){

			times = t;

		}

		void setAvailable(bool a){

			available = a;

		}

		sc_int<8> getBioTerm(){

			return bio_term;

		}

		sc_int<8> getCultTerm(){

			return cult_term;

		}

		sc_int<8> getEmoTerm(){

			return emo_term;

		}

		int getTimes(){

			return times;

		}

		bool getAvailable(){

			return available;
			
		}


};

#endif