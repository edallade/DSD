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
    checklist.push_back(0);
}

struct mensaje* Respuesta::getRequest(){
    int nbd_aux,idant=0,idsig;
    PaqueteDatagrama1 res(sizeof(mensaje));
    struct mensaje  dataRecv,*aux;
    vector<int>::iterator i;
    bool state = false;
  
    if(ServerSocket->SetDatagramTimeout(res,10,0) != -1 ){
        
        memcpy(&dataRecv,res.getData(),sizeof(dataRecv) );

        port = res.getPort();
        memcpy(ip,res.getAddress(),sizeof(ip));
       
        memcpy(&idsig,&dataRecv.requestId,sizeof(idsig));
        
         

       
         checklist.push_back(idsig);
        memcpy(&nbd_aux,&dataRecv.arguments,sizeof(nbd_aux));
        nbd= nbd_aux+nbd;
        memcpy(dataRecv.arguments,&nbd,sizeof(nbd));     
     
    
        
         PaqueteDatagrama1 rep ((char *)&dataRecv,sizeof(mensaje),ip,port);
         ServerSocket->envia(rep); 
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

