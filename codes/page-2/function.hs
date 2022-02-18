main = getting_started   -- main 和 getting_started 都是函数名，Haskell的函数名首字母必须小写。
                         -- Haskell以main作为函数入口，运行脚本后会自动运行main函数。

getting_started = do     -- 将一系列顺序操作的语句组成一起作为一个语句块
    -- 简单函数
    func1                       -- 无参数函数
    print (func2 2)             -- 有参数函数
    -- func3 = print "func3"    -- 只能在最外层定义函数

func1 = print "func1"
func2 x = x * 2
func3 = do
    print "func3"
    print "Hello world"
