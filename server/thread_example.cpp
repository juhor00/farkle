#include <iostream>
#include <thread>
#include <vector>
#include <memory>

using namespace std;

const int THREAD_COUNT = 3;


void PrintHello(int id) {

   cout << "Thread ID : " << id << endl;
   return;

}


void test()
{
    for (int i=0; i<THREAD_COUNT; i++){
        cout << "Creating thread " << i << endl;
        thread t(&PrintHello, i);
        t.detach();
    }
}
