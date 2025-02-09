# memset

# programs

1. memset_1.S : default
2. memset_2.S : use sw
3. memset_3.S : avoid misalined access

### test

1. compile test.c (```make compile```)
2. set CMD_SPIKE in test.py 
3. run test.py

```sh
$ python3 test.py misalign memset_num

misalign    : create misalign pointer
memset_num  : selector of memset_N
```

sample
```sh
$ python3 test.py 1 1 # test memset_1 with misaligned pointer
```