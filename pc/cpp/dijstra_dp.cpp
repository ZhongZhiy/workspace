#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define i128 __int128


#ifdef DEBUG
#define de(x) cout << (#x) << " = " << (x) << endl;
#define de2(x, y) cout << (#x) << " , " << (#y) << " = " << (x) << " ~ " << (y) << endl;
#else
#define de(x)
#define de2(x, y)
#endif

#define enld endl
#define endl '\n'
#define fi(x) for(int i = 1; i <= x; ++i)
#define fi0(x) for(int i = 0; i < x; ++i)
#define fj(n) for(int j = 1; j <= n; ++j)
#define caillo ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define PLEASE_AC return 0
typedef long long ll;
#define int long long


const int N = 1e5 + 10;
int M = 1e9 + 7;
int lowcost[N], routes[N], lessp[N], morep[N]; //lowcase是最短路的长度, routes是最短路的数量, lessp是最短路的最小值, morep是最短路的最大值
struct Edge{
    int v, w;
    Edge(){}
    Edge(int v, int w):v(v), w(w){}
};
vector<Edge> adj[N];
int n, m;

struct Node{
    int u, dis;
    Node(){}
    Node(int u, int dis):u(u), dis(dis){}
    bool operator < (const Node& a) const {
        return dis > a.dis;
    }
};

void bfs() {
    priority_queue<Node, vector<Node>> pq;
    memset(lowcost, 0x3f, sizeof(lowcost));
    memset(lessp, 0x3f, sizeof(lessp));
    routes[1] = 1;
    lessp[1] = 0;
    morep[1] = 0;
    lowcost[1] = 0;
    pq.push({1, 0});



    // 核心状态转移逻辑参考
    while (!pq.empty()) {
        auto [u, dis] = pq.top(); pq.pop();
        if (dis > lowcost[u]) continue;  //剪枝

        for (auto [v, w] : adj[u]) {
            if (lowcost[v] > dis + w) {
                // 情况 A：发现更短路
                lowcost[v] = dis + w;
                routes[v] = routes[u];
                lessp[v] = lessp[u] + 1;
                morep[v] = morep[u] + 1;
                pq.push({v, lowcost[v]});
            } else if (lowcost[v] == dis + w) {
                // 情况 B：发现等长路，更新统计指标
                routes[v] = (routes[v] + routes[u]) % M;
                lessp[v] = min(lessp[v], lessp[u] + 1);
                morep[v] = max(morep[v], morep[u] + 1);
            }
        }
    }
}

void printl(){
    cout << lowcost[n] << ' ' << routes[n] << ' ' << lessp[n] << ' ' << morep[n] << endl;
}
signed main() {
    caillo;
    cin >> n >> m;
    fi(m){
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    bfs();
    printl();
}
