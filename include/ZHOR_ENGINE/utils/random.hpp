#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <stdlib.h>
#include <ctime>

class Random
{
private:
    
public:
    Random() {
        srand(time(NULL));
    }
    ~Random() {}

    int onRangeInt(int min, int max){
        return rand()%(max-min) + min;        
    }

    double onRangeDouble(double min, double max){
        return min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
    }
};

#endif