#include "SocketDatagrama.h"
#include "mensaje.h"
#include<iostream>
class Respuesta
{
private:
   SocketDatagrama * ServerSocket;
   char ip[16];
   int port,consecutivo;
    int nbd;
public:
    Respuesta(int port );
    struct mensaje *getRequest(void);
    void sendReply(struct mensaje );
    int getCuenta();
   
};

