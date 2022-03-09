
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
   use GCC mode (afl-gcc/afl-g++) (or afl-clang/afl-clang++ for clang)
```


#