#include <stdlib.h>
#include <iostream>
#include <time.h> 
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include <algorithm> 
#include <sys/time.h>
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
  struct timeval timestamp;
  vector<struct registro>registros;
  vector<struct registro>::iterator it;
  vector<long int>celulares;
  vector<long int>::iterator it_cels;
  celulares.push_back(0);
  if((fd_archivo=open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0666))==-1){
      perror(argv[1]);
      exit(0);
  }
  int respuesta=0, control =0;
  PaqueteDatagrama1  p_recibido(sizeof(mjs));
  int temp=0;
  while (1)
  {
  servidor.recibe(p_recibido);
  memcpy(&mjs,p_recibido.getData(),sizeof(mjs));
  
   if(mjs.requestId==-1)
     break;
   if(mjs.requestId>control){
     
     memcpy(&reg_aux,(char *)&mjs.arguments,sizeof(reg_aux));

    long int cel_temp = atol(reg_aux.celular);
    
     if(binary_search(celulares.begin(),celulares.end(),cel_temp)==false){
        celulares.push_back(cel_temp);
       sort(celulares.begin(),celulares.end());
  
        gettimeofday(&timestamp,NULL);
        localtime(&timestamp.tv_usec);
        char seg [sizeof(long int)], microseg [sizeof(long int)];
        sprintf(seg,"%ld",timestamp.tv_sec);
        sprintf(microseg,"%ld",timestamp.tv_usec);
        write(fd_archivo,&seg,sizeof(long int));
        write(fd_archivo,&microseg,sizeof(long int)); 
        write(fd_archivo,&reg_aux,sizeof(reg_aux));
        mjs.requestId=control;
         control++;
       
      }
      else{
        control++;
        mjs.timestamp.tv_sec=0;
        mjs.timestamp.tv_usec=0;
        cout<<reg_aux.celular<<" duplicado\n";
        
        }

       PaqueteDatagrama1 p_respuesta((char *)&mjs,sizeof(mjs),p_recibido.getAddress(),p_recibido.getPort());
        servidor.envia(p_respuesta);
    
   
    
  
   
   }
    
   
   
   
    
 
    
  }  
 /* for(it=registros.begin();it!=registros.end();it++){
    reg_aux=*it;
    write(fd_archivo,&reg_aux,sizeof(reg_aux));
  }*/
  //int x=0;
 
  close(fd_archivo);
    
  
  
return 0;
} 