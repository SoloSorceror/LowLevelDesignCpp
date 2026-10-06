#include <iostream>
#include <thread>

using namespace std;

void print1() {
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout<<"\n";
}

void print2(){
    cout<<"---------------------------------------------------------------------------------------------------"<<endl;
    cout<<"\n";
}

int main() {
    thread t(print1);  // create a thread and run print()
    thread t2(print2);
    thread t3(print1);

    t.join();         // wait for the thread to finish
    t2.join();
    t3.join();

    cout << "Main thread finished" << endl;

    return 0;
}