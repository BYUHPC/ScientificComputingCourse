#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <utility>
#include <vector>

using namespace std;

/*

Compile this file with something like this:

$ g++ -std=c++14 -O3 WorkQueue.cc -lpthread -o WorkQueue

And then run:

$ ./WorkQueue

*/

class WorkQueue {
  mutex m;
  queue<int> q;

public:
  WorkQueue() = default;
  ~WorkQueue() = default;

  // bool indicates whether the queue is empty
  // Only use the int if the bool is true
  pair<bool, int> dequeue() {
    unique_lock<mutex> lock(m);
    if (q.empty()) {
      return pair<bool, int>(true, 0);
    } else {
      pair<bool, int> p{false, q.front()};
      q.pop();
      return p;
    }
  }

  void enqueue(int item) {
    unique_lock<mutex> lock(m);
    q.push(item);
  }
};

void worker(WorkQueue &queue, int tid, ostream &out) {
  do {
    pair<bool, int> r(queue.dequeue());
    if (get<bool>(r)) {
      return;
    }
    out << tid << ' ' << get<int>(r) << endl;
  } while (true);
}

int main(void) {
  WorkQueue queue;

  // produce all the work up front to simplify termination
  for (int i = 0; i < 100000; ++i) {
    queue.enqueue(i);
  }

  vector<thread> threads;
  threads.emplace_back(worker, ref(queue), 0, ref(cout));
  threads.emplace_back(worker, ref(queue), 1, ref(cerr));

  int failed = 0;
  for (auto &thread : threads) {
    if (thread.joinable()) {
      thread.join();
    } else {
      failed = 1;
      cerr << "Thread was not joinable" << endl;
    }
  }

  return failed;
}
