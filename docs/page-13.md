
案例来自 Fuzzing010

# 如何选择插桩工具？

在这个案例中主要是学习了如何选择插桩工具。翻译如下所示

```
+--------------------------------+
| clang/clang++ 11+  | --> 使用 LTO 模式 (afl-clang-lto/afl-clang-lto++)
+--------------------------------+    具体查看 https://github.com/AFLplusplus/AFLplusplus/blob/stable/instrumentation/README.lto.md
    |
    | 如果不满足条件，或者如果目标无法使用 LTO 模式
    |
    v
+---------------------------------+
| clang/clang++ 6.0+ | -->  使用 LLVM 模式(afl-clang-fast/afl-clang-fast++)
+---------------------------------+   具体查看 https://github.com/AFLplusplus/AFLplusplus/blob/stable/instrumentation/README.llvm.md
    |
    | 如果不满足条件
    |
    v
 +--------------------------------+
 | gcc 5+           | -> 使用 GCC_PLUGIN 模式 (afl-gcc-fast/afl-g++-fast)
 +--------------------------------+    具体查看 https://github.com/AFLplusplus/AFLplusplus/blob/stable/instrumentation/README.gcc_plugin.md
    |
    | 如果不满足条件
    |
    v
   使用 GCC 模式 (afl-gcc/afl-g++) (or afl-clang/afl-clang++ for clang)
```


# 编译使用

= =，Fuzzing010 教程每次都使用 gcc 先编译一次，删除后再使用插桩工具编译（应该是为了确保程序能正常编译）。我这直接偷懒使用插桩工具安装了。

```bash
# 创建文件夹
cd $HOME/2022
mkdir fuzzing_libexif && cd fuzzing_libexif/
# 下载 libexif
wget https://github.com/libexif/libexif/archive/refs/tags/libexif-0_6_14-release.tar.gz
tar -xzvf libexif-0_6_14-release.tar.gz
# 安装依赖
sudo apt-get install autopoint libtool gettext libpopt-dev
# 编译
autoreconf -fvi
CC=afl-clang-lto ./configure --enable-shared=no --prefix="$HOME/2022/fuzzing_libexif/install/"
make -j 4
make install
# 我在make install的时候发现有error信息，不过可以正常得到依赖文件，就没管了
```

下载并编译 Harness（调用该 libexif 的应用程序）
```bash
# 下载并解压
cd $HOME/2022/fuzzing_libexif
wget https://github.com/libexif/exif/archive/refs/tags/exif-0_6_15-release.tar.gz
tar -xzvf exif-0_6_15-release.tar.gz

# 编译安装
cd exif-exif-0_6_15-release/
autoreconf -fvi
./configure --enable-shared=no --prefix="$HOME/2022/fuzzing_libexif/install/" PKG_CONFIG_PATH="$HOME/2022/fuzzing_libexif/install/lib/pkgconfig"
make -j 4
make install
```

尝试简单使用
```bash
./install/bin/exif
```

下载测试种子
```bash
sudo apt install unzip

cd $HOME/2022/fuzzing_libexif
wget https://github.com/ianare/exif-samples/archive/refs/heads/master.zip
unzip master.zip
# 测试
./install/bin/exif ./exif-samples-master/jpg/Canon_40D_photoshop_import.jpg
```

# 模糊测试


# crash
