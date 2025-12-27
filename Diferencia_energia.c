#include "parametros.h"
int fuerza(int h){
	// Funcion que calcula la fuerza del indice h,
	// comprobando que se puedan referenciar esos valores
	int f,ind;
	f=0;
	ind=*(r+h);
	if(ind!=-1){// Si se puede referenciar lo sumo
		f=f+*(C+ind);
	}
	ind=*(l+h);
	if(ind!=-1){
		f=f+*(C+ind);
	}
	ind=*(d+h);
	if(ind!=-1){
		f=f+*(C+ind);
	}
	ind=*(u+h);
	if(ind!=-1){
		f=f+*(C+ind);
	}
	ind=*(ver+h);
	f=f+*(C+ind);// Siempre se puede referenciar
	return f;
}

int piso(int h){
	// Funcion que calcula en que piso esta este indice
	int p;
	p=1+h/(Lx*Ly);// Usamos la division entera
	return p;
}

double calculaProbabilidad(int i1,int i2){
	// Funcion que devuelve la probabilidad de un intercambio
	double prob,dife;
	dife=fuerza(i1)-fuerza(i2)+1.0+A*(1/pow(piso(i1),3)-1/pow(piso(i2),3));
	if(dife<0.0){
		prob=1.0;
	}else{
		prob=exp(-beta*dife);
	}
	return prob;
}
