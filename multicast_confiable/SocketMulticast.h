
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
    int  recibeSeguro(PaqueteDatagrama1 & p,int, int );
    int enviaConfiable(PaqueteDatagrama1 & p, unsigned char ttl, int num_receptores, int id_depto);
    void unisrseGrupo(char *);
    void salirseGrupo(char *);

};




