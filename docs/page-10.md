前一篇文章学习了如何编写 Harness，这一篇文章尝试使用 AFL 对 libxml2 进行模糊测试。（尝试利用模糊测试得出 1 day）

---

# Harness编写

这里复习一下前面所学的 Harness，编写 Harness 可以按照以下的步骤来编写。
1. 写出依赖库的简单用法。
2. 控制一些无关变量，并在上一步的基础上增加输入。
3. 合理利用 Fuzzer 工具的特性，提升 Fuzz 速度。

## 简单使用

首先安装 afl-training 所说的，先编译 libxml2 库，然后再使用。
```bash
# 下载子模块
git submodule init && git submodule update
cd libxml2
# 指定编译器，并生成makefile
CC=afl-clang-fast ./autogen.sh
# 使用ASAN模式来编译
AFL_USE_ASAN=1 make -j 4

# 为了方便编写代码，我把依赖库安装到本地了。
# 安装 libxml2
sudo make install
# 卸载 libxml2
```
再到网上找一些简单的使用案例：
**1、创建 xml**
```c
// example1.c
#include<stdio.h>
#include<libxml/parser.h>
#include<libxml/tree.h>


int main(int argc, char **argv){
    // 因为总是要在 xmlChar* 和char*之间进行类型转换，所以定义了一个宏 BAD_CAST
    // #define BAD_CAST (xmlChar *)
    xmlDocPtr doc = xmlNewDoc(BAD_CAST"1.0");
    xmlNodePtr rootNode = xmlNewNode(NULL, BAD_CAST"root");
    printf("success\n");
    xmlFreeDoc(doc);
    return 0;
}
```
编译运行
 
```bash
afl-clang-fast example1.c -I libxml2/include/ -lxml2 -o example1
./example1
# 输出 success
```
**2、解析 xml**
```c
// example2.c
#include<stdio.h>
#include<libxml/parser.h>
#include<libxml/tree.h>

// question：为什么Harness只是对文件进行初始化后就释放了？（answer：这个位置可探索的路径多，如果写得比较多就很难判断漏洞的位置）
// 攻击面？我尝试了以下创建文件，也找到了crash但不会判断是否存在漏洞。
int main(int argc, char **argv){
    xmlDocPtr doc = xmlReadFile("test.xml", NULL, 0);
    if(doc != NULL){
        xmlFreeDoc(doc);
    }
}
// 创建 test.xml 并在里面写入一个简单的xml。
```
编译运行
 
```bash
afl-clang-fast example2.c -I libxml2/include/ -lxml2 -o example1
./example2
# 输出 success
```

# harness

**harness-v1.c**

在使用的基础上，增加输入功能就可以得到 Harness 了。
```c
// harness-v1.c
#include<stdio.h>
#include<libxml/parser.h>
#include<libxml/tree.h>
#include<unistd.h>

#define SIZE 50

int main(int argc, char **argv){
    // 因为总是要在 xmlChar* 和char*之间进行类型转换，所以定义了一个宏 BAD_CAST
    // #define BAD_CAST (xmlChar *)
    
    char input[SIZE] = {0};
    read(STDIN_FILENO, input, SIZE);

    xmlDocPtr doc = xmlNewDoc(BAD_CAST"1.0");
    xmlNodePtr rootNode = xmlNewNode(NULL, BAD_CAST input);
    xmlFreeDoc(doc);
    
    return 0;
}
```
编译，Fuzz
```bash
# TODO
# 我最开始使用的这种命令来编译运行，结果发现一直无法找到新路径（last new path : none yet (odd, check syntax!)），不清楚具体原因
AFL_USE_ASAN=1 afl-clang-fast ./harness-v1.c -I /usr/local/include/libxml2 -lxml2 -o harness
# 参考 answer 的编译命令
AFL_USE_ASAN=1 afl-clang-fast ./harness-v1.c -I libxml2/include libxml2/.libs/libxml2.a -lz -lm -o harness
# fuzz（标准输入获取数据）
mkdir in
cd in && echo "<hi><hi/>" > hi.xml && cd ..
afl-fuzz -m none -i in/ -o out -x ~/Documents/AFLplusplus/dictionaries/xml.dict ./harness
# TODO：一直处在崩溃的状态，不懂得如何处理
```
运行结果
![](./images/12.jpg)


**harness-v2.c**

同理，可以将 example2.c 改写成 harness-v2.c
```c
// harness-v2.c
#include<stdio.h>
#include<libxml/parser.h>
#include<libxml/tree.h>
#include<unistd.h>

int main(int argc, char **argv){
    // 因为总是要在 xmlChar* 和char*之间进行类型转换，所以定义了一个宏 BAD_CAST
    // #define BAD_CAST (xmlChar *)

    xmlDocPtr doc = xmlReadFile(argv[1], NULL, 0);
    if(doc != NULL){
        xmlFreeDoc(doc);
    }
    
    return 0;
}
```
编译，并尝试fuzz
```bash
AFL_USE_ASAN=1 afl-clang-fast ./harness-v2.c -I libxml2/include libxml2/.libs/libxml2.a -lz -lm -o harness

# 注意！！文件输入和标准输入不同，文件输入需要使用 @@ 来代替文件名
afl-fuzz -m none -i in/ -o out -x ~/Documents/AFLplusplus/dictionaries/xml.dict ./harness @@ 
```

# 改进Harness



# 语料库





# 总结

Harness 的编写，字典的收集都还是一个难点。后续的例子尽可能往这两个方向去学习吧。


参考文档：
- [c++ libxml2 简明入门使用教程](https://blog.csdn.net/joelcat/article/details/78643799)
- [libxml2生成，解析，修改xml文件，以及使用实例](https://blog.csdn.net/hpu11/article/details/80793303)