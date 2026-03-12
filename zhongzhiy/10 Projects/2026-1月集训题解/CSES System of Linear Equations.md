---
title: CSES System of Linear Equations
date: 2026-01-23
categories:
  - 算法
tags:
  - 算法
  - 高斯消元
  - 线性代数
status:
difficulty: 🟡 中等
link: https://cses.fi/problemset/task/3154
---

# CSES System of Linear Equations
## 题意


> [!abstract] 
> 求解线性方程组

##  题解
模拟手动高斯消元
参考代码里的注释
##  参考代码
> [!example] 
```cpp fold
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

int qpow(int a, int b) {
    int res = 1;
    a %= M;
    while(b) {
        if(b&1) res = (res * a) % M;
        a = (a * a) % M;
        b >>= 1;
    }
    return res;
}

int inv(int n) {return  qpow(n, M-2);}

int gauss(vvi& mat, int n, int m, vi& ans) {
    int row = 0, col = 0;
    while(row < n && col < m) {
        //寻找主元, 为列中绝对值最大的一个, 只是为了稳定
        int pivot = row;
        for(int i = row + 1; i < n; ++i) {
            if(abs(mat[i][col]) > abs(mat[pivot][col])) pivot = i;
        }

        //这一列全是0, 也就是这个变量是自由变量
        if(mat[pivot][col] == 0) {
            col++;
            continue;
        }

        //高效交换指针, 化为最简行阶梯矩阵, 也就是每行每列最多一个非零元素(除了最右边)
        swap(mat[row], mat[pivot]);

        //算当前作为主元的逆元, 要算mat[row][col]/mat[row][col] <=> mat[row][col] * inv(mat[row][col])
        int cur_inv = inv(mat[row][col]);
        /**
        * mat[i][col] 要等于0 => mat[i][col] - mat[i][col]/mat[row][col] * mat[row][col]
        * factor = mat[i][col]/mat[row][col] <=> mat[i][col] * cur_inv
         */
        for(int i = 0;i < n; ++i) {
            //除了当前行的当前列, 其他都
            if(i != row && mat[i][col] != 0) {
                int factor = (mat[i][col] * cur_inv) % M;
                for(int j = col; j <= m; j++) {
                    mat[i][j] = (mat[i][j] - factor * mat[row][j] % M + M) % M;
                }
            }
        }
        row++; col++;
    }

    ans.assign(m, 0);
    //i>= row这部分应该全是0, row代表矩阵的秩Rank, 前row行都有一个系数非零
    for(int i = row; i < n; i++) {
        if(mat[i][m] != 0) return 0;
    }

    for(int i = 0;i < row; i++) {
        int j = 0;
        while(j < m && mat[i][j] == 0) j++;
        if(j < m) {
            ans[j] = (mat[i][m] * inv(mat[i][j])) % M;
        }
    }
    return (row < m) ? 2 : 1;
}

signed main() {
    hello;
    int n, m; cin >> n >> m;
    vvi mat(n, vi (m+1));
    for(int i = 0;i < n; ++i) {
        for(int j = 0; j <= m; ++j) cin >> mat[i][j];
    }

    vi ans;
    int res = gauss(mat, n, m, ans);
    if(res == 0) {
        cout << -1 << endl;
    }else {
        for(int i = 0;i < m; ++i) cout << ans[i] << ' ';
    }

    world;
}


```
