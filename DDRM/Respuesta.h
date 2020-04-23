#include "SocketDatagrama.h"
#include "mensaje.h"
#include<iostream>
#include <vector>
class Respuesta
{
private:
   SocketDatagrama * ServerSocket;
   char ip[16];
   int port,consecutivo;
   long int nbd;
   std::vector <int> checklist;
public:
    Respuesta(int port );
    struct mensaje *getRequest(void);
    void sendReply(struct mensaje *);
    int getCuenta();
   
};

