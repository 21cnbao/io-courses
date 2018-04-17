# 1. aio例子
    $ gcc aio.c -laio
    $ ./a.out epoll.c

# 2. libevent例子
    $ gcc event-exam.c -lev
http://mp.weixin.qq.com/s/Xp4-r-a2iWpDx_yntGIGOQ

# 3. epoll例子
    $ gcc epoll.c
### 等待输入回车

# 4. blktrace, blkparse
### 按照视频提示

# 5. debugfs, blkcat, dd
### 按照视频提示

# 6. bio生命周期
http://mp.weixin.qq.com/s/aghkAAv1hxR9sMce3Z69Zw

# 7. CFQ and ionice
    $ sudo sh -c 'echo cfq > scheduler'
    $ sudo ionice -c 2 -n 0 cat /dev/sda > /dev/null &
    $ sudo ionice -c 2 -n 7 cat /dev/sda > /dev/null &
    $ sudo iotop
### 对比第1个cat和第2个cat的速度差异

# 8. fuse例子
    $ sudo apt-get install libfuse-dev
    $ gcc -D_FILE_OFFSET_BITS=64 hello.c  -lfuse
    $ mkdir mnt
    $ ./a.out mnt
    $ cd mnt/
    $ ls
    hello
### 之后我们查看mount情况：
    $ mount
    /dev/sda1 on / type ext4 (rw,errors=remount-ro)
    ...
    a.out on /home/baohua/develop/training/io-courses/fuse-hello/mnt type fuse.a.out (rw,nosuid,nodev,user=baohua)
    
 # 9. 让文件系统不一致
    #dumpe2fs

    #dd if=image bs=4096 skip=18 | hexdump -C -n 32

 ###vim二进制编辑：
     %!xxd -g 1
     %!xxd -r  
 
