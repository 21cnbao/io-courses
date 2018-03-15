# CFQ and ionice
    $ sudo sh -c 'echo cfq > scheduler'
    $ sudo ionice -c 2 -n 0 cat /dev/sda > /dev/null &
    $ sudo ionice -c 2 -n 7 cat /dev/sda > /dev/null &
    $ sudo iotop
### 
