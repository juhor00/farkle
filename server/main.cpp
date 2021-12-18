#include <iostream>
#include <thread>
#include <vector>

using namespace std;

const int THREAD_COUNT = 3;


void *PrintHello(int id) {

   cout << "Thread ID : " << id << endl;
   return 0;

}


int main()
{
    vector<thread*> threads;
    for (int i=0; i<THREAD_COUNT; i++){
        cout << "Creating thread " << i << endl;
        thread* t = new thread(PrintHello, i);
        threads.push_back(t);
    }
    for(auto t : threads){
        t->join();
        delete t;
    }
}
