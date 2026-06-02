#pragma GCC optimize("Ofast, unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
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
int fa[N], son[N], dep[N], siz[N], dfs_ord[N], idx = 0, top[N], id[N], new_w[N], w[N];
vector<int> adj[N];
void dfs1(int x, int father) {
    fa[x] = father;
    dep[x] = dep[father] + 1;
    siz[x] = 1;

    for(auto c : adj[x]) {
        if(c == father) continue;
        dfs1(c, x);
        siz[x] += siz[c];
        if(!son[x] || siz[son[x]] < siz[c]) {
            son[x] = c;
        }
    }
}

void dfs2(int x, int topx) {
    id[x] = ++idx;
    new_w[idx] = w[x];
    top[x] = topx;
    if(!son[x]) return;
    dfs2(son[x], topx);
    for(auto c : adj[x]) {
        if(c == fa[x] || c == son[x]) continue;

        dfs2(c, c);
    }
}

int tr[N<<2], tag[N<<2];

inline void pushup(int p) {
    tr[p] = max(tr[p<<1] , tr[p<<1|1]);
}

void build(int p = 1, int l = 1, int r = idx) {
    if(l == r){
        tr[p] = new_w[l];
        return;
    }

    int mid = (l + r) >> 1;
    build(p<<1, l, mid);
    build(p<<1|1, mid+1, r);
    pushup(p);
}

inline void addtag(int p, int cl, int cr, int d) {
    tag[p] += d;
    tr[p] += (cr - cl + 1) * d;
}

inline void pushdown(int p, int l, int r) {
    if(tag[p]) {
        int mid = (l + r) >> 1;
        addtag(p<<1, l, mid, tag[p]);
        addtag(p<<1|1, mid+1, r, tag[p]);
        tag[p] = 0;
    }
}


void update(int l, int r, int d, int p = 1, int cl = 1, int cr = idx) {
    if(l <= cl && r >= cr) {
        addtag(p, cl, cr, d);
        return;
    }
    pushdown(p, cl, cr);
    int mid = (cl + cr) >> 1;

    if(l <= mid) update(l, r, d, p<<1, cl, mid);
    if(r > mid) update(l, r, d, p<<1|1, mid+1, cr);

    pushup(p);
}

int query(int l, int r, int p = 1, int cl = 1, int cr = idx) {
    if(l <= cl && r >= cr) {
        return tr[p];
    }
    pushdown(p, cl, cr);
    int mid = (cl + cr) >> 1;
    int sum = 0;
    if(l <= mid) sum = max(query(l, r, p<<1, cl, mid), sum);
    if(r > mid) sum = max(query(l, r, p<<1|1, mid+1, cr), sum);
    return sum;
}

int query_range(int x, int y) {
    int ans = 0;
    while(top[x] != top[y]) {
    if(dep[top[x]] < dep[top[y]]) swap(x, y);
        ans = max(ans, query(id[top[x]], id[x]));
        x = fa[top[x]];
    }

    if(dep[x] > dep[y]) swap(x, y);
    ans = max(ans, query(id[x],id[y]));
    return ans;
}

void update_range(int x, int d){
    update(id[x], id[x], -query(id[x], id[x])+ d);
}

signed main() {
    caillo;
    int n, q; cin >> n >> q;
    fi(n) cin >> w[i];

    fi(n-1) {
        int x, y; cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    dfs1(1, 0);
    dfs2(1, 1);
    build();

    fi(q) {
        int op; cin >> op;
        if(op == 2) {
            int x, y; cin >> x >> y;
            cout << query_range(x, y) << endl;
        }else if(op ==1){
            int u, v; cin >> u >> v;
            update_range(u, v);
        }
    }
}
