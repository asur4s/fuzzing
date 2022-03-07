
前面都是针对 libxml2 进行模糊测试，这次对二进制程序进行模糊测试。
> PS：通常二进制程序是由一个或多个依赖库组成。 

这篇文章主要是根据 fuzzing010 改编，他的内容主要针对新手，而我的文章则会把前面用过的内容再用一次。

# 下载并且构建目标

下载 xpdf
```bash
# 根据自己喜好创建目录  
cd $HOME/Documents
mkdir fuzzingXpdf && cd fuzzingXpdf/
# 下载构建工具
sudo apt install build-essential
# 下载 Xpdf 3.02：
wget https://dl.xpdfreader.com/old/xpdf-3.02.tar.gz
tar -xvzf xpdf-3.02.tar.gz
```
构建目标并简单使用
```bash
# 构建 Xpdf（--prefix指定安装目录）
./configure --prefix="$HOME/Documents/fuzzingXpdf/install/"
# -j 4 为了加快 make 速度。
make -j 4
make install


# 下载一些 PDF 示例X
cd $HOME/Documents/fuzzingXpdf
mkdir pdfExamples && cd pdfExamples
wget https://github.com/mozilla/pdf.js-sample-files/raw/master/helloworld.pdf
wget http://www.africau.edu/images/default/sample.pdf
wget https://www.melbpc.org.au/wp-content/uploads/2017/10/small-example-pdf-file.pdf


# 测试 pdfinfo
cd ~/Documents/fuzzingXpdf
./install/bin/pdfinfo -box -meta ./pdfExamples/helloworld.pdf
# 测试 pdftotext
 ./install/bin/pdftotext ./pdfExamples/helloworld.pdf output.txt
 cat output.txt
```

# 对目标进行模糊测试

在 Fuzzing010 中，并没有使用 ASAN，而是直接使用 gdb。我还是继续使用 ASAN 叭，方便对 crash 进行判断。首先对二进制程序重新编译
```bash
# 清空
cd ~/Documents/fuzzingXpdf
rm -rf install
cd ~/Documents/fuzzingXpdf/xpdf-3.02
make clean

# 重新编译
# configure 只是生成 makefile
CC=afl-clang-fast CXX=afl-clang-fast++ ./configure --prefix="$HOME/Documents/fuzzingXpdf/install/"
# 设置ASAN模式
AFL_USE_ASAN=1 make -j 4
make install
```
对二进制程序进行模糊测试
```bash
# 多核并行fuzzing，并且使用了 AFLplusplus 提供的字典。
afl-fuzz -i pdfExamples/ -o out -s 123 -x ~/Documents/AFLplusplus/dictionaries/pdf.dict -D -M fuzzer1 -- ./install/bin/pdftotext @@ output
afl-fuzz -i pdfExamples/ -o out -s 234 -x ~/Documents/AFLplusplus/dictionaries/pdf.dict -S fuzzer2 -- ./install/bin/pdftotext @@ output2
```

Fuzzing010 的作者只用了 18 分钟 Orz，我用了 30 分钟跑出 crash

![](./images/21.jpg)


# crash

崩溃信息 1（CVE-2020-19468—PDF2Json，PDF2Json是基于Xpdf的转换库）
```
==1270173==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000000 (pc 0x00000062ffd0 bp 0x7fffdc0e9830 sp 0x7fffdc0e9400 T0)
==1270173==The signal is caused by a READ memory access.
==1270173==Hint: address points to the zero page.
    #0 0x62ffd0 in EmbedStream::getChar() /home/joe/Documents/fuzzingXpdf/xpdf-3.02/xpdf/Stream.cc:787:15
    #1 0x512fa4 in Gfx::opBeginImage(Object*, int) /home/joe/Documents/fuzzingXpdf/xpdf-3.02/xpdf/Gfx.cc:3880:37
    #2 0x52a8f2 in Gfx::go(int) /home/joe/Documents/fuzzingXpdf/xpdf-3.02/xpdf/Gfx.cc:581:7
    #3 0x529e29 in Gfx::display(Object*, int) /home/joe/Documents/fuzzingXpdf/xpdf-3.02/xpdf/Gfx.cc:553:3
    #4 0x61c938 in Page::displaySlice(OutputDev*, double, double, int, int, int, int, int, int, int, int, Catalog*, int (*)(void*), void*) /home/joe/Documents/fuzzingXpdf/xpdf-3.02/xpdf/Page.cc:317:10
    #5 0x61c311 in Page::display(OutputDev*, double, double, int, int, int, int, Catalog*, int (*)(void*), void*) /home/joe/Documents/fuzzingXpdf/xpdf-3.02/xpdf/Page.cc:264:3
    #6 0x623939 in PDFDoc::displayPage(OutputDev*, int, double, double, int, int, int, int, int (*)(void*), void*) /home/joe/Documents/fuzzingXpdf/xpdf-3.02/xpdf/PDFDoc.cc:317:27
    #7 0x623939 in PDFDoc::displayPages(OutputDev*, int, int, double, double, int, int, int, int, int (*)(void*), void*) /home/joe/Documents/fuzzingXpdf/xpdf-3.02/xpdf/PDFDoc.cc:330:5
    #8 0x6a443b in main /home/joe/Documents/fuzzingXpdf/xpdf-3.02/xpdf/pdftotext.cc:237:10
    #9 0x7fab79d7e0b2 in __libc_start_main /build/glibc-sMfBJT/glibc-2.31/csu/../csu/libc-start.c:308:16
    #10 0x41d5fd in _start (/home/joe/Documents/fuzzingXpdf/asanInstall/bin/pdftotext+0x41d5fd)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV /home/joe/Documents/fuzzingXpdf/xpdf-3.02/xpdf/Stream.cc:787:15 in EmbedStream::getChar()
==1270173==ABORTING
```

崩溃信息 2（CVE-2019-13288）
```
==1431786==ERROR: AddressSanitizer: stack-overflow on address 0x7ffcb9150fa0 (pc 0x7f829f7088b1 bp 0x7ffcb9151460 sp 0x7ffcb9150ef0 T0)
    #0 0x7f829f7088b1 in __vfprintf_internal /build/glibc-sMfBJT/glibc-2.31/stdio-common/vfprintf-internal.c:1289:1
    #1 0x7f829f70bed1 in buffered_vfprintf /build/glibc-sMfBJT/glibc-2.31/stdio-common/vfprintf-internal.c:2377:12
    #2 0x7f829f708d53 in __vfprintf_internal /build/glibc-sMfBJT/glibc-2.31/stdio-common/vfprintf-internal.c:1346:12
    #3 0x43ce40 in fprintf (/home/joe/Documents/fuzzingXpdf/asanInstall/bin/pdftotext+0x43ce40)
    #4 0x4f7554 in error(int, char*, ...) /home/joe/Documents/fuzzingXpdf/xpdf-3.02/xpdf/Error.cc:29:5
    #5 0x61f567 in Parser::getObj(Object*, unsigned char*, CryptAlgorithm, int, int, int) /home/joe/Documents/fuzzingXpdf/xpdf-3.02/xpdf/Parser.cc:76:2
    #6 0x61f8fd in Parser::getObj(Object*, unsigned char*, CryptAlgorithm, int, int, int) /home/joe/Documents/fuzzingXpdf/xpdf-3.02/xpdf/Parser.cc:85:20
    #7 0x69d1e4 in XRef::fetch(int, int, Object*) /home/joe/Documents/fuzzingXpdf/xpdf-3.02/xpdf/XRef.cc:823:13
    #8 0x6210c9 in Object::dictLookup(char*, Object*) /home/joe/Documents/fuzzingXpdf/xpdf-3.02/xpdf/./Object.h:253:18
    #9 0x6210c9 in Parser::makeStream(Object*, unsigned char*, CryptAlgorithm, int, int, int) /home/joe/Documents/fuzzingXpdf/xpdf-3.02/xpdf/Parser.cc:156:9
    #10 0x61fd71 in Parser::getObj(Object*, unsigned char*, CryptAlgorithm, int, int, int) /home/joe/Documents/fuzzingXpdf/xpdf-3.02/xpdf/Parser.cc:94:18
    #11 0x69d1e4 in XRef::fetch(int, int, Object*) /home/joe/Documents/fuzzingXpdf/xpdf-3.02/xpdf/XRef.cc:823:13
    #12 0x6210c9 in Object::dictLookup(char*, Object*) /home/joe/Documents/fuzzingXpdf/xpdf-3.02/xpdf/./Object.h:253:18
    #13 0x6210c9 in Parser::makeStream(Object*, unsigned char*, CryptAlgorithm, int, int, int) /home/joe/Documents/fuzzingXpdf/xpdf-3.02/xpdf/Parser.cc:156:9
    #14 0x61fd71 in Parser::getObj(Object*, unsigned char*, CryptAlgorithm, int, int, int) /home/joe/Documents/fuzzingXpdf/xpdf-3.02/xpdf/Parser.cc:94:18
    #15 0x69d1e4 in XRef::fetch(int, int, Object*) /home/joe/Documents/fuzzingXpdf/xpdf-3.02/xpdf/XRef.cc:823:13
    #16 0x6210c9 in Object::dictLookup(char*, Object*) /home/joe/Documents/fuzzingXpdf/xpdf-3.02/xpdf/./Object.h:253:18
    #17 0x6210c9 in Parser::makeStream(Object*, unsigned char*, CryptAlgorithm, int, int, int) /home/joe/Documents/fuzzingXpdf/xpdf-3.02/xpdf/Parser.cc:156:9
    #18 0x61fd71 in Parser::getObj(Object*, unsigned char*, CryptAlgorithm, int, int, int) /home/joe/Documents/fuzzingXpdf/xpdf-3.02/xpdf/Parser.cc:94:18
    #19 0x69d1e4 in XRef::fetch(int, int, Object*) /home/joe/Documents/fuzzingXpdf/xpdf-3.02/xpdf/XRef.cc:823:13
……此处省略x千字
  

SUMMARY: AddressSanitizer: stack-overflow /build/glibc-sMfBJT/glibc-2.31/stdio-common/vfprintf-internal.c:1289:1 in __vfprintf_internal
==1431786==ABORTING
```
