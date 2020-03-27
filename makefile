clienUDP: cliente.cpp  SocketDatagrama.o
	g++ cliente.cpp SocketDatagrama.o PaqueteDatagrama1.o -o clienUDP
serUDP: servidor.cpp  SocketDatagrama.o
	g++ servidor.cpp SocketDatagrama.o PaqueteDatagrama1.o -o serUDP
SocketDatagrama.o: SocketDatagrama.cpp PaqueteDatagrama1.o SocketDatagrama.h
	g++ SocketDatagrama.cpp -c
PaqueteDatagrama1.o: PaqueteDatagrama1.cpp PaqueteDatagrama1.h
	g++ PaqueteDatagrama1.cpp -c
clienUDP: cliente.cpp  SocketDatagrama.o
	g++ cliente.cpp SocketDatagrama.o PaqueteDatagrama1.o -o clienUDP