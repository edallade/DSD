#include "SocketMulticast.h"
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
    PaqueteDatagrama1 rec((unsigned int)100);
    SocketMulticast receptor(puerto);
    receptor.unisrseGrupo(argv[1]);
    while (1)
    {
  cout<<receptor.recibe(rec)<<"bytes recibidos"<<endl;
    }
    
    

    receptor.salirseGrupo(argv[1]);
     return(0);

}