#include "Parser.h"


class Resultado{
public:
	string idCirc, idRect; 
	float distancia;

	Resultado(){
		idCirc = "-";
		idRect = "-";
		distancia = -1;
	}

	Resultado(string idCirc, string idRect, float distancia){
		this->idCirc = idCirc;
		this->idRect = idRect;
		this->distancia = distancia;
	}

	~Resultado(){}

	void print(){
		cout << "Resultado: " <<  idCirc << " " << idRect << " " << distancia << endl;
	}
};

int compararResultados(const void* r1, const void *r2){
	float a = ((Resultado*)r1)->distancia;
	float b = ((Resultado*)r2)->distancia;

	if (a < b) return -1;
	if (a == b) return 0;
	return 1;
}

int main(){
	Rectangulo rectangulos[SIZE];
	int cantRec = 0;
	Parser parserRec("rectangulos.txt");
	cantRec = parserRec.cargarRectangulos(rectangulos);
	cout << "Cant Rec: " << cantRec << endl;

	for (int i = 0; i < cantRec; i++){
		rectangulos[i].print();
	}

	Parser parserCirc("circulos.txt");

	Resultado resultados[SIZE];
	int ml = 0;

	while (! parserCirc.fin()){
		Circulo circulo;
		parserCirc.siguienteCirculo(circulo);
		circulo.print();

		for (int i = 0; i < cantRec; i++){
			if (circulo.chocaraCon(rectangulos[i])){
				float distancia = circulo.distA(rectangulos[i]);
				resultados[ml] = Resultado(circulo.id, rectangulos[i].id, distancia);
				ml++;
				break;
			}
		}
	}

	qsort(resultados, ml, sizeof(Resultado), compararResultados);

	for (int i = 0; i < ml; i++){
		resultados[i].print();
	}

	return 0;
}