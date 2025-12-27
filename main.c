#include "parametros.h"

int main(int argc, char *argv[]) {
	
	switch(argc){
		case 2:
			fp=fopen(argv[1],"r");
			fgets(texto,200,fp);
			fscanf(fp,"%d\t%d\t%lf\t%lf\t%d\t%d\t%lld", &Lx, &Ly, &A, &T, &Nmed, &radio, &restart, &sem);
			fclose(fp);
			break;
		default:
			printf("Error en el programa: %s numero de argumentos incorrecto\n",argv[0]);
			exit(0);
	}
	
	reservaMemoria();
	vecinos();
	descripcion();// Escribe los parametros de la simulacion
	if(restart==0){
		// Condiciones iniciales de siempre
		semilla();
		condicionesIniciales();
		k=1;//Inicializamos el numerod de cambios
		porce=1;
		tiempoContinuo=0.0;//Inicializamos el tiempo
	}else{
		// Hay que leer la ultima configuracion
		cargaValores(sem);//carga los valores C de la configuracion
		k=0;//Damos otra vez Npasos
		porce=1;
		cargaTiempoContinuo(sem);//carga el valor del tiempo continuo
		recalculaSaltos();
		zseed=sem;//Para que abra bien los archivos de nuevo.
	}
	abreArchivosInicial();
	mideFrente(0);
	mideFrente(1);
	cierraArchivosInicial();
	abreArchivos();//Abre los archivos de datos de las salidas
	sacaFronteraDroplet();
	while(k<Npasos){//Npasos=Ncambios que realiza el Monte Carlo
		// NUCLEO DEL ALGORITMO EN TIEMPO CONTINUO
		acumProb=0.0;
		for(i=0;i<numeroDeSaltos;i++){
			acumProb+=*(probabilidad+i);//tasa de aceptacion A(mu->nu)
			probabilidadAcumulada[i]=acumProb;		
		}
		aleatorio=FRANDOM;
		for(i=0;i<numeroDeSaltos;i++){
			proba=*(probabilidadAcumulada+i)/acumProb;//Normalizo
			if(aleatorio<proba){
				//Hago el cambio con este indice
				indiceCambio1=*(*(saltos+i)+0);
				indiceCambio2=*(*(saltos+i)+1);
				//printf("Entrando en cambio\n");
				//printf("i1:%d,i2:%d\n",indiceCambio1,indiceCambio2);
				cambio(indiceCambio1,indiceCambio2);
				// Dentro de cambio se hacen los retoques a la lista
				borraUltimaColumna();// Borramos la ultima Columna.
				break;//Salgo del for por que ya me dan igual el resto de probabilidades
			}
		}
		//Actualizo el tiempo y el paso
		tiempoContinuo+=(-1.0)/(log((Np*1.0-acumProb)/(Np*1.0)));
		//tiempoContinuo+=1/acumProb;//Aproximacion de lo anterior. Igual de valido (Np>>>acumProb). Escala igual
		k++;
		// Para medir.
		
		if((k%Nmed)==0){
			mideFrente(0);
			//mideFourier(0);
			mideFrente(1);
			//mideFourier(1);
			//mideCorrelacion();
		}
		if(((k*10)%Npasos)==0){
			configuracion2(porce);
			porce++;
		}
		//escribeSaltos();
		
		//if(haySaltoRepetido()){
		//	exit(1);
		//}
		
	}
	
	cierraArchivos();
	zseed=sem;
	configuracion();// Saca la configuracion por si queremos hacer un restart del programa
	graficas();//Para hacer las graficas
	return 1;
}
