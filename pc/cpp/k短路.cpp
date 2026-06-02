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
struct Edge{
    int to, w;
    Edge(){}
    Edge(int to, int w):to(to), w(w){}
};

struct Node{
    int u, dis, g;
    Node(){}
    Node(int u, int dis):u(u), dis(dis){}
    Node(int u, int dis, int g):u(u), dis(dis), g(g){}
    bool operator < (const Node& a) const {
        return dis > a.dis;
    }
};

int dis[N];
int n, m, k;
bool vis[N];
vector<Edge> edge[N], redge[N];
void dijkstra(){
    memset(dis, 0x3f, sizeof(dis));
    priority_queue<Node, vector<Node>> q;
    q.push({n, 0}); dis[n] = 0;

    while(!q.empty()) {
        int u = q.top().u, dist = q.top().dis; q.pop();
        if(vis[u]) continue;
        vis[u] = 1;

        for(auto [to, w] : redge[u]) {
            if(dis[to] > dis[u] + w) {
                dis[to] = dis[u] + w;
                q.push({to, dis[to]});
            }
        }
    }
}

int cnt[N], ans[N];
void Astar(){
    priority_queue<Node, vector<Node>> q;
    q.push({1, dis[1], 0});

    while(!q.empty()) {
        int u = q.top().u; int dist = q.top().dis;int g = q.top().g; q.pop();
        if(dis[u] == dis[0]) continue;
        cnt[u]++;
        if(u == n) ans[cnt[u]] = dist;
        if(cnt[n]>=k) break;
        if(cnt[u]>k) continue;

        for(auto [to, w] : edge[u]) {
            q.push({to, g+w +dis[to], g+w});
        }
    }
}

signed main() {
    caillo;

    // cin >> n >> m >> k;
    cin >> n >> m; k = 2;
    fi(m){
        int u, v, w;
        cin >> u >> v >> w;
        edge[u].push_back({v, w});
        redge[v].push_back({u, w});
    }

    dijkstra();
    Astar();
    for(int i= 1;i <= k; ++i) cout << ans[i] << ' ';
    // cout << ans[2] << endl;
}
