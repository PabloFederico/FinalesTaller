#include "stdafx.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include <iostream>
#include "math.h"

using namespace std;

const int MAX_BALAS = 50;
const float ALTO = 60;
const float ANCHO = 65;
const float COMIENZO_DIAGONAL_X = 60;
const float FIN_DIAGONAL1_Y = 40;
const float FIN_DIAGONAL3_Y = 20;

typedef struct{
	char id[20];
	float xInicial;
	float yInicial;
	float xFinal;
	float yFinal;
	float longitud;
	char destino[20];
}Recorrido;



int cargarBalas(Recorrido* recorridos){
	FILE* archivo;
	archivo = fopen("balas.txt", "r");
	int i = 0;
	if (archivo == NULL){
		cout << "El fichero no existe \n";
		getchar();
	}
	else {
		for (i=0; ! feof(archivo); i++){
			fscanf(archivo, "%s %f %f %f %f\n", recorridos[i].id, &recorridos[i].xInicial,
				&recorridos[i].yInicial, &recorridos[i].xFinal, &recorridos[i].yFinal);
			recorridos[i].longitud = -1;
			strcpy(recorridos[i].destino, "");
		}
	}
	fclose(archivo);
	return i;
}

float calcularDistancia(float xInicial, float yInicial, float xFinal, float yFinal){
	return sqrt((pow((xFinal-xInicial),2)) + (pow((yFinal-yInicial),2)));
}

bool verificarBordeSuperior(Recorrido &recorrido, float pendiente, float ordAlOrigen){
	bool choco = false;
	// y = pendiente*x + ordAlOrigen
	float interseccionConBordeX = ((ALTO-ordAlOrigen)/pendiente);
	if (interseccionConBordeX <= COMIENZO_DIAGONAL_X && interseccionConBordeX >= 0 && recorrido.xInicial < interseccionConBordeX){
		choco = true;
		float distancia = calcularDistancia(recorrido.xInicial, recorrido.yInicial, interseccionConBordeX, ALTO);
		recorrido.longitud = distancia;
		strcpy(recorrido.destino, "Borde superior");
	}
	return choco;
}

bool verificarBordeUno(Recorrido &recorrido, float pendiente, float ordAlOrigen){
	bool choco = false;
	float pendienteDiagonal = ((FIN_DIAGONAL1_Y - ALTO) / (ANCHO - COMIENZO_DIAGONAL_X));
	float ordAlOrigenDiagonalA = FIN_DIAGONAL1_Y - (pendienteDiagonal*ANCHO);
	float ordAlOrigenDiagonalB = ALTO - (pendienteDiagonal*COMIENZO_DIAGONAL_X);
	if ( ordAlOrigenDiagonalA != ordAlOrigenDiagonalB){
		cout << "La ordenada al origen no es igual verificando choque con borde 1 para la bala " << recorrido.id << "\n";
		cout << "OrdAlOrigenA: "<< ordAlOrigenDiagonalA << " | OrdAlOrigenB:" << ordAlOrigenDiagonalB << "\n";
	}
	float xInterseccion = ((ordAlOrigenDiagonalA - ordAlOrigen) / (pendiente - pendienteDiagonal));
	float yInterseccionA = ((pendienteDiagonal*xInterseccion) + ordAlOrigenDiagonalA);
	float yInterseccionB = ((pendiente*xInterseccion) + ordAlOrigen);
	if (yInterseccionA != yInterseccionB){
		cout << "La interseccion en y no es igual verificando choque con borde 1 para la bala " << recorrido.id << "\n";
		cout << "YintersecA: "<< yInterseccionA << " | YintersecB:" << yInterseccionB << "\n";
	}

	if (xInterseccion >= COMIENZO_DIAGONAL_X && xInterseccion <= ANCHO && yInterseccionA >= FIN_DIAGONAL1_Y && yInterseccionA <= ALTO){
		choco = true;
		float distancia = calcularDistancia(recorrido.xInicial, recorrido.yInicial, xInterseccion, yInterseccionA);
		recorrido.longitud = distancia;
		strcpy(recorrido.destino, "Borde 1");
	}
	return choco;
}

bool verificarBordeDos(Recorrido &recorrido, float pendiente, float ordAlOrigen){
	bool choco = false;
	// y = pendiente*x + ordAlOrigen
	float interseccionConBordeY = ((pendiente*ANCHO)+ordAlOrigen);
	if (interseccionConBordeY <= FIN_DIAGONAL1_Y && interseccionConBordeY >= FIN_DIAGONAL3_Y){
		choco = true;
		float distancia = calcularDistancia(recorrido.xInicial, recorrido.yInicial, ANCHO, interseccionConBordeY);
		recorrido.longitud = distancia;
		strcpy(recorrido.destino, "Borde 2");
	}
	return choco;
}

bool verificarBordeTres(Recorrido &recorrido, float pendiente, float ordAlOrigen){
	bool choco = false;
	float pendienteDiagonal = ((FIN_DIAGONAL3_Y - 0) / (ANCHO - COMIENZO_DIAGONAL_X));
	float ordAlOrigenDiagonalA = FIN_DIAGONAL3_Y - (pendienteDiagonal*ANCHO);
	float ordAlOrigenDiagonalB = 0 - (pendienteDiagonal*COMIENZO_DIAGONAL_X);
	if ( ordAlOrigenDiagonalA != ordAlOrigenDiagonalB){
		cout << "La ordenada al origen no es igual verificando choque con borde 3 para la bala " << recorrido.id << "\n";
		cout << "OrdAlOrigenA: "<< ordAlOrigenDiagonalA << " | OrdAlOrigenB:" << ordAlOrigenDiagonalB << "\n";
	}
	float xInterseccion = ((ordAlOrigenDiagonalA - ordAlOrigen) / (pendiente - pendienteDiagonal));
	float yInterseccionA = ((pendienteDiagonal*xInterseccion) + ordAlOrigenDiagonalA);
	float yInterseccionB = ((pendiente*xInterseccion) + ordAlOrigen);
	if (yInterseccionA != yInterseccionB){
		cout << "La interseccion en y no es igual verificando choque con borde 3 para la bala " << recorrido.id << "\n";
		cout << "YintersecA: "<< yInterseccionA << " | YintersecB:" << yInterseccionB << "\n";
	}

	if (xInterseccion >= COMIENZO_DIAGONAL_X && xInterseccion <= ANCHO && yInterseccionA >= 0 && yInterseccionA <= FIN_DIAGONAL3_Y){
		choco = true;
		float distancia = calcularDistancia(recorrido.xInicial, recorrido.yInicial, xInterseccion, yInterseccionA);
		recorrido.longitud = distancia;
		strcpy(recorrido.destino, "Borde 3");
	}
	return choco;
}

bool verificarBordeInferior(Recorrido &recorrido, float pendiente, float ordAlOrigen){
	bool choco = false;
	// y = pendiente*x + ordAlOrigen
	float interseccionConBordeX = ((0-ordAlOrigen)/pendiente);
	if (interseccionConBordeX <= COMIENZO_DIAGONAL_X && interseccionConBordeX >= 0 && recorrido.xInicial < interseccionConBordeX){
		choco = true;
		float distancia = calcularDistancia(recorrido.xInicial, recorrido.yInicial, interseccionConBordeX, 0);
		recorrido.longitud = distancia;
		strcpy(recorrido.destino, "Borde inferior");
	}
	return choco;
}

void procesarRecorridos(Recorrido* recorridos, int cantidadDeBalas){
	for (int i=0; i < cantidadDeBalas; i++){
		float pendiente = ((recorridos[i].yFinal - recorridos[i].yInicial) / (recorridos[i].xFinal - recorridos[i].xInicial));
		float ordAlOrigenA = recorridos[i].yFinal - (pendiente*recorridos[i].xFinal);
		float ordAlOrigenB = recorridos[i].yInicial - (pendiente*recorridos[i].xInicial);
		if( ordAlOrigenA != ordAlOrigenB ){
			cout << "La ordAlOrigen no es igual procesando recorridos para la bala " << recorridos[i].id << "\n";
			cout << "ordAlOrigenA: "<< ordAlOrigenA << " | ordAlOrigenB:" << ordAlOrigenB << "\n";
		}
		bool encontroChoque = false;
		if (! encontroChoque) encontroChoque = verificarBordeSuperior(recorridos[i], pendiente, ordAlOrigenA);
		if (! encontroChoque) encontroChoque = verificarBordeUno(recorridos[i], pendiente, ordAlOrigenA);
		if (! encontroChoque) encontroChoque = verificarBordeDos(recorridos[i], pendiente, ordAlOrigenA);
		if (! encontroChoque) encontroChoque = verificarBordeTres(recorridos[i], pendiente, ordAlOrigenA);
		if (! encontroChoque) encontroChoque = verificarBordeInferior(recorridos[i], pendiente, ordAlOrigenA);
	}
}

int comparar(const void *a, const void *b){
	if (((Recorrido*)a)->longitud > ((Recorrido*)b)->longitud) return 1;
	if (((Recorrido*)a)->longitud == ((Recorrido*)b)->longitud) return 0;
	if (((Recorrido*)a)->longitud < ((Recorrido*)b)->longitud) return -1;
}

void imprimirResultados(Recorrido* recorridos, int cantidadDeBalas){
	qsort(recorridos,cantidadDeBalas,sizeof(Recorrido),comparar);
	cout << "Longitud \t\tID \t\t\tDestino\n";
	for (int i = 0; i < cantidadDeBalas; i++){
		float longitud = recorridos[i].longitud;
		char* id = recorridos[i].id;
		char* destino = recorridos[i].destino;
		cout << longitud << "\t\t\t" << id << "\t\t\t" << destino << "\n";
	}
	getchar();
}

int main(int argc, _TCHAR* argv[])
{
	int cantidadDeBalas = 0;
	Recorrido recorridos[MAX_BALAS];
	cantidadDeBalas = cargarBalas(recorridos);
	procesarRecorridos(recorridos, cantidadDeBalas);
	imprimirResultados(recorridos, cantidadDeBalas);
	return 0;
}