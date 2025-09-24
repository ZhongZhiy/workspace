
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

int n;
char mp[20][20], col[20], row[20], ital[20];
int ans = 0, ans_cnt = 1;

void dfs(int x, int y, int cnt) {
	if(x > n) {
		if(cnt > ans) {ans = cnt;ans_cnt = 1;}
		else if(cnt == ans && ans != 0) ans_cnt++;
		return;
	}

	int nx = (x == y ? x+1 : x), ny = (x == y ? 1 : y+1);

	if(col[y] + row[x] + ital[x-y] == 0) {
		col[y] = row[x] = ital[x-y] = 1;
		dfs(nx, ny, cnt+1);
		col[y] = row[x] = ital[x-y] = 0;
	}

	dfs(nx, ny, cnt);

}

signed main() {
	//freopen("an", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >>n;
	fi(n)fj(i) {
		cin >> mp[i][j];
		if(mp[i][j] == '*') {
			col[j] = 1;
			row[i] = 1;
			ital[i-j] = 1;
		}
	}

	dfs(1, 1, 0);

	cout << ans << endl << ans_cnt;

	PLEASE_AC;
}
