#include "SocketDatagrama.h"
#include "SocketMulticast.h"
#include <iostream>
#include <string.h> 

using namespace std;

int main (int argc, char * argv []){
    if(argc!=4){
        cout<<"modo de uso "<<argv[0]<<" IPmulticast puerto TTL"<<endl;
        exit(0);
    }
    int puerto;
    unsigned char tll= *argv[3];
    srand(time(NULL));
    int numeros[2];
    numeros[0]=rand()%100+1;
    numeros[1]=rand()%100+1;
    unsigned int menLen;
    menLen = sizeof(numeros);
    puerto = atoi(argv[2]);
    SocketMulticast emisor(puerto,tll);
    SocketDatagrama emisor_unicast(puerto);
    PaqueteDatagrama1 pOut((char *)numeros,menLen,argv[1],puerto);
    PaqueteDatagrama1 pIn(sizeof(int)*2);
    int r;
      emisor.envia(pOut,tll);
    while (1)
    {
      
      
        r = emisor_unicast.RecibeTimeout(pIn,2,0);
        if(r!=-1){
            cout<<"el resultado es"<<r<<endl;
           r=-1;
        }
        

    }
    
    

}