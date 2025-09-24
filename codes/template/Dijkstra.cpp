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

struct edges{  //存边的信息的结构体，主要是边的目的地和权重
	int to, w;
	edges(int to, int w):to(to), w(w){}
};

const int N = 1e5 + 10, INF = INT_MAX;
vector<edges> ed[N];  //用vector存边
int dist[N], vis[N];  //每个点到出发点的距离，访问标记，到过就标记掉，防止重复访问

void init() {  //初始化，每个节点距离都初始化为无穷， 同时初始化vis,可以不用其实
	for(int i = 0; i < N; ++i) {
		dist[i] = INF;
		vis[i] = 0;
	}
}

struct Polar{  //节点信息，到这个节点的距离和节点编号
	int dist, id;
	Polar(int dist, int id) : dist(dist), id(id){}

	bool operator < (const Polar a) const {  //用来定义大根堆
		return dist > a.dist;
	}
};

priority_queue<Polar, vector<Polar> > Q;   //大根堆，注意写法


void Dij(int s) {  //从s节点出发
	dist[s] = 0;
	Q.push(Polar(0, s));  //节点s到s的距离为0,初始化的节点就这样
	while(!Q.empty()) {   //非空
		int p = Q.top().id;  //p就是当前处理的节点编号
		Q.pop();            //需要弹出
		if(vis[p])         //只处理没有访问过的节点
			continue;
		vis[p] = 1;    //在这里打标

		for(auto c : ed[p]) {   //寻找和当前节点相邻的节点，如果从当前节点到相邻节点比原来更短，就加入队列，队列允许冗余值
			int to = c.to;

			if(dist[p] + c.w < dist[to]) {
				dist[to] = dist[p] + c.w;  //更新更短值
				Q.push(Polar(dist[to], to));
			}
		}
	}
}



signed main() {
//	freopen("an", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	init();

	int n, m, s;
	cin >> n >> m >> s;

	for(int i = 1; i <= m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		ed[u].emplace_back(v, w);
	}
	Dij(s);

	for(int i = 1; i <= n; ++i) {
		cout << dist[i] << ' ';
	}

	


	return 0;
}
