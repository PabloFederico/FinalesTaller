#pragma once

#include <string> //std::string
#include <iostream> //cout,endl

class Barril
{
	public:
		std::string id;
		float x;
		float y;
		float distancia;

		Barril(std::string unID, float unX, float unY)
		{
			id = unID;
			x = unX;
			y = unY;
			distancia = -1;
		}

		virtual ~Barril(void) 
		{
		}

		void print() 
		{
			std::cout << "Barril: id="<< id << ", x=" << x << ", y=" << y << std::endl;
		}

};
