#include <iostream>

using namespace std;

typedef struct{

	char id_ladrillo[20];
	float xi;
	float xd;
	float y;
	int resistencia;
}Ladrillo;


typedef struct{
	char id_bala[20];
	float x;
	float y;
	int energia;
	float distancia;//guardo distancia en caso de que choque y mate ladrillo
	char id_ladrilo[20];//Para guardar en el caso de que mate ladrillo
}Bala;

/*PROCESO LOS LADRILLOS Y LOS ORDENO *******************************/
void procesarLadrillos(Ladrillo* ladrillos, int &cantidad){

	FILE* archivo;
	archivo = fopen("ladrillos.txt","r");
	int cant = 0;
	if (archivo == NULL){
		cout<<"archivo vacio"<<endl;
		getchar();
	}
	int i;
	for(i=0; !feof(archivo);i++){

		fscanf(archivo,"%s %f %f %f %i", &ladrillos[i].id_ladrillo, &ladrillos[i].xi, &ladrillos[i].xd, &ladrillos[i].y, &ladrillos[i].resistencia);
		cant = cant + 1;
	}
	cantidad = cant;
	fclose(archivo);
}

int compare(const void* e1, const void* e2)
{
	float y1 = ((Ladrillo*)e1)->y;
	float y2 = ((Ladrillo*)e2)->y;

	if (y1 < y2) return -1;
	if (y1 == y2) return 0;
	return 1;
}

void ordenarLadrillos(Ladrillo* ladrillos,int cantidadladrillos)
{
	qsort(ladrillos,cantidadladrillos,sizeof(Ladrillo),compare);
}

/*FIN PROCESAMIENTO LADRILLOS ******************************************/


bool choca(Ladrillo ladrillo, Bala bala)
{
	if(bala.x >= ladrillo.xi && bala.x <= ladrillo.xd) return true;
	else 
	return false;
}


void procesarChoqueBala(Bala &bala,Ladrillo* ladrillos,int cantidadladrillos){

	int i;
	for(i=0; i< cantidadladrillos;i++){

		if (bala.y >= ladrillos[i].y || ladrillos[i].resistencia <= 0) 
			{
				bala.distancia = 0.0;
				strcpy(bala.id_ladrilo,"");
				continue;
			}
		
		bool choco = choca(ladrillos[i],bala);
		if (choco == false) continue;
		else{//La bala encuentra a un ladrillo tvia vivo y lo puede chocar

			ladrillos[i].resistencia = ladrillos[i].resistencia - bala.energia;
				if( ladrillos[i].resistencia <= 0)
				{//la bala mato el ladrillo
					bala.distancia = ladrillos[i].y - bala.y;
					strcpy(bala.id_ladrilo,ladrillos[i].id_ladrillo);
				}
				else
				{
					bala.distancia = 0.0;
					strcpy(bala.id_ladrilo,"");
				}

			break;
		}
	}


}

/*PROCESAMIENTO DE CADA BALA */

void procesarBalas(Bala* balas, Ladrillo* ladrillos,int &cantidadbalas,int cantidadladrillos)
{

	FILE* archivo;
	archivo = fopen("balas.txt","r");
	int cant = 0;
	if (archivo == NULL){
		cout<<"archivo no se pudo abrir"<<endl;
		getchar();
	}
	int i;

	for(i=0; !feof(archivo); i++)
	{
		fscanf(archivo,"%s %f %f %i",&balas[i].id_bala,&balas[i].x,&balas[i].y,&balas[i].energia);
		procesarChoqueBala(balas[i],ladrillos,cantidadladrillos);
		cant = cant + 1;
	}
	cantidadbalas = cant;
	fclose(archivo);
}

void mostrarResultado(Bala* balas,int cantidad)
{
	int i;
	cout<<"ID BALA	"<<"ID LADRILLO	 "<<"DISTANCIA"<<endl;
	cout<<"-------	"<<"-----------	 "<<"---------"<<endl;
	for(i=0;i<cantidad;i++)
	{
		cout<<balas[i].id_bala<<"	"	<<balas[i].id_ladrilo<<"	"<<balas[i].distancia<<endl;
		cout<<endl;
	}

}

int main(){

	int cantidadladrillos;
	Ladrillo ladrillos[4];
	procesarLadrillos(ladrillos,cantidadladrillos);
	ordenarLadrillos(ladrillos,cantidadladrillos);

	Bala balas[6];
	int cantidadbalas;
	procesarBalas(balas,ladrillos,cantidadbalas,cantidadladrillos);
	mostrarResultado(balas,cantidadbalas);

	getchar();
	return 0;

}