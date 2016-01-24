#pragma once

#include <iostream> //cout,endl

class Plataforma
{
	public:
		float y;
		float xi;
		float xf;

		Plataforma(float uny, float unxi, float unxf)
		{
			y = uny;
			xi = unxi;
			xf = unxf;
		}

		virtual ~Plataforma(void) 
		{
		}

		void print() 
		{
			std::cout << "Plataforma: alto="<<y << ", xi=" << xi << ", xf=" << xf << std::endl;
		}

};
