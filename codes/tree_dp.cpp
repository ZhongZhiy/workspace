
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
#define PLEASE_AC return 0
typedef long long ll;
typedef unsigned long long ull;
#define int long long 

const int N = 105;
int n, q;  //n个节点， 保留q条边
struct E{
	int to, w;
	E(){}
	E(int to, int w):to(to), w(w){}
};
vector<E> e[N];

int d[N][N], sum[N];  //sum[i] 记录以i为根的子树总边数
void dfs(int x, int fa){
	for(int i = 0;i < e[x].size(); ++i){  //遍历所有的的子节点
		int to = e[x][i].to, w = e[x][i].w;
		if(to == fa) continue;
		dfs(to, x);   //先解决子树的情况
		sum[x] += sum[to] + 1;  // 刚刚算的子树大小 
		for(int j = sum[x]; j >= 0; j--)   //计算节点x保留j条边的最大值情况
			for(int k = 0;k < j; k++)  //分割这j条边， 让to子节点选取k条边， 其他子节点选取j-k-1条边
				d[x][j] = max(d[x][j], d[x][j - k - 1] + d[to][k] + w);
	}
}

signed main() {
//	freopen("an", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> q;
	fi(n-1){
		int a, b, w;
		cin >>a >> b >> w;
		e[a].push_back({b, w});
		e[b].push_back({a, w});

	}

	dfs(1, 0);
	cout << d[1][q];

	PLEASE_AC;
}
