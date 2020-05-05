#include <stdlib.h>
#include <iostream>
#include <time.h> 
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include <sys/time.h>
#include "SocketDatagrama.h"
#include "PaqueteDatagrama1.h"
#include "registro.h"
#include "mensaje.h"


using namespace  std;

int main (int argc, char*argv[]){
 
  SocketDatagrama cliente(0);
  PaqueteDatagrama1 p_res(sizeof(int));
  vector<struct registro>registros;
  vector<struct registro>::iterator it;
  int puerto = 7500;
  int fd_archivo;
  //int n_envios = atoi(argv[2]);
  mensaje mjs;
  registro reg_aux;
 
 if(argc!=3){
        cout<<"Modo de uso: ./cliente ip numero_registros_enviar \n";
      
        exit(0);
  }
  if((fd_archivo=open("70000registros",O_RDONLY))==-1){
    perror(argv[2]);
    exit(0);
  }
  int id_envio=1;
  int acr,flag;
  int prueba=0;
  while((flag =  read(fd_archivo, &reg_aux, sizeof(reg_aux)))>0){
    
    registros.push_back(reg_aux);
  }
  it = registros.begin();
  memcpy(mjs.arguments,(char *)&*it,sizeof(reg_aux));
  mjs.requestId = id_envio;

  int nveces = atoi(argv[2]);
  int x=1;
  for(it=registros.begin()+1;x<nveces;it++,x++){

  PaqueteDatagrama1  p((char *)&mjs, sizeof(mjs),argv[1],puerto);
   for(;;){

    cliente.envia(p);
    PaqueteDatagrama1  p_recibido (sizeof(mjs));
    acr = cliente.SetDatagramTimeout(p_recibido,5,0);
      if(acr!=-1){
        memcpy(&mjs,p_recibido.getData(),p_recibido.getLen());
          
        if(id_envio>=mjs.requestId){
          id_envio++;
          //read(fd_archivo, &reg_aux, sizeof(reg_aux));
          memcpy(&mjs.arguments,&*it,sizeof(reg_aux));
          mjs.requestId=id_envio;  
          break;
        }
        
      }
      else{
        cout<<"servidor no respondio "<<endl;
      }
    
   }
  
    
  }
  vector<struct registro>::reverse_iterator r_it;
  r_it=registros.rbegin();
  memcpy(&mjs.arguments,&*r_it,sizeof(reg_aux));
  id_envio++;
  mjs.requestId= id_envio;
  PaqueteDatagrama1 ultimo((char*)&mjs,sizeof(mjs),argv[1],puerto);
  cliente.envia(ultimo);
  mjs.requestId=-1;
  PaqueteDatagrama1 fin((char*)&mjs,sizeof(mjs),argv[1],puerto);
  cliente.envia(fin);
  close(fd_archivo);

return 0;
}

