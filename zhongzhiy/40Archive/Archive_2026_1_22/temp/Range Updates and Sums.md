```cpp fold
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
typedef pair<int, int> pii;
typedef long long ll;

const int N = 2e5 + 10;
int tr[N<<2], tagc[N<<2], tagi[N<<2];
int a[N];
int n, m;

void pushup(int p) {
    tr[p] = tr[p<<1] + tr[p<<1|1];
}

void build(int p = 1, int l = 1, int r = n) {
    if(l == r) {
        tr[p] = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(p<<1, l, mid);
    build(p<<1|1, mid+1, r);
    pushup(p);
}


void pushdown(int p, int l, int r){
    int mid = (l + r) >> 1;
    if(tagc[p]) {
        tr[p<<1] = (mid-l+1) * tagc[p];
        tr[p<<1|1] = (r - mid) * tagc[p];
        tagc[p<<1] = tagc[p<<1|1] = tagc[p];
        tagi[p<<1] = tagi[p<<1|1] = 0;
        tagc[p] = 0;
    }
    if(tagi[p]) {
        tr[p<<1] += (mid-l+1) * tagi[p];
        tr[p<<1|1] += (r-mid) * tagi[p];
        tagi[p<<1] +=  tagi[p];
        tagi[p<<1|1] += tagi[p];
        tagi[p] = 0;
    }
}
void addtagc(int d, int p, int l, int r) {
    tagi[p] = 0;
    tagc[p] = d;
    tr[p] = (r - l + 1) * d;
}
void addtagi(int d, int p, int l, int r) {
    tagi[p] += d;
    tr[p] += (r - l + 1) * d;
}

void updatec(int a, int b, int d, int p = 1, int cl = 1, int cr = n) {
    if(a <= cl && b >= cr) {
        addtagc(d, p, cl, cr);
        return;
    }
    pushdown(p, cl, cr);
    int mid = (cl + cr) >> 1;
    if(a <= mid) updatec(a, b, d, p<<1, cl, mid);
    if(b > mid) updatec(a, b, d, p<<1|1, mid+1, cr);
    pushup(p);
}


void updatei(int a, int b, int d, int p = 1, int cl = 1, int cr = n) {
    if(a <= cl && b >= cr) {
        addtagi(d, p, cl, cr);
        return;
    }
    pushdown(p, cl, cr);
    int mid = (cl + cr) >> 1;
    if(a <= mid) updatei(a, b, d, p<<1, cl, mid);
    if(b > mid) updatei(a, b, d, p<<1|1, mid+1, cr);
    pushup(p);
}

int query(int a, int b, int p = 1, int cl = 1, int cr = n) {
    if(a <= cl && b >= cr) {
        return tr[p];
    }
    pushdown(p, cl, cr);
    int mid = (cl + cr) >> 1;
    int ans = 0;
    if(a <= mid) ans += query(a, b, p<<1, cl, mid);
    if(b > mid) ans += query(a, b, p<<1|1, mid+1, cr);
    return ans;
}

signed main() {
    hello;
    cin >> n >> m;
    fi(n) cin >> a[i];
    build();

    fi(m) {
        int op; cin >> op;
        if(op == 1) {
            int a, b, x; cin >> a >> b >> x;
            updatei(a, b,x);
        }else if(op == 2) {
            int a, b, x; cin >> a >> b >> x;
            updatec(a, b, x);
        }else {
            int a, b; cin >> a >> b;
            cout << query(a, b) << '\n';
        }
    }
}


```