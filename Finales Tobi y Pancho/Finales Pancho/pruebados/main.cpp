#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <list>

using namespace std;

typedef struct Ladrillo{
	float xIzq;
	float xDer;
	float y;
	int resistencia;
	string id;
} ;

typedef struct Bala{
	string id;
	float x;
	float y;
	int energia;
};

typedef struct Mensaje{
	string idBala;
	string idLadrillo;
	float distancia;
};

list<Ladrillo* > listaLadrillos;
list<Mensaje* > listaMensajes;
list<Ladrillo* > ladrillosABorrar;

bool compararMensajes(const Mensaje* mensajeUno, const Mensaje* mensajeDos)
{
	return mensajeUno->distancia < mensajeDos->distancia;
}

void analizarChoqueBala(Bala bala);
void borrarLadrillos();
bool verSiEstaEnMismoX(Ladrillo* ladrillo, Bala bala);

int main(int argc, char** argv[])
{
	FILE* archivoLadrillos, *archivoBalas;
	char id[256];
	int i = 5;
	int vuelta;
	Ladrillo* ladrillo;
	ladrillo = new Ladrillo();
	float xIzq, xDer, y;
	int res;
	archivoLadrillos = fopen("datosLadrillos.txt", "r");
	archivoBalas = fopen("datosBalas.txt", "r");

	vuelta = fscanf(archivoLadrillos, "%s %f %f %f %i", id, &xIzq, &xDer, &y, &res);

	while( (vuelta > 0) || (!feof(archivoLadrillos) ) )
	{
		ladrillo = new Ladrillo();
		ladrillo->id = id;
		ladrillo->xDer = xDer;
		ladrillo->xIzq = xIzq;
		ladrillo->y = y;
		ladrillo->resistencia = res;

		//cout << "Ladrillo: " << ladrillo->id.c_str() << " " << ladrillo->xIzq << " " << ladrillo->xDer << " " << ladrillo->y << " " << ladrillo->resistencia << endl;
		
		listaLadrillos.push_back(ladrillo);

		vuelta = fscanf(archivoLadrillos, "%s %f %f %f %i", id, &xIzq, &xDer, &y, &res);
	}
	
	Bala bala;

	vuelta = fscanf(archivoBalas, "%s %f %f %i", id, &bala.x, &bala.y, &bala.energia);

	while( (vuelta > 0) || (!feof(archivoBalas) ) )
	{
		bala.id = id;

		//cout << "Bala: " << bala.id.c_str() << " " << bala.x << " " << bala.y << " " << bala.energia << endl;
		
		analizarChoqueBala(bala);

		vuelta = fscanf(archivoBalas, "%s %f %f %i", id, &bala.x, &bala.y, &bala.energia);
	}

	listaMensajes.sort(compararMensajes);

	list<Mensaje* >::iterator mensajito = listaMensajes.begin();
	list<Mensaje* >::const_iterator ENDmensajes = listaMensajes.end();

	for(; mensajito != ENDmensajes; mensajito++)
	{
		cout << "ID bala: " << (*mensajito)->idBala << " ID ladrillo: " << (*mensajito)->idLadrillo << " Distancia: " << (*mensajito)->distancia << endl;
	}

	fclose(archivoLadrillos);
	fclose(archivoBalas);
	delete ladrillo;

	while(i != 0)
	{
		cout << "Ingrese un 0 para terminar.\n" ;
		cin >> i;
	}
	
	return 0;
}


void analizarChoqueBala(Bala bala){
	
	int contadorLadrilloMasBajo = -1;
	int j = 0;
	float posYMasBajo = 10000;
	bool chocaEnX = false;
	Mensaje* mensaje = new Mensaje();

	list<Ladrillo* >::iterator ladrillito = listaLadrillos.begin();
	list<Ladrillo* >::const_iterator ENDladrillos = listaLadrillos.end();
	for(; ladrillito != ENDladrillos; ladrillito++, j++)
	{
		(*ladrillito)->resistencia = (*ladrillito)->resistencia - bala.energia;
		if( ((*ladrillito)->y > bala.y ) && (posYMasBajo > (*ladrillito)->y) && (verSiEstaEnMismoX( *ladrillito, bala)) )
		{
			posYMasBajo = (*ladrillito)->y;
			contadorLadrilloMasBajo = j;
		}
	}

	j = 0;

	list<Ladrillo* >::iterator ladrillitoYaChocados = listaLadrillos.begin();
	list<Ladrillo* >::const_iterator ENDladrillosYaChocados = listaLadrillos.end();
	for(; ladrillitoYaChocados != ENDladrillosYaChocados; ladrillitoYaChocados++, j++)
	{
		if(contadorLadrilloMasBajo == j)
		{
			if((*ladrillitoYaChocados)->resistencia < 0)
			{
				mensaje->idBala = bala.id;
				mensaje->idLadrillo = (*ladrillitoYaChocados)->id;
				mensaje->distancia = (*ladrillitoYaChocados)->y - bala.y;
				//cout << "ID bala: " << mensaje->idBala << " ID ladrillo: " << mensaje->idLadrillo << " Distancia: " << mensaje->distancia << endl;
				listaMensajes.push_back(mensaje);
				ladrillosABorrar.push_back((*ladrillitoYaChocados));
			}			
		} else {
			(*ladrillitoYaChocados)->resistencia = (*ladrillitoYaChocados)->resistencia + bala.energia;
		}
		
	}

	borrarLadrillos();

}

void borrarLadrillos()
{
	// Con esto borro los ladrillos ya chocados
	list<Ladrillo* >::iterator ladrillitoABorrar = ladrillosABorrar.begin();
	list<Ladrillo* >::const_iterator ENDladrillosABorrar = ladrillosABorrar.end();
	for(; ladrillitoABorrar != ENDladrillosABorrar; ladrillitoABorrar++)
	{
		listaLadrillos.remove(*ladrillitoABorrar);
	}
}

bool verSiEstaEnMismoX(Ladrillo* ladrillo, Bala bala)
{
	if( (ladrillo->xDer > bala.x) && (ladrillo->xIzq < bala.x) )
	{
		//cout << "Este en mismoX" << endl;
		return true;
	}
	return false;
}