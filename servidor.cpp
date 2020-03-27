#include "SocketDatagrama.h"
#include <string>
#include <string.h>
#include <iostream>

using namespace std;

int main(){
    SocketDatagrama servidor(7200, false);

    char texto_s[35]= "Hola cliente recibi tu mensaje";

    PaqueteDatagrama1 recibi_de_cliente(50);
    PaqueteDatagrama1 mensaje_a_cliente(texto_s, strlen(texto_s), "127.0.0.1", servidor.getPuerto());

    while(true){
        servidor.recibe(recibi_de_cliente);
        cout << "Recibi del cliente: " << recibi_de_cliente.getData() << endl;
        servidor.envia(mensaje_a_cliente);
        cout << "Envie al cliente: " << mensaje_a_cliente.getData() << endl;
    }

    return 0;
}