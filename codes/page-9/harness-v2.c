// 测试 lib_echo 函数（控制一些不是很关键的变量）
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "library.h"

// fixed size buffer based on assumptions about the maximum size that is likely necessary to exercise all aspects of the target function
// 固定缓冲区大小，设置最大值是必要的。
#define SIZE 50

int main() {

	// make sure buffer is initialized to eliminate variable behaviour that isn't dependent on the input.
	// 初始化缓冲区大小，消除不依赖于变量的行为（控制变量）
	char input[SIZE] = {0};

	ssize_t length;
	// 从标准输入读取数据。数据存入 input 数组，数组长度为 SIZE。
	length = read(STDIN_FILENO, input, SIZE);

	lib_echo(input, length);
}