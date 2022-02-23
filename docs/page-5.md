
AFL++ 是基于 AFL 进行拓展的一个项目，将 AFL 相关的项目整合到一起。其主要是由 C 语言编写，因此建议选择采用 Linux 来搭建相关的环境。

这里推荐采用 Ubuntu 20.04，后面在实践 Fuzz101 项目的时候会比较方便。

我在安装的时候遇到了以下的问题。

**1、Ubuntu切换国内源**

Ubuntu 20.04 的源和 16.04 的源不一样，采用 16.04 会出现一些比较奇怪的错误（找不到依赖啥的），建议改用下面的源
```
deb http://mirrors.aliyun.com/ubuntu/ focal main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ focal main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ focal-security main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ focal-security main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ focal-updates main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ focal-updates main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ focal-proposed main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ focal-proposed main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ focal-backports main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ focal-backports main restricted universe multiverse
```
相关的命令有：
```bash
sudo cp /etc/apt/sources.list /etc/apt/sources.list.backup
vim /etc/apt/sources.list
sudo apt update
sudo apt-upgrade
```

**2、UnicornAFL报错**

切换源之后，就可以安装相关的依赖了。
```bash
sudo apt-get update
sudo apt-get install -y build-essential python3-dev automake cmake git flex bison libglib2.0-dev libpixman-1-dev python3-setuptools
# try to install llvm 11 and install the distro default if that fails
sudo apt-get install -y lld-11 llvm-11 llvm-11-dev clang-11 || sudo apt-get install -y lld llvm llvm-dev clang
sudo apt-get install -y gcc-$(gcc --version|head -n1|sed 's/.* //'|sed 's/\..*//')-plugin-dev libstdc++-$(gcc --version|head -n1|sed 's/.* //'|sed 's/\..*//')-dev
sudo apt-get install -y ninja-build # for QEMU mode
git clone https://github.com/AFLplusplus/AFLplusplus
```
然后进入AFL++的文件夹进行编译安装
```bash
cd AFLplusplus
make distrib        # UnicornAFL 的测试会报错，可以暂时不用管。作者只适配了 16.04 版，而我也比一定会使用，战略性放弃，可以直接 install，不会影响使用。
sudo make install
```

**三、测试是否安装成功**

首先创建一个`in`文件夹，在in文件夹中里面创建一个文件并写入任意数据，然后使用下面的命令判断AFL是否正常安装。
```bash
sudo bash -c "echo core >/proc/sys/kernel/core_pattern"        # 修改崩溃后转储的方式。
afl-fuzz -Q -m none -i in -o out test @@
```
如果AFL成功安装，即可出现如下图所示的状态
![](./images/4.jpg)

参考文档：
- [ubuntu20.04 LTS 更换国内163源、阿里源、清华源、中科大源](https://www.cnblogs.com/zqifa/p/12910989.html)
- [Building and installing AFL++](https://github.com/AFLplusplus/AFLplusplus/blob/stable/docs/INSTALL.md)
- [AFL++实战（一）-黑盒测试FFmpeg](https://blog.csdn.net/qq_36711003/article/details/107016408?spm=1001.2014.3001.5502)
- [Ubuntu 20.04.3 LTS (Focal Fossa)](https://releases.ubuntu.com/20.04.3/)
