
#include<bits/stdc++.h>
using namespace std;
#define de(x) cout << (#x) << " = " << (x) << endl;
#define de2(x, y) cout << (#x) << " , " << (#y) << " = " << (x) << " ~ " << (y) << endl;
#define endl '\n'
#define f(n) for(int i = 0;i < n; ++i)
#define ff(i, a, b) for(int i = a; i < b; ++i)
typedef long long ll;
typedef unsigned long long ull;
#define int long long 

const int N = 2500 + 100;
int dp[N], countj[N], frontj[N], counth[N], fronth[N];

void init() {
	for(int i = 0 ;i < N; ++i) dp[i] = 1e8;
}

signed main() {
//	freopen("an", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);


	init();
	int n, m;
	cin >> n >> m;
de(n)
	string s;
	cin >> s;
de(s)
	for(int i = 1; i <= n; ++i) {
		if(s[i-1] == 'J') {
			countj[i] += countj[i-1] + 1;
			counth[i] = counth[i-1];
		}
		else {
			counth[i] += counth[i-1] + 1;
			countj[i] = countj[i];
		}

		de2(i, countj[i])de2(i,counth[i])
	}

	dp[0] = 0;
	for(int i = 1 ;i <= n; ++i) {
		for(int j = i-1; j >= 0; ++j) {
			if(abs(countj[i] - countj[j] + counth[i] - counth[j]) <= m || (countj[i] - countj[j]) == 0 || (counth[i] - counth[j]) == 0)
			dp[i] = min(dp[j] + 1, dp[i]);
		}
	}

	cout << dp[n];
	return 0;
}
