#include <pthread.h>
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;

#define DEBUG
#ifdef DEBUG
#define de(x) cout << (#x) << "=" << (x) << endl;
#define de2(x, y) cout << (#x) << " " << (#y) << " = " << (x) << " " << (y) << endl;
#else
#define de(x)
#define de2(x, y)
#endif
#define endl '\n'
#define fi(n) for(int i = 1;i <= n; ++i)
#define fi0(n) for(int i = 0;i < n; ++i)
#define fj(n) for(int j = 1;j <= n; ++j)
#define all(x) (x).begin(), (x).end()
#define hello ios::sync_with_stdio(0); cin.tie(0);cout.tie(0);
#define world return 0;
#define int long long
typedef vector<int> vi;
#define F first
#define S second
typedef pair<int, int> pii;
typedef vector<vector<int>> vvi;
typedef long long ll;

constexpr int N = 1e5;
int fa[N][20], dp[N];
vi e[N];

void init(int x){
    for(int i = 1;i < 20; ++i) fa[x][i] = fa[fa[x][i-1]][i-1];
    for(auto &c : e[x]){
        if(c == fa[x][0]) continue;
        dp[c] = dp[x] + 1;
        init(c);
    }
}

int lca(int x, int y){
    if(dp[x] < dp[y]) swap(x, y);
    for(int d = dp[x] - dp[y], i = 0; d; d >>= 1, i++){
        if(d&1) x = fa[x][i];
    }
    if(x == y) return x;
    for(int i = 20;i ; i--){
        if(fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    }
}

void solve(){

}

signed main() {
    hello;
    solve();

    world;
}
