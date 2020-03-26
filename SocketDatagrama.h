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
public:
    SocketDatagrama(/* args */);
    ~SocketDatagrama();
};

SocketDatagrama::SocketDatagrama(/* args */)
{
}
