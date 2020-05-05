#ifndef PAQUETEDATAGRAMA1_H_
#define PAQUETEDATAGRAMA1_H_
class PaqueteDatagrama1
{
private:
    char *datos;
    char ip[16];
    unsigned int longitud;
    int puerto;
    int paqueteId;
public:
  // PaqueteDatagrama1(Datos_del paquete char *,tamanio del datagrama_ unsigned int , ip_envio char*,puerto_ int);
    PaqueteDatagrama1(char *,unsigned int , char*,int);
    PaqueteDatagrama1(unsigned int );
    ~PaqueteDatagrama1();
    char *getAddress();
    unsigned int getLen();
    int getPort();
    char *getData();
    void setPort(int );
    void setIp(char *);
    void setData(char *);    
};
#endif

