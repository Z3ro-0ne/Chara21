#ifndef BC_H
#define BC_H

#include <iostream>

class BC{

private:
	int bio;
	int cult;
	int emo;
	int x;
	int y;

public:

	BC(){

		bio = 5;
		cult = 5;
		emo = 5;
		x = 0;
		y = 0;

	}

	BC(int _bio, int _cult, int _emo, int _x, int _y){

		bio = _bio;
		cult = _cult;
		emo = _emo;
		x = _x;
		y = _y;

	}

	void setBio(int _bio){

		bio = _bio;

		if(bio > 10){

			bio = 10;

		} else if(bio < 0){

			bio = 0;

		}


	}

	void setCult(int _cult){

		cult = _cult;

		if(cult > 10){

			cult = 10;

		} else if(cult < 0){

			cult = 0;

		}

	}

	void setEmo(int _emo){

		emo = _emo;

		if(emo > 10){

			emo = 10;

		} else if(emo < 0){

			emo = 0;

		}

	}

	void setX(int _x){

		x = _x;

	}

	void setY(int _y){

		y = _y;
	}

	int getBio(){

		return bio;

	}

	int getCult(){

		return cult;

	}

	int getEmo(){

		return emo;

	}

	int getX(){

		return x;

	}	

	int getY(){

		return y;

	}

	~BC(){}

	void Tired(){

		if(bio > 0){

			bio--;

		} else {

			bio = 0;

		}

	}

	void Bored(){

		if(cult > 0){

			cult--;

		} else {

			cult = 0;

		}

	}

	void Anxiety(){

		int desire = 10;

		if(((desire - bio) >= 1) and ((desire - bio) < 3)){

			if(emo > 0){

				emo--;

			}

		} else if(((desire - bio) >= 3) and ((desire - bio) < 6)){

				if(emo > 0){

					emo = emo - 3;

					if(emo < 0){

						emo = 0;

					}

				}


		} else if(((desire - bio) >= 5) and ((desire - bio) < 9)){

				if(emo > 0){

					emo = emo - 5;

					if(emo < 0){

						emo = 0;

					}

				}

		}


		if(((desire - cult) >= 1) and ((desire - cult) < 3)){

			if(emo > 0){

				emo--;

			}

		} else if(((desire - cult) >= 3) and ((desire - cult) < 6)){

				if(emo > 0){

					emo = emo - 3;

					if(emo < 0){

						emo = 0;

					}

				}


		} else if(((desire - cult) >= 6) and ((desire - cult) < 9)){

				if(emo > 0){

					emo = emo - 5;

					if(emo < 0){

						emo = 5;

					}

				}

		}

	}


};

#endif