#include "parametros.h"

void reservaMemoria(){
	saltos=malloc(Np*sizeof(long*));// Reservo Np saltos. Indice 1
	for(i=0;i<Np;i++){
		saltos[i]=malloc(2*sizeof(long));// De 2 cada uno. Indice 2
	}
	
	C=malloc(N*sizeof(int));
	r=malloc(N*sizeof(int));
	l=malloc(N*sizeof(int));
	u=malloc(N*sizeof(int));
	d=malloc(N*sizeof(int));
	ver=malloc(N*sizeof(int));
	probabilidad=malloc(Np*sizeof(double));
	probabilidadAcumulada=malloc(Np*sizeof(double));
	conectados=malloc(N*sizeof(int));
	conectadosBorde=malloc(N*sizeof(int));
	indices=malloc(N*sizeof(int));
	h0=malloc(Ly*sizeof(double));
	h1=malloc(Ly*sizeof(double));
	
}

void vecinos(){
	// Funcion que define los vecinos. CC PERIODICAS
	int ind;
	for(ind=0;ind<N;ind++){
		r[ind]=ind+1;
		l[ind]=ind-1;
		u[ind]=ind+Lx;
		d[ind]=ind-Lx;
		ver[ind]=ind+Lx*Ly;
	}
	// Retocamos la vertical. Solo la del piso de arriba.
	for(ind=Lx*Ly;ind<N;ind++){
		ver[ind]=ind-Lx*Ly;
	}
	// Ponemos a -1 aquellos vecinos que no existan. En este caso TODOS los bordes
	// Retocamos los de abajo y los de arriba:
	for(ind=0;ind<Lx;ind++){
		d[ind]=-1;//Fila de abajo Piso 1.
		d[ind+Lx*Ly]=-1;//Fila de abajo Piso 2.
		u[ind+(Ly-1)*Lx]=-1;//Fila de arriba. Piso 1
		u[ind+(Ly-1)*Lx+Lx*Ly]=-1;//Fila de arriba. Piso 2
	}
	// Retocamos los de la izquierda y la derecha:
	// Estos los sigo poniendo a -1
	for(ind=0;ind<Ly;ind++){
		l[ind*Lx]=-1;//Columna de la izquierda. Piso 1.
		l[ind*Lx+Lx*Ly]=-1;//Columna de la izquierda. Piso 2.
		r[(ind+1)*Lx-1]=-1;//Columna de la derecha. Piso 1
		r[(ind+1)*Lx-1+Lx*Ly]=-1;//Columna de la derecha. Piso 2
	}
}

void condicionesIniciales(){
	// Funcion que pone las condiciones iniciales
	// Todo a cero salvo el Droplet Reservoir que se pone a 1
	int ind;
	numeroParticulas[0]=0;
	numeroParticulas[1]=0;
	for(ind=0;ind<N;ind++){
		C[ind]=0;
		conectados[ind]=0;
		if(perteneceDropletQ(ind)){
			C[ind]=1;
			conectados[ind]=1;
			numeroParticulas[getZ(ind)]++;
		}
	}
	// Anadimos los saltos correspondientes
	numeroDeSaltos=0;//suficiente para reiniciar los valores de los saltos
	for(ind=0;ind<N;ind++){
		if(C[ind]==1){
			if(C[r[ind]]==0){
				anadirSalto(ind,r[ind]);
			}
			if(C[l[ind]]==0){
				anadirSalto(ind,l[ind]);
			}
			if(C[d[ind]]==0){
				anadirSalto(ind,d[ind]);
			}
			if(C[u[ind]]==0){
				anadirSalto(ind,u[ind]);
			}
			// El vertical no es necesario revisarlo inicialmente (llenos con llenos y vacios con vacios)
		}
	}
	//ultimoRadio=1.0;
	ultimoRadio=radio+10.0;// Para evitar problemas en la primera medida
	lineaDroplet=getY(DROPLET1);
	columnaDroplet=getX(DROPLET1);
}

void cargaValores(randint semilla){
	snprintf(nombre,sizeof(nombre),"Configuracion_%lld.dat",semilla);
	fp=fopen(nombre,"r");
	for(i=0;i<N;i++){
		fscanf(fp,"%d\n",&C[i]);
	}
	fclose(fp);
	// Calculo del numero de particulas en cada capa
	numeroParticulas[0]=0;
	numeroParticulas[1]=0;
	for(i=0;i<(Lx*Ly);i++){
		numeroParticulas[0]+=C[i];
	}
	for(i=(Lx*Ly);i<N;i++){
		numeroParticulas[1]+=C[i];
	}
	// Ponemos conectados a 1 en el Droplet
	conectados[DROPLET1]=1;
	conectados[DROPLET2]=1;
}

void cargaTiempoContinuo(randint semilla){
	int ch=0;
	snprintf(nombre,sizeof(nombre),"Salida_%lld.dat",semilla);
	fp=fopen(nombre,"r");
	while((ch=fgetc(fp))!=EOF){// Lee hasta que se acabe el archivo
		fscanf(fp,"%lf\t%lf\t%lf\t%d\t%lf\t%lf\t%d",&com0,&com1,&com2,&como1,&com3,&com4,&como2);
	}
	tiempoContinuo=com0;
	fclose(fp);
}

void recalculaSaltos(){
	int ind;
	longitudIndices=0;
	for(i=0;i<N;i++){
		if(*(C+i)==1){// Si la celda esta llena
			ind=*(r+i);
			if((ind!=-1)&&(*(C+ind)==0)){// Si puedo referenciarlo y esta vacio
				anadirSalto(i,ind);
			}
			ind=*(l+i);
			if((ind!=-1)&&(*(C+ind)==0)){// Si puedo referenciarlo y esta vacio
				anadirSalto(i,ind);
			}
			ind=*(u+i);
			if((ind!=-1)&&(*(C+ind)==0)){// Si puedo referenciarlo y esta vacio
				anadirSalto(i,ind);
			}
			ind=*(d+i);
			if((ind!=-1)&&(*(C+ind)==0)){// Si puedo referenciarlo y esta vacio
				anadirSalto(i,ind);
			}
			ind=*(ver+i);
			if(*(C+ind)==0){// Si esta vacio
				anadirSalto(i,ind);
			}
		}
	}
}
