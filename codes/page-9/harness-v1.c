#include "library.h"
#include <string.h>
#include <stdio.h>

void main() {
    // 尝试调用函数（程序没有外部输入）。
    char *data = "Some input data\n";
    lib_echo(data, strlen(data));
    printf("%d\n", lib_mul(1,2));
}