#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Location of frame: %p\n", main);

    auto* x = new int(1);
    printf("Location of heap: %p\n", x);

    int y = 0;
    printf("Location of stack: %p\n", &y);
}
