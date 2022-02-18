
# Haskell编程环境

这里摘抄一段关于编程环境的描述：
> 在Haskell语言的众多实现中，有两个被广泛应用，Hugs和GHC。其中Hugs是一个解析器，主要用于教学。而GHC(Glasgow Haskell Compiler)更加注重实践，它编译成本地代码，支持并行执行，并带有更好的性能分析工具和调试工具。由于这些因素，在本书中我们将采用GHC。
>
>GHC主要有三个部分组成。
> - ghc是生成快速本底代码的优化编译器。
> - ghci是一个交互解析器和调试器。
> - runghc是一个以脚本形式(并不要首先编译)运行Haskell代码的程序。

在学习过程中，最常用的应该是`ghc`和`runghc`。

# Ubuntu

直接使用 apt 命令下载
```sh
sudo apt install haskell-platform
```
Haskell Platform 是软件包、工具和依赖库的集合。

# Windows

需要使用 chocolate 安装
```sh
choco install haskell-dev haskell-stack
```