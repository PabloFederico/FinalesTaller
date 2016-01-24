#include <iostream>
#include <stdio.h>
#include <string>
#include "Rectangulo.h"
#include "Circulo.h"

using namespace std;

int compararRectangulos(const void* r1, const void* r2){
	float a = ((Rectangulo*)r1)->infIzq.x;
	float b = ((Rectangulo*)r2)->infIzq.x;

	if (a < b) return -1;
	if (a == b) return 0;
	return 1;
}

class Parser{
public:
	FILE* file;

	Parser(string filename){
		this->file = fopen(filename.c_str(), "r");
	}

	~Parser(){
		fclose(file);
	}

	Rectangulo siguienteDispersor(){
		char id[SIZE];
		float x, y, alto, ancho;
		fscanf(file, "%s %f %f %f %f\n", id, &x, &y, &alto, &ancho);
		return Rectangulo(id, Vec(x, y), ancho, alto);
	}

	int cargarRectangulos(Rectangulo (&rectangulos)[SIZE]){
		bool eof = feof(file);
		int cantidad = 0;

		while (!eof){
			rectangulos[cantidad] = siguienteDispersor();
			cantidad++;
			eof = feof(file);
		}

		qsort(rectangulos, cantidad, sizeof(Rectangulo), compararRectangulos);

		return cantidad;
	}

	bool siguienteCirculo(Circulo& circulo){
		bool eof = feof(file);
		if (eof) return true;

		char id[SIZE];
		fscanf(file, "%s %f %f %f\n", id, &circulo.centro.x, &circulo.centro.y, &circulo.radio);
		circulo.id = id;
		return feof(file);
	}

	bool fin(){
		return feof(file);
	}
};

