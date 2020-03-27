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

using namespace std;


SocketDatagrama::SocketDatagrama(int port, int pc){
    s = socket(AF_INET,SOCK_DGRAM,0);
    puerto=port;
        bzero((char *)&DirForanea,sizeof(DirForanea));
        DirForanea.sin_family=AF_INET;
        DirForanea.sin_addr.s_addr=inet_addr("192.168.0.5");
        DirForanea.sin_port=htons(port);

        bzero((char*)&DirLocal,sizeof(DirLocal));
        DirLocal.sin_family=AF_INET;
        DirLocal.sin_addr.s_addr=INADDR_ANY;
        DirLocal.sin_port=htons(pc);

        bind(s,(struct sockaddr *)&DirLocal,sizeof(DirLocal));

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
   
    char * d = new char[p.getLen()+1];
    unsigned int clilen = sizeof(DirForanea);
    int ret = recvfrom(s,(char *)&p.getData,p.getLen()*sizeof(char),0,(struct sockaddr *)&DirForanea,&clilen);
    cout << "Recibi de la dirección: " << inet_ntoa(DirForanea.sin_addr) << " y puerto: " << ntohs(DirForanea.sin_port) << endl;
    p.setIp(inet_ntoa(DirForanea.sin_addr));
    p.setPort(ntohs(DirForanea.sin_port));
    return ret;

    
}

int SocketDatagrama::envia(PaqueteDatagrama1 & p){
      return sendto(s, (char*) p.getData(), p.getLen() * sizeof(char), 0, (struct sockaddr*) &DirForanea, sizeof(DirForanea));

}

int SocketDatagrama::getPuerto(){
    return puerto;
}