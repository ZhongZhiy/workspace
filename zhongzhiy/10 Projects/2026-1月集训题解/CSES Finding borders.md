---
title: CSES Finding borders
date: 2026-01-24
categories:
tags:
  - KMP
  - 算法
  - 字符串
status:
difficulty: 🟡 中等
link: https://cses.fi/problemset/result/16034888/
---

# CSES Finding borders
## 题意

#字符串 #KMP

求字符串中有多少个borders
算`pi`数组, 每个数代表的是下标`i`之前的子串的最长真相等前后缀长度
注意代码细节
##  题解

每个border可能包含, 那么就需要从最长的border往回跳, 并且记录
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


const int N = 1e6 + 10;
vi cal_pi(const string& s) {
    int len = s.size();
    vi pi(len);
    for(int i = 1, j = 1; i < len; ++i) {
        j = pi[i-1];
        while(j > 0 && s[i] != s[j]) j = pi[j-1];
        if(s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

signed main() {
    string s; cin >> s;
    int len = s.size();
    vi pi = cal_pi(s);
    int k = pi[len-1];
    vi ans;
    //k 必须>0, 否则会在0处死循环
    for(; k > 0; k = pi[k-1]){
        ans.push_back(k);
    }
    sort(all(ans));
    for(auto c : ans) cout << c << ' ';
}


```
</mark>