
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

const int N = 5e5 + 10;;
struct  Edge{int to, next; }edge[N<<1];
int head[N<<1], cnt;
void init(){
	for(int i = 0;i < (N<<1);++i) {edge[i].next = -1; head[i] = -1;}
	cnt = 0;
}

void addedge(int u, int v) {
	edge[++cnt].to = v;
	edge[cnt].next = head[u];
	head[u] = cnt;
}

int deep[N], siz[N], son[N], top[N], fa[N];
void dfs1(int x, int father) {
	deep[x] = deep[father] + 1;
	fa[x] = father;
	siz[x] = 1;
	for(int i = head[x];~i; i = edge[i].next) {
		int y = edge[i].to;
		if(y != father) {
			fa[y] = x;
			dfs1(y, x);
			siz[x] += siz[y];
			if(!son[x] || siz[son[x]] < siz[y])
				son[x] = y;
		}
	}
}

void dfs2(int x, int topx) {
	top[x] = topx;
	if(!son[x]) return;
	dfs2(son[x], topx);
	for(int i = head[x]; ~i; i = edge[i].next) {
		int y = edge[i].to;
		if(y != fa[x] && y != son[x])
			dfs2(y, y);  //light son
	}
}

int LCA(int x, int y) {
	while(top[x] != top[y]) {
		if(deep[top[x]] < deep[top[y]]) swap(x, y);
		x = fa[top[x]];
	}
	return deep[x] < deep[y] ? x : y;
}


signed main() {
//	freopen("an", "r", stdin);
	caillo;
	init();
	int n, m, root; cin >> n >> m >> root;
	for(int i = 1;i < n; ++i) {
		int u, v; cin >> u >> v;
		addedge(u, v); addedge(v, u);
	}

	dfs1(root, 0);
	dfs2(root, root);
	while(m--) {
		int a, b; cin >> a >> b;
		cout << LCA(a, b) << endl;
	}


	PLEASE_AC;
}
