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
typedef unsigned long long ull;
// #define int long long

const int N = 2e5 + 10;
int n, q;
int dep[N], dp[N][20], val[N], sum[N];
vector<int> adj[N];

void dfs(int x, int fa){
    dep[x] = dep[fa]+1;
    dp[x][0] = fa;
    for(auto c : adj[x]){
        if(c == fa) continue;
        dfs(c, x);
    }
}


int LCA(int x, int y) {
    if(dep[x] < dep[y]) swap(x, y);

    int dec = dep[x] - dep[y];
    for(int i = 0;(1<<i) <= dec; ++i){
        if(dec & (1<<i)) x = dp[x][i];
    }


    if(x == y) return y;

    for(int i = 19; i >= 0; i--) {
        if(dp[x][i] != dp[y][i]) {
            x = dp[x][i]; y = dp[y][i];
        }
    }
    return dp[x][0];
}

void dfs_sum(int x, int fa) {
    sum[x] = val[x];
    for(auto c : adj[x]) {
        if(c == fa) continue;
        dfs_sum(c, x);
        sum[x] += sum[c];
    }

}

signed main() {

    caillo;
    cin >> n >> q;
    fi(n-1){
        int t, h; cin >> t >> h;
        adj[t].push_back(h);
        adj[h].push_back(t);
    }

    dfs(1, 0);

    for(int j = 1;j < 20; ++j){
        for(int i = 1; i <= n; ++i) {
            dp[i][j] = dp[dp[i][j-1]][j-1];
        }
    }



    for(int i = 1;i <= q; ++i){
        int x, y; cin >> x >> y;
        int com = LCA(x, y);
        val[x]++;
        val[y]++;
        val[com] -= 1;
        val[dp[com][0]] -= 1; //注意这里
    }

    dfs_sum(1, 0);

    for(int i = 1;i <= n; ++i){
        cout << sum[i] << endl;
    }
}
