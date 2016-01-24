#include <iostream>
#include <stdio.h>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include "circulo.h"
#include "rectangulo.h"
#include <vector>
using namespace std;
/* Funcion auxiliar par imprimir resultados de las pruebas: */
void print_test(char* name, bool result){
	printf("%s: %s\n", name, result? "OK" : "ERROR");
}


int main(int argc, char** argv)
{
/*
 *  NOTA: ESTO TENIA PROBLEMAS LEYENDO EL ULTIMO VALOR DE LA LINEA
 * LA FORMA DE ABAJO ANDA DE 10 :)
	vector<Circulo> circulos;
	FILE* fd_cir = fopen("circulos.txt", "r");
	if (!fd_cir) return 1;
	float a,b,c = 0;
	int x = fscanf(fd_cir,"%f %f %f", &a, &b, &c);
	while (x != -1){
		circulos.push_back(Circulo(a,b,c));
		printf("Circulo: A: %f, B: %f C:%f, X: %d\n",a,b,c,x);
		x = fscanf(fd_cir,"%f %f %f", &a, &b, &c);
	}
	fclose(fd_cir);

	vector<Rectangulo> rectangulos;
	FILE* fd_rec = fopen("rectangulos.txt", "r");
	if (!fd_rec) return 1;
	a = b = c = 0;
	float d = 0;
	x = -1;
	x = fscanf(fd_rec,"%f %f %f %f", &a, &b, &c, &d);
	while (x != -1){
		rectangulos.push_back(Rectangulo(a,b,c,d));
		printf("Rectangulo A: %f, B: %f C:%f, D:%f X: %d\n",a,b,c,d,x);
		x = fscanf(fd_rec,"%f %f %f", &a, &b, &c, &d);
	}
	fclose(fd_rec);
	*/


	ifstream fd_cir("circulos.txt", ifstream::in);
	string line;
	vector<Circulo> circulos;
	while(getline(fd_cir, line))    //read stream line by line
	{
		istringstream in(line);     //make a stream for the line itself
		float a, b, c;
		in >> a >> b >> c;      //now read the whitespace-separated floats
		circulos.push_back(Circulo(a,b,c));
		printf("Circulo: A: %f, B: %f C:%f\n",a,b,c);
	}
	fd_cir.close();

	line.clear();
	ifstream fd_rec("rectangulos.txt", ifstream::in);
	vector<Rectangulo> rectangulos;
	while(getline(fd_rec, line))    //read stream line by line
	{
		istringstream in(line);     //make a stream for the line itself
		float a, b, c,d;
		in >> a >> b >> c >> d;      //now read the whitespace-separated floats
		rectangulos.push_back(Rectangulo(a,b,c,d));
		printf("Rectangulo: A: %f, B: %f C:%f D: %f\n",a,b,c,d);
	}
	fd_rec.close();
	cout<< "Circulos con rectangulos\n";
	for (vector<Circulo>::iterator itC = circulos.begin(); itC != circulos.end(); itC++){
		for(vector<Rectangulo>::iterator itR = rectangulos.begin(); itR != rectangulos.end(); itR++){
			if (itC->colisionarConRectangulo(*itR)) std::cout <<"OK: "<<(itC)->tostring() << " ; " << (itR)->tostring() << "\n";
			else std::cout << "FALSE: "<<(itC)->tostring() << " ; " << (itR)->tostring() << "\n";
	//		print_test("Circulo c3(5,12.5,12.5); Rectangulo r(5,5,5,5);", c3.colisionarConRectangulo(&r));
		}
	}

	cout<< "Circulos con Circulos\n";
	for (vector<Circulo>::iterator itC = circulos.begin(); itC != circulos.end(); itC++){
		for(vector<Circulo>::iterator itR = circulos.begin(); itR != circulos.end(); itR++){
			if ((itC->colisionarConCirculo(*itR)) or (itR->colisionarConCirculo(*itC))) std::cout <<"OK: "<<(itC)->tostring() << " ; " << (itR)->tostring() << "\n";
			else std::cout << "FALSE: "<<(itC)->tostring() << " ; " << (itR)->tostring() << "\n";
	//		print_test("Circulo c3(5,12.5,12.5); Rectangulo r(5,5,5,5);", c3.colisionarConRectangulo(&r));
		}
	}
	
	cout<< "rectangulos con rectangulos\n";
		for(vector<Rectangulo>::iterator itC = rectangulos.begin(); itC != rectangulos.end(); itC++){
		for(vector<Rectangulo>::iterator itR = rectangulos.begin(); itR != rectangulos.end(); itR++){
			if ((itC->colisionarConRectangulo(*itR)) or (itR->colisionarConRectangulo(*itC))) std::cout <<"OK: "<<(itC)->tostring() << " ; " << (itR)->tostring() << "\n";
			else std::cout << "FALSE: "<<(itC)->tostring() << " ; " << (itR)->tostring() << "\n";
	//		print_test("Circulo c3(5,12.5,12.5); Rectangulo r(5,5,5,5);", c3.colisionarConRectangulo(&r));
		}
	}
/*
	Circulo c(5,5,5);
	Rectangulo r(5,5,5,5);
	print_test("Circulo c(5,5,5); Rectangulo r(5,5,5,5);", c.colisionarConRectangulo(&r));
	Circulo c2(5,7.5,7.5);
	print_test("Circulo c2(5,7.5,7.5); Rectangulo r(5,5,5,5);", c2.colisionarConRectangulo(&r));
	Circulo c3(5,12.5,12.5);
	print_test("Circulo c3(5,12.5,12.5); Rectangulo r(5,5,5,5);", c3.colisionarConRectangulo(&r));
	Circulo c4(1,12.5,12.5);
	print_test("Circulo c4(1,12.5,12.5); Rectangulo r(5,5,5,5);", c4.colisionarConRectangulo(&r));*/
	return 0;
}
