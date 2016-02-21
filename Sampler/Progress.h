#include <thread>   // for threads
#include <chrono>   // for expresssing duration
#include <atomic>   
#include <iomanip>
#include <functional>   // for std::ref()
using namespace std; 

class progress_bar {
    atomic<bool> finished; 
    atomic<int> n; 
    thread t;
  public: 
    progress_bar() : finished(false),n(0), t(ref(*this)) { }    // initiate the bar by starting a new thread
    void operator() () {                                       // function executed by the thread
      while (!finished) {
        this_thread::sleep_for(chrono::milliseconds(1000));   
        cout << setw(++n) << setfill("\e[1;47m \e[0m") << " "; 
      }
   }
   void terminate() {                                  // tell the thread/bar to stop 
     finished = true;
     if (t.joinable())
       t.join(); 
   }
};
