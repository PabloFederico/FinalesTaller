#include "Figuras.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

/*Aclaracion: el (x,y) dentro del archivo de texto sera el punto central,
 * tanto para el rectangulo como para el circulo. En particular, luego
 * me interesara la esquina superior izquierda para el rectangulo.*/

#define ARCH_RECT "rectangulos.txt"
#define ARCH_CIR "rectangulos.txt"
char SEPARADOR = ';';

struct rectangulo{
	int x, y;
	int ancho, alto;
};

struct circulo{
	int x, y;
	int radio;
};

rectangulo_t* parsearRectangulo(char* linea){
	char c = linea[0];
	unsigned int i = 0, j = 0;
	char* aux = malloc (sizeof(char) * 5);
	int vector[4];
	unsigned int idx = 0;
	
	while (c != '\0'){
		if (c == SEPARADOR){
			aux[j] = '\0';
			vector[idx] = atoi(aux);
			free(aux);
			aux = malloc(sizeof(char) * 5);
			j = 0;
			idx++;
		}else{		
			aux[j] = c;
		
			j++;
		}
		i++;
		c = linea[i];
	}
	
	free(aux);
	rectangulo_t* r = rectangulo_crear(vector[0] - (vector[2] / 2), vector[1] - (vector[3] / 2), vector[2], vector[3]);
	return r;
}

circulo_t* parsearCirculo(char* linea){
	char c = linea[0];
	unsigned int i = 0, j = 0;
	char* aux = malloc (sizeof(char) * 5);
	int vector[3];
	unsigned int idx = 0;
	
	while (c != '\0'){
		if (c == SEPARADOR){
			aux[j] = '\0';
			vector[idx] = atoi(aux);
			free(aux);
			aux = malloc(sizeof(char) * 5);
			j = 0;
			idx++;
		}else{		
			aux[j] = c;
			j++;		
		}
		i++;
		c = linea[i];
	}
	free(aux);
	
	return circulo_crear(vector[0], vector[1], vector[2]);
}


bool cargarRectangulos(rectangulo_t*** vector, unsigned int* cant, char* ruta){
	FILE* archivo = fopen(ruta,"r");
	if (!archivo) return false;
	unsigned int tam = 10;
	
	rectangulo_t** rec = (rectangulo_t**) malloc (sizeof(rectangulo_t*) * tam);
	if (!rec) return false;
	unsigned int n = 0;
	
	char* buffer;
	char c = 0;
	unsigned int i = 0;
	while (!feof(archivo)){
		i = 0;
		buffer = (char*)malloc (sizeof(char) * 30);
		while (!feof(archivo) && (c = fgetc(archivo)) != '\n'){
			buffer[i] = c;
			i++;
		}
			
		buffer[i] = '\0';
		if (strlen(buffer) == 1 || strlen(buffer) == 0) continue;
		
		if (n == tam){
			tam += 10;
			rectangulo_t** aux = (rectangulo_t**) realloc (rec,sizeof(rectangulo_t*) * tam);
			if (!aux){ free (rec); return false;}
			rec = aux;
		}
		rec[n] = parsearRectangulo(buffer);
		free(buffer);
		n++;
	}
	
	fclose(archivo);
	
	*vector = rec;
	*cant = n;
	free(buffer);
	return true;
}


bool cargarCirculos(circulo_t*** vector, unsigned int* cant, char* ruta){
	unsigned int tam = 10;
	FILE* archivo = fopen(ruta,"r");
	if (!archivo) return false;
	
	circulo_t** cir = (circulo_t**) malloc (sizeof(circulo_t*) * tam);
	if (!cir) return false;
	unsigned int n = 0;
	
	
	char* buffer;
	char c = 0;
	unsigned int i = 0;
	while (!feof(archivo)){
		i = 0;
		buffer = (char*)malloc (sizeof(char) * 30);
		while (!feof(archivo) && (c = fgetc(archivo)) != '\n'){
			buffer[i] = c;
			i++;
		}
		
		buffer[i] = '\0';
		
		if (n == tam){
			tam += 10;
			circulo_t** aux = (circulo_t**) realloc (cir,sizeof(circulo_t*) * tam);
			if (!aux){ free (cir); return false;}
			cir = aux;
		}
		cir[n] = parsearCirculo(buffer);
		n++;
	}
	
	fclose(archivo);
	
	*vector = cir;
	*cant = n;
	free(buffer);
	return true;
}


bool colisionanRectangulos(rectangulo_t* rect1, rectangulo_t* rect2){
	int aux, auxOtra;

	aux = rect1->x + rect1->ancho;
	auxOtra = rect2->x;
	if (auxOtra > aux) return false;

	aux = rect1->x;
	auxOtra = rect2->x + rect2->ancho;
	if (auxOtra < aux) return false;

	aux = rect1->y + rect1->alto;
	auxOtra = rect2->y;
	if (auxOtra > aux) return false;

	aux = rect1->y;
	auxOtra = rect2->y + rect2->alto;
	if (auxOtra < aux) return false;

	return true;

}

bool colisionanCirculos (circulo_t* circ1, circulo_t* circ2){
	int x = circ1->x - circ2->x;
	int y = circ1->y - circ2->y;
	int dist_centros_cuad = x*x + y*y;
	
	int suma_radios = circ1->radio + circ2->radio;
	
	int suma_radios_cuad = suma_radios * suma_radios;
	
	return (suma_radios_cuad >= dist_centros_cuad);
		
}

void obtenerVerticeMasCercano(rectangulo_t*, circulo_t*, int*, int*);

bool centroEnRectangulo(rectangulo_t* rect ,circulo_t* circ){
	if (circ->x < rect->x) return false;
	
	if (circ->x > (rect->x + rect->ancho)) return false;
	
	if (circ->y < rect->y) return false;
	
	if (circ->y > (rect->y + rect->alto)) return false;
	
	return true;
}

bool colisionaRectanguloConCirculo(rectangulo_t* rect, circulo_t* circ){
	if (centroEnRectangulo(rect, circ)) return true;
	
	int pto_x, pto_y;
	
	if ((circ->x >= rect->x) && (circ->x <= (rect->x + rect->ancho))){
		pto_x = circ->x;
		if (circ->y >= (rect->y + rect->alto))
			pto_y = rect->y + rect->alto;
		else
			pto_y = rect->y;
				
	}else if ((circ->y >= rect->y) && (circ->y <= (rect->y + rect->alto))){
		pto_y = circ->y;
		if (circ->x >= (rect->x + rect->ancho))
			pto_x = rect->x + rect->ancho;
		else
			pto_x = rect->x;
		
	} else{
		obtenerVerticeMasCercano(rect, circ, &pto_x, &pto_y);
	}
	
	int x = pto_x - circ->x;
	int y = pto_y - circ->y;
	
	int dist_cuad = x * x + y * y;
	int radio_c = circ->radio * circ->radio;
	
	return (radio_c >= dist_cuad);
}

void obtenerVerticeMasCercano(rectangulo_t* rect, circulo_t* circ, int* x, int* y){
	int rcentro_x = rect->x + rect->ancho / 2;
	int rcentro_y = rect->y + rect->alto / 2;
	
	//me fijo si el centro del circulo esta arriba del centro del rectangulo
	if (circ->y < rcentro_y){
		//esta arriba:
		*y = rect->y;
		//me fijo si el centro del ciruclo esta a la izquierda del centro del rectangulo
		if (circ->x < rcentro_x)
			*x = rect->x;
		else			
			*x = rect->x + rect->ancho;	
	}else{
		//esta abajo:
		*y = rect->y + rect->alto;
		//me fijo si el centro del ciruclo esta a la izquierda del centro del rectangulo
		if (circ->x < rcentro_x)
			*x = rect->x;
		else
			*x = rect->x + rect->ancho;
	}
}

rectangulo_t* rectangulo_crear(int x, int y, int ancho, int alto){
	if (ancho <= 0 || alto <= 0) return NULL;
	rectangulo_t* rec = (rectangulo_t*) malloc (sizeof(rectangulo_t));
	if (!rec) return NULL;
	
	rec->x = x;
	rec->y = y;
	rec->ancho = ancho;
	rec->alto = alto;
	return rec;
}

circulo_t* circulo_crear(int x, int y, int radio){
	if (radio <= 0) return NULL;
	circulo_t* cir = (circulo_t*) malloc (sizeof(circulo_t));
	if (!cir) return NULL;
	
	cir->x = x;
	cir->y = y;
	cir->radio = radio;
	return cir;
}

void rectangulo_destruir(rectangulo_t* rec){
	free (rec);
}

void circulo_destruir(circulo_t* cir){
	free (cir);
}

void rectangulo_obtenerParametros(rectangulo_t* r, int* x, int* y, int* an, int* al){
	if (x) 
		*x = r->x;
	if (y) 
		*y = r->y;
	if (al) 
		*al = r->alto;
	if (an) 
		*an = r->ancho;
}

void circulo_obtenerParametros(circulo_t* c, int* x, int* y, int* r){
	if (x) 
		*x = c->x;
	if (y) 
		*y = c->y;
	if (r) 
		*r = c->radio;
}
