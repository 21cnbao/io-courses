# CFQ and ionice
    $ sudo sh -c 'echo cfq > scheduler'
    $ sudo ionice -c 2 -n 0 cat /dev/sda > /dev/null &
    $ sudo ionice -c 2 -n 7 cat /dev/sda > /dev/null &
    $ sudo iotop
### 对比第1个cat和第2个cat的速度差异

# libevent例子
    $ gcc event-exam.c -lev
http://mp.weixin.qq.com/s/Xp4-r-a2iWpDx_yntGIGOQ

# epoll例子
    $ gcc epoll.c
### 等待输入回车

