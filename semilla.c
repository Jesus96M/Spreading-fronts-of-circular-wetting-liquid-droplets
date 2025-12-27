#include "parametros.h"
void semilla(void){
	// Copiado del generador que me dio Juanjo
	FILE* Frandfile;
	zseed=0;
	Frandfile = fopen("/dev/urandom","r");
	fread(&zseed,8,1,Frandfile);
	zseed=(unsigned long long) abs(zseed);
	fclose(Frandfile);
	sem=zseed;
}
