#include "parametros.h"

void cambio(int h1,int h2){
	// Funcion que actualiza los valores de las celdas y la lista de saltos cuando se ha
	// aceptado el cambio h1-->h2
	C[h1]=0;
	C[h2]=1;
	if(perteneceDropletQ(h1)){// Si es del Droplet lo reponemos
		C[h1]=1;//Lo reponemos
		comprobacionCD(h2);
		// El h2-->h1 no hay que quitarlo en este caso (Se ha anadido una vez solo)
		// El h1-->h2 hay que quitarlo ahora también
		//quitarSalto(h1,h2);//No se habia quitado
		// Esto ultimo no es necesario ya que h1 se repone (esta lleno) y el salto se quita en la comprobacion C
		// Hay que anadir una particula al recuento
		numeroParticulas[getZ(h1)]++;
	} else{
		comprobacionAB(h1);
		comprobacionCD(h2);
		// Al hacer estas comprobaciones no estamos quitando el salto h1-->h2, ya que ahora h1 esta vacio y al hacer 
		// la comprobacionCD no se elmina, y ademas estamos anadiendo el salto h2-->h1 dos veces, uno en la AB y otro en CD
		quitarSalto(h1,h2);//No se habia quitado
		quitarSalto(h2,h1);//Se habia anadido 2 veces
	}
	// No solo es necesario anadir y quitar transiciones. Tambien hay que recalcular la probabilidad de
	// aquellas que estan cerca y su energia se ve afectada.
	recalculaProbabilidades(h1,h2);
	if(*(ver+h1)==h2){
		// Si el cambio se ha dado en vertical hay que retocar el numero de particulas de ambos.
		numeroParticulas[getZ(h1)]--;
		numeroParticulas[getZ(h2)]++;
	}
}

void comprobacionAB(int h1){
	// CASO A
	// Vecinos llenos de la celda que se ha quedado vacia
	// CASO B
	// Vecinos vacios de la celda que se ha quedado vacia
	int ind;
	ind=*(r+h1);
	if(ind!=-1){//Podemos referenciarlo
		if(*(C+ind)==1){// Y esta lleno (CASO A)
			anadirSalto(ind,h1);// Lo anadimos
		}else{// Si esta vacio (CASO B)
			quitarSalto(h1,ind);
		}
	}
	ind=*(u+h1);
	if(ind!=-1){//Podemos referenciarlo
		if(*(C+ind)==1){// Y esta lleno (CASO A)
			anadirSalto(ind,h1);// Lo anadimos
		}else{// Si esta vacio (CASO B)
			quitarSalto(h1,ind);
		}
	}
	ind=*(d+h1);
	if(ind!=-1){//Podemos referenciarlo
		if(*(C+ind)==1){// Y esta lleno (CASO A)
			anadirSalto(ind,h1);// Lo anadimos
		}else{// Si esta vacio (CASO B)
			quitarSalto(h1,ind);
		}
	}
	ind=*(l+h1);
	if(ind!=-1){//Podemos referenciarlo
		if(*(C+ind)==1){// Y esta lleno (CASO A)
			anadirSalto(ind,h1);// Lo anadimos
		}else{// Si esta vacio (CASO B)
			quitarSalto(h1,ind);
		}
	}
	// Aqui no hay que comprobarlo ya que el ver siempre existe.
	ind=*(ver+h1);;
	if(*(C+ind)==1){// Y esta lleno (CASO A)
		anadirSalto(ind,h1);// Lo anadimos
	}else{// Si esta vacio (CASO B)
		quitarSalto(h1,ind);
	}
}

void comprobacionCD(int h2){
	// CASO C
	// Vecinos llenos de la celda que se ha quedado llena
	// CASO D
	// Vecinos vacios de la celda que se ha quedado llena
	int ind;
	ind=*(r+h2);
	if(ind!=-1){//Podemos referenciarlo
		if(*(C+ind)==1){// Y esta lleno (CASO C)
			quitarSalto(ind,h2);
		}else{// Si esta vacio (CASO D)
			anadirSalto(h2,ind);
		}
	}
	ind=*(u+h2);
	if(ind!=-1){//Podemos referenciarlo
		if(*(C+ind)==1){// Y esta lleno (CASO C)
			quitarSalto(ind,h2);
		}else{// Si esta vacio (CASO D)
			anadirSalto(h2,ind);
		}
	}
	ind=*(d+h2);
	if(ind!=-1){//Podemos referenciarlo
		if(*(C+ind)==1){// Y esta lleno (CASO C)
			quitarSalto(ind,h2);
		}else{// Si esta vacio (CASO D)
			anadirSalto(h2,ind);
		}
	}
	ind=*(l+h2);
	if(ind!=-1){//Podemos referenciarlo
		if(*(C+ind)==1){// Y esta lleno (CASO C)
			quitarSalto(ind,h2);
		}else{// Si esta vacio (CASO D)
			anadirSalto(h2,ind);
		}
	}
	ind=*(ver+h2);
	if(*(C+ind)==1){// Y esta lleno (CASO C)
		quitarSalto(ind,h2);
	}else{// Si esta vacio (CASO D)
		anadirSalto(h2,ind);
	}
}

void recalculaProbabilidades(int h1, int h2){
	int ind;
	// Todas aquellas transiciones que tengan algun indice vecino de h1 o h2 deben
	// recalcular su probabilidad de transicion.
	for(i=0;i<numeroDeSaltos;i++){
		// Recorro todas las transiciones y compruebo si hay alguno de los vecinos de h1 o de h2 en cualquiera de
		// las posiciones del salto. Si es asi actualizo la probabilidad.
		ind=*(r+h1);
		if(ind!=-1){// Si puedo referenciarlo
			if(((*(*(saltos+i)+0))==ind)||(*(*(saltos+i)+1))==ind){// Si alguno de los indice coincide
				probabilidad[i]=calculaProbabilidad(*(*(saltos+i)+0),*(*(saltos+i)+1));// Recalculo
			}
		}
		ind=*(r+h2);
		if(ind!=-1){// Si puedo referenciarlo
			if(((*(*(saltos+i)+0))==ind)||(*(*(saltos+i)+1))==ind){// Si alguno de los indice coincide
				probabilidad[i]=calculaProbabilidad(*(*(saltos+i)+0),*(*(saltos+i)+1));// Recalculo
			}
		}
		ind=*(l+h1);
		if(ind!=-1){// Si puedo referenciarlo
			if(((*(*(saltos+i)+0))==ind)||(*(*(saltos+i)+1))==ind){// Si alguno de los indice coincide
				probabilidad[i]=calculaProbabilidad(*(*(saltos+i)+0),*(*(saltos+i)+1));// Recalculo
			}
		}
		ind=*(l+h2);
		if(ind!=-1){// Si puedo referenciarlo
			if(((*(*(saltos+i)+0))==ind)||(*(*(saltos+i)+1))==ind){// Si alguno de los indice coincide
				probabilidad[i]=calculaProbabilidad(*(*(saltos+i)+0),*(*(saltos+i)+1));// Recalculo
			}
		}
		ind=*(u+h1);
		if(ind!=-1){// Si puedo referenciarlo
			if(((*(*(saltos+i)+0))==ind)||(*(*(saltos+i)+1))==ind){// Si alguno de los indice coincide
				probabilidad[i]=calculaProbabilidad(*(*(saltos+i)+0),*(*(saltos+i)+1));// Recalculo
			}
		}
		ind=*(u+h2);
		if(ind!=-1){// Si puedo referenciarlo
			if(((*(*(saltos+i)+0))==ind)||(*(*(saltos+i)+1))==ind){// Si alguno de los indice coincide
				probabilidad[i]=calculaProbabilidad(*(*(saltos+i)+0),*(*(saltos+i)+1));// Recalculo
			}
		}
		ind=*(d+h1);
		if(ind!=-1){// Si puedo referenciarlo
			if(((*(*(saltos+i)+0))==ind)||(*(*(saltos+i)+1))==ind){// Si alguno de los indice coincide
				probabilidad[i]=calculaProbabilidad(*(*(saltos+i)+0),*(*(saltos+i)+1));// Recalculo
			}
		}
		ind=*(d+h2);
		if(ind!=-1){// Si puedo referenciarlo
			if(((*(*(saltos+i)+0))==ind)||(*(*(saltos+i)+1))==ind){// Si alguno de los indice coincide
				probabilidad[i]=calculaProbabilidad(*(*(saltos+i)+0),*(*(saltos+i)+1));// Recalculo
			}
		}
		ind=*(ver+h1);
		if(((*(*(saltos+i)+0))==ind)||(*(*(saltos+i)+1))==ind){// Si alguno de los indice coincide
			probabilidad[i]=calculaProbabilidad(*(*(saltos+i)+0),*(*(saltos+i)+1));// Recalculo
		}
		ind=*(ver+h2);
		if(((*(*(saltos+i)+0))==ind)||(*(*(saltos+i)+1))==ind){// Si alguno de los indice coincide
			probabilidad[i]=calculaProbabilidad(*(*(saltos+i)+0),*(*(saltos+i)+1));// Recalculo
		}
	}
}

bool perteneceDropletQ(int h){
	// Funcion que calcula si una celda es del Droplet Reservoir
	// True=Si False=No
	double distanciaAlCentro;
	//Calculamos la distancia al centro
	distanciaAlCentro=distanciaEuclidea(h,DROPLET1);
	if(distanciaAlCentro<radio){
		return true;
	}else{
		return false;
	}
}

bool algunVecinoVacioQ(int h){
	// Funcion que calcula si una celda tiene algun vecino vacio.
	// True=Si False=No
	// Recorremos los vecinos del h
	bool b;
	b=false;
	int ind;
	// Hay que ver si el C es igual a 0 (vacio)
	// pero primero hay que ver si se puede referenciar ese vecino
	ind=*(r+h);
	if(ind!=-1){//Podemos referenciarlo
		if((*(C+ind))==0){// Y esta vacio
			b=true;
			return b;
		}
	}
	ind=*(u+h);
	if(ind!=-1){
		if((*(C+ind))==0){
			b=true;
			return b;
		}
	}
	ind=*(d+h);
	if(ind!=-1){
		if((*(C+ind))==0){
			b=true;
			return b;
		}
	}
	ind=*(l+h);
	if(ind!=-1){
		if((*(C+ind))==0){
			b=true;
			return b;
		}
	}
	// Aqui no hay que comprobarlo ya que el ver siempre existe.
	ind=*(ver+h);
	if((*(C+ind))==0){
		b=true;
		return b;
	}
	return b;
}

void borraUltimaColumna(){
	// Funcion que pone a 0 toda la ultima columna (x=Lx-1)
	// Recorremos la ultima columna en ambos pisos
	// Si encontramos un elemento que este a 1 entonces lo ponemos a 0 y lo quitamos
	// de la lista de adyacencia
	// Hay que llamar a la funcion en cada paso del for
	int h,ind;
	x=Lx-1;
	for(y=0;y<Ly;y++){
		h=x+y*Lx;// Indice para el piso de abajo
		if(*(C+h)==1){//Si esta lleno
			//printf("Vaciando la celda del borde %d\n",h);
			C[h]=0;//Lo pongo a 0
			numeroParticulas[0]--;
			//Recorro las transiciones y quito todas aquellas en las que el primer indice sea el h
			for(ind=0;ind<numeroDeSaltos;ind++){
				//printf("%ld -> %ld\n",(*(*(saltos+ind)+0)),(*(*(saltos+ind)+1)));
				if((*(*(saltos+ind)+0))==h){
					//printf("Quitando salto de la ultima columna:\n");
					quitarSalto((*(*(saltos+ind)+0)),(*(*(saltos+ind)+1)));
					ind--;// cuando se quita un salto, numeroDeSaltos-- y todos se mueven uno a la izquierda
				}
			}
		}
		h=x+y*Lx+Lx*Ly;// Indice para el piso de arriba
		if(*(C+h)==1){//Si esta lleno
			//printf("Vaciando la celda del borde %d\n",h);
			C[h]=0;//Lo pongo a 0
			numeroParticulas[1]--;
			//escribeSaltos();
			//printf("h:%d\n",h);
			//Recorro las transiciones y quito todas aquellas en las que el primer indice sea el h
			for(ind=0;ind<numeroDeSaltos;ind++){
				//printf("%d -> %d\n",(*(*(saltos+ind)+0)),(*(*(saltos+ind)+1)));
				if((*(*(saltos+ind)+0))==h){
					//printf("Quitando salto de la ultima columna\n");
					quitarSalto((*(*(saltos+ind)+0)),(*(*(saltos+ind)+1)));
					ind--;
				}
			}
		}
	}
	x=0;
	for(y=0;y<Ly;y++){
		h=y*Lx;// Indice para el piso de abajo
		if(*(C+h)==1){//Si esta lleno
			//printf("Vaciando la celda del borde %d\n",h);
			C[h]=0;//Lo pongo a 0
			numeroParticulas[0]--;
			//Recorro las transiciones y quito todas aquellas en las que el primer indice sea el h
			for(ind=0;ind<numeroDeSaltos;ind++){
				//printf("%d -> %d\n",(*(*(saltos+ind)+0)),(*(*(saltos+ind)+1)));
				if((*(*(saltos+ind)+0))==h){
					//printf("Quitando salto de la ultima columna\n");
					quitarSalto((*(*(saltos+ind)+0)),(*(*(saltos+ind)+1)));
					ind--;// cuando se quita un salto, numeroDeSaltos-- y todos se mueven uno a la izquierda
				}
			}
		}
		h=y*Lx+Lx*Ly;// Indice para el piso de arriba
		if(*(C+h)==1){//Si esta lleno
			//printf("Vaciando la celda del borde %d\n",h);
			C[h]=0;//Lo pongo a 0
			numeroParticulas[1]--;
			//escribeSaltos();
			//printf("h:%d\n",h);
			//Recorro las transiciones y quito todas aquellas en las que el primer indice sea el h
			for(ind=0;ind<numeroDeSaltos;ind++){
				//printf("%d -> %d\n",(*(*(saltos+ind)+0)),(*(*(saltos+ind)+1)));
				if((*(*(saltos+ind)+0))==h){
					//printf("Quitando salto de la ultima columna\n");
					quitarSalto((*(*(saltos+ind)+0)),(*(*(saltos+ind)+1)));
					ind--;
				}
			}
		}
	}
	y=0;
	for(x=0;x<Lx;x++){
		h=x;// Indice para el piso de abajo
		if(*(C+h)==1){//Si esta lleno
			//printf("Vaciando la celda del borde %d\n",h);
			C[h]=0;//Lo pongo a 0
			numeroParticulas[0]--;
			//Recorro las transiciones y quito todas aquellas en las que el primer indice sea el h
			for(ind=0;ind<numeroDeSaltos;ind++){
				//printf("%d -> %d\n",(*(*(saltos+ind)+0)),(*(*(saltos+ind)+1)));
				if((*(*(saltos+ind)+0))==h){
					//printf("Quitando salto de la ultima columna\n");
					quitarSalto((*(*(saltos+ind)+0)),(*(*(saltos+ind)+1)));
					ind--;// cuando se quita un salto, numeroDeSaltos-- y todos se mueven uno a la izquierda
				}
			}
		}
		h=x+Lx*Ly;// Indice para el piso de arriba
		if(*(C+h)==1){//Si esta lleno
			//printf("Vaciando la celda del borde %d\n",h);
			C[h]=0;//Lo pongo a 0
			numeroParticulas[1]--;
			//escribeSaltos();
			//printf("h:%d\n",h);
			//Recorro las transiciones y quito todas aquellas en las que el primer indice sea el h
			for(ind=0;ind<numeroDeSaltos;ind++){
				//printf("%d -> %d\n",(*(*(saltos+ind)+0)),(*(*(saltos+ind)+1)));
				if((*(*(saltos+ind)+0))==h){
					//printf("Quitando salto de la ultima columna\n");
					quitarSalto((*(*(saltos+ind)+0)),(*(*(saltos+ind)+1)));
					ind--;
				}
			}
		}
	}
	y=Ly-1;
	for(x=0;x<Lx;x++){
		h=x+y*Lx;// Indice para el piso de abajo
		if(*(C+h)==1){//Si esta lleno
			//printf("Vaciando la celda del borde %d\n",h);
			C[h]=0;//Lo pongo a 0
			numeroParticulas[0]--;
			//Recorro las transiciones y quito todas aquellas en las que el primer indice sea el h
			for(ind=0;ind<numeroDeSaltos;ind++){
				//printf("%d -> %d\n",(*(*(saltos+ind)+0)),(*(*(saltos+ind)+1)));
				if((*(*(saltos+ind)+0))==h){
					//printf("Quitando salto de la ultima columna\n");
					quitarSalto((*(*(saltos+ind)+0)),(*(*(saltos+ind)+1)));
					ind--;// cuando se quita un salto, numeroDeSaltos-- y todos se mueven uno a la izquierda
				}
			}
		}
		h=x+y*Lx+Lx*Ly;// Indice para el piso de arriba
		if(*(C+h)==1){//Si esta lleno
			//printf("Vaciando la celda del borde %d\n",h);
			C[h]=0;//Lo pongo a 0
			numeroParticulas[1]--;
			//escribeSaltos();
			//printf("h:%d\n",h);
			//Recorro las transiciones y quito todas aquellas en las que el primer indice sea el h
			for(ind=0;ind<numeroDeSaltos;ind++){
				//printf("%d -> %d\n",(*(*(saltos+ind)+0)),(*(*(saltos+ind)+1)));
				if((*(*(saltos+ind)+0))==h){
					//printf("Quitando salto de la ultima columna\n");
					quitarSalto((*(*(saltos+ind)+0)),(*(*(saltos+ind)+1)));
					ind--;
				}
			}
		}
	}
}

/*
int numeroVecinosVacios(int h){
	// Funcion que devuelve el numero de vecinos vacios de una celda dada
	int contador,ind;
	contador=0;
	ind=r[h];
	if(ind!=-1){//Podemos referenciarlo
		if(C[ind]==0){// Y esta vacio
			contador++;
		}
	}
	ind=u[h];
	if(ind!=-1){
		if(C[ind]==0){
			contador++;
		}
	}
	ind=d[h];
	if(ind!=-1){
		if(C[ind]==0){
			contador++;
		}
	}
	ind=l[h];
	if(ind!=-1){
		if(C[ind]==0){
			contador++;
		}
	}
	// Aqui no hay que comprobarlo ya que el ver siempre existe.
	if(C[ver[h]]==0){
		contador++;
	}
	return contador;
}
*/
/*
void calculaVecinosVacios(int h, int nV){
	//Funcion que da los vecinosVacios de un indice dado
	//Veamos cuanta memoria tenemos que reservar
	int contador,ind;
	vecinosVacios=(int*)realloc(vecinosVacios,nV*sizeof(int));
	// Ahora rellenamos este vector.
	contador=0;
	ind=r[h];
	if(ind!=-1){//Podemos referenciarlo
		if(C[ind]==0){// Y esta vacio
			vecinosVacios[contador]=ind;
			contador++;
		}
	}
	ind=u[h];
	if(ind!=-1){
		if(C[ind]==0){
			vecinosVacios[contador]=ind;
			contador++;
		}
	}
	ind=d[h];
	if(ind!=-1){
		if(C[ind]==0){
			vecinosVacios[contador]=ind;
			contador++;
		}
	}
	ind=l[h];
	if(ind!=-1){
		if(C[ind]==0){
			vecinosVacios[contador]=ind;
			contador++;
		}
	}
	// Aqui no hay que comprobarlo ya que el ver siempre existe.
	ind=ver[h];
	if(C[ind]==0){
		vecinosVacios[contador]=ind;
		contador++;
	}
}
*/

