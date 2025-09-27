
#include<bits/stdc++.h>
using namespace std;
#define i128 __int128
#define de(x) cout << (#x) << " = " << (x) << endl;
#define de2(x, y) cout << (#x) << " , " << (#y) << " = " << (x) << " ~ " << (y) << endl;
#define endl '\n'
#define fi(x) for(int i = 1; i <= x; ++i)
#define fi0(x) for(int i = 0; i < x; ++i)
#define fj(n) for(int j = 1; j <= n; ++j)
#define fj0(n) for(int j = 0; j < n; ++j)
#define caillo ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define PLEASE_AC return 0
typedef long long ll;
typedef unsigned long long ull;
#define int long long 

const int N = 2e5 + 10;
int n;
int a[N];

struct cmp{
	bool operator()(const int& g, const int &b) const {
		if(g == 0 || b == 0) return g < b;
		int la = 64 - __builtin_clzll(g);
		int lb = 64 - __builtin_clzll(b);
		if(la != lb) return la > lb;
		return g > b;
	}
};

signed main() {
//	freopen("an", "r", stdin);
	caillo;

	cin >> n;

	priority_queue<int, vector<int>, cmp> q;

	fi(n) {
		int k;
		cin >> k;
		q.push(k);
	}
	int sum = 0;
	while(q.size() > 1){
		int f = q.top(); q.pop();
		int s = q.top(); q.pop();
		sum += (f&s)<<1;
		q.push(f^s);
	}
	cout << sum;
	PLEASE_AC;
}
