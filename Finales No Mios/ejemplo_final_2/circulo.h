#ifndef CIRCULO_H
#define CIRCULO_H
class Rectangulo;
#include <string>
#include <ostream>
class Circulo
{
	public:
		Circulo(float radio, float x,float y);
		bool colisionarConRectangulo(Rectangulo& r);
			std::string tostring()                   const;
		float radio,x,y;
//		std::ostream& operator<<(ostream& out, const Circulo& r);
};

#endif /* CIRCULO_H */ 
