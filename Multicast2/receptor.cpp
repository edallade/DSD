#include "SocketMulticast.h"
#include "SocketDatagrama.h"
#include <iostream>
#include <string.h> 

using namespace std;

int main(int argc, char * argv[]){
    if(argc!=3){
        cout<<"modo de uso"<<argv[0]<<" IPmulticast Puerto"<<endl;
        exit(0);
    }
    int puerto;
    puerto = atoi(argv[2]);

    PaqueteDatagrama1 rec(sizeof(int)*2);
    SocketMulticast receptor(puerto);
   
    receptor.unisrseGrupo(argv[1]);
   PaqueteDatagrama1 pIn = receptor.recibe(rec,puerto);
   cout<<"port to send unicast message: "<<pIn.getPort()<<endl;
    SocketDatagrama receptor_unicast(0);
    receptor_unicast.envia(pIn);
    receptor.salirseGrupo(argv[1]);
     return(0);

} 