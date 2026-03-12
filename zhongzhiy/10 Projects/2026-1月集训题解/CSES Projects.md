---
title: CSES Projects
date: 2026-01-25
categories:
tags:
  - 背包DP
  - 算法
  - DP
status:
difficulty: 🟡 中等
link: https://cses.fi/problemset/result/16049780/
---

# CSES Projects
## 题意

> [!abstract] 题目关键信息
> 给定每个项目的起止时间, 同一个时间点不能参加两个项目, 每个项目有一个权值, 求可以得到的最大权值

##  题解
类似01背包问题, 每个项目有对应的消费和权值, 但是不同点在于, 每个项目确定了费用区间, 也就相当于背包中确定了指定容量的占用, 那么选了当前的项目, 那么选的之前的项目必须结束时间在当前项目之前, 也就是`start_time[cur] > end_time[pre]`, 这样就能正常转移了
**定义状态**: `dp[i]`为第`i`天及之前能得到的最大价值
**状态转移**: `dp[i] = max(dp[i], dp[pre] + w`
**初始化**: 注意, 这我刚开始漏掉了, 如果今天没有项目可以选择, 那么它的`dp[i] = dp[i-1]`

##  参考代码
> [!example] 
```cpp fold
#include <algorithm>
#include <complex>
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

const int N = 2e5 + 10;
struct Node{
    int f, e, w;
    Node(){}
    Node(int f, int e, int w): f(f), e(e), w(w){}
    bool operator<(const Node& a) const {
        return e < a.e;
    }
}proje[N];

int num[N<<2], a[N], b[N], w[N], idx = 0;
int dp[N<<2];

signed main() {
    hello;
    int n; cin >> n;
    fi(n) {
        cin >> a[i] >> b[i] >> w[i];
        num[++idx] = a[i];
        num[++idx] = b[i];
    }
    sort(num+1, num+1+idx);
    int sz = unique(num+1, num+1+idx) - (num + 1);
    fi(n){
        proje[i].f = lower_bound(num+1, num+1+sz, a[i]) - num;
        proje[i].e = lower_bound(num+1, num+1+sz, b[i]) - num;
        proje[i].w = w[i];
    }

    sort(proje+1, proje+1+n);

    int max_ans = 0;
    for(int i = 1;i <= sz; ++ i) {
        dp[i] = dp[i-1];
        int id = lower_bound(proje+1, proje+1+n, Node(1, i, 0)) - proje;
        while(proje[id].e == i) {
            dp[i] = max(dp[i], dp[proje[id].f-1] + proje[id].w);
            id++;
        }
        max_ans = max(max_ans, dp[i]);
    }
    cout << max_ans << endl;



    world;
}


```
