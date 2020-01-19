#include <iostream>
#include <thread>
#include <vector>
#include <sys/time.h>

class Wallet {
    int mMoney;
public:
    Wallet() : mMoney(0) {}

    int getMoney() { return mMoney; }

    void addMoney(int money) {
        for (int i = 0; i < money; ++i) {
            mMoney++;
        }
    }
};

int testMultithreadedWallet() {
    Wallet walletObject;
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.push_back(std::thread(&Wallet::addMoney, &walletObject, 1000));
    }

    for (int i = 0; i < threads.size(); i++) {
        threads.at(i).join();
    }
    return walletObject.getMoney();
}

int money;

void addMoney() {
//    std::this_thread::sleep_for(std::chrono::seconds(3));
    for (auto i = 0; i < 10; i++)
        money++;
}

void sleep(int time){
    std::this_thread::sleep_for(std::chrono::seconds(time));
    timeval t;
    gettimeofday(&t, nullptr);
    std::cout<<t.tv_sec<<std::endl;
}

class Client{
private:
    std::string name;
public:
    Client(std::string & name){
        this->name = name;
    }
    void displayName(){
        std::cout<<this->name<<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        timeval t;
        gettimeofday(&t, nullptr);
        std::cout<<t.tv_sec<<std::endl;
    }
};

class Wrapper{
private:
    Client *client;
public:
    Wrapper(std::string& name){
        this->client = new Client(name);
    }
    void doDisplay(){
//        std::thread(std::ref(Client::displayName), std::ref(this->client));
    }
};

int main() {
    money = 0;
    std::thread th1(std::ref(addMoney));
    std::thread th2(std::ref(addMoney));
    th1.detach();
    th2.detach();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout<<money<<std::endl;
    return 0;
}