
#include<bits/stdc++.h>
#include <climits>
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

const int N = 1e5 + 10;
vector<int> e[N];
int max_[N], sum_[N], a[N];

int dfs(int x, int fa) {
	for(auto c : e[x]) {
		if(c == fa) continue;
		int t = dfs(c, x);
		sum_[x] += t;
		max_[x] = sum_[x];
		max_[x] = max(max_[c], max_[x]);
	}
	
	return sum_[x];
}
int ans = 0;
bool success = false;
void dff(int x, int fa) {
	int cnt = 0, ma = LLONG_MIN, sem = LLONG_MIN;
	for(auto c : e[x]) {
		if(c != fa) {
			cnt++;
			if(max_[c] > ma) {
				sem = ma;
				ma = max_[c];
			}
			else if(max_[c] > sem) sem = max_[c];
		}
	}
	
	if(cnt < 2) {
		for(auto c : e[x]) if(c != fa) dff(c, x);
	} else success = true, ans = sem + ma;
}
signed main() {
//	freopen("an", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;
	fi(n) {cin >> a[i];sum_[i] = max_[i] = a[i];}
	fi(n-1) {
		int x, t;
		cin >> x >> t;
		e[x].push_back(t);
		e[t].push_back(x);
	}
	dfs(1, 0);
	fi(n) cout << sum_[i] << ' ';
	cout << endl;fj(n) cout << max_[i] << ' ';
	dff(1, 0);
	if(success) cout << ans;
	else cout << "Impossible";
	






	PLEASE_AC;
}
