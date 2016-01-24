#include "Vec.h"
#include <string>
#include <math.h>

using namespace std;

class Circulo{
public:
	Vec centro;
	float radio;
	string id;

	Circulo(){
		centro = Vec(0,0);
		radio = 0;
		id = "-";
	}

	Circulo(string id, Vec centro, float radio){
		this->id = id;
		this->centro = centro;
		this->radio = radio;
	}

	~Circulo(){}

	void print(){
		cout << id;
		centro.print();
		cout << radio << endl;
	}

	bool chocaraCon(const Rectangulo &rec){		
		return !(centro.y - radio > rec.ySup() || centro.y + radio < rec.yInf());
	}

	float distA(const Rectangulo& rec){
		if (rec.yInf() <= centro.y && centro.y <= rec.ySup())
			return rec.x() - (centro.x + radio);
		
		float deltaY = 0;
		if (centro.y > rec.ySup())
			deltaY = centro.y - rec.ySup();
		else
			deltaY = rec.yInf() - centro.y;

		float deltaX = sqrt(radio*radio - deltaY*deltaY);

		return (rec.x() - centro.x - deltaX);
	}
};