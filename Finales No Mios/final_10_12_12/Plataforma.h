#pragma once

#include <iostream> //cout,endl

class Plataforma
{
	private:
		float y;
		float xi;
		float xf;
	public:
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

		float gety() { return y; }
		float getxi() { return xi; }
		float getxf() { return xf; }
};
