#include "parametros.h"
void graficas(){
	int ind;
	// Funcion que genera los archivos necesarios para hacer las graficas del frente
	snprintf(nombre,sizeof(nombre),"Configuracion_%lld.dat",sem);
	FILE *datos1=fopen(nombre,"w");
	for(i=0;i<N;i++){
		// Pinta las capas
		fprintf(datos1,"%d\n",*(C+i));
	}
	fclose(datos1);
	calculaConectados(0);
	calculaConectadosBorde(0);
	datos1=fopen("Conectados0.dat","w");
	for(ind=0;ind<(Lx*Ly);ind++){
		if(*(conectados+ind)==1){
			fprintf(datos1,"%lf\t%lf\n",getX(ind)+0.5,getY(ind)+0.5);
			if(*(C+ind)==0){
				printf("Indice vacio y conectado: %d\n",ind);
			}
		}
	}
	fclose(datos1);
	datos1=fopen("ConectadosBorde0.dat","w");
	for(ind=0;ind<(Lx*Ly);ind++){
		if(*(conectadosBorde+ind)==1){
			fprintf(datos1,"%lf\t%lf\n",getX(ind)+0.5,getY(ind)+0.5);
		}
	}
	datos1=fopen("Frontera1.dat","w");//Frontera abajo
	for(ind=0;ind<(Lx*Ly);ind++){
		// Si el indice esta conectado al Droplet y tiene algun vecino conectado al Borde entonces
		// es de la frontera
		if(*(conectados+ind)==1){
			if((*(r+ind)!=-1)&&(*(conectadosBorde+*(r+ind))==1)){
				fprintf(datos1,"%d\t%d\n",getX(ind)+1,getY(ind)+1);
				fprintf(datos1,"%d\t%d\n",getX(ind)+1,getY(ind));
			}
			if((*(l+ind)!=-1)&&(*(conectadosBorde+*(l+ind))==1)){
				fprintf(datos1,"%d\t%d\n",getX(ind),getY(ind));
				fprintf(datos1,"%d\t%d\n",getX(ind),getY(ind)+1);
			}
			if((*(u+ind)!=-1)&&(*(conectadosBorde+*(u+ind))==1)){
				fprintf(datos1,"%d\t%d\n",getX(ind)+1,getY(ind)+1);
				fprintf(datos1,"%d\t%d\n",getX(ind),getY(ind)+1);
			}
			if((*(d+ind)!=-1)&&(*(conectadosBorde+*(d+ind))==1)){
				fprintf(datos1,"%d\t%d\n",getX(ind),getY(ind));
				fprintf(datos1,"%d\t%d\n",getX(ind)+1,getY(ind));
			}
		}
	
	}
	fclose(datos1);
	calculaConectados(1);
	calculaConectadosBorde(1);
	datos1=fopen("Conectados1.dat","w");
	for(ind=(Lx*Ly);ind<(2*Lx*Ly);ind++){
		if(*(conectados+ind)==1){
			fprintf(datos1,"%lf\t%lf\n",getX(ind)+0.5,getY(ind)+0.5);
			if(*(C+ind)==0){
				printf("Indice vacio y conectado: %d\n",ind);
			}
		}
	}
	fclose(datos1);
	datos1=fopen("ConectadosBorde1.dat","w");
	for(ind=(Lx*Ly);ind<(2*Lx*Ly);ind++){
		if(*(conectadosBorde+ind)==1){
			fprintf(datos1,"%lf\t%lf\n",getX(ind)+0.5,getY(ind)+0.5);
		}
	}
	fclose(datos1);
	datos1=fopen("Frontera2.dat","w");//Frontera arriba
	for(ind=(Lx*Ly);ind<(2*Lx*Ly);ind++){
		// Si el indice esta conectado al Droplet y tiene algun vecino conectado al Borde entonces
		// es de la frontera
		if(*(conectados+ind)==1){
			if((*(r+ind)!=-1)&&(*(conectadosBorde+*(r+ind))==1)){
				fprintf(datos1,"%d\t%d\n",getX(ind)+1,getY(ind)+1);
				fprintf(datos1,"%d\t%d\n",getX(ind)+1,getY(ind));
			}
			if((*(l+ind)!=-1)&&(*(conectadosBorde+*(l+ind))==1)){
				fprintf(datos1,"%d\t%d\n",getX(ind),getY(ind));
				fprintf(datos1,"%d\t%d\n",getX(ind),getY(ind)+1);
			}
			if((*(u+ind)!=-1)&&(*(conectadosBorde+*(u+ind))==1)){
				fprintf(datos1,"%d\t%d\n",getX(ind)+1,getY(ind)+1);
				fprintf(datos1,"%d\t%d\n",getX(ind),getY(ind)+1);
			}
			if((*(d+ind)!=-1)&&(*(conectadosBorde+*(d+ind))==1)){
				fprintf(datos1,"%d\t%d\n",getX(ind),getY(ind));
				fprintf(datos1,"%d\t%d\n",getX(ind)+1,getY(ind));

			}
		}
	}
	fclose(datos1);
}

void configuracion(){
	// Funcion que genera el archivo con la configuracion para hacer un restart
	snprintf(nombre,sizeof(nombre),"Configuracion_%lld.dat",sem);
	FILE *datos1=fopen(nombre,"w");
	for(i=0;i<N;i++){
		// Pinta las capas
		fprintf(datos1,"%d\n",*(C+i));
	}
	fclose(datos1);
}

void configuracion2(int porcent){
	// Funcion que genera el archivo con la configuracion para hacer un restart
	snprintf(nombre,sizeof(nombre),"Configuracion_%d_%lld.dat",porcent,sem);
	FILE *datos1=fopen(nombre,"w");
	for(i=0;i<N;i++){
		// Pinta las capas
		fprintf(datos1,"%d\n",*(C+i));
	}
	fclose(datos1);
}

void sacaFronteraDroplet(){
	int ind;
	snprintf(nombre,sizeof(nombre),"Frontera_DROPLET.dat");
	FILE *datos1=fopen(nombre,"w");
	calculaConectados(0);
	calculaConectadosBorde(0);
	for(ind=0;ind<(Lx*Ly);ind++){
		// Si el indice esta conectado al Droplet y tiene algun vecino conectado al Borde entonces
		// es de la frontera
		if(*(conectados+ind)==1){
			if((*(r+ind)!=-1)&&(*(conectadosBorde+*(r+ind))==1)){
				fprintf(datos1,"%d\t%d\n",getX(ind)+1,getY(ind)+1);
				fprintf(datos1,"%d\t%d\n",getX(ind)+1,getY(ind));
			}
			if((*(l+ind)!=-1)&&(*(conectadosBorde+*(l+ind))==1)){
				fprintf(datos1,"%d\t%d\n",getX(ind),getY(ind));
				fprintf(datos1,"%d\t%d\n",getX(ind),getY(ind)+1);
			}
			if((*(u+ind)!=-1)&&(*(conectadosBorde+*(u+ind))==1)){
				fprintf(datos1,"%d\t%d\n",getX(ind)+1,getY(ind)+1);
				fprintf(datos1,"%d\t%d\n",getX(ind),getY(ind)+1);
			}
			if((*(d+ind)!=-1)&&(*(conectadosBorde+*(d+ind))==1)){
				fprintf(datos1,"%d\t%d\n",getX(ind),getY(ind));
				fprintf(datos1,"%d\t%d\n",getX(ind)+1,getY(ind));
			}
		}
	
	}
	fclose(datos1);
}

void descripcion(){
	// Funcion que genera un archivo txt donde se escriben las caracteristicas de la simulacion
	FILE *datos1=fopen("descripcion.txt","w");
	fprintf(datos1,"Simulación hecha para el Monte Carlo en tiempo continuo que calcula\n");
	fprintf(datos1,"y va actualizando la lista de transciones posibles del sistema.\n");
	fprintf(datos1,"El sistema tiene geometría circular.\n");
	fprintf(datos1,"Los parámetros utilizados son:\n");
	fprintf(datos1,"T=%lf,A=%lf,Lx=%d,Ly=%d,radio=%d\n",T,A,Lx,Ly,radio);
	fprintf(datos1,"Npasos=%ld, Nmed=%d\n",Npasos,Nmed);
	fclose(datos1);
}
