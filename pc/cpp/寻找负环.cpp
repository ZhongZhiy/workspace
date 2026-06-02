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

const int N = 2505;
struct Edge{int u, v, w;};
vector<Edge> edges;
int n, m;
int dis[N], pre[N];


void bellman() {
    int last_node = -1;
    for(int i = 1;i <= n; ++i) {
        last_node = -1;
        for(auto &[u, v, w] : edges) {
            if(dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                pre[v] = u;
                last_node = v;
            }
        }
    }

    if(last_node == -1) cout << "NO\n";
    else {
        cout << "YES\n";
        int cur = last_node;
        for(int i = 1;i <= n; ++i) cur = pre[cur];

        vector<int> cycle;
        int tp = cur;
        do {
            cycle.push_back(tp);
            tp = pre[tp];

        }while(tp != cur);
        reverse(cycle.begin(), cycle.end());
        for(auto &c : cycle) cout << c << ' ';
        cout << cycle[0];

    }
}

signed main() {
    caillo;
    cin >> n >> m;
    fi(m){
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }
    bellman();
    return 0;

}
