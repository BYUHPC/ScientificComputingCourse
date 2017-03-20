#ifndef FSL_BARRIER_HH
#define FSL_BARRIER_HH

#include <mutex>
#include <condition_variable>

namespace fsl {

class Barrier {

	std::mutex m;
	std::condition_variable cv;
	size_t count;
	size_t expect;
	size_t generation;
	std::function<void()> cf;

public:

	// Barriers cannot be safely copied
	Barrier(Barrier const &) = delete;
	Barrier & operator=(Barrier const &) = delete;

	explicit Barrier(size_t n):
		m{},
		cv{},
		count{n},
		expect{n},
		generation{0},
		cf{[]() {}}
	{}

	template<typename CompletionFunction>
	Barrier(size_t n, CompletionFunction f):
		m{},
		cv{},
		count{n},
		expect{n},
		generation{0},
		cf{f}
	{}

	void wait() {
		{
			// lock will be released at the end of scope
			std::unique_lock<std::mutex> lock{m};

			if (--count != 0) {
				// taken by all threads except the last

				// capture the current generation
				auto gen = generation;

				do {
					// release lock and sleep until signalled
					cv.wait(lock);
					// upon waking the lock will be acquired

				// While loop prevents spurious wake-ups.
				// Also prevents issues with a thread coming
				// back into the barrier before all the
				// other threads have left.
				} while (gen == generation);

				return; // lock is released

			}

			// remainder executed by only the last thread

			cf();
			count = expect;

			// increasing the generation will allow the
			// waiting threads to continue when they wake
			++generation;

		} // lock is released

		// signal all the threads waiting on the
		// condition to wake up
		cv.notify_all();

	}

};

}

#endif
