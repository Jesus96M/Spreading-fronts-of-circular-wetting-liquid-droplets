#include "parametros.h"
void anadirIndice(int nuevo){
	// Funcion que anade un elemento a la lista de indices
	indices[longitudIndices]=nuevo;
	longitudIndices++;
}

void quitarIndice(int eliminar){
	// Funcion que quita un elemento de la lista de indices
	int empieza;
	int ind;// indice local para evitar problemas cuando hay llamadas a muchas funciones
	empieza=N;// Si no hay ninguno no mueva nada.
	for(ind=0;ind<longitudIndices;ind++){
		if(*(indices+ind)==eliminar){
			empieza=ind;
			longitudIndices--;
			break;
		}
	}
	for(ind=empieza;ind<longitudIndices;ind++){
		indices[ind]=*(indices+(ind+1));
	}
}

bool perteneceIndiceQ(int h){
	//Funcion que calcula si un indice esta en la lista de indices
	bool p;
	int ind;
	p=false;
	for(ind=0;ind<longitudIndices;ind++){
		if(*(indices+ind)==h){
			p=true;
			return p;
		}
	}
	return p;
}
