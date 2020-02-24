#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <systemc.h>

class Entity{

	private:
		sc_int<4> bio_term;
		sc_int<4> cult_term;
		sc_int<4> emo_term;
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

		Entity(int b, int c, int e, int t, bool a){

			bio_term = b;
			cult_term = c;
			emo_term = e;
			times = t;
			available = a;

		}

		void setBioTerm(int b){

			bio_term = b;

		}

		void setCultTerm(int c){

			cult_term = c;

		}

		void setEmoTerm(int e){

			emo_term = e;

		}

		void setTimes(int t){

			times = t;

		}

		void setAvailable(bool a){

			available = a;

		}

		sc_int<4> getBioTerm(){

			return bio_term;

		}

		sc_int<4> getCultTerm(){

			return cult_term;

		}

		sc_int<4> getEmoTerm(){

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