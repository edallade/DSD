#include "SocketMulticast.h"
#include "SocketDatagrama.h"
#include "mensaje.h"
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
    int cuenta=0;
    int dbi=0;
    SocketMulticast receptor(puerto);
   int response;
 receptor.unisrseGrupo(argv[1]);
   while (1)
   {
        PaqueteDatagrama1 * rec = new PaqueteDatagrama1(sizeof(mensaje));
       
        response = receptor.recibeSeguro(*rec,puerto,cuenta);
        if(response>0){
            cuenta++;
            dbi = dbi + response;
        }
        else if(response == -1)
            break;

        rec->~PaqueteDatagrama1();
        
   }
   cout<<"cuenta final en servidor remoto"<<dbi<<endl;
    receptor.salirseGrupo(argv[1]);    
     return(0);

} 