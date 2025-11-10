### 问题 G: bus

时间限制: 1.000 Sec  内存限制: 128 MB  

#### 题目描述

两个球队的支持者要一起坐车去看球，他们已经排成了一列。我们要让他们分乘若干辆巴士，同一辆巴士上的人必须在队伍中是连续的。为了在车上不起冲突，希望两队的支持者人数尽量相等，差至多是D。有一个例外，就是一辆车上的人全部都是一个球队的支持者。问要将这N个人全部送至球场，至少要几辆巴士。

#### 输入

第一行是整数N和D。  
接下来一行，按排队的顺序，描述每个人支持的球队，用H或J表示。该行没有任何多余的字符。  

#### 输出

一个整数，表示要多少巴士。

#### 样例输入 Copy

14 3
HJHHHJHJHHHHHH

#### 样例输出 Copy

2

#### 提示

对于100%的数据：N,D≤2500，数据有合理的梯度。

## 题意
就是把一个字符串分割为最少的段，每段要满足要求

## 分析
这是一个求解最优化的问题，需要求最少，满足最优子结构，所以考虑动态规划，
```cpp

#include<bits/stdc++.h>
using namespace std;
#define de(x) cout << (#x) << " = " << (x) << endl;
#define de2(x, y) cout << (#x) << " , " << (#y) << " = " << (x) << " ~ " << (y) << endl;
#define endl '\n'
#define f(n) for(int i = 0;i < n; ++i)
#define ff(i, a, b) for(int i = a; i < b; ++i)
#define PLACE_AC return 0
typedef long long ll;
typedef unsigned long long ull;
#define int long long 


const int N = 2507;
int dp[N + 100];
int n, d;
int cnth[N], cntj[N];

void init(string s) {
	for(int i = 1; i <= s.size(); ++i) {
		if(s[i-1] == 'H') cnth[i] = cnth[i-1] + 1, cntj[i] = cntj[i-1];
		else cntj[i] = cntj[i-1] + 1, cnth[i]  = cnth[i-1];
	}

	for(int i = 0; i < N; ++i) dp[i] = N;
}

int deff(int i, int j) {

	int ch = cnth[j] - cnth[i];
	int cj = cntj[j] - cntj[i];
	if(cj && ch) {
		if(abs(ch - cj) <= d) return true;
		else return false;
	}
	
	return true;
}

signed main() {
//	freopen("an", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> d;
	string s;
	cin >> s;
	init(s);

	dp[0] = 0;
	for(int i = 1; i <= n; ++i) {
		for(int j = 0; j < i; ++j) {
			if(deff(j, i)) dp[i] = min(dp[i], dp[j] + 1);
		}
	}

	cout << dp[n];


	PLACE_AC;
}
```
