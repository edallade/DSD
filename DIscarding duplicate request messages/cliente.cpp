#include <stdlib.h>
#include <iostream>
#include <time.h> 
#include "Solicitud.h"

using namespace  std;

int main (int argc, char*argv[]){
  if(argc!=3){
        cout<<"Modo de uso: ./cliente NumDepositos ip\n";
        exit(0);
  }
  srand(time(NULL));
    int cantidad;
    int puerto = 7500;
    int   fin[1],ret;
    fin[0]=0;
    long int NumDepositos;
    NumDepositos= atoi(argv[1]);
    cantidad= rand()%10+1;
    Solicitud cliente;
    for(int idDepto = 1;idDepto<NumDepositos;idDepto++){     
   ret= cliente.doOperation (argv[2],puerto,idDepto,(char *)&cantidad,cantidad);
    if(ret ==1){
        cantidad= rand()%10+1;
    }

   
    }
    cliente.doOperation(argv[2],puerto,-1,(char *)fin,0);
cout<<"Cuenta local final del cliente "<<cliente.getCuenta()<<endl;
}

