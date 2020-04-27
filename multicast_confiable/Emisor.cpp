
#include "SocketMulticast.h"
#include "mensaje.h"
#include <iostream>
#include <string.h> 

using namespace std;

int main (int argc, char * argv []){
    if(argc!=5){
        cout<<"modo de uso "<<argv[0]<<" IPmulticast puerto TTL numDepositos"<<endl;
        exit(0);
    }
    int puerto,numDepositos,id_depto=0,depto;
    mensaje mje;
   
    numDepositos = atoi(argv[4]); /*numero de numDepositos*/
    unsigned char ttl= *argv[3];
    srand(time(NULL));
    int cuenta_local;
    int numClientes = 3;
    unsigned int menLen;
   
    puerto = atoi(argv[2]);
    SocketMulticast emisor(puerto,ttl);
   
    depto = rand()%9+1;
    cuenta_local=depto;
    
    id_depto=1;
    for(int x =1;x<=numDepositos-1;x++){
      
        mje.cuenta=depto;
        mje.messageid=id_depto;
        menLen = sizeof(mje);
        PaqueteDatagrama1 * pOut= new PaqueteDatagrama1((char *)&mje,menLen,argv[1],puerto);
        int retorno = emisor.enviaConfiable(*pOut,ttl,numClientes,id_depto);
      
        if(retorno == 1){
           id_depto++;
            depto = rand()%9+1;
            if(id_depto<numDepositos)
            cuenta_local=cuenta_local+depto;
         
           
        }
        else{
            x=x-1;
        }
        pOut->~PaqueteDatagrama1();

      }
        mje.cuenta=cuenta_local;
        mje.messageid=-1;//fin del programa
        PaqueteDatagrama1 * pOut= new PaqueteDatagrama1((char *)&mje,menLen,argv[1],puerto);
        emisor.enviaConfiable(*pOut,ttl,numClientes,id_depto);
        cout<<"cuenta local: "<<cuenta_local<<endl;
    }
    
    
