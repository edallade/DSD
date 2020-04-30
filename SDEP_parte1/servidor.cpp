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

using namespace std;

int main(int argc, char * argv[]){
  if(argc != 2){
    cout<<"modo de uso "<<argv[0]<<" nombre_de_archivo_guardar_datos"<<endl;
    exit(0);
  }
    SocketDatagrama servidor(7500);
    int fd_archivo;
    registro reg_aux;
    if((fd_archivo=open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0666))==-1){
      perror(argv[1]);
      exit(0);
    }
    int respuesta = 1;
    PaqueteDatagrama1  p_recibido(sizeof(reg_aux));
   
       
      servidor.recibe(p_recibido);
      memcpy(&reg_aux,p_recibido.getData(),p_recibido.getLen());
      write(fd_archivo,&reg_aux,sizeof(reg_aux));
     
   close(fd_archivo);
    
  
  
    return 0;
} 