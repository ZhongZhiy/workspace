
#include<bits/stdc++.h>
using namespace std;
#define de(x) cout << (#x) << " = " << (x) << endl;
#define de2(x, y) cout << (#x) << " , " << (#y) << " = " << (x) << " ~ " << (y) << endl;
#define endl '\n'
#define fi(x) for(int i = 1; i <= x; ++i)
#define fj(n) for(int j = 1; j <= n; ++j)
#define PLEASE_AC return 0
typedef long long ll;
typedef unsigned long long ull;
#define int long long 



signed main() {
//	freopen("an", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;
	vector<int> f(n+1);

	int idx = 0;
	fi(n) {
		int t;
		cin >> t;

		if(t > f[idx]) f[++idx] = t;
		else {
			*lower_bound(f.begin()+1, f.begin()+1+idx, t) = t;
		}
	}
	cout << idx;

	PLEASE_AC;
}
