#pragma once

#include <string> //std::string
#include <iostream> //cout,endl

class Barril
{
	private:
		std::string id;
		float x;
		float y;
		float distancia;

	public:
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

		void setDistancia(float unadist) { 	distancia = unadist; }

		std::string getID() { return id; }
		float getY() const { return y; }
		float getX() const { return x; }
		float getDistancia() const { return distancia; }
};
