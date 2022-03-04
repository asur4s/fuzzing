#include <stdio.h>
#include <unistd.h>
#include "library.h"

#define SIZE 108

int main(int argc, char *argv[])
{
    char input[SIZE] = {0};
    int a, b;
    read(STDIN_FILENO, &a, 4);
    read(STDIN_FILENO, &b, 4);
    printf("%d\n", lib_mul(a, b));

    ssize_t length;
    length = read(STDIN_FILENO, input, SIZE);
    lib_echo(input, length);

}