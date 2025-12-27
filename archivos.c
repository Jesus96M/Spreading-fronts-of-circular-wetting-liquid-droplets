#include "parametros.h"

void abreArchivos(){
	snprintf(nombre,sizeof(nombre),"Salida_0_%lld.dat",sem);
	fp1=fopen(nombre,"a");
	snprintf(nombre,sizeof(nombre),"Salida_1_%lld.dat",sem);
	fp2=fopen(nombre,"a");
	snprintf(nombre,sizeof(nombre),"NumeroPuntosFrontera_%lld.dat",sem);
	fp3=fopen(nombre,"a");

}

void cierraArchivos(){
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
}

void abreArchivosInicial(){
	/*
	snprintf(nombre,sizeof(nombre),"Salida_0_%lld_Inicial.dat",sem);
	fp1=fopen(nombre,"a");
	snprintf(nombre,sizeof(nombre),"Salida_1_%lld_Inicial.dat",sem);
	fp2=fopen(nombre,"a");
	snprintf(nombre,sizeof(nombre),"NumeroPuntosFrontera_%lld_Inicial.dat",sem);
	fp3=fopen(nombre,"a");
	*/
	// Todos con el mismo nombre (ya que son todos iguales)
	fp1=fopen("Salida_0_Inicial.dat","a");
	fp2=fopen("Salida_1_Inicial.dat","a");
	fp3=fopen("NumeroPuntosFrontera_Inicial.dat","a");
}

void cierraArchivosInicial(){
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
}

void mideFrente(int hz){
	//Medimos distancia media, varianza media y el numero de particulas en cada piso
	//calculaConectados(0);// Ya se le llama dentro de mideDistanciaMedia
	//printf("Midiendo Radio\n");
	int numPuntos,ind;
	double distancia,distanciaCom;
	distancia=0.0;
	numPuntos=0;
	//Recalculamos conectados y conectadosBorde
	calculaConectados(hz);
	calculaConectadosBorde(hz);
	if(hz==0){
		fprintf(fp1,"%lf\t%d",tiempoContinuo,numeroParticulas[0]);
		fflush(fp1);
	}
	if(hz==1){
		fprintf(fp2,"%lf\t%d",tiempoContinuo,numeroParticulas[1]);
		fflush(fp2);
	}
	// Recorremos los indices del piso dado
	for(ind=(hz*Lx*Ly);ind<((hz+1)*Lx*Ly);ind++){
		// Si el indice esta conectado al Droplet y tiene algun vecino conectado al Borde entonces
		// es de la frontera y mido sobre el.
		if(*(conectados+ind)==1){
			if(algunVecinoConectadoBorde(ind)){// Si tiene algun vecino conectado al borde es frontera
				//numPuntos++;
				// Da igual calcular la distancia con DROPLET1 o 2, ya que ambos tienen
				// las mismas coordenadas x e y.
				if(hz==0){
					distanciaCom=distanciaEuclidea(ind,DROPLET1);
					distancia+=distanciaCom;
					numPuntos++;
					fprintf(fp1,"\t%ld\t%ld\t%lf\t%lf",getX(ind),getY(ind),distanciaCom,getAngulo(ind));
					fflush(fp1);
				}
				if(hz==1){
					distanciaCom=distanciaEuclidea(ind,DROPLET1);
					numPuntos++;
					fprintf(fp2,"\t%ld\t%ld\t%lf\t%lf",getX(ind),getY(ind),distanciaCom,getAngulo(ind));
					fflush(fp2);
				}
			}
		}
	}
	if(hz==0){
		fprintf(fp1,"\n");
		fflush(fp1);
		med0=distancia/numPuntos;
		if(!isnan(med0)){
			ultimoRadio=med0;
		}
		fprintf(fp3,"%d\t",numPuntos);
		fflush(fp3);
	}
	if(hz==1){
		fprintf(fp2,"\n");
		fflush(fp2);
		fprintf(fp3,"%d\n",numPuntos);
		fflush(fp3);
	}
}

// Funciones antiguas. Sin uso ahora

/*
void mideFourier(int hz){
	//Calcula la transformada de Fourier discreta del frente y la escribe
	// t |chi_1|^2 ... |chi_k|^2
	// LLamar inmediatamente despues de medir lo otro o recalcular conectados cada vez que se vaya a calcular
	// ya que si no los valores de las h0 y h1 no estan actualizados.
	// Piso 0
	int n,lim;
	if(hz==0){
		fprintf(fp2,"%lf\t",tiempoContinuo);
		fflush(fp2);
		lim=(tamanhoFrontera0+1)/2;
		for(n=0;n<lim;n++){
			fprintf(fp2,"%lf\t",(pow(calculaFourierRe(n,0),2.0)+pow(calculaFourierIm(n,0),2.0)));
			fflush(fp2);
		}
		fprintf(fp2,"\n");
		fflush(fp2);
	}
	// Piso 1
	if(hz==1){
		fprintf(fp3,"%lf\t",tiempoContinuo);
		fflush(fp3);
		lim=(tamanhoFrontera1+1)/2;
		for(n=0;n<lim;n++){
			fprintf(fp3,"%lf\t",(pow(calculaFourierRe(n,1),2.0)+pow(calculaFourierIm(n,1),2.0)));
			fflush(fp3);
		}
		fprintf(fp3,"\n");
		fflush(fp3);
	}
}
*/
/*
void mideCorrelacion(){
	// t	r=1	C_1(piso1)  C_2(piso1)  C_1(piso2)  C_2(piso2)
	// LLamar inmediatamente despues de medir lo otro o recalcular conectados cada vez que se vaya a calcular
	// ya que si no los valores de las h0 y h1 no estan actualizados.
	// Calculo de la fucion de correlacion C1
	double acum1,acum2,acum3,acum4;
	int lim;
	lim=Ly/2+1;
	for(rr=0;rr<lim;rr++){
		fprintf(fp4,"%lf\t%d\t",tiempoContinuo,rr);
		fflush(fp4);
		acum1=0.0;
		acum2=0.0;
		acum3=0.0;
		acum4=0.0;
		for(yy=0;yy<Ly;yy++){
			yc=(rr+yy)%Ly;//r+y
			acum1+=(*(h0+yc))*(*(h0+yy));
			acum2+=pow(((*(h0+yc))-(*(h0+yy))),2.0);
			acum3+=(*(h1+yc))*(*(h1+yy));
			acum4+=pow(((*(h0+yc))-(*(h0+yy))),2.0);
		}
		acum1=acum1/Ly;
		acum2=acum2/Ly;
		acum3=acum3/Ly;
		acum4=acum4/Ly;
		fprintf(fp4,"%lf\t%lf\t%lf\t%lf\n",acum1,acum2,acum3,acum4);
		fflush(fp4);
	}
}
*/
