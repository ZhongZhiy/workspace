
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

constexpr int N = 1e5 + 100, LOGN = 20;
int logn[N], f[N][LOGN];  //f[i][j] 代表在[i, i + 2^j)范围中的最大值

inline void initlg() {
	logn[1] = 0;
	for(int i = 2; i <= N; ++i) {
		logn[i] = logn[i/2] + 1;
	}
}

int n, m;
void stable() {
	cin >> n >> m;
	for(int i = 1; i <= n; ++i) {
		cin >> f[i][0];
	}

	initlg();

	for(int j = 1; j <= LOGN; ++j) {
		for(int i = 1; i + (1 << j) - 1 <= n; ++i) {
			f[i][j] = max(f[i][j-1], f[i + (1 << (j-1))][j-1]);
		}
	}
}

int query(int x, int y) {
	int s = logn[y - x + 1];
	return max(f[x][s], f[y- (1<< s) + 1][s]);
}

signed main() {
//	freopen("an", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);


	stable();

	cin >> m;
	for(int i = 1; i <= m; ++i) {
		int x, y;
		cin >> x >> y;
		cout << query(x, y) << endl;
	}
	return 0;
}
