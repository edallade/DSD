#include "PaqueteDatagrama1.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
class SocketMulticast
{
private:
    int s;
    struct sockaddr_in direccionLocal;
    struct sockaddr_in direccionForanea; 
public:
    SocketMulticast(int);
    SocketMulticast(int , unsigned char);
    ~SocketMulticast();
    int recibe(PaqueteDatagrama1 & p);
    int envia(PaqueteDatagrama1 & p, unsigned char ttl);
    void unisrseGrupo(char *);
    void salirseGrupo(char *);

};




