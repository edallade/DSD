#include "SocketMulticast.h"
#include "SocketDatagrama.h"
#include <sys/types.h>
#include "mensaje.h"
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
    int reuse =1;
    s = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(setsockopt(s,SOL_SOCKET,SO_REUSEPORT,&reuse,sizeof(reuse))<0){
    cout<<"Error al confugurar puerto reusable"<<endl;
    }
    
    bzero((char *)&direccionLocal,sizeof(direccionLocal));

    direccionLocal.sin_family = AF_INET;
    direccionLocal.sin_addr.s_addr=INADDR_ANY;
    direccionLocal.sin_port = htons(port);
    
    bind(s,(struct sockaddr *)&direccionLocal,sizeof(direccionLocal));
    }

SocketMulticast::SocketMulticast(int port, unsigned char TLL){
    s = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(setsockopt(s,IPPROTO_IP, IP_MULTICAST_TTL,(void *)&TLL,sizeof(TLL))<0){
        cout<<"error al crear socket del emisor"<<endl;
        exit(0);
        }
    }

int SocketMulticast::recibeSeguro(PaqueteDatagrama1 &p,int pto,int num_depto){
        int acr, res;
        mensaje recibido;
         PaqueteDatagrama1 * aux;
        unsigned int len = sizeof(direccionForanea);
        //se bloquea el receptor hasta que recibe mensaje del gruppo multicast
        recvfrom(s, (char*) p.getData(), p.getLen(), 0, (struct sockaddr*) &direccionForanea, &len);
        //se guarda en la instancia local de la estructura mensaje "recibido"
        memcpy(&recibido,p.getData(),sizeof(recibido));
       
       if(recibido.messageid==-1){
            return -1;
        }
        if(num_depto < recibido.messageid){//si no se ha recibido el paquete retorna el monto de dpto
            res = recibido.cuenta;
            
        }
        else{//si se recibe de nueva cuenta el paquete 
           res = 0;
            }
        //se contesta por unicast al cliente el id recibido 
        aux  = new PaqueteDatagrama1((char *)&recibido.messageid,sizeof(int),inet_ntoa(direccionForanea.sin_addr),pto+1); 
        SocketDatagrama * response_udp = new SocketDatagrama(0);
        response_udp->envia(*aux);
        response_udp->~SocketDatagrama();
        aux->~PaqueteDatagrama1();
        return res;
     

    }

    int SocketMulticast::enviaConfiable(PaqueteDatagrama1 &p, unsigned char ttl, int num_receptores,int id_depto){
        bzero((char *)&direccionForanea, sizeof(direccionForanea));
        direccionForanea.sin_family = AF_INET;
        direccionForanea.sin_addr.s_addr = inet_addr(p.getAddress());
        direccionForanea.sin_port = htons( p.getPort() );
        int control =0,res=0;
        int estado = 1;
        PaqueteDatagrama1 * pIN = new PaqueteDatagrama1(sizeof(int));//paquete para almacenar la respuesta
        SocketDatagrama * respuesta_destinatarios = new SocketDatagrama(p.getPort());//socket unicast para recibir respuesta
         //se envia al grupo multicast el dpto con su id
          sendto(s, (char *)p.getData(), p.getLen(), 0, (struct sockaddr *) &direccionForanea, sizeof(direccionForanea));
       while (control < num_receptores)
        {  
          
            //se espera respuesta de los miembros del grupo, -1 si no contestan o el acuse de cada  servidor 
            res = respuesta_destinatarios->RecibeTimeout(*pIN,0,10000);
            if(id_depto==res ){
              control++;
                estado=1;
           }
          else  {
                sendto(s, (char *)p.getData(), p.getLen(), 0, (struct sockaddr *) &direccionForanea, sizeof(direccionForanea));
              estado=-1;
              break;
           }



        }
       respuesta_destinatarios->~SocketDatagrama();//cerrar el socket unicast para los acr's de esta  transeaccion

        return estado;
        
        
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