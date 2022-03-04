前一篇文章学习了如何编写 Harness，这一篇文章尝试使用 AFL 对 libxml2 进行模糊测试。（尝试利用模糊测试得出 1 day）

---

# Harness编写

这里复习一下前面所学的 Harness，编写 Harness 可以按照以下的步骤来编写。
1. 写出依赖库的简单用法。
2. 控制一些无关变量，并在上一步的基础上增加输入。
3. 合理利用 Fuzzer 工具的特性，提升 Fuzz 速度。

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
再到网上找

# 总结

Harness 的编写，字典的收集都还是一个难点。后续的例子尽可能往这两个方向去学习吧。


参考文档：
- [c++ libxml2 简明入门使用教程](https://blog.csdn.net/joelcat/article/details/78643799)
- [libxml2生成，解析，修改xml文件，以及使用实例](https://blog.csdn.net/hpu11/article/details/80793303)