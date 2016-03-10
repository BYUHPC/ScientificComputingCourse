#ifndef BARRIER_HH
#define BARRIER_HH

#include <mutex>
#include <condition_variable>


class Barrier {

    std::mutex m;
    std::condition_variable cv;
    unsigned int count;
    unsigned int expect;
    unsigned int generation;

public:

    explicit Barrier(unsigned int n);

    /**
     * Returns true for the last thread in - false for all others
     */ 
    bool sync(); 

};


#endif
