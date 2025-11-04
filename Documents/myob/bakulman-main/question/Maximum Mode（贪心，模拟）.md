### 问题 I: Maximum Mode

时间限制: 1.000 Sec  内存限制: 128 MB  

#### 题目描述

The mode of an integer sequence is the value that appears most often. Chiaki has n integers a1,a2,...,an. She woud like to delete exactly m of them such that: the rest integers have only one mode and the mode is maximum.  

  

#### 输入

There are multiple test cases. The first line of input contains an integer T, indicating the number of test cases. For each test case:  
The first line contains two integers n and m (1 ≤ n ≤ 105, 0 ≤ m < n) -- the length of the sequence and the number of integers to delete.  
The second line contains n integers a1, a2, ..., an (1 ≤ ai ≤ 109) denoting the sequence.  
It is guaranteed that the sum of all n does not exceed 106.  

  

#### 输出

For each test case, output an integer denoting the only maximum mode, or -1 if Chiaki cannot achieve it.  

  

#### 样例输入 Copy

5
5 0
2 2 3 3 4
5 1
2 2 3 3 4
5 2
2 2 3 3 4
5 3
2 2 3 3 4
5 4
2 2 3 3 4

#### 样例输出 Copy

-1
3
3
3
4

## 题意
询问t次，每次n个数和m个删除次数，求在可以删除m次的情况下，最大的众数是哪一个，如果没有就输出-1

## 分析
由于询问t次，每次都会不一样，所以需要处理t次
1. 对统计每个数的频数，根据数的大小排序，算每个数成为众数需要删除的个数，依次查询，当遇到第一个满足要求的数就是当前的答案，否则就为-1
2. 很朴素的想法，但是在计算每个数的过程，时间复杂度为o（k2），会超时
3. 因此需要加速计算每个数需要的删除个数，可以对频数相同的数可以一起计算，这样可以大大优化

## 参考代码
```cpp

#include<bits/stdc++.h>
#include <unordered_map>
#include <vector>
using namespace std;
#define de(x) cout << (#x) << " = " << (x) << endl;
#define de2(x, y) cout << (#x) << " , " << (#y) << " = " << (x) << " ~ " << (y) << endl;
#define endl '\n'
#define f(n) for(int i = 0;i < n; ++i)
#define ff(i, a, b) for(int i = a; i < b; ++i)
typedef long long ll;
typedef unsigned long long ull;


struct foo{
	int a, b;
	bool operator < (const foo& v) const {
		if(b != v.b) return b > v.b;
		else return a > v.a;
	}
};


void slove() {
	unordered_map<int, int> freq;

	int t, s;
	cin >> t >> s;

	vector<int> v;
	f(t)  {
		int h;
		cin >> h;
		freq[h]++;
	}

	unordered_map<int, vector<int>> f_to_n; //存频数和数的
	for(auto c : freq) {
		v.emplace_back(c.first);
		f_to_n[c.second].emplace_back(c.first);
	}

	sort(v.begin(), v.end(), greater<int>());

	int len = v.size();
	vector<int> an;
	for(int i = 0;i < len; ++i) {
		int t = -1;
		for(auto &[fq, g] : f_to_n) {
			if(fq < freq[v[i]]) continue;
			else  t += g.size() * (fq - freq[v[i]] + 1); 
		}
		an.emplace_back(t);



	} 

	for(int i = 0;i < len; ++i) {
		if(an[i] <= s) {cout << v[i] << endl; return;}
	}
	cout << -1 << endl;

}
int main() {
//	freopen("an", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	while(n--) {
		slove();
	}
	return 0;
}
```
