
学习完这一章节，你将能写出最基本的 Haskell 代码。

# Hello World

Haskell和C语言一样，都是从 main 函数开始，从 main 函数结束（Hakell 中没有宏）。

现在我们来看一下最简单的 Haskell 程序。
> PS：代码保存在 codes 目录下。
```haskell
main = print "Hello World"
```
左边的 main 就是 main 函数，右边是想要运行的代码。可以考虑将 main 看成变量，右边的函数是表达式，在运行代码的时候，会默认运行 main 函数。

Haskell类似Python，是靠缩进来识别代码块的，也不需要在最后写分号，很像是数学表达式。

将上面的代码保存到 `helloworld.hs` 中，运行结果如下所示：
```
$> runhaskell helloworld.hs 
"Hello World"
```
这里的`Hello World`是被引号包裹住的，这个以后再介绍。

# 代码块

写了上面的例子，我们会迫不及待的想要增加一些功能。除了输出 `Hello World`，还想输出 1。我们可能就会构造出下面这种代码：
```haskell
main = print 1
       print 2
```

上面的写法是错的！！！

Haskell 如果想要写多行的代码，必须使用 do 来标记代码块。
```haskell
main = do
    print "Hello world"
    print 1

    if 1 == 1
        then do
            print 2
    else
        print 3

    let a = 1 + 1
    print a
```
需要注意的是在 Python 中，`if` 语句后有冒号，但在 Haskell 中没有冒号，而是用 then。

运行结果如下所示：
```haskell
$> "Hello world"
1
2
2
```
> PS：Haskell 是没有循环的，没有 for，也没有 while。你能想象一个没有循环的世界吗？

# 函数

在 Haskell 中，函数是第一等对象，是最复杂的。这里只简单的列举几种常见的函数形式。
- 无参数函数
- 有参数函数
```haskell
main = getting_started   -- main 和 getting_started 都是函数名，Haskell的函数名首字母必须小写。
                         -- Haskell以main作为函数入口，运行脚本后会自动运行main函数。

getting_started = do     -- 将一系列顺序操作的语句组成一起作为一个语句块
    -- 简单函数
    func1                       -- 无参数函数
    print (func2 2)             -- 有参数函数
    func3
    -- func3 = print "func3"    -- 只能在最外层定义函数

func1 = print "func1"
func2 x = x * 2
func3 = do
    print "func3"
    print "Hello world"
```
在`func2 x = x * 2`中，第一个 `x` 表示参数为 `x`，第二个 `x` 和 2 组成表达式，`x*2` 会被作为返回值返回。

---

以前写代码的之前总会思考一个问题，“这个是不是有人做过了？”。这个问题应该有两种答案，在不同情景使用不同的答案。
- 快速实现需求：
- 学习：不管别人是否做过，如果在**自己规划的学习路线**上，那么就细细研究。如果别人写得不好，尽力优化它。如果别人写得好，分析并学习它得优点。

第二种思维很重要，也是我自己很缺乏的，学东西总是浅尝则止。

自己尝试规划学习路线也非常重要，可以大致浏览`莫烦Python`的Youtube视频发布时间线，你能感觉到他在按照自己的节奏逐步的进步。

当然，上面的都是理论，自己一步一步践行才是硬道理。《让子弹再飞一会》中有句经典台词，步子别迈大了容易扯到蛋。