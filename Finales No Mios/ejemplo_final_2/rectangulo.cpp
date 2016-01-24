#include "rectangulo.h"
#include "circulo.h"
#include <cmath>
#include <sstream>
#include <string>
using namespace std;

Rectangulo::Rectangulo(float uh, float uw ,float unX,float unY)
{
	h= uh; 
	w =uw;
	x= unX;
	y = unY;
}

bool Rectangulo::colisionarConCirculo(Circulo* c){
	return c->colisionarConRectangulo(*this);
}

string Rectangulo::tostring() const
{
    ostringstream out;
    out << "Rect: (x: " << x << ", y: " << y << ", w: " << w << " ,h: " << h << ")";
    return out.str();
}
