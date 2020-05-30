#ifndef SEMAFORO_H_
#define SEMAFORO_H_

#include <iostream>
#include <condition_variable>
#include <mutex>
using namespace std;
class Semaforo{
    private:
        mutex mutex_;
        condition_variable condition_;
        unsigned long count_;
    public:
        Semaforo(unsigned long = 0);
        void post();
        void wait();
        void init(unsigned long);
};
#endif
