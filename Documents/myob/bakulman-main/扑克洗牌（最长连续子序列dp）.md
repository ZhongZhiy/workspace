### 问题 G: 扑克洗牌

时间限制: 2.000 Sec  内存限制: 512 MB  

#### 题目描述

Nanarikom 有 n 张扑克牌。初始状态下，牌堆中第 i 张扑克牌上的数字为 i。  
  
为了进行洗牌，Nanarikom 每次会进行以下操作中的一种：  

- 从牌堆顶取出 1 张牌，插入到牌堆的任意位置中。
- 从牌堆底取出 1 张牌，插入到牌堆的任意位置中。

在操作过程中，牌堆内未被取出的牌相对顺序保持不变。  
  
现在，Nanarikom 想要衡量牌堆的混乱程度。具体地，对于给定的牌堆，Nanarikom 想知道，从初始状态牌堆变换到给定牌堆所需的最小操作次数。  
  
你需要回答 Nanarikom 的 T 组询问。  

  

#### 输入

第一行包含一个整数 T（1≤T≤105），代表测试数据组数。对于每组测试数据：  
第一行包含一个整数 n（1≤n≤105），代表扑克牌的数量；  
第二行包含 n 个整数 a1,a2,…,an（1≤ai≤n），代表给定的牌堆顺序。  
输入数据保证 ∑n≤106，且 a1,a2,…,an 是一个排列。  

#### 输出

对于每组测试数据，输出一个整数，代表完成变换的最小操作次数。

#### 样例输入 Copy

1
5
4 1 2 5 3

#### 样例输出 Copy

2

#### 参考代码
```cpp

#include<bits/stdc++.h>
using namespace std;
#define de(x) cout << (#x) << " = " << (x) << endl;
#define de2(x, y) cout << (#x) << " , " << (#y) << " = " << (x) << " ~ " << (y) << endl;
#define endl '\n'
#define f(n) for(int i = 0;i < n; ++i)
#define ff(i, a, b) for(int i = a; i < b; ++i)
#define PLEASE_AC return 0
typedef long long ll;
typedef unsigned long long ull;
#define int long long 

const int N = 1e5 + 10;
int v[N];
int dp[N];
void solve() {
	int n;
	cin >> n;

	for(int i = 0; i <= n ; ++i) v[i] = dp[i] = 0;

	int max_len = 0;
	for(int i = 1; i <= n; ++i) {
		cin >> v[i];
		dp[v[i]] = dp[v[i]-1]+1;
		max_len = max(dp[v[i]], max_len);
	}

	cout <<n -  max_len << endl;

	
}


signed main() {
	//freopen("an", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int t;
	cin>> t;
	while(t--) solve();

	PLEASE_AC;
}
```