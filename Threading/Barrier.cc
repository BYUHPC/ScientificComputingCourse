#include "Barrier.hh"

Barrier::Barrier(unsigned int n) : m{}, cv{}, count{0}, expect{n}, generation{0} {}

bool Barrier::sync() {
    // lock will be released at the end of the function scope
    std::unique_lock<std::mutex> lock{m};

    // capture the current generation - this will be used in a loop
    auto gen = generation;

    if (++count < expect) {
        // this branch is taken by all threads except the last
        do {
            // will release the lock and sleep until signalled
            cv.wait(lock);
            // upon waking the lock will be acquired
         
          // while loop prevents spurious wake-ups
          // Also prevents issues with a thread coming back into the barrier
          // before all the other threads have left
        } while (gen == generation);

        // lock will be released upon returning
        return false;

    } else {
        // this branch is taken by only the last thread
        count = 0;

        // increasing the generation will allow the waiting threads to continue
        ++generation;

        // signal all the threads waiting on the condition
        cv.notify_all();

        // lock will be released upon returning
        return true;
    }
}


