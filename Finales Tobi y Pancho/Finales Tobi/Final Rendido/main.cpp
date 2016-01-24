#include <iostream>
#include <stdio.h>
#include <string>

#include "Parser.h"

using namespace std;

int main(){
	cout << "Hola Mundo!" << endl;
	Plataforma plataformas[100];
	Parser parserPlataformas("segmentos.txt");
	int cantidad = parserPlataformas.cargarPlataformas(plataformas);
	cout << "Cantidad: " << cantidad << endl;

	/*
	for (int i = 0; i < cantidad; i++){
		plataformas[i].print();
	}
	cout << endl;
	*/

	Parser parserBalas("tiros.txt");
	list<Plataforma> rotas;

	while (!parserBalas.fin()){
		Bala bala = parserBalas.siguienteBala();
		for (int i = 0; i < cantidad; i++){
			if (plataformas[i].laChoca(bala)){
				plataformas[i].colisionarCon(bala);
				if (!plataformas[i].vive()){
					rotas.push_back(plataformas[i]);
				}
				break;
			}
		}
	}

	list<Plataforma>::iterator rota = rotas.begin();

	for (; rota != rotas.end(); rota++){
		rota->print();
	}



	return 0;
}