#include <stdlib.h>
#include <iostream>
#include "Solicitud.h"

using namespace  std;

int main (int argc, char*argv[]){
    cout<<"Modo de uso: ./cliente NumDepositos ip\n";
    int cantidad [1];
    int puerto = 7500;
    long int NumDepositos;
    NumDepositos= atoi(argv[1]);

    Solicitud cliente;
    for(int i = 0;i<NumDepositos;i++){     
    cantidad[0]= rand()%10+1;
    cliente.doOperation(argv[2],puerto,1,(char *)cantidad, cantidad[0]);
        
    }
    cout<<"Cuenta local final del cliente "<<cliente.getCuenta()<<endl;

}

