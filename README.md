# MUS & SUS

## MUS の表示

```
$ make main
$ ./main abacbabcabca
 1  2  3  4  5  6  7  8  9 10 11 12 
 a  b  a  c  b  a  b  c  a  b  c  a 
|-------||----|      |-------|
      |----||-------|
number of MUSs: 5
3
2
2
3
3
```

## MUS および LS, SS の表示

```
$ make SS
$ ./SS abacbabcabca
 1  2  3  4  5  6  7  8  9 10 11 12 
 a  b  a  c  b  a  b  c  a  b  c  a 
|-------||----|      |-------|
      |----||-------|
number of MUSs: 5
Longest Repeating Suffix (LS): 
                        |----------|
Shortest occ \leq 2 Suffix (SS): 
                              |----|
```

## k-mismatch MUS の表示

```
$ make kmis
$ ./kmis abacbabcabca 2    # ./kmis (string) (number of mismatchs permitted)
 1  2  3  4  5  6  7  8  9 10 11 12 
 a  b  a  c  b  a  b  c  a  b  c  a 
|----------------|
         |-------------------|
number of 2-MUSs: 2
```

## スライド窓内の MUS の表示

```
$ make slide
$ ./slide abacbabcabca 4    # ./slide (string) (width of window)
 1  2  3  4  5  6  7  8  9 10 11 12 
 a  b  a  c  b  a  b  c  a  b  c  a 
[ 2,  2]  1 
[ 3,  3]  2 
[ 4,  4]  1  2  3  4 
[ 5,  5]  3 
[ 6,  6]  4  5 
[ 7,  7]  6 
[ 8,  8]  5  6  7 
[ 9,  9]  7  8 
[10, 10]  8  9 
[11, 11]  9 
```
下部の表示の意味：
(MUS区間) (その区間が MUS となるスライド窓の開始位置の列)

## MUS および SUS の表示（対話式）

```
$ make SUS
$ ./SUS 
input string: abacbabcabca
 1  2  3  4  5  6  7  8  9 10 11 12 
 a  b  a  c  b  a  b  c  a  b  c  a 
|-------||----|      |-------|
      |----||-------|
query position: 4
SUSs for position  4: [ 3,  4] [ 4,  5] 
      |----|
         |----|
query position: 11
SUSs for position 11: [ 8, 11] 
                     |----------|
query position: q
```
