#include "Figuras.h"
#include <stdio.h>
#include <stdlib.h>
#define RUTA_R "rectangulos.txt"

/* Funcion auxiliar par imprimir resultados de las pruebas: */
void print_test(char* name, bool result){
	printf("%s: %s\n", name, result? "OK" : "ERROR");
}

void pruebas_parseoRect(){
	printf("\nCOMIENZO PRUEBAS PARSEO RECTANGULO\n");
	char* ejemplo = "10;10;10;10;";
	rectangulo_t* rect = (rectangulo_t*) parsearRectangulo((char*)ejemplo);
	
	int ancho, alto, x, y;
	
	rectangulo_obtenerParametros(rect, &x ,&y, &ancho, &alto);
	
	print_test("El ancho esta bien parseado (10)", ancho == 10);
	print_test("El alto esta bien parseado (10)", alto == 10);
	print_test("El x esta bien parseado (5)", x == 5);
	print_test("El y esta bien parseado (5)", y == 5);
	
	rectangulo_destruir(rect);
	
	ejemplo = "300;250;150;26;";
	rect = (rectangulo_t*) parsearRectangulo((char*)ejemplo);
	
	
	rectangulo_obtenerParametros(rect, &x ,&y, &ancho, &alto);
	
	print_test("El ancho esta bien parseado (150)", ancho == 150);
	print_test("El alto esta bien parseado (26)", alto == 26);
	print_test("El x esta bien parseado (225)", x == 225);
	print_test("El y esta bien parseado (237)", y == 237);
	
	rectangulo_destruir(rect);
}

void pruebas_parseoCirc(){
	printf("\nCOMIENZO PRUEBAS PARSEO CIRCULO\n");
	char* ejemplo = "10;10;10;";
	circulo_t* circ = (circulo_t*) parsearCirculo((char*)ejemplo);
	
	int radio, x, y;
	
	circulo_obtenerParametros(circ, &x ,&y, &radio);
	
	print_test("El ancho esta bien parseado (10)", radio == 10);
	print_test("El x esta bien parseado (10)", x == 10);
	print_test("El y esta bien parseado (10)", y == 10);
	
	circulo_destruir(circ);
	
	ejemplo = "150;130;112;";
	circ = (circulo_t*) parsearCirculo((char*)ejemplo);
	
	circulo_obtenerParametros(circ, &x ,&y, &radio);
	
	print_test("El ancho esta bien parseado (112)", radio == 112);
	print_test("El x esta bien parseado (150)", x == 150);
	print_test("El y esta bien parseado (130)", y == 130);
	
	circulo_destruir(circ);
	
}

void pruebas_cargaRectangulo(){
	printf("\nCOMIENZO DE PRUEBAS DE LEVANTAR RECTAGULOS DESDE ARCHIVO\n");
	
	rectangulo_t** rects;
	unsigned int cant;
	
	print_test("bien cargados los rectangulos",cargarRectangulos(&rects, &cant, RUTA_R));
	
	unsigned int i;
	
	for (i = 0; i < cant; i++)
		free(rects[i]);
	
	free(rects);
}

int main (void){
	
	pruebas_parseoRect();
	pruebas_parseoCirc();
	pruebas_cargaRectangulo();
	return 0;
}
