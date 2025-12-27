#include "parametros.h"
void anadirSalto(int i1,int i2){
	// Funcion que anade un elemento a la lista de adyacentes
	//printf("Anadiendo salto %d -> %d \n",i1,i2);
	//printf("NS:%d, NP:%d\n",numeroDeSaltos,Np);
	saltos[numeroDeSaltos][0]=i1;
	saltos[numeroDeSaltos][1]=i2;
	probabilidad[numeroDeSaltos]=calculaProbabilidad(i1,i2);
	numeroDeSaltos++;
	//printf("Salto anadido\n");
	//printf("NS:%d, NP:%d\n",numeroDeSaltos,Np);
}
/*
bool perteneceQ(int h){
	//Funcion que calcula si una celda esta en la lista de adyacencia
	bool p;
	int ind;
	p=false;
	for(ind=0;ind<longitud;ind++){
		if(ady[ind]==h){
			p=true;
			return p;
		}
	}
	return p;
}
*/
void quitarSalto(int i1,int i2){
	// Funcion que quita un elemento de la lista de adyacentes
	int empieza;
	int ind;// indice local para evitar problemas cuando hay llamadas a muchas funciones
	empieza=5*N;// Si no hay ninguno no mueva nada.
	//printf("Quitando salto: %d -> %d \n",i1,i2);
	//printf("NS:%d, NP:%d\n",numeroDeSaltos,Np);
	for(ind=0;ind<numeroDeSaltos;ind++){
		if(((*(*(saltos+ind)+0))==i1)&&((*(*(saltos+ind)+1))==i2)){
			empieza=ind;
			//printf("Salto quitado bien\n");
			numeroDeSaltos--;
			break;
		}
	}
	//numeroDeSaltos--;
	for(ind=empieza;ind<numeroDeSaltos;ind++){
		saltos[ind][0]=(*(*(saltos+(ind+1))+0));
		saltos[ind][1]=(*(*(saltos+(ind+1))+1));
		probabilidad[ind]=*(probabilidad+(ind+1));
	}
	//printf("Salto quitado\n");
	//printf("NS:%d, NP:%d\n",numeroDeSaltos,Np);
}

// Funciones para comprobar que el codigo es correcto
// No se usan en la ejecucion del codigo MC

bool haySaltoRepetido(){
	int ind,indd;
	int ind1,ind2;
	for(ind=0;ind<numeroDeSaltos;ind++){
		ind1=(*(*(saltos+ind)+0));
		ind2=(*(*(saltos+ind)+1));
		if((*(C+ind1))==0){
			printf("Indice 1 esta vacio (%d)\n",ind1);
		}
		if((*(C+ind2))==1){
			printf("Indice 2 esta lleno (%d)\n",ind2);
		}
		for(indd=(ind+1);indd<numeroDeSaltos;indd++){
			if(((*(*(saltos+indd)+0))==ind1)&&((*(*(saltos+indd)+1))==ind2)){
				printf("El salto repetido es %d -> %d\n",ind1,ind2);
				return true;
			}
		}
	}
	return false;
}

void escribeSaltos(){
	printf("Pintando los saltos\n");
	for(i=0;i<numeroDeSaltos;i++){
		printf("Salto %d: %ld->%ld\n",i,(*(*(saltos+i)+0)),(*(*(saltos+i)+1)));
	}
}

