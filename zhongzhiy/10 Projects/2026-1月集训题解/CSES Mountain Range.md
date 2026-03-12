---
title: CSES Montain Range
date: 2026-01-26
categories: 
tags:
status: #todo
difficulty: 🟡 中等
link: 

---

# CSES Montain Range
## 题意
在山间滑行, 如果从$a$到$b$, 那么需要确保$a > b$, 而且$a$于$b$之间的山的高度也都要在$a$于$b$之间, 
求最大滑翔到达山的数量


##  题解
这个只要是从高到低就可以了, 也就可以左可以右, 不一定是向右的递减序列, 
第一个误解是写成了最长下降子序列
定义状态: `dp[i]`是以山`i`为最低点的最大到达山的个数, 那么它一定是从`i`的左边或者右边最近的比`i`高的山转移过来的, 
因此状态转移: `dp[i] = max(dp[i], dp[l[i]])` `dp[i] = mac(dp[i],d[r[i]])`
其中左右最近比较高的山可以通过两次单调栈来找, 注意单调栈**严格递减的特征**
初始化: 对与最高的山, `dp[i] = 1`



##  参考代码
> [!example] 
```cpp fold
#include <climits>
#include <queue>
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

const int N = 2e5 + 10;
int a[N], l[N], r[N], dp[N];

signed main() {
    hello;
    int n; cin >> n;
    fi(n) cin >> a[i];
    stack<int> st;

    //哨兵
    a[0] = a[n+1] = INT_MAX;
    //单调栈求左边的高值
    for(int i = 1;i <= n + 1; ++i) {
        while(!st.empty() && a[st.top()] <= a[i]) {
            int lh  = st.top();  st.pop();
            if(!st.empty()) l[lh] = st.top();
        }
        st.push(i);
    }

    while(!st.empty()) st.pop();

    //单调栈求右边的高值
    for(int i = n + 1;i >= 0 ; --i) {
        while(!st.empty() && a[st.top()] <= a[i]) {
            int rh = st.top(); st.pop();
            if(!st.empty()) r[rh] = st.top();
        }
        st.push(i);
    }

    //用优先队列, 让较高的在队头, 优先更新高的
    priority_queue<pair<int, int>> pq;
    for(int i = 1;i <= n; ++i) {
        pq.push({a[i], i});
        if(l[i] == 0 && r[i] == n+1) dp[i] = 1;
    }

    int max_ans = 0;
    //转移, 从左右转移过来
    while(!pq.empty()) {
        int i = pq.top().S; pq.pop();
        if(l[i] != 0) dp[i] = max(dp[i], dp[l[i]]+1);
        if(r[i] != n+1) dp[i] = max(dp[i], dp[r[i]]+1);
        max_ans = max(max_ans, dp[i]);
    }
    cout << max_ans << endl;



    world;
}


```
