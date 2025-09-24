# 问题 C: 取最大值
时间限制: 1.000 Sec  内存限制: 128 MB
## 题目描述
 今有一两行n列的长矩阵，其中的数有正有负，均不超出整数的范围。小明想从这个长矩阵中圈出一个“凹”字形（可正可倒），使得这个“凹”字形中的所有数之和尽可能大，请问能达到的最大值是多少？	
## 输入
输入第一行包含一个整数n，即矩阵的列数，n小于1000000。以下两行，每行包含n个数，用来描述这个矩阵。所有数在整数范围内。	
## 输出
输出包含一行一个数，即求出的最大值。	
样例输入 Copy

【样例1】
```
4
1 -1 1 1
-4 1 1 1
```
【样例2】
```
10
47 -10 48 -24 -14 3 -40 -23 10  -25
-1 -28 25 31 -20 -48 -22 49 26 –48
```

样例输出 

【样例1】
3
【样例2】
116

## 题解
```
|----|____|-------|
|    c    d       |
|                 |
|                 |
|_________________|
a                 b
```
设第一行前缀和和第二行前缀和为`pre1`和`pre2`
如图,可得凹字形的值为`pre1[b] - pre1[a-1] - pre1[d] + pre1[c-1] + pre2[b] - pre2[a-1]`,整理就是`pre1[b] + pre2[b] - (pre1[a-1] + pre2[a-1]) + pre1[c-1] - pre1[d]`,可以一步一步求得最大值
1. 第一步求左边界a,`fa[i]`表示以i为左边界的最

参考代码:
```cpp
#include <bits/stdc++.h>
using namespace std ;
const int N = 1e6 + 10 ;
typedef long long ll ;
ll a[N] , b[N] ;
ll fa[N] , fb[N] , fc[N] , fd[N] , prea[N] , preb[N] ;
int n ;
ll ans = 0 ;
void solve()
{
       // for(int i = 0; i <= n ;i ++) fa[i] = fb[i] = fc[i] = fd[i] = -1e9 ;

       fa[0] = 0 ;
       for(int i = 1; i <= n ;i ++)
        fa[i] = max(fa[i - 1] , -prea[i] - preb[i]) ;

       fd[1] = prea[1] ;
       for(int i = 2 ;i <= n ;i ++)
        fd[i] = max(fd[i - 1] , fa[i - 1] + prea[i]) ;

       fc[2] = - prea[2] + fd[1] ;
       for(int i = 3 ;i <= n ;i ++)
        fc[i] = max(fc[i - 1] , -prea[i] + fd[i - 1]) ;

       fb[3] = prea[3] + preb[3] + fc[2];
       for(int i = 4; i <= n ;i ++)
        fb[i] = max(fb[i - 1] , prea[i] + preb[i] + fc[i - 1]) ;

       ans = max(ans , fb[n]) ;
}
int main()
{
   scanf("%d" , &n) ;
   for(int i =  1; i <= n ;i ++)
    scanf("%lld" , &a[i]) ;
   for(int i = 1; i <= n ;i ++)
    scanf("%lld" , &b[i]) ;
   for(int i = 1; i <= n ;i ++)
    prea[i] = prea[i - 1] + a[i] , preb[i] = preb[i - 1] + b[i] ;
   solve() ;
   for(int i = 1; i <= n ;i ++)
    swap(prea[i] , preb[i]) ;
   solve() ;
   cout << ans << endl ;
   return 0 ;
}


```

