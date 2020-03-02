#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>

class Entity{

	private:
		int bio_term;
		int cult_term;
		int emo_term;
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

		int getBioTerm(){

			return bio_term;

		}

		int getCultTerm(){

			return cult_term;

		}

		int getEmoTerm(){

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