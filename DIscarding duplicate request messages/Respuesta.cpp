#include "Respuesta.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <iostream>
using namespace std;

Respuesta::Respuesta( int port ){
    ServerSocket = new SocketDatagrama(port);
    nbd=0;
    consecutivo=0;
}

struct mensaje* Respuesta::getRequest(){    
    int nbd_aux;
    PaqueteDatagrama1 res(sizeof(mensaje));
    struct mensaje  dataRecv,* aux;
    
    ServerSocket->recibe(res);

        memcpy(&dataRecv,res.getData(),sizeof(dataRecv) );
        port = res.getPort();
        memcpy(ip,res.getAddress(),sizeof(ip));
       // memcpy(&idDepto_recibido,&dataRecv.requestId,(idDepto_recibido));
     
         if(dataRecv.requestId==-1)
        {
            cout<<"cuenta final en el servidor "<<nbd<<endl;
            nbd=0;
            consecutivo=0;
            
        }
         if(dataRecv.requestId>consecutivo){
           memcpy(&nbd_aux,&dataRecv.arguments,sizeof(nbd_aux));
           nbd= nbd_aux+nbd;
           dataRecv.requestId=consecutivo;
           consecutivo++;
           
         }
       
        
        memcpy(dataRecv.arguments,&nbd,sizeof(nbd));      
        aux = &dataRecv;
        return aux;

        }
  
   
    

void Respuesta::sendReply(struct mensaje * replay){
           
       PaqueteDatagrama1 rep ((char *)replay,sizeof(mensaje),ip,port);
        ServerSocket->envia(rep);
}

