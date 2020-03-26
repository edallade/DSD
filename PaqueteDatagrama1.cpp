#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include "PaqueteDatagrama1.h"

PaqueteDatagrama1::PaqueteDatagrama1(char *data,unsigned int sizeChar, char* address,int port)
{
    datos= new char [sizeChar+1];
    longitud=sizeChar;
    //copiar datos ingresados en el objeto  
    memcpy(datos,data,longitud);
    memcpy(ip,address,sizeof(ip));
    puerto=port;
}
PaqueteDatagrama1::PaqueteDatagrama1(unsigned int sizeChar)
{
    datos = new char[sizeChar+1];
    datos[0]=0;
    longitud=sizeChar;
}

PaqueteDatagrama1::~PaqueteDatagrama1(){
    delete [] datos;
}


char * PaqueteDatagrama1::getAddress(){
   return ip;
}
unsigned int PaqueteDatagrama1::getLen()
{
    return longitud;
}

int PaqueteDatagrama1::getPort(){
    return puerto;
}

char * PaqueteDatagrama1::getData(){
    return datos;
}

void PaqueteDatagrama1::setData(char * data){
    memcpy(datos,data,strlen(data));
}

void PaqueteDatagrama1::setIp(char * address){
    memcpy(ip,address,strlen(address));
}

void PaqueteDatagrama1::setPort(int port){
    puerto = port;
}

