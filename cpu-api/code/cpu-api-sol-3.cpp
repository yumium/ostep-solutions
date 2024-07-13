#include <string.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

// TODO (yzai) learn deeper about these sys calls; learn `open()` and `spawn()`; check how we can ensure order without using wait(); 
// then finish rest of exercises, learning the relevant sys calls as needed 
int main(int argc, char* argv[])
{
    const auto rc = fork();
    if (rc < 0) {
        std::cerr << "Forking failed." << std::endl;
        return 0;
    } else if (rc == 0) {
        std::cout << "Hello" << std::endl;
    } else {
        wait(NULL);
        std::cout << "Goodbye" << std::endl;
    }
}