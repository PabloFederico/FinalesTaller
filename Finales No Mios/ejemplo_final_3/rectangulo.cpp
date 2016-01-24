#include "rectangulo.h"
#include "circulo.h"
#include <cmath>
#include <sstream>
#include <string>

using namespace std;

Rectangulo::Rectangulo(float uh, float uw ,float unX,float unY)
{
	// X e Y son el centro del rectangulo
	h= uh; 
	w =uw; 
	x= unX; 
	y = unY;
}

bool Rectangulo::colisionarConCirculo(Circulo* c){
	return c->colisionarConRectangulo(*this);
}

bool Rectangulo::verticeDentro(float x, float y){
	if (( x >= this->x - this->w / 2) and ( x <= this->x + this->w / 2) ){
		if (( y >= this->y - this->h / 2) and ( y <= this->y + this->h / 2)) return true;
	}
	return false;
}

bool Rectangulo::colisionarConRectangulo(Rectangulo& r){
	if (this->verticeDentro(r.x + r.w/2, r.y + r.h/2)) return true;
	if (this->verticeDentro(r.x + r.w/2, r.y - r.h/2)) return true;
	if (this->verticeDentro(r.x - r.w/2, r.y + r.h/2)) return true;
	if (this->verticeDentro(r.x - r.w/2, r.y - r.h/2)) return true;
	return false;
}

string Rectangulo::tostring() const {
    ostringstream out;
    out << "Rect: (x: " << x << ", y: " << y << ", w: " << w << " ,h: " << h << ")";
    return out.str();
}
