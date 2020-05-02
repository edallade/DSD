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
using namespace std;

int main(int argc, char * argv[]){
  if(argc != 2){
    cout<<"modo de uso "<<argv[0]<<" nombre_de_archivo_guardar_datos"<<endl;
    exit(0);
  }

  SocketDatagrama servidor(7500);
  int fd_archivo;
  mensaje mjs;
  registro reg_aux;
  vector<struct registro>registros;
  vector<struct registro>::iterator it;
  if((fd_archivo=open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0666))==-1){
      perror(argv[1]);
      exit(0);
  }
  int respuesta, control =0;
  PaqueteDatagrama1  p_recibido(sizeof(mjs));
  while (1)
  {
  servidor.recibe(p_recibido);
  memcpy(&mjs,p_recibido.getData(),sizeof(mjs));
  
   if(mjs.requestId==-1)
     break;
   if(mjs.requestId>control){
     memcpy(&reg_aux,(char *)&mjs.arguments,sizeof(reg_aux));
     //write(fd_archivo,&reg_aux,sizeof(reg_aux));
     registros.push_back(reg_aux);
    mjs.requestId=control;
    control++;
    
   }
    
   
   PaqueteDatagrama1 p_respuesta((char *)&mjs,sizeof(mjs),p_recibido.getAddress(),p_recibido.getPort());
   servidor.envia(p_respuesta);
    
 
    
  }  
  for(it=registros.begin();it!=registros.end();it++){
    reg_aux=*it;
    write(fd_archivo,&reg_aux,sizeof(reg_aux));
  }
  close(fd_archivo);
    
  
  
return 0;
} 