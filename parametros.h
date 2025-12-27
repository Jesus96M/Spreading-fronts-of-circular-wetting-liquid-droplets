#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>
//////////////////////////////////////////////////////////
//////// DEFINICIONES PARA GENERACION N ALEATORIO ////////
//////////////////////////////////////////////////////////
typedef unsigned long long randint;
// typedef double randreal;
#define TWOBRMINUS1   18446744073709551615ULL //2^64 - 1
#define TWOBR         18446744073709551616.   //2^64
#define TWOBRM1       9223372036854775808ULL  //2^63
#define FNORM (5.4210108624275218e-20)// max double such that RAND_MAX*NORMF<1
#define CGRANDOM  ( zseed=zseed*3202034522624059733LLU+1)
#define PRRANDOM  ( (ira[ip++]=ira[ip1++]+ira[ip2++]) ^ira[ip3++] )
// #define MYRANDOM   PRRANDOM                         // P-R generator
#define MYRANDOM   CGRANDOM                       // Congruential generator
#define HIRANDOM  ((randint) (PRRANDOM + CGRANDOM)) //Addition of both
#define FRANDOM (FNORM*MYRANDOM)   //A floating point, 0<=pseudo-random<1
#define CGFRANDOM (FNORM*CGRANDOM)   //A floating point, 0<=pseudo-random<1
#define FHIRANDOM (FNORM*HIRANDOM) //A floating point, 0<=pseudo-random<1
randint zseed;
//////////////////////////////////////////////////////////

#define N Lx*Ly*2 //Numero de celdas total
//#define Nmed (Lx*Ly*10)// Cada cuantos pasos mido.
#define Npasos (Nmed*(5000UL)) // Numero de pasos que da la cadena SI ES LONG
//#define Npasos (Lx*Ly*25000) // Numero de pasos que da la cadena
#define beta 1.0/T
#define Np (5*Lx*Ly-2*Ly-2*Lx)//Numero de parejas que se pueden proponer para saltos
#define PI 3.14159265358979323846// PI
#define DROPLET1 (Lx*(Ly-1)/2+(Lx-1)/2) //Celda del droplet abajo
#define DROPLET2 (Lx*(Ly-1)/2+(Lx-1)/2+Lx*Ly) // Celda del droplet arriba

// VARIABLES GLOBALES
// VARIABLES QUE SE LEEN DE ARCHIVO DE ENTRADA
int Lx, Ly;// Dimensiones del sistema Crece en la direccion x
int restart;// 0 desde el principio. 1 lee un archivo externo
double T, A;// Temperatura y constante de Hamaker
int Nmed;// Cada cuanto mido
int radio;//radio del Droplet inicial
// PUNTEROS PARA LOS QUE HAY QUE RESERVAR MEMORIA
int* C;// valores de las celdas 0=vacio 1=llena
int* r;//vecino derecho
int* l;//vecino izquierdo
int* u;//vecino arriba
int* d;//vecino abajo
int* ver;//vecino vertical
long** saltos;//lista de transiciones del sistema (indices)
double* probabilidad;//tasa de aceptacion (A(mu->nu)) de cada salto
double* probabilidadAcumulada;// acumulado del valor de arriba
int* conectados;// conectado a Droplet 0=no 1=si
int* conectadosBorde;// conectado a Borde 0=no 1=si
int* indices;//lista de indices necesaria en el metodo de cluster
double* h0;// h(y,t) planta 0
double* h1;// h(y,t) planta 1
// VARIABLES LONGITUD DE LISTA (RESERVAMOS MEMORIA POR EXCESO) PARA indices y listaDeSaltos
int numeroDeSaltos;
int longitudIndices;
// VARIABLES PARA LA PARTE CENTRAL DEL ALGORITMO
long k;//paso del MC
double tiempoContinuo;//tiempo de la simulacion
double acumProb;// acumulado de las probabilidades
int indiceCambio1;// Indice de la celda que hace 1->0
int indiceCambio2;// Indice de la celda que hace 0->1
double ultimoRadio;
int columnaDroplet;
int lineaDroplet;
// UTILES VARIOS COMODINES
int i,j,kk; // indices
int x,y,z; // mas indices
double aleatorio;//Numero aletorio
char nombre[50];//Nombre del archivo donde vamos a escribir los datos. Llevara en el nombre la semilla para evitar que nos pise el archivo cada vez
double proba;//variable comodin para evitar acceder dos veces al mismo array
double med0;//media de la distancia Piso 0. Para no promediar 2 veces
double med1;//media de la distancia Piso 1. Para no promediar 2 veces
double anchoFrente0;// L=2PiTheta
double anchoFrente1;
int tamanhoFrontera0;//numero de puntos que componen la frontera de la precursora.
int tamanhoFrontera1;
int kf,rr,yy,yc;// mas indices
int numeroParticulas[2];// numero de particulas en z=0 y z=1
randint sem;//Semilla leida
FILE *fp;//archivo para leer condiciones.dat
char texto[200];//comodin para leer la primera linea
double com0,com1,com2,com3,com4;//comodines necesarios para leer el tiempo continuo
int como1,como2;//comodines necesarios para leer el tiempo continuo
int porce;//Para ir sacando las configuraciones
// Archivos de salida del sistema
FILE *fp1;
FILE *fp2;
FILE *fp3;
FILE *fp4;
FILE *fp5;
FILE *fp6;
FILE *fp7;


// Declaracion de las funciones
void anadirSalto(int i1,int i2);
void quitarSalto(int i1,int i2);
void comprobacionAB(int);
void comprobacionCD(int);
void recalculaProbabilidades(int h1, int h2);
bool valorRepetido();
bool algunVecinoVacioQ(int h);
void semilla();
void vecinos();
void condicionesIniciales();
int eleccionVecinoVacio(int h);
int fuerza(int h);
int piso(int h);
bool perteneceDropletQ(int h);
//bool perteneceQ(int h);
void anadirIndice(int nuevo);
void quitarIndice(int eliminar);
bool perteneceIndiceQ(int h);
void revisarVecinos(int ind);
double tamanhoMembranaMedia(int hz);
int distanciaMembrana(int hz,int hy);
bool salirBucleQ();
void comprobacionVecinosNuevo(int h2);
void comprobacionVecinosAntiguo(int h1);
void cambio(int h1,int h2);
void borraUltimaColumna();
double mideDistanciaMedia(int hz);
double calculaVarianza(double media,int hz);
void graficas();
void calculaVecinosVacios(int h, int nV);
int numeroVecinosVacios(int h);
double calculaProbabilidad(int i1,int i2);
void descripcion();
void configuracion();
void calculaConectados(int hz);
double calculaFourierRe(int kf,int piso);
double calculaFourierIm(int kf,int piso);
void abreArchivos();
void cierraArchivos();
int getZ(int ind);
int getY(int ind);
int getX(int ind);
double getAngulo(int ind);
double getAngulo2(int ind);
void mideFrente();
void mideFourier();
void mideCorrelacion();
void reservaMemoria();
bool haySaltoRepetido();
void escribeSaltos();
void cargaValores(randint semilla);
void cargaTiempoContinuo();
void recalculaSaltos();
void calculaConectadosBorde(int hz);
void revisarVecinosConectadosBorde(int ind);
bool algunVecinoConectadoBorde(int ind);
double distanciaEuclidea(int ind1,int ind2);
double distanciaX(int ind1,int ind2);
double distanciaY(int ind1,int ind2);
bool dentroCuadradoQ(int i1,double radio);
void sacaFronteraDroplet();
void configuracion2(int pasosDados);
void abreArchivosInicial();
void cierraArchivosInicial();
