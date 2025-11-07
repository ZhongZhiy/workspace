
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
#define startime auto start = chrono::high_resolution_clock::now();
#define endtime auto end = chrono::high_resolution_clock::now();
#define runningtime cout << "running time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count()<<" ms\n";
typedef long long ll;
typedef unsigned long long ull;
#define int long long 

int n, m;
constexpr int N = 3e5 + 10;
bool vis[N], ept[N];
vector<int> e[N];
vector<pair<int, int>> ans;
int order[N];
int idx = 2, start = 1;

void show(){
	cout << ans.size() << endl;
	for(auto [u, v] : ans) cout << u << ' ' << v << endl;
	exit(0);
}

void dfs(int u){
	vis[u] = 1;
	if(idx == n + 1){
		show();
	}

	if(ept[u] && u == order[start]){  //if this is empty node and start node
		start = idx;
		dfs(order[idx++]);
	}else if(ept[u]){  //if this is empty node, just return;
		return;
	}

	int no_ex = 0;

	while(!ept[u]){  //if there exist any node
		no_ex = 0;
		int found = 0;
		for(auto v : e[u]){
			if(!vis[v]) no_ex = 1;  //exist not visited node
			
			if(v == order[idx]){  //if find the target
				found = 1;
				dfs(order[idx++]);
			}
		}
		if(!no_ex) ept[u] = 1;  //if no node

		if(!found){  //not find the node
			if(ept[u]) {  //all adjnode be visited
				if(u == order[start]){
				start = idx;
				dfs(order[idx++]);
				}
			}else {  //exist node not visited
				ans.push_back({u, order[idx]});
				dfs(order[idx++]);
			}
		}
	}

}


signed main() {
	// freopen("an", "r", stdin);
	caillo;


	cin >> n >> m;
	fi(m){
		int x, y; cin >> x >> y;
		e[x].push_back(y);
		e[y].push_back(x);
	}
	fi(n) cin >> order[i];


	dfs(order[start]);

	PLEASE_AC;
}
