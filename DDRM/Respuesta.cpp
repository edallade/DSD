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

Respuesta::Respuesta(int port ){
    ServerSocket = new SocketDatagrama(port);
    nbd=0;
    consecutivo=1;
}

struct mensaje* Respuesta::getRequest(){
    int nbd_aux;
    PaqueteDatagrama1 res(sizeof(mensaje));
    struct mensaje  dataRecv,*aux;
    
    if(ServerSocket->SetDatagramTimeout(res,10,0) != -1 ){

        memcpy(&dataRecv,res.getData(),sizeof(dataRecv) );
        port = res.getPort();
        memcpy(ip,res.getAddress(),sizeof(ip));
        memcpy(&consecutivo,&dataRecv.requestId,(consecutivo));
        cout << "request id "<<consecutivo<<endl;
        memcpy(&nbd_aux,&dataRecv.arguments,sizeof(nbd_aux));
        nbd= nbd_aux+nbd;
        memcpy(dataRecv.arguments,&nbd,sizeof(nbd));      
        aux = &dataRecv;
        return aux;
  
        }
    else{
        cout<<"Tiempo de espera por cliente nuevo terminado cuenta ="<<nbd<<endl;
        nbd=0;
        consecutivo=0;
        aux = &dataRecv;
        return aux;
        }
        
    
}

void Respuesta::sendReply(struct mensaje * replay){
           
       PaqueteDatagrama1 rep ((char *)replay,sizeof(mensaje),ip,port);
        ServerSocket->envia(rep);
}

