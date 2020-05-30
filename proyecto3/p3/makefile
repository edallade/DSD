gndorcoord_v1: gndorcoord_v1.cpp Semaforo.o
	g++ -std=c++11 gndorcoord_v1.cpp Semaforo.o -o gndorcoord_v1 -lpthread
	rm *.o *.gch
Semaforo.o: Semaforo.cpp Semaforo.h
	g++ -std=c++11 Semaforo.cpp Semaforo.h -c -lpthread 