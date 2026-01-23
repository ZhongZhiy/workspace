---
title: CSES Graph Paths II
date: 2026-01-23
categories:
tags:
  - 矩阵快速幂
  - 算法
  - 组合数学
  - CSES
status:
difficulty: 🟡 中等
link: https://cses.fi/problemset/task/1724/
---

# CSES Graph Paths II
## 题意

> [!abstract] 题目关键信息
>求到从$1$到$n$经过$k$条边的最短路径
##  题解
使用拓展矩阵快速幂运算为`ret.v[i][j] = min(ret.v[i][j] , v[i][k] + a.v[k][j]);
每次选取从`i->k->j`的最短路径
因此矩阵初始化为$oo$且`qpow`中的单位矩阵也要满足对角线为$0$, 而且注意会有重边
##  参考代码
> [!example] 
```cpp fold
#include <climits>
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;

#define DEBUG
#ifdef DEBUG
#define de(x) cout << (#x) << "=" << (x) << endl;
#define de2(x, y) cout << (#x) << " " << (#y) << " = " << (x) << " " << (y) << endl;
#else
#define de(x)
#define de2(x, y)
#endif
#define endl '\n'
#define fi(n) for(int i = 1;i <= n; ++i)
#define fi0(n) for(int i = 0;i < n; ++i)
#define fj(n) for(int j = 1;j <= n; ++j)
#define all(x) (x).begin(), (x).end()
#define hello ios::sync_with_stdio(0); cin.tie(0);cout.tie(0);
#define world return 0;
#define int long long
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<vector<int>> vvi;
typedef long long ll;

const int M = 1e9 + 7;
const int N = 2e18;

struct Matrix{
    vvi v;
    int r, c;
    Matrix(int r, int c){this->r = r,this->c = c;v.assign(r, vector<int> (c, N));}

    Matrix operator * (const Matrix& a) const {
        Matrix ret(r, a.c);
        for(int i = 0;i < r; ++i)
            //优化cpu缓存命中, 使j是连续的
            for(int k = 0;k < c; ++k) {
                //剪枝
                if(v[i][k] == N) continue;
                for(int j = 0;j < a.c; ++j)
                    //每次乘法都是新矩阵, 也就一定会更新
                    ret.v[i][j] = min(ret.v[i][j] , v[i][k] + a.v[k][j]);
            }
        return ret;

    }
};

Matrix qpow(Matrix &base, int pow) {
    Matrix ret(base.r, base.r);
    for(int i = 0;i < base.r;++i) ret.v[i][i] = 0;
    while(pow){
        if(pow&1) ret = ret * base;
        base = base * base;
        pow >>= 1;
    }
    return ret;
}


signed main() {
    hello;
    int n, m, k; cin >> n >> m >> k;
    Matrix start(n, n);
    for(int i = 0;i < m; ++i) {
        int x, y, v; cin >> x >> y >> v;x--; y--;
        //居然有重边
        start.v[x][y] = min(start.v[x][y],v);
    }

    Matrix ret = qpow(start, k);

    cout << (ret.v[0][n-1] == N ? -1 : ret.v[0][n-1]) << endl;




    world;
}


```
