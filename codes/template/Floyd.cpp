

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

int dist[400][400];
int n, m;  //n个点，m条边

void Floyd(int n) {
	for(int k = 1; k <= n; ++k)   //经过k个点的最短路径，
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);  //状态转移，经过1-n个点中从i到j路径最短的距离
	return;
}

void init() {
	memset(dist, 0x3f, sizeof(dist));  //初始化为一个很大的数字

	for(int i = 1; i <= n; ++i) dist[i][i] = 0;  //从i到i的距离初始化为0

	for(int i = 0; i < m; ++i) {  //读入m条边的数据
		int u, v, w;
		cin >> u >> v >> w;
		dist[u][v] = w;
	}
}

signed main() {
//	freopen("an", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);


	return 0;
}
