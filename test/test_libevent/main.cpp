#include "nonblocking.hpp"
#include "log.hpp"

int main(int c, char **v) {
    setvbuf(stdout, nullptr, _IONBF, 0);
    run();
    return 0;
}