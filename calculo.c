#include "parametros.h"
void calculaConectados(int hz){
	int ind;
	// Funcion que aplica el Metodo de Cluster para calcular que celdas estan conectadas al Droplet via
	// primeros vecinos llenos
	// Renovamos todo el vector a cero salvo el Droplet
	// Renovamos a cero la planta correspondiente
	for(i=(hz*Lx*Ly);i<((hz+1)*Lx*Ly);i++){
		conectados[i]=0;
	}
	//Anadimos la celda del Droplet a conectados
	if(hz==0){//Piso abajo
		conectados[DROPLET1]=1;
	}
	if(hz==1){//Piso arriba
		conectados[DROPLET2]=1;
	}
	//Reinicio los indices
	longitudIndices=0;
	// Anado los 4 indices que son vecinos del Droplet si estan llenos
	if(hz==0){//Piso abajo
		if(*(C+*(r+DROPLET1))==1){
			anadirIndice(*(r+DROPLET1));
		}
		if(*(C+*(l+DROPLET1))==1){
			anadirIndice(*(l+DROPLET1));
		}
		if(*(C+*(u+DROPLET1))==1){
			anadirIndice(*(u+DROPLET1));
		}
		if(*(C+*(d+DROPLET1))==1){
			anadirIndice(*(d+DROPLET1));
		}
	}
	if(hz==1){//Piso arriba
		if(*(C+*(r+DROPLET2))==1){
			anadirIndice(*(r+DROPLET2));
		}
		if(*(C+*(l+DROPLET2))==1){
			anadirIndice(*(l+DROPLET2));
		}
		if(*(C+*(u+DROPLET2))==1){
			anadirIndice(*(u+DROPLET2));
		}
		if(*(C+*(d+DROPLET2))==1){
			anadirIndice(*(d+DROPLET2));
		}
	}
	while(longitudIndices>0){//Mientras quedan indices
		ind=(int) longitudIndices*FRANDOM;//Elijo un indice al azar
		ind=*(indices+ind);
		conectados[ind]=1;//Lo anado a conectados
		//Anado los vecinos que esten llenos y no esten en conectados
		// ni en la lista de indices
		revisarVecinos(ind);
		// Elimino este indice que ya ha sido anadido a conectados
		quitarIndice(ind);
	}
}

void revisarVecinos(int ind){
	// Funcion necesaria para aplicar el metodo de Cluster. Revisa que vecinos
	// estan en conectados o en la lista de indices para actualizar esta ultima
	int indr,indd,indl,indu;
	indr=*(r+ind);
	indd=*(d+ind);
	indu=*(u+ind);
	indl=*(l+ind);
	if((indr!=-1)&&(*(C+indr)==1)&&(*(conectados+indr)==0)&&(!perteneceIndiceQ(indr))){
		// Si puedo referenciarlo y
		// Esta lleno y
		// No esta en conectados y
		// No pertenece a la lista de Indices, entonces lo anado
		anadirIndice(indr);
	}
	if((indd!=-1)&&(*(C+indd)==1)&&(*(conectados+indd)==0)&&(!perteneceIndiceQ(indd))){
		anadirIndice(indd);
	}
	if((indu!=-1)&&(*(C+indu)==1)&&(*(conectados+indu)==0)&&(!perteneceIndiceQ(indu))){
		anadirIndice(indu);
	}
	if((indl!=-1)&&(*(C+indl)==1)&&(*(conectados+indl)==0)&&(!perteneceIndiceQ(indl))){
		anadirIndice(indl);
	}
}

void calculaConectadosBorde(int hz){
	int ind;
	// Funcion que aplica el Metodo de Cluster para calcular que celdas estan conectadas al Borde via
	// primeros vecinos vacios
	// Renovamos todo el vector a cero salvo el borde inferior izquierda
	for(i=0;i<N;i++){
		conectadosBorde[i]=0;
	}
	//Anadimos la celda a conectadosBorde
	if(hz==0){//Piso abajo
		conectadosBorde[0]=1;
	}
	if(hz==1){//Piso arriba
		conectadosBorde[Lx*Ly]=1;
	}
	//Reinicio los indices
	longitudIndices=0;
	// Anado los 2 indices que son vecinos de la celda si estan vacios.
	// El vecino izquierdo y abajo no existe
	if(hz==0){//Piso abajo
		// Dos radios a la izquierda del Droplet comprobamos los 4 vecinos
		ind=DROPLET1-2*ceil(ultimoRadio);
		if(*(C+*(r+ind))==0){
			anadirIndice(*(r+ind));
		}
		if(*(C+*(u+ind))==0){
			anadirIndice(*(u+ind));
		}
		if(*(C+*(d+ind))==0){
			anadirIndice(*(d+ind));
		}
		if(*(C+*(l+ind))==0){
			anadirIndice(*(l+ind));
		}
	}
	if(hz==1){//Piso arriba
		ind=DROPLET2-2*ceil(ultimoRadio);
		if(*(C+*(r+ind))==0){
			anadirIndice(*(r+ind));
		}
		if(*(C+*(u+ind))==0){
			anadirIndice(*(u+ind));
		}
		if(*(C+*(d+ind))==0){
			anadirIndice(*(d+ind));
		}
		if(*(C+*(l+ind))==0){
			anadirIndice(*(l+ind));
		}
	}
	while(longitudIndices>0){//Mientras quedan indices
		ind=(int) longitudIndices*FRANDOM;//Elijo un indice al azar
		ind=*(indices+ind);
		conectadosBorde[ind]=1;//Lo anado a conectados
		//Anado los vecinos que esten llenos y no esten en conectados
		// ni en la lista de indices
		revisarVecinosConectadosBorde(ind);
		// Elimino este indice que ya ha sido anadido a conectados
		quitarIndice(ind);
	}
}

void revisarVecinosConectadosBorde(int ind){
	// Funcion necesaria para aplicar el metodo de Cluster. Revisa que vecinos
	// estan en conectados o en la lista de indices para actualizar esta ultima
	int indr,indd,indl,indu;
	double radioLim;
	radioLim=10.0+2.0*ultimoRadio;//Definicion del radio limite
	// Reviso los vecinos que estan en su mismo piso
	indr=*(r+ind);
	indd=*(d+ind);
	indu=*(u+ind);
	indl=*(l+ind);
	if((indr!=-1)&&(*(C+indr)==0)&&(*(conectadosBorde+indr)==0)&&(!perteneceIndiceQ(indr))&&(dentroCuadradoQ(indr,radioLim))){
		// Si puedo referenciarlo y
		// Esta vacio y
		// No esta en conectadosBorde y
		// No pertenece a la lista de Indices
		// Y esta dentro del cuadrado definido, entonces lo anado
		anadirIndice(indr);
	}
	if((indd!=-1)&&(*(C+indd)==0)&&(*(conectadosBorde+indd)==0)&&(!perteneceIndiceQ(indd))&&(dentroCuadradoQ(indd,radioLim))){
		anadirIndice(indd);
	}
	if((indu!=-1)&&(*(C+indu)==0)&&(*(conectadosBorde+indu)==0)&&(!perteneceIndiceQ(indu))&&(dentroCuadradoQ(indu,radioLim))){
		anadirIndice(indu);
	}
	if((indl!=-1)&&(*(C+indl)==0)&&(*(conectadosBorde+indl)==0)&&(!perteneceIndiceQ(indl))&&(dentroCuadradoQ(indl,radioLim))){
		anadirIndice(indl);
	}
}
/*
double mideDistanciaMedia(int hz){
	double distancia;
	int numPuntos,ind;
	distancia=0.0;
	numPuntos=0;
	//Recalculamos conectados y conectadosBorde
	calculaConectados(hz);
	calculaConectadosBorde(hz);
	// Recorremos los indices del piso dado
	for(ind=(hz*Lx*Ly);ind<((hz+1)*Lx*Ly);ind++){
		// Si el indice esta conectado al Droplet y tiene algun vecino conectado al Borde entonces
		// es de la frontera y mido sobre el.
		if(*(conectados+ind)==1){
			if(algunVecinoConectadoBorde(ind)){// Si tiene algun vecino conectado al borde es frontera
				numPuntos++;
				distancia+=distanciaEuclidea(ind,DROPLET1);
				// Da igual calcular la distancia con DROPLET1 o 2, ya que ambos tienen
				// las mismas coordenadas x e y.
			}
		}
	}
	distancia=distancia/numPuntos;
	if(hz==0){
		tamanhoFrontera0=numPuntos;
	}
	if(hz==1){
		tamanhoFrontera1=numPuntos;
	}
	return distancia;
}
*/
bool algunVecinoConectadoBorde(int h){
	// Funcion que nos dice si esta celda tiene algun vecino vacio conectado al borde
	int ind;
	ind=*(r+h);
	if((ind!=-1)&&(*(conectadosBorde+ind)==1)){
		// Si puedo referenciarlo y esta conectado devuelvo true;
		return true;
	}
	ind=*(l+h);
	if((ind!=-1)&&(*(conectadosBorde+ind)==1)){
		// Si puedo referenciarlo y esta conectado devuelvo true;
		return true;
	}
	ind=*(u+h);
	if((ind!=-1)&&(*(conectadosBorde+ind)==1)){
		// Si puedo referenciarlo y esta conectado devuelvo true;
		return true;
	}
	ind=*(d+h);
	if((ind!=-1)&&(*(conectadosBorde+ind)==1)){
		// Si puedo referenciarlo y esta conectado devuelvo true;
		return true;
	}
	return false;// En otro caso devuelvo false;
}

double calculaVarianza(double media,int hz){
	// Esta funcion calcula la varianza de las distancias que miden el tamanho de la membrana
	// Antes de llamar a esta funcion es necesario llamar a mideDistanciaMedia, ya que en 
	// esta ultima se actualiza el vector conectados que va a ser necesario aqui.
	// hz: 0 piso de abajo y 1 piso de arriba
	int numPuntos,ind;
	double acumulaCuadrados;
	acumulaCuadrados=0.0;
	numPuntos=0;
	// El proceso de calculo es el mismo que en el de mideDistanciaMedia
	for(ind=(hz*Lx*Ly);ind<((hz+1)*Lx*Ly);ind++){
		// Si el indice esta conectado al Droplet y tiene algun vecino conectado al Borde entonces
		// es de la frontera y mido sobre el.
		if(*(conectados+ind)==1){
			if(algunVecinoConectadoBorde(ind)){// Si tiene algun vecino conectado al borde es frontera
				numPuntos++;
				acumulaCuadrados+=pow(distanciaEuclidea(ind,DROPLET1)-media,2.0);
				// Da igual calcular la distancia con DROPLET1 o 2, ya que ambos tienen
				// las mismas coordenadas x e y.
			}
		}
	}
	acumulaCuadrados=acumulaCuadrados/numPuntos;
	return acumulaCuadrados;
}

double calculaFourierRe(int n,int hz){
	anchoFrente0=2*PI*med0;
	anchoFrente1=2*PI*med1;
	double fourier;
	double dista;
	int ind;
	int nn;//hace de n. n hace de k
	fourier=0.0;
	nn=0;
	if(hz==0){
		// Recorrer los puntos de la frontera.
		for(ind=0;ind<(Lx*Ly);ind++){
			// Si el indice esta conectado al Droplet y tiene algun vecino conectado al Borde entonces
			// es de la frontera y mido sobre el.
			if(*(conectados+ind)==1){
				if(algunVecinoConectadoBorde(ind)){// Si tiene algun vecino conectado al borde es frontera
					// Da igual calcular la distancia con DROPLET1 o 2, ya que ambos tienen
					// las mismas coordenadas x e y.
					dista=distanciaEuclidea(ind,DROPLET1);
					fourier+=(dista-med0)*cos(2.0*PI*n*nn/(1.0*tamanhoFrontera0));
					nn++;
				}
			}
		}
		fourier=fourier/sqrt(anchoFrente0);
	}
	if(hz==1){
		for(ind=(Lx*Ly);ind<(2*Lx*Ly);ind++){
			// Si el indice esta conectado al Droplet y tiene algun vecino conectado al Borde entonces
			// es de la frontera y mido sobre el.
			if(*(conectados+ind)==1){
				if(algunVecinoConectadoBorde(ind)){// Si tiene algun vecino conectado al borde es frontera
					// Da igual calcular la distancia con DROPLET1 o 2, ya que ambos tienen
					// las mismas coordenadas x e y.
					dista=distanciaEuclidea(ind,DROPLET2);
					fourier+=(dista-med1)*cos(2.0*PI*n*nn/(1.0*tamanhoFrontera1));
					nn++;
				}
			}
		}
		fourier=fourier/sqrt(anchoFrente1);
	}
	return fourier;
}

double calculaFourierIm(int n,int hz){
	anchoFrente0=2*PI*med0;
	anchoFrente1=2*PI*med1;
	double fourier;
	double dista;
	int ind;
	int nn;//hace de n. n hace de k
	fourier=0.0;
	nn=0;
	if(hz==0){
		// Recorrer los puntos de la frontera.
		for(ind=0;ind<(Lx*Ly);ind++){
			// Si el indice esta conectado al Droplet y tiene algun vecino conectado al Borde entonces
			// es de la frontera y mido sobre el.
			if(*(conectados+ind)==1){//Si esta lleno
				if(algunVecinoConectadoBorde(ind)){// Si tiene algun vecino conectado al borde es frontera
					// Da igual calcular la distancia con DROPLET1 o 2, ya que ambos tienen
					// las mismas coordenadas x e y.
					dista=distanciaEuclidea(ind,DROPLET1);
					fourier+=(dista-med0)*sin(2.0*PI*n*nn/(1.0*tamanhoFrontera0));
					nn++;
				}
			}
		}
		fourier=fourier/sqrt(anchoFrente0);
	}
	if(hz==1){
		for(ind=(Lx*Ly);ind<(2*Lx*Ly);ind++){
			// Si el indice esta conectado al Droplet y tiene algun vecino conectado al Borde entonces
			// es de la frontera y mido sobre el.
			if(*(conectados+ind)==1){
				if(algunVecinoConectadoBorde(ind)){// Si tiene algun vecino conectado al borde es frontera
					// Da igual calcular la distancia con DROPLET1 o 2, ya que ambos tienen
					// las mismas coordenadas x e y.
					dista=distanciaEuclidea(ind,DROPLET2);
					fourier+=(dista-med1)*sin(2.0*PI*n*nn/(1.0*tamanhoFrontera1));
					nn++;
				}
			}
		}
		fourier=fourier/sqrt(anchoFrente1);
	}
	return fourier;
}

int getZ(int ind){
	// Funcion que calcula la coordenada z de una celda dada. Empieza en 0
	return ind/(Lx*Ly);
}
int getY(int ind){
	// Funcion que calcula la coordenada y de una celda dada
	return (ind-(getZ(ind))*Lx*Ly)/Lx;
}
int getX(int ind){
	// Funcion que calcula la coordenada y de una celda dada
	return (ind-(getZ(ind))*Lx*Ly-(getY(ind))*Lx);
}

double getAngulo(int ind){
	//Calcula el angulo relativo al centro DROPLET
	int xrelativo,yrelativo;
	double cociente;
	xrelativo=getX(ind)-getX(DROPLET1);
	yrelativo=getY(ind)-getY(DROPLET1);
	if(yrelativo!=0){
		cociente=(1.0*yrelativo)/(1.0*xrelativo);
	}
	//printf("Get Angulo: xr:%d yr:%d coc:%lf\n",xrelativo,yrelativo,cociente);
	if(xrelativo>0&&yrelativo>=0){
		return atan(cociente);
	}else if(xrelativo==0&&yrelativo>0){
		return PI/2.0;
	}else if(xrelativo<0){
		return atan(cociente)+PI;
	}else if(xrelativo==0&&yrelativo<0){
		return 3.0*PI/2.0;
	}else if(xrelativo>0&&yrelativo<0){
		return atan(cociente)+2.0*PI;
	}
}

double getAngulo2(int ind){
	//Calcula el angulo relativo al centro DROPLET
	int xrelativo,yrelativo;
	double cociente;
	xrelativo=getX(ind)-getX(DROPLET1);
	yrelativo=getY(ind)-getY(DROPLET1);
	//printf("Get Angulo2: xr:%d yr:%d ang:%lf\n",xrelativo,yrelativo,atan2(yrelativo*1.0,xrelativo*1.0));
	return atan2(yrelativo,xrelativo);
}

double distanciaEuclidea(int ind1,int ind2){
	// Funcion que calcula la distancia euclidea entre dos puntos.
	// Se considera que estan en el mismo piso
	return sqrt(pow(1.0*(getX(ind1)-getX(ind2)),2.0)+pow(1.0*(getY(ind1)-getY(ind2)),2.0));
}

double distanciaX(int ind1,int ind2){
	// Funcion que calcula la distancia en la direccion x
	return abs(1.0*(getX(ind1)-getX(ind2)));
}

double distanciaY(int ind1,int ind2){
	// Funcion que calcula la distancia en la direccion y
	return abs(1.0*(getY(ind1)-getY(ind2)));
}

bool dentroCuadradoQ(int i1,double radio){
	int radioRedondeado;
	int linea, columna;
	int distColumna, distLinea;
	radioRedondeado=ceil(radio);//Redondeamos el radio dado hacia arriba
	linea=getY(i1);
	columna=getX(i1);
	distColumna=abs(columna-columnaDroplet);
	distLinea=abs(linea-lineaDroplet);
	if(distColumna>radioRedondeado){
		return false;
	}
	if(distLinea>radioRedondeado){
		return false;
	}
	return true;
}
