#include "Vec.h"
#include <string>
#include <iostream>

using namespace std;

class Rectangulo{
public:
	string id;
	Vec infIzq;
	float ancho, alto;

	Rectangulo(){
		id = "-";
		infIzq = Vec(0,0);
		ancho = alto = 0;
	}

	Rectangulo(string id, Vec infIzq, float ancho, float alto){
		this->id = id;
		this->infIzq = infIzq;
		this->ancho = ancho;
		this->alto = alto;
	}

	~Rectangulo(){}

	void print(){
		cout << id;
		infIzq.print();
		cout << ancho << " " << alto << endl;
	}

	float ySup() const{
		return (infIzq.y + alto);
	}

	float yInf() const{
		return (infIzq.y);
	}

	float x() const{
		return infIzq.x;
	}
};