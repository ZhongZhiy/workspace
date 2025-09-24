
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

int n;
struct E{
	int to, val;
	E(){}
	E(int to, int val):to(to), val(val){}
};
vector<E> e[250];
struct node {
	int dis, u;
	node(){}
	node(int d, int u):dis(d), u(u){}
	bool operator > (const node&a) const {return dis > a.dis;}
};
priority_queue<node, vector<node>, greater<node> > q;

bool vis[250];
int dist[250];
void bfs(int x){
	while(!q.empty()) q.pop();
	memset(vis, 0, sizeof(vis));
	memset(dist, 0x3f, sizeof(dist));
	dist[x] = 0;
	q.push({0, x});

	while(!q.empty()) {
		int pos = q.top().u, dis = q.top().dis;
		q.pop();

		if(vis[pos]) continue;
		vis[pos] = 1;

		for(auto c : e[pos]) {
			int to = c.to, val = c.val;
			if(dist[to] > dist[pos] + val) {
				dist[to] = dist[pos] + val;
				q.push({dist[to], to});
			}
		}
	}
}
int fri[250];
signed main() {
//	freopen("an", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >>n;
	fi(n) {
		fj(n) {
			int a;cin >> a;
			if(a) e[i].push_back({j, a});
			
		}
	}

	fi(n) cin >> fri[i];

	int min_dis = INT_MAX, id = 0;
	fi(n) {
		bfs(i);
		int cur = 0;
		fi(n) cur += dist[i] * fri[i];
		if(min_dis > cur) min_dis = cur, id = i;
	}
	cout << id << endl << min_dis;




	PLEASE_AC;
}
