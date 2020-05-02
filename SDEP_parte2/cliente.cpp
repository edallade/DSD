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
        cout<<"Modo de uso: ./cliente ip nombre_archivo_enviar \n";
        exit(0);
  }
  SocketDatagrama cliente(0);
  PaqueteDatagrama1 p_res(sizeof(int));
  vector<struct registro>registros;
  vector<struct registro>::iterator it;
  int puerto = 7500;
  int fd_archivo;
  //int n_envios = atoi(argv[2]);
  mensaje mjs;
  registro reg_aux;
  if((fd_archivo=open(argv[2],O_RDONLY))==-1){
    perror(argv[2]);
    exit(0);
  }
  int id_envio=1;
  int acr,flag;
  while((flag =  read(fd_archivo, &reg_aux, sizeof(reg_aux)))>0){
    registros.push_back(reg_aux);
  }
  it = registros.begin();
  memcpy(mjs.arguments,(char *)&*it,sizeof(reg_aux));
  mjs.requestId = id_envio;
  for(it=registros.begin()+1;it!=registros.end();it++){

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

