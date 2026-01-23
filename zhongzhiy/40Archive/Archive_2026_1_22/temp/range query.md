## Subarray Sum Queries
动态求最大子区间

```cpp fold
#include<bits/stdc++.h>
using namespace std;

#define DEBUG
#ifdef DEBUG
#define de(x) cout << (#x) << "=" << (x) << endl;
#define de2(x, y) cout << (#x) << " " << (#y) << " = " << (x) << " " << (y) << endl;
#else
#define de(x) 42
#define de2(x, y) 42
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
typedef pair<int, int> pii;
typedef long long ll;

const int N = 2e5 + 10;
struct Node {
    int pre, suf, sum, mx;
    Node(){}
    Node(int pre, int suf, int sum, int mx): pre(pre), suf(suf), sum(sum), mx(mx){}
};
Node tr[N<<2];
int a[N];
int n;

void pushup(int p) {
    tr[p].sum = tr[p<<1].sum + tr[p<<1|1].sum;
    tr[p].pre = max(tr[p<<1].pre, tr[p<<1|1].pre+tr[p<<1].sum);
    tr[p].suf = max(tr[p<<1].suf+tr[p<<1|1].sum, tr[p<<1|1].suf);
    tr[p].mx = max({tr[p<<1].mx, tr[p<<1|1].mx, tr[p<<1].suf+tr[p<<1|1].pre});
}
void build(int p = 1, int l = 1, int r = n) {
    if(l == r) {
        tr[p] = {max(0LL, a[l]), max(0LL, a[l]), a[l], max(0LL, a[l])};
        return;
    }

    int mid = (l + r) >> 1;
    build(p<<1, l, mid);
    build(p<<1|1, mid+1, r);
    pushup(p);
}

void update(int l, int r, int d, int p = 1, int cl = 1, int cr = n) {
    if(l <= cl && r >= cr) {
        tr[p] = {max(0LL, d),max(0LL, d),d,max(0LL, d)};
        a[l] = d;
        return;
    }
    int mid = (cl + cr) >> 1;
    if(l <= mid) update(l, r, d, p<<1, cl, mid);
    if(r > mid) update(l, r, d, p<<1|1, mid+1, cr);
    pushup(p);
}

signed main() {
    hello;
    int m; cin >> n >> m;
    fi(n) cin >> a[i];
    build();

    fi(m) {
        int k, x; cin >> k >> x;
        update(k, k, x);
        cout << tr[1].mx << endl;
    }
}


```

## Subarray Sum Queries II

```cpp fold
#include<bits/stdc++.h>
using namespace std;

#define DEBUG
#ifdef DEBUG
#define de(x) cout << (#x) << "=" << (x) << endl;
#define de2(x, y) cout << (#x) << " " << (#y) << " = " << (x) << " " << (y) << endl;
#else
#define de(x) 42
#define de2(x, y) 42
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
typedef pair<int, int> pii;
typedef long long ll;

const int N = 2e5 + 10;
struct Node {
    int pre, suf, sum, mx;
    Node(){}
    Node(int pre, int suf, int sum, int mx): pre(pre), suf(suf), sum(sum), mx(mx){}
};
Node tr[N<<2];
int a[N];
int n;

Node pushup(Node L, Node R) {
    return {max(L.pre, L.sum+R.pre),
        max(R.suf, L.suf+R.sum),
        L.sum+R.sum,
        max({R.mx, L.mx, L.suf+R.pre})};
}
void build(int p = 1, int l = 1, int r = n) {
    if(l == r) {
        tr[p] = {max(0LL, a[l]), max(0LL, a[l]), a[l], max(0LL, a[l])};
        return;
    }

    int mid = (l + r) >> 1;
    build(p<<1, l, mid);
    build(p<<1|1, mid+1, r);
    tr[p] = pushup(tr[p<<1], tr[p<<1|1]);
}

void update(int l, int r, int d, int p = 1, int cl = 1, int cr = n) {
    if(l <= cl && r >= cr) {
        tr[p] = {max(0LL, d),max(0LL, d),d,max(0LL, d)};
        a[l] = d;
        return;
    }
    int mid = (cl + cr) >> 1;
    if(l <= mid) update(l, r, d, p<<1, cl, mid);
    if(r > mid) update(l, r, d, p<<1|1, mid+1, cr);
    tr[p] = pushup(tr[p<<1], tr[p<<1|1]);
}

Node query(int l, int r, int p = 1, int cl = 1, int cr = n ) {
    if(l <= cl && r >= cr) {
        return tr[p];
    }
    int mid = (cl + cr) >> 1;
    if(r <= mid) return query(l, r, p<<1, cl, mid);
    if(l > mid) return query(l, r, p<<1|1, mid+1, cr);
    return pushup(query(l, r, p<<1, cl, mid),
        query(l, r, p<<1|1, mid+1, cr));
}
signed main() {
    hello;
    int m; cin >> n >> m;
    fi(n) cin >> a[i];
    build();

    fi(m) {
        int x, y; cin >> x >> y;
        cout << query(x, y).mx << endl;
    }
}


```

## Distinct Values Queries
可持久化线段树

```cpp fold
#include <algorithm>
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
// #define int long long
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef long long ll;

const int N = 2e5 + 10;
struct Node {
    int l, r, val;
    Node(){}
    Node(int l, int r, int val):l(l), r(r), val(val){}
};

Node tr[N*40];
int a[N], root[N], idx;

int update(int pre, int x, int d, int l, int r) {
    int cur = ++idx;
    tr[cur] = tr[pre];
    if(l == r) {
        tr[cur].val += d;
        return cur;
    }
    int mid = (l + r) >> 1;
    if(x <= mid) tr[cur].l = update(tr[pre].l, x, d, l, mid);
    else tr[cur].r = update(tr[pre].r, x, d, mid+1, r);
    tr[cur].val = tr[tr[cur].l].val + tr[tr[cur].r].val;
    return cur;
}

int query(int l, int r, int p, int cl, int cr) {
    if(l <= cl && r >= cr) {
        return tr[p].val;
    }
    int mid = (cl + cr) >> 1;
    int res = 0;
    if(l <= mid) res += query(l, r, tr[p].l, cl, mid);
    if(r > mid) res += query(l, r, tr[p].r, mid+1, cr);
    return res;
}

signed main() {
    hello;
    int n, m; cin >> n>> m;
    map<int, int> mp;
    fi(n) {
        cin >> a[i];
    }
    fi(n) {
        if(mp.count(a[i])) {
            int tp = update(root[i-1], mp[a[i]], -1, 1, n);
            root[i] = update(tp, i, 1, 1, n);
        }else {
            root[i] = update(root[i-1], i, 1, 1, n);
        }
        mp[a[i]] = i;
    }

    fi(m) {
        int x, y; cin >> x >> y;
        cout << query(x, y, root[y], 1, n) << endl;
    }
    world;

}


```

##