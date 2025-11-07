
#include<bits/stdc++.h>
#include <climits>
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
#define startime auto start = chrono::high_resolution_clock::now();
#define endtime auto end = chrono::high_resolution_clock::now();
#define runningtime cout << "running time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count()<<" ms\n";
typedef long long ll;
typedef unsigned long long ull;
#define int long long 

const int N = 200;
int mp[N][N], vis[N];
int head[N];
struct E{int to, w, nxt;};
E edge[N];

int idx = 1;

void add_edge(int u, int v, int w){
	edge[idx].to = v;
	edge[idx].w = w;
	edge[idx].nxt = head[u];
	head[u] = idx++;
}

void dfs(int st, int fa){
	cout << ' ' << (char)st ;
	vis[st] = 1;
	for(int p = head[st]; ~p; p = edge[p].nxt){
		int u, v; u = edge[p].to;
		if(!vis[u]) dfs(u, st);
	}
}

void bfs(int st, int fa){
	queue<int> q;
	q.push(st);
	while(!q.empty()){
		int cur = q.front();q.pop();
		vis[cur] = 1;
		cout << ' ' << (char) cur ;
		for(int p = head[cur]; ~p; p = edge[p].nxt){
			if(!vis[edge[p].to]) {
				vis[edge[p].to] = 1;
				q.push(edge[p].to);
			}
		}
	}
}

void degree(int st){

	for(int i = 1;i < N; ++i){
		int cnt = 0;
		for(int t = head[i]; ~t; t = edge[t].nxt){
			int u = edge[t].to;
			cnt++;
		}

		if(cnt){
			cout << endl << (char)i << ":"<< cnt ;
		}
	}
}

signed main() {
//	freopen("an", "r", stdin);
	caillo;

	int n, m; cin >> n >> m;
	memset(mp, -1, sizeof(mp));
	memset(head, -1, sizeof(head));

	// de2(n, m);
	int mins = INT_MAX;
	fi(m){
		// int u, v, w; cin >> u >> v >> w;
		char u, v; int w; cin >> u >> v >> w;
		// de2((int)u, (int)v)
		// de2(u, v)
		add_edge(u, v, w);
		add_edge(v, u, w);
		mins = min({(int)u, (int)v, mins});
	}

	cout << "DFS:";
	dfs(mins, 0);
	cout << endl;
	memset(vis, 0, sizeof(vis));
	cout << "BFS:";
	bfs(mins, 0);
	degree(mins);

	PLEASE_AC;
}
