
CC=afl-clang-fast
# -g：启用调试信息
# -w：不生成任何警告信息。
# AFL_HARDEN：促使CC自动化代码加固，试得检测简单的内存bug更加容易。
CFLAGS = -g -w

all:	vulnerable

clean:
	rm -f vulnerable

vulnerable: vulnerable.c
	${CC} ${CFLAGS} vulnerable.c -o vulnerable