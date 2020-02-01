#include <iostream>

using namespace std;

class ASingleton {
public:
    static ASingleton* getInstance() {
        return &m_data;
    }

    void do_something() {
        cout << "ASingleton do_something!" << endl;
    }


private:
    ~ASingleton();
    static ASingleton m_data;//static data member 在类中声明，在类外定义
    ASingleton();

};

class BSingleton {
public:
    static BSingleton *getInstance() {
        return &m_data;
    }

    void do_something() {
        cout << "BSingleton do_something!" << endl;
    }

protected:
    static BSingleton m_data;

    //static data member 在类中声明，在类外定义
    BSingleton();

};

ASingleton ASingleton::m_data;
BSingleton BSingleton::m_data;

ASingleton::ASingleton() {
    cout << "ASingleton constructor!" << endl;
    BSingleton::getInstance()->do_something();
}

ASingleton::~ASingleton() {

}

BSingleton::BSingleton() {
    cout << "BSingleton constructor!" << endl;
}