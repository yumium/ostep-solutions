#include <string.h>
#include <iostream>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int x = 100;
    const auto rc = fork();
    if (rc < 0) {
        printf("Forking failed.");
        return 1;
    } else if (rc == 0) {
        x += 1;
        printf("This is the child (pid: %d). x = %d\n", (int) getpid(), x);
    } else {
        x += 1;
        printf("This is the parent process (pid: %d) for child (pid: %d). x = %d\n", (int) getpid(), (int) rc, x);
    }

    return 0;
}