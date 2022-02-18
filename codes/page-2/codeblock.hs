main = do
    print "Hello world"
    print 1

    if 1 == 1               -- 注意没有引号
        then do
            print 2
    else
        print 3

    let a = 1+1
    print a