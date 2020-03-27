#include "PaqueteDatagrama1.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
class SocketDatagrama
{
private:
    struct sockaddr_in DirLocal;
    struct sockaddr_in DirForanea;
    int s,puerto;
    bool tipo;
public:
    SocketDatagrama(int, int);
    SocketDatagrama(int);
    ~SocketDatagrama();
//Recibe un paquete tipo datagrama proveniente de este socket
    int recibe(PaqueteDatagrama1 & p);
//Envía un paquete tipo datagrama desde este socket
    int envia(PaqueteDatagrama1 & p);
    int getPuerto();
};

