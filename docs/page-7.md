本篇文章的主要目标是熟悉 AFL 的基本使用，主要基于 afl-training 项目的源码。步子迈大了容易扯着蛋，一步步来。

# 基础

AFL 包含很多命令行工具，其中最核心的工具就是 `afl-fuzz`。简化的 AFL 原理如下所示

![](./images/5.png)

通过图片可知，AFL 需要运行起来需要准备以下的东西：
```
1、变异初始的种子。
2、插桩后的二进制程序。
```

# 实战

下载 afl-training，并进入 quickstart 目录
```
git clone https://github.com/mykter/afl-training.git
cd afl-training/quickstart
```
在 quickstart 文件夹中，已经准备好了变异使用的种子（inputs 目录下），还有用来模糊测试的源码（vulerable.c），所以我们只需要准备一个插桩后的二进制程序即可。

AFL提供了编译工具（afl-gcc、afl-clang、afl-clang-fast 等等），可以将源码编译成插桩后的二进制程序。这里我们使用AFL提供的编译器来生成可执行文件：
```bash
CC=afl-clang-fast AFL_HARDEN=1 make
# CC 是 Makefile 的变量，用于指定编译器。
# AFL_HARDEN：促使 CC 自动化代码加固，试得检测简单的内存 bug 更加容易。
# make 后不跟任何参数，默认生成第一个目标，此处第一个目标是 all。
```
运行二进制程序，并尝试输入数据（简单探索一下目标，分析入口点）。
```bash
$ ./vulnerable
# Press enter to get usage instructions.
# Test it on one of the provided inputs:
$ ./vulnerable < inputs/u
```
进行模糊测试。
```bash
$ afl-fuzz -i inputs -o out ./vulnerable
```
我运行 21 分钟的效果如下所示（生成了 9 个 uniq crash）：
![](./images/6.jpg)

# 分析

afl-training 教程到这里就没有东西了，但总觉得缺少点什么。



参考文档：
- [[Fuzzing with AFL] Fuzzing simple C program with AFL on Linux](https://www.youtube.com/watch?v=NiGC1jxFx78&list=PLHGgqcJIME5kYhOSdJjvtVS4b4_OXDqM-&index=2)
- [Damn_Vulnerable_C_Program](https://github.com/hardik05/Damn_Vulnerable_C_Program)
- [Fuzzing with AFL workshop](https://github.com/mykter/afl-training)

