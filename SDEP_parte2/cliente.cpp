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
#include "mensaje.h"


using namespace  std;

int main (int argc, char*argv[]){
  if(argc!=3){
        cout<<"Modo de uso: ./cliente ip numero_registros_a_enviar \n";
        exit(0);
  }
  SocketDatagrama cliente(0);
  PaqueteDatagrama1 p_res(sizeof(int));
  vector<struct registro>registros;
  int puerto = 7500;
  int fd_archivo;
  int n_envios = atoi(argv[2]);
  mensaje mjs;
  registro reg_aux;
  if((fd_archivo=open("7000registros",O_RDONLY))==-1){
    perror(argv[2]);
    exit(0);
  }
  int id_envio=1;
  int acr;
  read(fd_archivo, &reg_aux, sizeof(reg_aux));
  memcpy(mjs.arguments,(char *)&reg_aux,sizeof(reg_aux));
  mjs.requestId = id_envio;
  for(int x = 1;x<=n_envios;x++){

  PaqueteDatagrama1  p((char *)&mjs, sizeof(mjs),argv[1],puerto);
   for(;;){

    cliente.envia(p);
    PaqueteDatagrama1  p_recibido (sizeof(mjs));
    acr = cliente.SetDatagramTimeout(p_recibido,3,0);
      if(acr!=-1){
        memcpy(&mjs,p_recibido.getData(),p_recibido.getLen());
          
        if(id_envio>mjs.requestId){
          id_envio++;
          read(fd_archivo, &reg_aux, sizeof(reg_aux));
          memcpy(&mjs.arguments,&reg_aux,sizeof(reg_aux));
          mjs.requestId=id_envio;  
          break;
        }
        
      }
      else{
        cout<<"servidor no respondio "<<endl;
      }
    
   }
  
    
  }
  mjs.requestId=-1;
  PaqueteDatagrama1 fin((char*)&mjs,sizeof(mjs),argv[1],puerto);
  cliente.envia(fin);
  close(fd_archivo);

return 0;
}

