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

char * Solicitud::doOperation(char * ip,int puerto,int operId,char * arguments, int suma){
    struct mensaje msj,replay_msj;
    int random,r;
    int i;
    consecutivo++;
    memcpy(msj.arguments,arguments,sizeof(arguments));
    msj.operationId=operId;//id = 1 = suma si no , error
    msj.messageType=0;//0= solicitud 1 = respuesta
    msj.requestId=consecutivo;//
    PaqueteDatagrama1 pd((char *)&msj,sizeof(msj),ip,puerto);//se llena el datagram package a enviar
    PaqueteDatagrama1 respuesta(sizeof(msj));//como argumento ssolo el tamaño de un mensaje(datagrampackage)
    bool state = true;
    i =0;
    int retorno;
    while(state){//se intentara hasta 7 veces el envio de cada paquerte 
        socketLocal->envia(pd);
        //se espera respuesta del servidor
        if(socketLocal->SetDatagramTimeout(respuesta,2,500000) != -1){
        memcpy(&replay_msj,respuesta.getData(),sizeof (replay_msj));//se guardan datos del mensaje recibdo en una instancia msj local
        memcpy(&r,&replay_msj.arguments,sizeof(r));//se obtiene numero del msj recibido en un a variable local
        memcpy(&retorno,&replay_msj.requestId,sizeof(retorno));
        checksum=checksum+suma;
            if(checksum!=r){
                cout << "Error cuneta local = "<<checksum<<" cuenta en el servidor= "<<r<<endl;
                exit(-1);
            }
            cout<<"reotrno "<<retorno<<" vs id enviadoo"<<consecutivo<<endl;
            if(retorno==consecutivo)
                state= false;
            
        }else{
                    i++;
                    cout << "intento de envio: "<< i<<endl;
                    
            }
      }
        
        return arguments;
    
    }
        
    


