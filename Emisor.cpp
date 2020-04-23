#include "SocketMulticast.h"
#include <iostream>
#include <string.h> 

using namespace std;

int main (int argc, char * argv []){
    if(argc!=5){
        cout<<"modo de uso "<<argv[0]<<" IPmulticast puerto TTL Cadena_a_difunfir"<<endl;
        exit(0);
    }
    int puerto;
<<<<<<< HEAD
    unsigned char tll= *argv[3];
    char * mensaje = argv[4];
    unsigned int menLen;
    menLen = strlen(mensaje);
    puerto = atoi(argv[2]);
=======
     unsigned char tll= *argv[3];
     char * mensaje = argv[4];
     unsigned int menLen;
     menLen = strlen(mensaje);
    puerto = atoi(argv[2]);
  cout<<argv[3]<<":"<<puerto<<endl;
>>>>>>> cc9ddd8a56d8fdf3707c5b3fc98c1ea803ed9757
    SocketMulticast emisor(puerto,tll);
    PaqueteDatagrama1 p(mensaje,menLen,argv[1],puerto);

    while (1)
    {
        emisor.envia(p,tll);
    }
    
    

}