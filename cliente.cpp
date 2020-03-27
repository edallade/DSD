#include "SocketDatagrama.h"
#include <string>
#include <iostream>
#include <string.h>

using namespace std;

int main(){

    SocketDatagrama cliente(7200, 0);

    char texto_c[50] = "mensaje enviado al servidor";

    PaqueteDatagrama1 mensaje_a_servidor(texto_c, strlen(texto_c), "192.168.0.5", cliente.getPuerto());
    PaqueteDatagrama1 recibi_de_servidor(50);

    cliente.envia(mensaje_a_servidor);
    cout << "Envie al servidor: " << mensaje_a_servidor.getData() << endl;
    cliente.recibe(recibi_de_servidor);
    cout << "Recibi del servidor: " << recibi_de_servidor.getData() << endl;

    return 0;
}