#include <bits/stdc++.h>
using namespace std;


const int N = 1e5 + 10;

const int M = 1e9 + 7;
int dp[1<<20][20];
vector<int> adj[20];  //反向边


int main() {
    int n, m;cin >> n >> m;

    for(int i = 0;i < m; ++i) {
        int u, v; cin >> u >> v;
        u--;v--;
        adj[v].push_back(u);
    }

    dp[1][0] = 1;

    for(int mask = 2; mask < (1<<n); mask++) {
        if(!(mask&1)) continue;  //剪枝, 如果 mask 不包含起点，跳过

        //剪枝: 如果提前到达重点,
        if((mask&(1<<(n-1)))&& mask != ((1<<n)-1)) continue;

        for(int u = 0;u < n; ++u) {
            if(!(mask & (1<<u))) continue;

            //寻找上一个节点
            int prev = mask ^ (1 << u);
            for(int v : adj[u]) {
                if(prev & (1<<v)) {
                    dp[mask][u] = (dp[mask][u] + dp[prev][v]) % M;
                }
            }
        }
    }
    cout << dp[(1<<n)-1][n-1] << endl;

}
