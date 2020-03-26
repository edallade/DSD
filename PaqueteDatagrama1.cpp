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
    datos= new char [lon+1];
    longitud=sizeChar;
    address=ip;
    puerto=port;
}
PaqueteDatagrama1::PaqueteDatagrama1(unsigned int sizeChar)
{
    longitud=sizeChar;
}

char * PaqueteDatagrama1::getAddr(){
    char * ip_addr;
    ip_addr = ip;
    return ip_addr;
}
unsigned int PaqueteDatagrama1::getLen()
{
    return longitud;
}

int Pa

