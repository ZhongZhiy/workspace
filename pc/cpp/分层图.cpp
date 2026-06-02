#include <queue>
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define i128 __int128

#define DEBUG
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
const int M = 2e5 + 10;

int dist[N][2];
struct {int to, w, next;}edge[M];
int head[N], idx;
void init() {
    memset(head, -1, sizeof(head));
    memset(dist, 0x3f, sizeof(dist));
    idx = 0;
}

void addedge(int u, int v, int w) {
    edge[++idx].to = v; edge[idx].w = w;edge[idx].next = head[u]; head[u] = idx;
}

struct Node{
    int u, k, dis;
    Node(){}
    Node(int u, int k, int dis):u(u), k(k), dis(dis){}
    bool operator < (const Node& a) const {
        return dis > a.dis;
    }
};

void dijkstra() {
    priority_queue<Node, vector<Node>> q;
    q.push({1,0,0});
    dist[1][0] = 0;

    while(!q.empty()) {
        int u = q.top().u, k = q.top().k, dis = q.top().dis;
        q.pop();
        if(dis > dist[u][k]) continue;

        for(int i = head[u]; ~i; i = edge[i].next) {
            int to = edge[i].to; int w = edge[i].w;
            if(dist[u][k] + w < dist[to][k]) {
                dist[to][k] = dist[u][k] + w;
                q.push({to, k, dist[to][k]});
            }


            if(k == 0 && dist[u][0] + w/2 < dist[to][1]) {
                dist[to][1] = dist[u][0] + w/2;
                q.push({to, 1, dist[to][1]});
            }
        }
    }
}

signed main() {
    caillo;
    init();
    int n, m; cin >> n >> m;
    fi(m){
        int u, v, w; cin >> u >> v >> w;
        addedge(u, v, w);
    }

    dijkstra();
    cout << dist[n][1] << endl;

}
