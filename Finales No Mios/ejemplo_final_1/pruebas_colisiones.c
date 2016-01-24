#include "Figuras.h"
#include <stdio.h>
#include <stdlib.h>

/* Funcion auxiliar par imprimir resultados de las pruebas: */
void print_test(char* name, bool result){
	printf("%s: %s\n", name, result? "OK" : "ERROR");
}


void pruebas_rectangulo_rectangulo(){
	
	printf("\nPRUEBAS DE COLISION RECTANGULO - RECTANGULO\n");
	
	rectangulo_t* rec1 = rectangulo_crear(0, 0, 10, 10);
	rectangulo_t* rec2 = rectangulo_crear(100, 100, 10, 10);
	
	print_test("1. no colisionan", !colisionanRectangulos(rec1, rec2) && !colisionanRectangulos(rec2, rec1));
	rectangulo_destruir(rec2);
	rec2 = rectangulo_crear(11, 11, 1, 2);
	print_test("2. no colisionan", !colisionanRectangulos(rec1, rec2) && !colisionanRectangulos(rec2, rec1));
	rectangulo_destruir(rec2);
	
	rec2 = rectangulo_crear(10, 10, 100, 200);
	print_test("3. colisionan", colisionanRectangulos(rec1, rec2) && colisionanRectangulos(rec2, rec1));
	rectangulo_destruir(rec2);
	
	rec2 = rectangulo_crear(0, 10, 1, 2);
	print_test("4. colisionan", colisionanRectangulos(rec1, rec2) && colisionanRectangulos(rec2, rec1));
	rectangulo_destruir(rec2);
	
	rec2 = rectangulo_crear(0, 0, 1, 1);
	print_test("5. colisionan", colisionanRectangulos(rec1, rec2) && colisionanRectangulos(rec2, rec1));
	rectangulo_destruir(rec2);
	
	
	rec2 = rectangulo_crear(0, 0, 10,10);
	print_test("6. colisionan", colisionanRectangulos(rec1, rec2) && colisionanRectangulos(rec2, rec1));
	rectangulo_destruir(rec2);
	
	
	rec2 = rectangulo_crear(0, 0, 100, 100);
	print_test("7. colisionan", colisionanRectangulos(rec1, rec2) && colisionanRectangulos(rec2, rec1));
	rectangulo_destruir(rec2);
	
	
	rec2 = rectangulo_crear(-10, -10, 10, 10);
	print_test("8. colisionan", colisionanRectangulos(rec1, rec2) && colisionanRectangulos(rec2, rec1));
	rectangulo_destruir(rec2);
	
	
	rec2 = rectangulo_crear(-10, -10, 10, 9);
	print_test("9. No colisionan", !colisionanRectangulos(rec1, rec2) && !colisionanRectangulos(rec2, rec1));
	rectangulo_destruir(rec2);
	
	rec2 = rectangulo_crear(-5, -3, 4, 2);
	print_test("10. No colisionan", !colisionanRectangulos(rec1, rec2) && !colisionanRectangulos(rec2, rec1));
	rectangulo_destruir(rec2);
	
	rec2 = rectangulo_crear(-5, -3, 5, 2);
	print_test("12. No colisionan", !colisionanRectangulos(rec1, rec2) && !colisionanRectangulos(rec2, rec1));
	rectangulo_destruir(rec2);
	
	rec2 = rectangulo_crear(-5, -3, 8, 1);
	print_test("13. No colisionan", !colisionanRectangulos(rec1, rec2) && !colisionanRectangulos(rec2, rec1));
	rectangulo_destruir(rec2);
	
	
	rec2 = rectangulo_crear(-5, -3, 4, 9);
	print_test("14. No colisionan", !colisionanRectangulos(rec1, rec2) && !colisionanRectangulos(rec2, rec1));
	rectangulo_destruir(rec2);
	
	rec2 = rectangulo_crear(-5, -3, 6, 6);
	print_test("15. colisionan", colisionanRectangulos(rec1, rec2) && colisionanRectangulos(rec2, rec1));
	rectangulo_destruir(rec2);
	
	rec2 = rectangulo_crear(-10, -10, 30, 50);
	print_test("16. colisionan", colisionanRectangulos(rec1, rec2) && colisionanRectangulos(rec2, rec1));
	rectangulo_destruir(rec2);
	
	rectangulo_destruir(rec1);
}

void pruebas_circulo_circulo(){
	
	printf("\nPRUEBAS DE COLISION CIRCULO - CIRCULO\n");
	
	circulo_t* circ1 = circulo_crear(10, 10, 10);
	
	circulo_t* circ2 = circulo_crear(100, 100, 10);
	print_test("1. no colisionan", !colisionanCirculos(circ1, circ2) && !colisionanCirculos(circ2, circ1));
	circulo_destruir(circ2);
	
	
	circ2 = circulo_crear(100, 10, 100);
	print_test("2. colisionan", colisionanCirculos(circ1, circ2) && colisionanCirculos(circ2, circ1));
	circulo_destruir(circ2);
	
	
	circ2 = circulo_crear(10, 20, 10);
	print_test("3. colisionan", colisionanCirculos(circ1, circ2) && colisionanCirculos(circ2, circ1));
	circulo_destruir(circ2);
	
	
	circ2 = circulo_crear(10, 30, 10);
	print_test("4. colisionan", colisionanCirculos(circ1, circ2) && colisionanCirculos(circ2, circ1));
	circulo_destruir(circ2);
	
	circ2 = circulo_crear(10, 31, 10);
	print_test("5. No colisionan", !colisionanCirculos(circ1, circ2) && !colisionanCirculos(circ2, circ1));
	circulo_destruir(circ2);
	
	
	circ2 = circulo_crear(10, -5, 10);
	print_test("6. colisionan", colisionanCirculos(circ1, circ2) && colisionanCirculos(circ2, circ1));
	circulo_destruir(circ2);
	
	
	circ2 = circulo_crear(15, -5, 5);
	print_test("7. no colisionan", !colisionanCirculos(circ1, circ2) && !colisionanCirculos(circ2, circ1));
	circulo_destruir(circ2);
	
	
	circ2 = circulo_crear(15, -5, 15);
	print_test("8. colisionan", colisionanCirculos(circ1, circ2) && colisionanCirculos(circ2, circ1));
	circulo_destruir(circ2);
	
	
	circ2 = circulo_crear(18, 2, 1);
	print_test("9. no colisionan", !colisionanCirculos(circ1, circ2) && !colisionanCirculos(circ2, circ1));
	circulo_destruir(circ2);
	
	
	circ2 = circulo_crear(20, 2, 2);
	print_test("10. no colisionan", !colisionanCirculos(circ1, circ2) && !colisionanCirculos(circ2, circ1));
	circulo_destruir(circ2);
	
	
	circ2 = circulo_crear(18, 2, 5);
	print_test("11. colisionan", colisionanCirculos(circ1, circ2) && colisionanCirculos(circ2, circ1));
	circulo_destruir(circ2);
	
	
	circ2 = circulo_crear(100, 100, 10);
	print_test("12. no colisionan", !colisionanCirculos(circ1, circ2) && !colisionanCirculos(circ2, circ1));
	circulo_destruir(circ2);
	
	
	circ2 = circulo_crear(27, 24, 10);
	print_test("13. no colisionan", !colisionanCirculos(circ1, circ2) && !colisionanCirculos(circ2, circ1));
	circulo_destruir(circ2);
	
	
	circ2 = circulo_crear(27, 24, 15);
	print_test("14. colisionan", colisionanCirculos(circ1, circ2) && colisionanCirculos(circ2, circ1));
	circulo_destruir(circ2);
	
	
	circ2 = circulo_crear(10, 10, 5);
	print_test("15. colisionan", colisionanCirculos(circ1, circ2) && colisionanCirculos(circ2, circ1));
	circulo_destruir(circ2);
	
	circulo_destruir(circ1);
	
}

void pruebas_rectangulo_circulo(){
	printf("\nPRUEBAS DE COLISION RECTANGULO - CIRCULO\n");
	
	rectangulo_t* rect = rectangulo_crear(10,10,20,10);
	circulo_t* circ;
	
	circ = circulo_crear(10, 10, 5);
	print_test("1. Mismo punto de origen: colisionan", colisionaRectanguloConCirculo(rect,circ));
	circulo_destruir(circ);
	
	circ = circulo_crear(20, 15, 1);
	print_test("2. Circulo contenido en rectangulo: colisionan", colisionaRectanguloConCirculo(rect,circ));
	circulo_destruir(circ);
	
	circ = circulo_crear(15, 9, 3);
	print_test("3. Circulo un poco mas a la derecha y arriba que el rect: colisionan", colisionaRectanguloConCirculo(rect,circ));
	circulo_destruir(circ);
	
	circ = circulo_crear(100, 10, 100);
	print_test("4. Circulo muy corrido pero con gran radio: colisionan", colisionaRectanguloConCirculo(rect,circ));
	circulo_destruir(circ);
	
	circ = circulo_crear(20, 15, 30);
	print_test("5. Circulo contiene rectangulo: colisionan", colisionaRectanguloConCirculo(rect,circ));
	circulo_destruir(circ);
	
	circ = circulo_crear(15, 15, 5);
	print_test("6. Circulo toca apenas al rectangulo por un lado: colision", colisionaRectanguloConCirculo(rect,circ));
	circulo_destruir(circ);
	
	circ = circulo_crear(10, 15, 5);
	print_test("7. Circulo toca apenas al rectangulo por un vertice: colision", colisionaRectanguloConCirculo(rect,circ));
	circulo_destruir(circ);
	
	circ = circulo_crear(5, 15, 8);
	print_test("8. Chocan por un costado: colision", colisionaRectanguloConCirculo(rect,circ));
	circulo_destruir(circ);
	
	circ = circulo_crear(6, 11, 3);
	print_test("9. No chocan desde un costado: no colisionan", !colisionaRectanguloConCirculo(rect,circ));
	circulo_destruir(circ);
	
	circ = circulo_crear(7, 11, 4);
	print_test("10. aumento un poco el radio del caso anterior: colision", colisionaRectanguloConCirculo(rect,circ));
	circulo_destruir(circ);
	
	circ = circulo_crear(7, 11, 5);
	print_test("11. Lo aumento aun mas: colision", colisionaRectanguloConCirculo(rect,circ));
	circulo_destruir(circ);
	
	circ = circulo_crear(50, 50, 10);
	print_test("12. Esta muy corrido el circulo: no colisionan", !colisionaRectanguloConCirculo(rect,circ));
	circulo_destruir(circ);
	
	circ = circulo_crear(35, 5, 6);
	print_test("13. No colisionan", !colisionaRectanguloConCirculo(rect,circ));
	circulo_destruir(circ);
	
	circ = circulo_crear(25, 10, 6);
	print_test("14. Chocan por un costado: colision", colisionaRectanguloConCirculo(rect,circ));
	circulo_destruir(circ);
	
	circ = circulo_crear(35, 15, 3);
	print_test("15. Desde un costado no llegan: no colisionan", !colisionaRectanguloConCirculo(rect,circ));
	circulo_destruir(circ);
	
	rectangulo_destruir(rect);
}

//Pruebas de que anden las colisiones
int main (void){
	pruebas_rectangulo_rectangulo();
	pruebas_circulo_circulo();
	pruebas_rectangulo_circulo();
	return 0;
}
