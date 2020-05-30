#include <iostream>
#include <unistd.h>
#include <thread>
#include <limits.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <cmath>
#include "Semaforo.h"

#define pi 3.14159265
double n_terminos = 1;
int n_graficas=20;
int pto = 7500;
Semaforo sem1,sem2;
using namespace std;

struct Mensaje{
     double coord[2];
    int messageType;//0= Solicitud, 1 = Respuesta
    int requestId;//Identificador del mensaje
    //int operationId;//Identificador de la operación
    //char arguments[TAM_MAX_DATA]; 
};

void pintar(){
 while (1)
 {

    sem1.wait();
    Mensaje mensaje;
    struct sockaddr_in msg_to_srv_addr,client_addr;
    int s, num,res;
    double coord[2];
    double angulo;
  
    mensaje.messageType=1;
    mensaje.requestId=0;
    unsigned int clilen;

    s = socket(AF_INET,SOCK_DGRAM,0);

    bzero((char*)&msg_to_srv_addr,sizeof(msg_to_srv_addr));
    msg_to_srv_addr.sin_family = AF_INET;
    msg_to_srv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    msg_to_srv_addr.sin_port=htons(pto);

    bzero((char*)&client_addr,sizeof(client_addr));
    client_addr.sin_family=AF_INET;
    client_addr.sin_addr.s_addr=INADDR_ANY;
    client_addr.sin_port=htons(7000);

    bind(s,(struct sockaddr *)&client_addr,sizeof(client_addr));

    clilen = sizeof(client_addr);
   // coord[0] = x,  coord[1] = y;                  0.0125 para el real 
    for( coord[0] = -5;coord[0]<=5;coord[0]=coord[0]+0.0125){
        for (double n= 1;n<=n_terminos;n++) {//3 equivale al numero de terminos de la serie 
            angulo = ((pi+pi)*n*coord[0])/static_cast<double>(5);
            coord[1] = coord[1] + (static_cast<double>(1)/n)*(sin(angulo));
          }
            coord[1] = 2.5+((static_cast<double>(-5)/pi)*coord[1]);
            mensaje.coord[0] = coord[0];mensaje.coord[1]=coord[1];
            sendto(s,(struct Mensaje *)&mensaje,sizeof(mensaje),0,(struct sockaddr *)&msg_to_srv_addr,sizeof(msg_to_srv_addr));
            
            recvfrom(s,(char *)&res,sizeof(int),0,(struct sockaddr *)&client_addr,&clilen);

             coord[1]=0;
     
   }
   close(s);
   sem2.post();   
 }

}



void borrar(){

while (1)
{
    /* code */


   sem2.wait();
   Mensaje mensaje;
   struct sockaddr_in msg_to_srv_addr,client_addr;
   int s, num,res;
   double coord[2];
   double angulo;
  
   mensaje.messageType=0;
   mensaje.requestId=0;
   unsigned int clilen;

    s = socket(AF_INET,SOCK_DGRAM,0);

    bzero((char*)&msg_to_srv_addr,sizeof(msg_to_srv_addr));
    msg_to_srv_addr.sin_family = AF_INET;
    msg_to_srv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    msg_to_srv_addr.sin_port=htons(pto);

   bzero((char*)&client_addr,sizeof(client_addr));
    client_addr.sin_family=AF_INET;
    client_addr.sin_addr.s_addr=INADDR_ANY;
    client_addr.sin_port=htons(7200);

    bind(s,(struct sockaddr *)&client_addr,sizeof(client_addr));

 clilen = sizeof(client_addr);
   
   // coord[0] = x,  coord[1] = y;                  0.0125 para el real 
   for( coord[0] = -5;coord[0]<=5;coord[0]=coord[0]+0.0125){
        for (double n=1;n<=n_terminos;n++) {//3 equivale al numero de terminos de la serie 
            angulo = ((pi+pi)*n*coord[0])/static_cast<double>(5);
            coord[1] = coord[1] + (static_cast<double>(1)/n)*(sin(angulo));
          }
            coord[1] = 2.5+((static_cast<double>(-5)/pi)*coord[1]);
            mensaje.coord[0] = coord[0];mensaje.coord[1]=coord[1];
            sendto(s,(struct Mensaje *)&mensaje,sizeof(mensaje),0,(struct sockaddr *)&msg_to_srv_addr,sizeof(msg_to_srv_addr));
          
            recvfrom(s,(char *)&res,sizeof(int),0,(struct sockaddr *)&client_addr,&clilen);

             coord[1]=0;
     
   }
   close(s);
   n_terminos++;
  
   sem1.post();   

   }
}


int main(){//Inicializa los semaforos
    
  sem1.init(1);
    sem2.init(0);
    thread th1(pintar), th2(borrar);
    th1.join();
    th2.join();
    
    exit(0);
}