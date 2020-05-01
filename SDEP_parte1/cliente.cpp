#include <stdlib.h>
#include <iostream>
#include <time.h> 
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include "SocketDatagrama.h"
#include "PaqueteDatagrama1.h"
#include "registro.h"


using namespace  std;

int main (int argc, char*argv[]){
  if(argc!=3){
        cout<<"Modo de uso: ./cliente ip nombre_archivo_datos\n";
        exit(0);
  }
  SocketDatagrama cliente(0);
  vector<struct registro>registros;
  int puerto = 7500;
  int fd_archivo,buffer;
  registro reg_aux;
  if((fd_archivo=open(argv[2],O_RDONLY))==-1){
    perror(argv[2]);
    exit(0);
  }
  int prueba=0;
 read(fd_archivo, &reg_aux, sizeof(reg_aux));
    PaqueteDatagrama1  p((char *)&reg_aux, sizeof(reg_aux),argv[1],puerto);
    cliente.envia(p);
close(fd_archivo);

return 0;
}

