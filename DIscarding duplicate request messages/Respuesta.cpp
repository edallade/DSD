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

struct mensaje * Respuesta::getRequest(){    
    int nbd_aux[1];
    PaqueteDatagrama1 * res= new PaqueteDatagrama1(sizeof(mensaje));
   mensaje  dataRecv,* aux;
    
    ServerSocket->recibe(*res);

        memcpy(&dataRecv,res->getData(),sizeof(dataRecv) );
        port = res->getPort();
       // cout<<"ADRESS"<<res->getAddress();
        memcpy(ip,res->getAddress(),sizeof(ip));
       // memcpy(&idDepto_recibido,&dataRecv.requestId,(idDepto_recibido));
    // cout<<dataRecv.requestId<<" id local" <<consecutivo<<endl;
         if(dataRecv.requestId==-1)
        {
            cout<<"cuenta final en el servidor "<<nbd<<endl;
            nbd=0;
            consecutivo=0;
            
        }
         if(dataRecv.requestId>consecutivo){
           nbd_aux[0]=dataRecv.arguments;
           nbd= nbd_aux[0]+nbd;
           dataRecv.requestId=consecutivo;
           consecutivo++;
          // cout<<"num recibido "<<nbd_aux[0]<<":"<<dataRecv.arguments<<"id constestar"<<dataRecv.requestId<<endl;
         }
       
        
        //memcpy(dataRecv.arguments,(char *)&nbd,sizeof(nbd));      
       
        
       PaqueteDatagrama1 * rep = new PaqueteDatagrama1((char *)&dataRecv,sizeof(mensaje),ip,port);
        ServerSocket->envia(*rep);
        res->~PaqueteDatagrama1();
        rep->~PaqueteDatagrama1();
        aux = &dataRecv;
        return aux;
        }
  
   
    

void Respuesta::sendReply(struct mensaje replay){
           
       
     
}

