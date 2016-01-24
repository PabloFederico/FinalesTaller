#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <list>

using namespace std;

const int limiteDerecho = 60;
const int limiteSuperior = 60;
const int limiteInferior = 0;
const int limiteBordeDos = 65;

enum Bordes { SUPERIOR , INFERIOR , UNO , DOS , TRES };

typedef struct Vector{
	double x;
	double y;
} vertice, vectorDireccion; 

typedef struct Mensaje{
	double longRecorrido;
	Bordes bordeSalida;
	string idRec;
} mensajes;

list<Mensaje> listaMensajes;

bool compararRecorridos(const Mensaje& mensajeUno,const Mensaje& mensajeDos)
{
	return mensajeDos.longRecorrido > mensajeUno.longRecorrido;
}

// ESTOS SON LOS POSTA
void escribirMensaje(FILE* archivoSalida, double longitud,const char* id, Bordes bordeImpacto);
string getStringFromEnum(Bordes borde);

bool colisionDerechaOArriba(Vector vectorDestino, double xOrigen, double yOrigen, double *recorridoTotal);
bool colisionDerechaOAbajo(Vector vectorDestino, double xOrigen, double yOrigen, double *recorridoTotal);

Bordes verConQueBordeDerechoChoco(Vector vectorDestino, double xOrigen, double yOrigen, double *recorridoTotal);

int main(int argc, char** argv[]){

	char id[256];
	float xOrigen, yOrigen, xDestino, yDestino;
	int vuelta;
	Vector vectorDestino;
	FILE * archivoEntrada, *archivoSalida;
	int i = 5;
	archivoEntrada = fopen("datos.txt", "r");
	archivoSalida = fopen("salida.txt", "w+");
	
	vuelta = fscanf(archivoEntrada, "%s %f %f %f %f", id, &xOrigen, &yOrigen, &xDestino, &yDestino);

	while( (vuelta > 0) || (!feof(archivoEntrada)))
	{		
		double recorrido;
		Mensaje mensaje;
		recorrido = -1;
		//cout << "Imprimo lo que lei: \n";
		//cout << id << " ";
		//cout << xOrigen << " " << yOrigen << " " << xDestino << " "<< yDestino << "\n";
		vectorDestino.x = xDestino - xOrigen;
		vectorDestino.y = yDestino - yOrigen;

		//cout << "El vector director X: " << vectorDestino.x << " Y: " << vectorDestino.y << ".\n" ;

		mensaje.idRec = id;
		if(vectorDestino.y > 0)
		{
			bool colisionArriba;
			colisionArriba = colisionDerechaOArriba(vectorDestino, xOrigen, yOrigen,&recorrido);
			if(colisionArriba){
				mensaje.longRecorrido = recorrido;
				mensaje.bordeSalida = SUPERIOR;
			} else {
				Bordes borde = verConQueBordeDerechoChoco(vectorDestino, xOrigen, yOrigen,&recorrido);
				mensaje.longRecorrido = recorrido;
				mensaje.bordeSalida = borde;
			}
		}
		if(vectorDestino.y < 0)
		{
			bool colisionAbajo;
			colisionAbajo = colisionDerechaOAbajo(vectorDestino, xOrigen, yOrigen, &recorrido);
			if(colisionAbajo)
			{
				mensaje.longRecorrido = recorrido;
				mensaje.bordeSalida = INFERIOR;
			} else {
				Bordes borde = verConQueBordeDerechoChoco(vectorDestino, xOrigen, yOrigen,&recorrido);
				mensaje.longRecorrido = recorrido;
				mensaje.bordeSalida = borde;
			}
		}
		if( (vectorDestino.y < 0.1) &&(vectorDestino.y > - 0.1) && (vectorDestino.x > 0) )
		{
			Bordes borde = verConQueBordeDerechoChoco(vectorDestino, xOrigen, yOrigen,&recorrido);
			mensaje.longRecorrido = recorrido;
			mensaje.bordeSalida = borde;
		}
		
		listaMensajes.push_back(mensaje);
		vuelta = fscanf(archivoEntrada, "%s %f %f %f %f", id, &xOrigen, &yOrigen, &xDestino, &yDestino);
	}
	cout << "vuelta: " << vuelta << "\n" ;

	listaMensajes.sort(compararRecorridos);
	
	list<Mensaje>::iterator mensajes = listaMensajes.begin();
	list<Mensaje>::const_iterator ENDmensajes = listaMensajes.end();
	for (; mensajes != ENDmensajes; mensajes++) {
		escribirMensaje(archivoSalida, (*mensajes).longRecorrido, (*mensajes).idRec.c_str(), (*mensajes).bordeSalida);
	}

	while(i != 0)
	{
		cout << "Ingrese un cero para terminar.\n" ;
		cin >> i;
	}

	fclose(archivoEntrada);
	fclose(archivoSalida);
	return 0;
}

// ESTOS SON LOS POSTA
bool colisionDerechaOArriba(Vector vectorDestino, double xOrigen, double yOrigen, double *recorridoTotal)
{
	double pasos;
	pasos = (limiteSuperior - yOrigen) / vectorDestino.y;
	if(vectorDestino.x * pasos > limiteDerecho - xOrigen)
	{
		*recorridoTotal = -1;
		return false;
	}
	double catetoUno = pow ( (pasos * vectorDestino.x), 2.0 );
	double catetoDos = pow ( (pasos * vectorDestino.y), 2.0 );
	*recorridoTotal = sqrt( catetoUno + catetoDos );
	return true;
}

bool colisionDerechaOAbajo(Vector vectorDestino, double xOrigen, double yOrigen, double *recorridoTotal)
{
	double pasos;
	pasos = yOrigen / (-vectorDestino.y);
	if(vectorDestino.x * pasos > limiteDerecho - xOrigen)
	{
		*recorridoTotal = -1;
		return false;
	}
	double catetoUno = pow ( (pasos * vectorDestino.x), 2.0 );
	double catetoDos = pow ( (pasos * vectorDestino.y), 2.0 );
	*recorridoTotal = sqrt( catetoUno + catetoDos );
	return true;
}

Bordes verConQueBordeDerechoChoco(Vector vectorDestino, double xOrigen, double yOrigen, double *recorridoTotal)
{
	double pasos = 0;

	bool chocoContraBordeUno, chocoContraBordeDos, chocoContraBordeTres;
	chocoContraBordeUno = false;
	chocoContraBordeDos = false;
	chocoContraBordeTres = false;
	Vector vectorAuxiliar;
	vectorAuxiliar.x = xOrigen ; vectorAuxiliar.y = yOrigen;
	while( (!chocoContraBordeUno) && (!chocoContraBordeDos) && (!chocoContraBordeTres) )
	{
		vectorAuxiliar.x = vectorAuxiliar.x + (pasos * vectorDestino.x);
		vectorAuxiliar.y = vectorAuxiliar.y + (pasos * vectorDestino.y);
		if( (vectorAuxiliar.y < 60) && (vectorAuxiliar.y > 40) )
		{
			double bordeUno = ( 300 - vectorAuxiliar.y ) / 4;
			chocoContraBordeUno = vectorAuxiliar.x >= bordeUno;
		}
		if( (vectorAuxiliar.y < 40) && (vectorAuxiliar.y > 20) )
		{
			chocoContraBordeDos = vectorAuxiliar.x >= limiteBordeDos;
		}
		if( (vectorAuxiliar.y < 20) && (vectorAuxiliar.y > 0) )
		{
			double bordeTres = ( vectorAuxiliar.y + 240 ) / 4;
			chocoContraBordeTres = vectorAuxiliar.x >= bordeTres;
		}
		pasos = pasos + 0.001;
		vectorAuxiliar.x = xOrigen ; vectorAuxiliar.y = yOrigen;
	}
	double catetoUno = pow ( (pasos * vectorDestino.x), 2.0 );
	double catetoDos = pow ( (pasos * vectorDestino.y), 2.0 );
	*recorridoTotal = sqrt( catetoUno + catetoDos );
	if(chocoContraBordeUno)
	{
		return UNO;
	} 
	if(chocoContraBordeDos)
	{
		return DOS;
	}
	if(chocoContraBordeTres)
	{
		return TRES;
	}
	return UNO;
}


void escribirMensaje(FILE* archivoSalida, double longitud,const char* id, Bordes bordeImpacto)
{
	fprintf(archivoSalida, "Longitud recorrido:  %.3f || ID:  %s || Borde: %s.\n", longitud, id, getStringFromEnum(bordeImpacto).c_str());
}

string getStringFromEnum(Bordes borde)
{
	switch(borde)
	{
	case SUPERIOR: return "Borde_Sup";
	case INFERIOR: return "Borde_Inf";
	case UNO: return "Borde_Uno";
	case DOS: return "Borde_Dos";
	case TRES: return "Borde_Tres";
	default: return "BordeIncorrecto";
  }
}