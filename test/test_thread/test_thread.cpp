#include <iostream>
#include <thread>

using namespace std;

class B{
private :
    int m_int;
public:
    B(const int& a):m_int(a){

    }
    void print(int b){
        cout<<this->m_int<<endl;
        cout<<b<<endl;
    }
};

class A {
private:
    B b;
public:
    A(int i):b(B(i)){

    }
    void APrint(int i){
        thread th1(&B::print, this->b, i);
        th1.detach();
    }
};

int main(){
    A a(4);
    a.APrint(5);
    this_thread::sleep_for(chrono::seconds(1));
}