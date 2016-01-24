#ifndef RECTANGULO_H
#define RECTANGULO_H
#include <string>
#include <ostream>
class Circulo;
class Rectangulo
{
	public:
		Rectangulo(float uh, float uw ,float unX,float unY);
		bool colisionarConCirculo(Circulo* C);
		bool colisionarConRectangulo(Rectangulo& r);
		bool verticeDentro(float x, float y);
			std::string tostring()                   const;
		float x,y;
		float h,w;
//		std::ostream& operator<<(ostream& out, const Rectangulo& r);
};

#endif /* RECTANGULO_H */ 
