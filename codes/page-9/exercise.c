#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "library.h"

// fixed size buffer based on assumptions about the maximum size that is likely necessary to exercise all aspects of the target function
#define SIZE 100

int main(int argc, char* argv[]) {

        char input[SIZE] = {0};
        // 打开指定文件并将其内容读入缓冲区。
        FILE *fp = fopen(argv[1],"r");
        // size_t在32位架构上是4字节，在64位架构上是8字节
        ssize_t length;
        // fread(void *buffer, size_t size, size_t count, FILE * stream);
        // buffer为接收数据的地址，size为一个单元的大小，count为单元个数，stream为文件流。
        // 从文件中读取的数据大小为 length * 1。
        fread(input, length, 1, fp);

        lib_echo(input, length);
        fclose(fp);
}