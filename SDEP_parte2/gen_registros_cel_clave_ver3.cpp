//Programa para crear registros de votos [celular, CURP, partido, separador], con el campo "celular" como clave 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream> 
#include <iterator> 
#include "registro.h"
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <cstdlib>      // std::rand, std::srand


using namespace std; 



int main(int argc, char *argv[]){
	char telefono[11], curp[19], t[11], sexo;
	int i, n, destino, j, opcion, inicial, elemento;
	struct registro reg1;
	int fd_archivo;
    vector<struct registro> registros_vector; 

	//Partidos disponibles 2018
	char const partidos[9][5] = {"PRI\n", "PAN\n", "PRD\n", "P_T\n", "VDE\n", "MVC\n", "MOR\n", "PES\n", "PNL\n"};

	//Entidades federativas
	char const entidad[32][3] =  {"AS", "BC", "BS", "CC", "CS", "CH", "CL", "CM", "DF", "DG", "GT", "GR", "HG", "JC", "MC", "MN", "MS", "NT", "NL", "OC", "PL", "QT", "QR", "SP", "SL", "SR", "TC", "TL", "TS", "VZ", "YN", "ZS"};

	if(argc != 3){
		printf("Forma de uso: programa numero_registros nombre_archivo_de_salida\n");
		exit(0);
	}

	//Numero de registros n
	n = atoi(argv[1]);

	//Genera un numeros telefonicos inicial de 9 digitos y despues se obtendran su secuenciales para evitar repeticion
	inicial = 500000000 + rand()%100000000;

	//Crea todos los registros con numero de telefono consecutivo y los almacena en un vector
	for(j=0; j<n; j++){
		sprintf(telefono, "5%9d", inicial);
		inicial++;
		strcpy(reg1.celular, telefono);
		if(rand()%2 == 0)
			sexo = 77;
		else
			sexo = 72;

		i = rand()%32;
		sprintf(curp, "%c%c%c%c%c%c%c%c%c%c%c%s%c%c%c%c%c", 65 + rand()%25 , 65 + rand()%25, 65 + rand()%25, 65 + rand()%25, rand()%10 + 48, rand()%10 + 48, rand()%10 + 48, rand()%10 + 48, rand()%10 + 48, rand()%10 + 48, 
			sexo, entidad[i], 65 + rand()%25, 65 + rand()%25, 65 + rand()%25, rand()%10 + 48, rand()%10 + 48);
		strcpy(reg1.CURP, curp);
		i = rand()%9;
		strcpy(reg1.partido, partidos[i]);
		registros_vector.push_back(reg1);
	}

	//Aleatoriza el vector de registros e imprime el resultado
	random_shuffle(registros_vector.begin(), registros_vector.end());
	
	if((fd_archivo=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0666))==-1)
	{
		perror(argv[2]);
		exit(-1);
	}
	char buffer[BUFSIZ];
	for (std::vector<struct registro>::iterator it=registros_vector.begin(); it!=registros_vector.end(); ++it){
		reg1 = *it;
		write(fd_archivo, &reg1, sizeof(reg1));
		
	}
	close(fd_archivo);
	/* para leer y ver en pantallae l archivo 
	fd_archivo=open("holi",O_RDONLY);
	int nbytes;
	while ((nbytes=read(fd_archivo, &reg1, sizeof(reg1)))>0){
		write(1,&reg1,nbytes);
	}
	close(fd_archivo);*/
	
	
}
