#include <iostream>
#include <stdio.h>
#include <string>
#include <list>

using namespace std;

class Bala{
public:
	string id;
	float x, y;
	int energia;

	Bala(){
		id = "-";
		x = y= 0;
		energia = 0;
	}

	Bala(const Bala& b){
		id = b.id;
		x = b.x;
		y = b.y;
		energia = b.energia;
	}
	
	~Bala(){}

	Bala(string id, float x, float y, int energia){
		this->id = id;
		this->x = x;
		this->y = y;
		this->energia = energia;
	}
};


class Plataforma{
public:
	string id;
	float x0, xf, y;
	int energia;
	list<string> idBalas;

	Plataforma(string id, float x0, float y, float xf, int energia){
		this->id = id;
		this->x0 = x0;
		this->xf = xf;
		this->y = y;
		this->energia = energia;
	}

	Plataforma(){
		id = "-";
		x0 = xf = y = 0;
		energia = 0;
	}

	Plataforma(const Plataforma& p){
		this->x0 = p.x0;
		this->xf = p.xf;
		this->y = p.y;
		this->id = p.id;
		this->energia = p.energia;
		this->idBalas = p.idBalas;
	}

	bool vive(){
		return (energia > 0);
	}

	bool laChoca(const Bala& bala){
		return (vive() && bala.y < y && x0 < bala.x && bala.x < xf);
	}

	bool colisionarCon(const Bala& bala){
		bool choca = laChoca(bala);
		if (choca){
			energia -= bala.energia;
			idBalas.push_back(bala.id);
		}else{
			cout << "Estoy haciendo chocar la bala " << bala.id << " con la plataforma " << id << " aunque no chocan" << endl;
		}
		return choca;
	}

	void print(){
		cout << id << " " << energia;
		list<string>::iterator it = idBalas.begin();
		for (; it != idBalas.end(); it++){
			cout << " " << *it;
		}
		cout << endl;
	}
};



int compararPlat(const void* p1, const void* p2){
	float y1 = ((Plataforma*)p1)->y;
	float y2 = ((Plataforma*)p2)->y;

	if (y1 < y2) return -1;
	if (y1 == y2) return 0;
	return 1;
}


class Parser{
public:
	FILE* file;

	Parser(string filename){
		file = fopen(filename.c_str(), "r");
	}

	~Parser(){
		fclose(file);
	}

	bool fin(){
		return feof(file);
	}

	Bala siguienteBala(){
		char id[100];
		float x, y;
		int energia;
		fscanf(file, "%s %f %f %d\n", id, &x, &y, &energia);
		return Bala(id, x, y, energia);
	}

	Plataforma siguientePlataforma(){
		char id[100];
		float x0, xf, y;
		int energia;
		fscanf(file, "%s %f %f %f %d\n", id, &x0, &y, &xf, &energia);
		return Plataforma(id, x0, y, xf, energia);
	}

	int cargarPlataformas(Plataforma (&plataformas)[100]){
		int i = 0;
		while (!fin()){
			plataformas[i] = siguientePlataforma();
			i++;
		}

		qsort(plataformas, i, sizeof(Plataforma), compararPlat);


		return i;
	}
};