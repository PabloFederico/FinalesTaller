#include <algorithm>
#include <iostream>
#include "Filehandler.h"
#include "Barril.h"

/*
Para evitar el error al querer generar en modo DEBUG:
PROJECT->PROPERTIES->CONFIG PROPERTIES->DEBUGGING->GENERATE DEBUG INFO = "YES"
PROJECT->PROPERTIES->CONFIG PROPERTIES->C/C++->DEBUG INFORMATION FORMAT = "/Zi"


Para evitar que se cierre la terminal al terminar de debuggear:
Poner un breakpoint en el "return 0" del main


Para debuggear mas facil:
hacerle un metodo "print" a cada clase relevante.


Para ver que includes requiere un tipo:
clic derecho sobre el tipo -> "ir a definicion" , y 
fijarse el nombre del archivo que sale, o
fijarse el "typedef" y repetir el procedimiento


Atajos de teclado:
F5					-> DEBUGGEAR
CTRL+SHIFT+B		-> COMPILAR
CTRL+J				-> SUGERENCIAS AL ESCRIBIR
CTRL+ESPACIO		-> SUGERENCIAS AL ESCRIBIR
*/

using namespace std;      //<----- No hay problema si esto lo ponemos en un .cpp

const string archbarriles = "C:\\Users\\Betty\\Desktop\\barriles.txt"; //notar las dobles barras
const string archescenario = "C:\\Users\\Betty\\Desktop\\escenario.txt"; //notar las dobles barras

bool compararBarriles(Barril uno, Barril dos) 
{
	return (uno.distancia < dos.distancia);
}

int main ()
{
	Filehandler fh (archbarriles, archescenario);
	cout << "CARGANDO DATOS..." << endl;
	fh.cargarPlataformas();
	fh.cargarBarriles();

	vector<Barril> resultado = fh.calcularDistancias();
	// Piden mostrar los barriles ordenados por distancia ascendente:
	sort(resultado.begin(),resultado.end(), compararBarriles);

	cout << "RESULTADO:" << endl;
	for (int i = 0; i < resultado.size(); ++i)
	{
		cout << "Id de barril: " << resultado[i].id;
		cout << ", distancia: " << resultado[i].distancia;
		cout << endl;
	}

	return 0;
}