#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "library.h"

// fixed size buffer based on assumptions about the maximum size that is likely necessary to exercise all aspects of the target function
// 固定缓冲区大小
#define SIZE 100

int main(int argc, char* argv[]) {
	// 将 lib_echo 和 lib_mul 分开（当然可以考虑写成两个文件）。
	if((argc == 2) && strcmp(argv[1], "echo") == 0) {
		// make sure buffer is initialized to eliminate variable behaviour that isn't dependent on the input.
		// 初始化缓冲区大小
		char input[SIZE] = {0};

		ssize_t length;
		length = read(STDIN_FILENO, input, SIZE);

		lib_echo(input, length);
	} else if ((argc == 2) && strcmp(argv[1], "mul") == 0) {
		// 从标准输入读取 4 个字节作为 int 值
		int a,b = 0;
		read(STDIN_FILENO, &a, 4);
		read(STDIN_FILENO, &b, 4);
		printf("%d\n", lib_mul(a,b));
	} else {
		printf("Usage: %s mul|echo\n", argv[0]);
	}
}