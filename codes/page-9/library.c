#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "library.h"

// 可能的漏洞类型:内存溢出
void lib_echo(char *data, ssize_t len){
	if(strlen(data) == 0) {
		return;
	}
	char *buf = calloc(1, len);
	strncpy(buf, data, len);
	printf("%s",buf);
	free(buf);

	// A crash so we can tell the harness is working for lib_echo
	// 假设的崩溃
	if(data[0] == 'p') {
		if(data[1] == 'o') {
			if(data[2] =='p') {
				if(data[3] == '!') {
					assert(0);
				}
			}
		}
	}
}

// 可能的漏洞：不满足功能（标准乘法运算）
int  lib_mul(int x, int y){
	if(x%2 == 0) {
		return y << x;

	} else if (y%2 == 0) {
		return x << y;

	} else if (x == 0) {
		return 0;

	} else if (y == 0) {
		return 0;

	} else {
		return x * y;

	}
}
