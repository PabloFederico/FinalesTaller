#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <list>

using namespace std;

struct Mensaje{
	string idTanque;
	string idPozo;
	float distancia;
};

struct Vector{
	float x;
	float y;
};

struct Pozo{
	string id;
	Vector centro;
	float radio;
};

struct Tanque{
	string id;
	Vector esquinaInfIzq;
	Vector esquinaSupDer;
};

list<Mensaje* > listaMensajes;
list<Pozo* > listaPozos;

// FUNCTION DECLARATIONS
bool compararMensajes(const Mensaje *mensajeUno, const Mensaje *mensajeDos)
{
	return mensajeUno->distancia < mensajeDos->distancia;
}

void analizarCaidaTanque(Tanque *tanque);
bool entraTanqueEnPozo(Pozo *pozo, Tanque *tanque);

int main(int argc, char** argv[])
{
	FILE *archivoPozos, *archivoTanques;
	archivoPozos = fopen("datosPozos.txt", "r");
	archivoTanques = fopen("datosTanques.txt", "r");

	int i = 5;
	int vuelta;
	float centroX, centroY, radio;
	char id[128];
	Pozo *pozo = new Pozo();

	vuelta = fscanf(archivoPozos, "%s %f %f %f", id, &centroX, &centroY, &radio);

	while( (vuelta > 0) || (!feof(archivoPozos)) ){
		
		pozo = new Pozo();
		pozo->centro.x = centroX;
		pozo->centro.y = centroY;
		pozo->radio = radio;
		pozo->id = id;
		listaPozos.push_back(pozo);
		vuelta = fscanf(archivoPozos, "%s %f %f %f", id, &centroX, &centroY, &radio);
	}

	Tanque tanque;
	float esquinaInfIzqX, esquinaInfY, esquinaDerX, esquinaDerY;
	vuelta = fscanf(archivoTanques, "%s %f %f %f %f", id, &esquinaInfIzqX, &esquinaInfY, &esquinaDerX, &esquinaDerY);

	while( (vuelta > 0) || (!feof(archivoTanques)) ){
		tanque.id = id;
		tanque.esquinaInfIzq.x = esquinaInfIzqX;
		tanque.esquinaInfIzq.y = esquinaInfY;
		tanque.esquinaSupDer.x = esquinaDerX;
		tanque.esquinaSupDer.y = esquinaDerY;
		analizarCaidaTanque(&tanque);
		vuelta = fscanf(archivoTanques, "%s %f %f %f %f", id, &esquinaInfIzqX, &esquinaInfY, &esquinaDerX, &esquinaDerY);
	}

	listaMensajes.sort(compararMensajes);

	list<Mensaje* >::iterator  mensajitos = listaMensajes.begin();
	list<Mensaje* >::const_iterator ENDmensajes = listaMensajes.end();

	for(; mensajitos != ENDmensajes; mensajitos++){
		cout << "IDtanque: " << (*mensajitos)->idTanque.c_str() << " IDpozo: " << (*mensajitos)->idPozo.c_str() << " Distancia: " << (*mensajitos)->distancia << endl;
	}	
	while(i != 0){
		cout << "Ingrese un 0 para terminar.\n";
		cin >> i;
	}

	fclose(archivoPozos);
	fclose(archivoTanques);

	return 0;
}

void analizarCaidaTanque(Tanque *tanque)
{
	float posXMasCercana = 999999;
	int i = 0;
	float posXPozoIzq, posXPozoDer;
	Pozo *pozoPorElQueCayo = NULL;
	list<Pozo* >::iterator  pozitos = listaPozos.begin();
	list<Pozo* >::const_iterator ENDpozos = listaPozos.end();
	for(; pozitos != ENDpozos ; pozitos++){
		posXPozoIzq = (*pozitos)->centro.x - (*pozitos)->radio;
		posXPozoDer = (*pozitos)->centro.x + (*pozitos)->radio;
		if( (posXPozoIzq < posXMasCercana) && (entraTanqueEnPozo(*pozitos, tanque)) && (posXPozoDer > tanque->esquinaInfIzq.x) ){
			posXMasCercana = posXPozoIzq;
			pozoPorElQueCayo = *pozitos;
		}
	}

	if(pozoPorElQueCayo != NULL)
	{
		Mensaje *mensaje = new Mensaje();
		mensaje->idPozo = pozoPorElQueCayo->id;
		mensaje->idTanque = tanque->id;
		float distanciaCaidaPozo = (pozoPorElQueCayo->centro.x - pozoPorElQueCayo->radio) + ( (tanque->esquinaSupDer.x - tanque->esquinaInfIzq.x) / 2 );
		float distanciaDelTanqueAlPozo = ( (tanque->esquinaSupDer.x - tanque->esquinaInfIzq.x) / 2) + tanque->esquinaInfIzq.x;
		mensaje->distancia = distanciaCaidaPozo - distanciaDelTanqueAlPozo;
		listaMensajes.push_back(mensaje);
	}
}

bool entraTanqueEnPozo(Pozo *pozo, Tanque *tanque)
{
	float radioPozo = pozo->radio;
	float yCentroPozo = pozo->centro.y;
	bool tanqueEntraEnY = (yCentroPozo + radioPozo > tanque->esquinaSupDer.y) && (yCentroPozo - radioPozo < tanque->esquinaInfIzq.y);
	bool tanqueEntraEnX = (radioPozo > tanque->esquinaSupDer.x  - tanque->esquinaInfIzq.x);
	if( tanqueEntraEnX && tanqueEntraEnY ) {
		return true;
	}
	return false;
}