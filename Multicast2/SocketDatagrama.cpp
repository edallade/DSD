#include "SocketDatagrama.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <iostream>
#include <errno.h>

using namespace std;


SocketDatagrama::SocketDatagrama(char * ip,int port){
    s = socket(AF_INET,SOCK_DGRAM,0);



}

SocketDatagrama::SocketDatagrama(int port){
     puerto= port;
    s = socket(AF_INET,SOCK_DGRAM,0);
        bzero((char*)&DirLocal,sizeof(DirLocal));
        DirLocal.sin_family=AF_INET;
        DirLocal.sin_addr.s_addr=INADDR_ANY;
        DirLocal.sin_port=htons(port);

        bind(s,(struct sockaddr *)&DirLocal,sizeof(DirLocal));

}

int SocketDatagrama::recibe(PaqueteDatagrama1 & p){

    unsigned int clilen = sizeof(DirForanea);//tamaño longitud del mensaje entrante por el socket
    //recvfrom guarda en el datagrampackage "p" los datos recibidos
    int ret = recvfrom(s,(char *) p.getData(),p.getLen(),0,(struct sockaddr *)&DirForanea,&clilen);
    p.setIp(inet_ntoa(DirForanea.sin_addr));
    p.setPort(ntohs(DirForanea.sin_port));
    return ret;
}

int SocketDatagrama::RecibeTimeout(PaqueteDatagrama1 &p, time_t seg, suseconds_t microseg)
{
    timeout.tv_sec=seg;
    timeout.tv_usec=microseg;
    setsockopt(s,SOL_SOCKET,SO_RCVTIMEO,(char*)&timeout,sizeof(timeout));

    unsigned int clilen = sizeof(DirForanea);//tamaño longitud del mensaje entrante por el socket
    //recvfrom guarda en el datagrampackage "p" los datos recibidos
    int ret = recvfrom(s,(char *) p.getData(),p.getLen()*sizeof(int),0,(struct sockaddr *)&DirForanea,&clilen);
     if(ret>0){
         int numeros[1];
         memcpy(numeros,p.getData(),sizeof(numeros));
        p.setIp(inet_ntoa(DirForanea.sin_addr));
        p.setPort(ntohs(DirForanea.sin_port));
        cout<<"Respuesta de "<<p.getAddress()<<":"<<p.getPort()<<endl;
        return numeros[0];
     }
     else{
         if(errno==EWOULDBLOCK){
         //   cout<<"Tiempo de espera de respuesta excedido\n";
             return -1;
         }
         else
            fprintf(stderr, "Error en recvfrom\n");
            return -1;
         
     }
  


}

int SocketDatagrama::envia(PaqueteDatagrama1 & p){
        //se envia al destino Dirfonranea 
         bzero((char *)&DirForanea, sizeof(DirForanea));
         cout<<"enviando a "<<p.getAddress()<<":"<<p.getPort()<<endl;
    DirForanea.sin_family = AF_INET;
    DirForanea.sin_addr.s_addr = inet_addr(p.getAddress());
   	DirForanea.sin_port = htons(p.getPort());
      return sendto(s, (char*) p.getData(), p.getLen() , 0, (struct sockaddr*) &DirForanea, sizeof(DirForanea));

}

int SocketDatagrama::getPuerto(){
    return puerto;
}