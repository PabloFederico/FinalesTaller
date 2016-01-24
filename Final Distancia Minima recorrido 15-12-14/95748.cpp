// 95748.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <iostream>
#include "stdlib.h"
#include <vector>
#include <fstream>
#include "string.h"

using namespace std;

typedef struct {
	char id[20];
	float x;
	float y;
	float distanciaRecorrida;
}Personaje;

typedef struct {
	float xInicial;
	float xFinal;
}Plataforma;

typedef struct {
	float y;
	Plataforma plataformas[10];
	int cantidadPlataformas;
}Nivel;


int procesarNiveles(Nivel* niveles){
	FILE* archivo;
	archivo = fopen("escenario.txt", "r");

	int i;
	int j = 0;
	for (i = 0; ! feof(archivo); i++){
		int j = 0;
		int cantidadDePlataformas;
		fscanf(archivo, "%i %f %f %f", &cantidadDePlataformas, &niveles[i].y, &niveles[i].plataformas[j].xInicial, &niveles[i].plataformas[j].xFinal);
		//cout << cantidadDePlataformas << "|" << niveles[i].y << "|" << niveles[i].plataformas[j].xInicial << "|" << niveles[i].plataformas[j].xFinal;
		j++;
		while (cantidadDePlataformas > j){
			fscanf(archivo, " %f %f", &niveles[i].plataformas[j].xInicial, &niveles[i].plataformas[j].xFinal);
			//cout << "|" << niveles[i].plataformas[j].xInicial << "|" << niveles[i].plataformas[j].xFinal;
			j++;
		}
		//cout << endl;
		niveles[i].cantidadPlataformas = cantidadDePlataformas;
	}
	niveles[i].y = 0;
	niveles[i].plataformas[0].xInicial = -50;
	niveles[i].plataformas[0].xFinal = 50;
	niveles[i].cantidadPlataformas = 1;
	fclose(archivo);
	return (i+1);
}

int compararNiveles (const void* n1, const void* n2){
	float y1 = ((Nivel*)n1)->y;
	float y2 = ((Nivel*)n2)->y;
	if (y1 < y2) return 1;
	if (y1 == y2) return 0;
	return -1;
}

void ordenarNivelesPorAltura(Nivel* niveles, int cantidad){
	qsort(niveles, cantidad, sizeof(Nivel), compararNiveles);
}

bool personajeChocaConPlataforma(Personaje pj, Plataforma plataforma){
	return ((pj.x >= plataforma.xInicial) && (pj.x <= plataforma.xFinal));
}

int compararPersonajes(const void *pj1, const void *pj2){
	float d1 = ((Personaje*)pj1)->distanciaRecorrida;
	float d2 = ((Personaje*)pj2)->distanciaRecorrida;
	if (d1 > d2) return 1;
	if (d1 == d2) return 0;
	return -1;
}

Personaje procesarCaidaDePersonaje(Nivel* niveles, int cantidadNiveles, Personaje personaje){
	vector<Personaje> posiciones;
	posiciones.push_back(personaje);
	for(int i = 0; i < cantidadNiveles; i++){
		int cantidadPJS = posiciones.size();
		for (int j = 0; j < cantidadPJS; j++){
			if (niveles[i].y >= posiciones[j].y) continue;
			for (int k = 0; k < niveles[i].cantidadPlataformas; k++){
				if ((posiciones[j].y != -1) && (personajeChocaConPlataforma(posiciones[j], niveles[i].plataformas[k]))){
					posiciones[j].distanciaRecorrida = posiciones[j].distanciaRecorrida + posiciones[j].y - niveles[i].y;
					posiciones[j].y = niveles[i].y;

					if (niveles[i].y != 0){
						Personaje pj1, pj2;

						strcpy(pj1.id, posiciones[j].id);
						pj1.distanciaRecorrida = posiciones[j].distanciaRecorrida + (posiciones[j].x - niveles[i].plataformas[k].xInicial) /*+ 0.001*/;
						pj1.x = niveles[i].plataformas[k].xInicial - 0.001;
						pj1.y = posiciones[j].y;

						strcpy(pj2.id, posiciones[j].id);
						pj2.distanciaRecorrida = posiciones[j].distanciaRecorrida + (niveles[i].plataformas[k].xFinal - posiciones[j].x) /*+ 0.001*/;
						pj2.x = niveles[i].plataformas[k].xFinal + 0.001;
						pj2.y = posiciones[j].y;

						posiciones.push_back(pj1);
						posiciones.push_back(pj2);
						posiciones[j].y = -1;
					}
				}
			}
		}
	}
	int cantidadPJS = posiciones.size();
	Personaje pjs[256];
	for (int i = 0; i < cantidadPJS; i++){
		pjs[i] = posiciones[i];
	}
	qsort(pjs, cantidadPJS, sizeof(Personaje), compararPersonajes);
	int i = -1;
	bool encontrado = false;
	while (! encontrado){
		i++;
		if (pjs[i].y != -1) encontrado = true;
	}
	Personaje pjConMenorDistancia = pjs[i];
	return pjConMenorDistancia;
}

Personaje* procesarPersonajes(Nivel* niveles, int cantidadNiveles, Personaje* personajes, int &cantidadPersonajes){
	FILE* archivo;
	archivo = fopen("personajes.txt", "r");
	int cantidadPJ;
	for (cantidadPJ = 0; ! feof(archivo); cantidadPJ++){
		fscanf(archivo, "%s %f %f", personajes[cantidadPJ].id, &personajes[cantidadPJ].x, &personajes[cantidadPJ].y);
		personajes[cantidadPJ].distanciaRecorrida = 0;
		Personaje pjConMenorDistancia = procesarCaidaDePersonaje(niveles, cantidadNiveles, personajes[cantidadPJ]);
		personajes[cantidadPJ] = pjConMenorDistancia;
	}
	fclose(archivo);
	cantidadPersonajes = cantidadPJ;
	return personajes;
}

void ordenarPersonajesPorDistancia(Personaje* personajes, int cantidadPersonajes){
	qsort(personajes, cantidadPersonajes, sizeof(Personaje), compararPersonajes);
}

void imprimirPersonajesPorPantalla(Personaje* personajes, int cantidadPersonajes){
	cout << "ID_PJ\t\t\tDIST" << endl;
	for (int i = 0; i < cantidadPersonajes; i++){
		cout << personajes[i].id << "\t\t\t" << personajes[i].distanciaRecorrida << endl;
	}
	getchar();
}

int main(int argc, char* argv[])
{
	Nivel niveles[9];
	int cantidadNiveles = procesarNiveles(niveles);
	ordenarNivelesPorAltura(niveles, cantidadNiveles);
	Personaje personajes[10];
	int cantidadPersonajes;
	Personaje* pjs = procesarPersonajes(niveles, cantidadNiveles, personajes, cantidadPersonajes);
	ordenarPersonajesPorDistancia(pjs, cantidadPersonajes);
	imprimirPersonajesPorPantalla(pjs, cantidadPersonajes);
	return 0;
}

