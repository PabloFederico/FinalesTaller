#pragma once

#include <sstream> //istringstream
#include <fstream> //ifstream
#include <string> //getline
#include <vector>
#include <algorithm>
#include "Plataforma.h"
#include "Barril.h"

//using namespace std;      <----- no usarlo en los .H !!!

class Filehandler
{
	private:
		std::ifstream				archivoBarriles;
		std::ifstream				archivoEscenario;
		std::vector<Plataforma>		plataformas;
		std::vector<Barril>			barriles;

	public:
		Filehandler(std::string ab, std::string ae) 
		{
			archivoBarriles.open(ab.c_str());
			archivoEscenario.open(ae.c_str());
		}

		virtual Filehandler::~Filehandler(void) 
		{
			archivoBarriles.close();
			archivoEscenario.close();
		}

		void Filehandler::cargarPlataformas()
		{
			std::string line; // cada linea tiene 1 campo fijo y "n" (variable) campos de la forma (xi,xf)
			float y, xi, xf;
			while ( getline(archivoEscenario,line)) 
			{
				std::istringstream in(line);
				in >> y;        // el "y" es constante para cada plataforma de una misma linea
				while ( in >> xi >> xf ) // la lectura va dentro del while para no leer lo ultimo 2 veces
				{
					Plataforma plataforma (y, xi, xf);
					plataforma.print();
					plataformas.push_back(plataforma);
				}

			}
		}

		void Filehandler::cargarBarriles() 
		{
				std::string line; // cada linea tiene solo 3 campos: id, x, y
				std::string id;
				float x, y;
				while ( getline(archivoBarriles,line)) 
				{
					std::istringstream in(line);
					in >> id >> x >> y;
					Barril barril (id, x, y);
					barril.print();
					barriles.push_back(barril);
				}
		}

		void Filehandler::getNearestVerticalPlatform(const float x, const float y, float* distance, Plataforma** p)
		{
			float minDist = y;
			Plataforma* temp = NULL;
			for (int i = 0; i < plataformas.size(); ++i) 
			{
				temp = &(plataformas[i]);
				bool cond1 = ( temp->xi <= x && x <= temp->xf ); // punto arriba de la plataforma
				bool cond2 = ( temp->y < y ); // plataforma mas baja que el punto
				bool cond3 = ( minDist > (y - temp->y) ); // distancia mas corta que la guardada
				
				if (cond1 && cond2 && cond3)
				{
					*p = temp;
					minDist = y - temp->y;
					*distance = minDist;
				}
			}
		}
		
		//	Calcula la distancia entre un punto (x,y) arbitrario y el piso (y=0)
		float Filehandler::distanciaAlPiso(float x, float y) 
		{
			float distanciaAPlataforma = -1;
			Plataforma* p = NULL;
			getNearestVerticalPlatform(x, y, &distanciaAPlataforma, &p);
			if (p == NULL)  { // No hay plataformas entre el barril y el piso
				return y; //devolvemos la altura actual del barril
			}
			else
			{
				/*
				If there's a platform between (x, y) and the ground, 
				then return the distance to the nearest such platform 
				(i.e. that has the greatest platform_y) y - platform_y, 
				plus the minimum of (x - platform_min_x) + distanceToGround(platform_min_x, platform_y) 
				and
				(platform_max_x - x) + distanceToGround(platform_max_x, platform_y). 
				This basically finds the distance to either end of the platform, 
				and then the shortest distance from either end to the ground.
				*/
				float rightDistance = (p->xf - x) + distanciaAlPiso(p->xf, p->y);
				float leftDistance = (x - p->xi) + distanciaAlPiso(p->xi, p->y);

				return (distanciaAPlataforma + std::min(rightDistance,leftDistance));

			}	
		}


		std::vector<Barril> Filehandler::calcularDistancias()
		{
			for (int i = 0; i < barriles.size(); ++i) 
			{
				barriles[i].distancia = distanciaAlPiso(barriles[i].x, barriles[i].y);
			}
			return barriles;
		}

};