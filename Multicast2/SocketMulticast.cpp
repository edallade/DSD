#include "SocketMulticast.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

using namespace std;

SocketMulticast::SocketMulticast(int port){
    s = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    
    bzero((char *)&direccionLocal,sizeof(direccionLocal));

    direccionLocal.sin_family = AF_INET;
    direccionLocal.sin_addr.s_addr=INADDR_ANY;
    direccionLocal.sin_port = htons(port);
    
    bind(s,(struct sockaddr *)&direccionLocal,sizeof(direccionLocal));
    }

SocketMulticast::SocketMulticast(int port, unsigned char TLL){
    //unsigned char f = CM;
    int reuse = 1;
    s = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(setsockopt(s,IPPROTO_IP, IP_MULTICAST_TTL,(void *)&TLL,sizeof(TLL))<0){
        cout<<"error al crear socket del emisor"<<endl;
        exit(0);
        }
    if(setsockopt(s,SOL_SOCKET,SO_REUSEPORT,&reuse,sizeof(reuse))<0){
        cout<<"Error al confugurar puerto reusable"<<endl;
        }
    }

    PaqueteDatagrama1 SocketMulticast::recibe(PaqueteDatagrama1 &p,int pto){
        int n[2],r[1];
        unsigned int len = sizeof(direccionForanea);
        int salida = recvfrom(s, (char*) p.getData(), p.getLen() * sizeof(int), 0, (struct sockaddr*) &direccionForanea, &len);
        cout << "Recibi de la dirección: " << inet_ntoa(direccionForanea.sin_addr) << " y puerto: " << ntohs(direccionForanea.sin_port) << endl;
       memcpy(n,p.getData(),sizeof(n));
        r[0]= n[0]+n[1];
       std::cout<<n[0]<<"+"<<n[1]<<"="<<r[0]<<endl;
      PaqueteDatagrama1  aux(p.getLen());
        memcpy(aux.getData(),(char *)&r[0],sizeof(r));
        aux.setIp(inet_ntoa(direccionForanea.sin_addr));
          cout<<"esperando fffff"<<endl;
        aux.setPort(pto);
         cout<<"esperando fffffx2"<<endl;
        return aux;
    }

    int SocketMulticast::envia(PaqueteDatagrama1 &p, unsigned char ttl){
        bzero((char *)&direccionForanea, sizeof(direccionForanea));
        direccionForanea.sin_family = AF_INET;
        direccionForanea.sin_addr.s_addr = inet_addr(p.getAddress());
        direccionForanea.sin_port = htons( p.getPort() );
        cout<<"enviando a"<<p.getAddress()<<":"<<p.getPort()<<endl;
        return sendto(s, (char *)p.getData(), p.getLen() * sizeof(int), 0, (struct sockaddr *) &direccionForanea, sizeof(direccionForanea));
    }

    void SocketMulticast::unisrseGrupo(char * multicastIp){
       struct ip_mreq multicast;
       multicast.imr_multiaddr.s_addr=inet_addr(multicastIp);
       multicast.imr_interface.s_addr=htonl(INADDR_ANY);
       if(setsockopt(s, IPPROTO_IP, IP_ADD_MEMBERSHIP,(void *)&multicast,sizeof(multicast))!=-1)
       cout<<"Unido con exito al grupo multicast"<<endl;
       else{
           cout<<"Error al unir al grupo multicast"<<endl;
           exit(0);
       }
    }

    void SocketMulticast::salirseGrupo(char * multicastIp){
       struct ip_mreq multicast;
       multicast.imr_multiaddr.s_addr=inet_addr(multicastIp);
       multicast.imr_interface.s_addr=htonl(INADDR_ANY);
       if(setsockopt(s, IPPROTO_IP, IP_DROP_MEMBERSHIP,(void *)&multicast,sizeof(multicast))!=-1)
       cout<<"Salida  con exito del grupo multicast"<<endl;
       else{
           cout<<"Error al Salir del grupo multicast"<<endl;
           exit(0);
       }
    }