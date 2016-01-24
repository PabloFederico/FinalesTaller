#include "circulo.h"
#include "rectangulo.h"
#include <cmath>
#include <sstream>
#include <string>

using namespace std;
Circulo::Circulo(float unRadio, float unX,float unY)
{
	radio = unRadio; x = unX; y = unY;
}


bool Circulo::colisionarConRectangulo(Rectangulo& rect){

// http://stackoverflow.com/questions/401847/circle-rectangle-collision-detection-intersection

/* The first pair of lines calculate the absolute values of the x and y difference between
 * the center of the circle and the center of the rectangle.
 * This collapses the four quadrants down into one, so that the calculations do not have to be done four times.
 * The image shows the area in which the center of the circle must now lie. Note that only the single quadrant is shown.
 * The rectangle is the grey area, and the red border outlines the critical area
 * which is exactly one radius away from the edges of the rectangle.
 * The center of the circle has to be within this red border for the intersection to occur.*/

	float dx = abs(x - rect.x);
    float dy = abs(y - rect.y);

/* The second pair of lines eliminate the easy cases where the circle is far enough away
 * from the rectangle (in either direction) that no intersection is possible.
 * This corresponds to the green area in the image. */

    if (dx > (rect.w/2 + radio)) { return false; }
    if (dy > (rect.h/2 + radio)) { return false; }

/* The third pair of lines handle the easy cases where the circle is close enough
* to the rectangle (in either direction) that an intersection is guaranteed.
* This corresponds to the orange and grey sections in the image.
* Note that this step must be done after step 2 for the logic to make sense. */

    if (dx <= (rect.w/2)) { return true; } 
    if (dy <= (rect.h/2)) { return true; }

/* The remaining lines calculate the difficult case where the circle may intersect
 * the corner of the rectangle. To solve, compute the distance from the center of
 * the circle and the corner, and then verify that the distance is not more than
 * the radius of the circle. This calculation returns false for all circles whose
 * center is within the red shaded area and returns true for all circles whose center
 * is within the white shaded area */

    float  cornerDistance_sq = (dx - rect.w/2) * (dx - rect.w/2) +
                         (dy - rect.h/2) * (dy - rect.h/2);

    return (cornerDistance_sq <= (radio * radio));                    
}

string Circulo::tostring() const
{
    ostringstream out;
    out << "Circulo: (" << x << ", " << y << ", " << "Radio: " << radio << ")";
    return out.str();
}
