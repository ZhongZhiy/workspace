---
title: Cow Dance Show
date: 2026-02-11
categories:
tags:
  - 资源调度
status:
link: https://www.luogu.com.cn/problem/P3611
---

# Cow Dance Show
## 题意

$n$ 头牛准备表演, 一个舞台可以容纳 $k$ 头牛, 当其中某头牛表演完了, 下一头牛就会上去表演, 舞台上所有的牛都表演完了的时间为 $t$ , 给定 $t_{max}$ 求最小的 $k$ 

##  题解
这是明显的二分答案, 但是怎么在二分答案中检查:  
可以用小根堆, 每次最小时间  $t_{top}$ 的弹出, 压入 $t_{i} + t_{top}$ , 直到最后只有一个的情况就是最后花费的总时间

考虑, 一头牛跳完了, 下一头牛立即开始, 那么意味着: 下一个牛不在乎是谁跳完的, 只在乎 $k$ 个位置哪个是最先空出来的, 对于这个位置来说哪头牛在跳并不重要, 只要知道有谁来接替就行了, 就像是在接力
类似有银行排队, 超市排队
##  参考代码
> [!example] 
```cpp
#include <functional>
#include <queue>
#include <vector>
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
#define F first
#define S second
typedef pair<int, int> pii;
typedef vector<vector<int>> vvi;
typedef long long ll;

int n, t;
int d[100010];
bool check(int mid) {
    priority_queue<int, vector<int>, greater<int>> q;
    for(int i = 1; i <= mid; ++i) q.push(d[i]);
    for(int i = mid + 1; i <= n; ++i) {
        int ti = q.top(); q.pop();
        q.push(ti + d[i]);
    }
    int ti = q.top();
    while(!q.empty()) {ti = q.top(); q.pop();}
    return ti <= t;
}

signed main() {
    hello;
    cin >> n >> t;
    fi(n) cin >> d[i];

    int l = 1, r = n, mid;
    while(l <= r) {
        mid = (l + r) >> 1;
        if(check(mid)) r = mid - 1;
        else l = mid + 1;
    }
    cout << l ;


    world;
}


```
