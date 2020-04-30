#include "Solicitud.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <cstdlib>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <iostream>
using namespace std;
Solicitud::Solicitud(){
    socketLocal = new SocketDatagrama(0);
    checksum=0;
    consecutivo=1;
}

int Solicitud::getCuenta(){
    return checksum;
}

int  Solicitud::doOperation(char * ip,int puerto,int idDepto,char * arguments,int cantidad){
     mensaje msj,replay_msj;
  
    msj.arguments=cantidad;
    
    if(idDepto==-1){
    msj.requestId=idDepto;
   }
    else
    msj.requestId=consecutivo;//
    PaqueteDatagrama1 pd((char *)&msj,sizeof(msj),ip,puerto);//se llena el datagram package a enviar
    PaqueteDatagrama1 respuesta(sizeof(msj));//como argumento ssolo el tamaño de un mensaje(datagrampackage)
   
   
    int retorno;
    for(;;){//se intentara hasta 7 veces el envio de cada paquerte 
       if( socketLocal->envia(pd)==-1){
            cout<<"error al enviar \n";
       }
    
       
        //se espera respuesta del servidor
        if(socketLocal->SetDatagramTimeout(respuesta,2,0) != -1){
        memcpy(&replay_msj,respuesta.getData(),sizeof (replay_msj));//se guardan datos del mensaje recibdo en una instancia msj local
      // r=msj.arguments;//se obtiene numero del msj recibido en un a variable local
       retorno=replay_msj.requestId;
       //cout<<retorno<<"aaaaaaaaaaaaaaaaaaaaaa"<<endl;
        if(retorno==-1){
            return 0;

        }
        if(retorno<consecutivo){
            checksum= checksum+cantidad;
            consecutivo++;
            return 1;
        }
        else
        {
            return -1;
        }
        
    
      }
      else{
          cout<<"servidor no respondio "<<endl;
         
      }
        
    }
    return -1;
   
    }
        
    


