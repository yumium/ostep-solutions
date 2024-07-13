#include <string.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    const int file_descriptor = open("./example.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (file_descriptor < 0)
    {
        std::cerr << "Error: File could not be opened." << std::endl;
        return 1;
    }

    const int N = 1'000'000;

    /*
    Initially you see a string of 1s. I believe this is when the child process is being created.
    The interleaving 0s and 1s is probably from both processes asking for the file lock, and CPU alternating control.
    The string of 0s at the end is the child process writing as the parent is finished.
    */
    const auto rc = fork();
    if (rc < 0) {
        std::cerr << "Forking failed." << std::endl;
        return 1;
    } else if (rc == 0) {
        for (size_t i = 0; i < N; i++)
        {
            write(file_descriptor, "0", strlen("0"));
        }
    } else {
        for (size_t i = 0; i < N; i++)
        {
            write(file_descriptor, "1", strlen("1"));
        }
    }

    return 0;
}