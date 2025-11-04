### 问题 AG: Sliding Window Cost

时间限制: 1.000 Sec  内存限制: 128 MB  

#### 题目描述

You are given an array of n integers. Your task is to calculate for each window of k elements, from left to right, the minimum total cost of making all elements equal.  
You can increase or decrease each element with cost x where x is the difference between the new and the original value. The total cost is the sum of such costs.  

#### 输入

The first input line contains two integers n and k: the number of elements and the size of the window.  
Then there are n integers x1,x2,...,xn: the contents of the array.  
Constraints  
1≤k≤n≤2*105  
1≤xi≤109  

#### 输出

Output n-k+1 values: the costs.

#### 样例输入 Copy

8 3
2 4 3 5 8 1 2 1

#### 样例输出 Copy

2 2 5 7 7 1

思路:使用对顶堆维护中位数, 同时用两个数组维护两个堆的和

参考代码:
```cpp

#include<bits/stdc++.h>
using namespace std;
#define de(x) cout << (#x) << " = " << (x) << endl;
#define de2(x, y) cout << (#x) << " , " << (#y) << " = " << (x) << " ~ " << (y) << endl;
#define endl '\n'
#define fi(x) for(int i = 1; i <= x; ++i)
#define fi0(x) for(int i = 0; i < x; ++i)
#define fj(n) for(int j = 1; j <= n; ++j)
#define fj0(n) for(int j = 0; j < n; ++j)
#define PLEASE_AC return 0
typedef long long ll;
typedef unsigned long long ull;
#define int long long 

int n, k;
struct node {
	int val, id;
	node(){}
	node(int val, int id):val(val), id(id){}

	bool operator < (const node& a)const {
		return (val == a.val ? id < a.id : val < a.val);
	}
};
int slower = 0, supper = 0;
set<node> upper, lower;

void balance() {
	while(lower.size() > (k + 1) /2) {
		upper.insert(*lower.rbegin());
		supper += lower.rbegin()->val;
		slower -= lower.rbegin()->val;
		lower.erase(--lower.end());

	}
	while(!upper.empty()&&lower.size() < (k + 1)/2) {
		lower.insert(*upper.begin());
		slower += upper.begin()->val;
		supper -= upper.begin()->val;
		upper.erase(upper.begin());
	}
	while(!upper.empty() && lower.empty() && *upper.begin() < *lower.rbegin()) {
		auto u = *upper.begin(), l = *lower.rbegin();
		upper.erase(upper.begin());
		lower.erase(--lower.end());
		upper.insert(l);
		lower.insert(u);
		slower += u.val, slower -= l.val;
		supper += l.val, supper -= u.val;
	}

}
void add(const node& v) {
	if(!lower.empty() && v < *lower.rbegin()) lower.insert(v), slower += v.val;
	else upper.insert(v), supper += v.val;
	balance();
}

void remove(const node& v) {
	if(lower.count(v)) lower.erase(v), slower -= v.val;
	else upper.erase(v), supper -= v.val;
	balance();
}

int get_mid() {
	if(k&1) return lower.rbegin()->val;
	else return (lower.rbegin()->val + upper.begin()->val)/2;
}

int sum() {
	int ans = 0;
	int mid = get_mid();
	return (k & 1 ? supper + mid - slower : supper - slower);
}

signed main() {
//	freopen("an", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> k;

	vector<int> v(n + 1);
	fi(n) cin >> v[i];

	for(int i = 1;i <= k; ++i) add({v[i], i});
	cout << sum() << ' ';

	for(int i = k+1;i <= n; ++i){
		remove({v[i-k], i-k});
		add({v[i], i});
		cout << sum() << ' ';
	}

	PLEASE_AC;
}

```