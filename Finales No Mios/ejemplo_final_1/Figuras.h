#ifndef	FIGURAS_H
#define FIGURAS_H
#include <stdbool.h>

typedef struct rectangulo rectangulo_t;
typedef struct circulo circulo_t;

bool cargarRectangulos(rectangulo_t***, unsigned int*, char*);

bool cargarCirculos(circulo_t***, unsigned int*,char*);

rectangulo_t* rectangulo_crear(int, int , int, int);
circulo_t* circulo_crear(int, int, int);

bool colisionanCirculos(circulo_t*, circulo_t*);
bool colisionanRectangulos(rectangulo_t*, rectangulo_t*);
bool colisionaRectanguloConCirculo(rectangulo_t*, circulo_t*);

void rectangulo_destruir(rectangulo_t*);
void circulo_destruir(circulo_t*);

void rectangulo_obtenerParametros(rectangulo_t*, int*, int*, int*, int*);
void circulo_obtenerParametros(circulo_t*, int*, int*, int*);

#endif // FIGURAS_H
