求区间求和, 区间等差修改

```cpp fold
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
int tr[N<<2], tag_times[N<<2], tag_add[N<<2];

int ab[N];
int n;
void pushup(int p) {
    tr[p] = tr[p<<1] + tr[p<<1|1];
}

void build(int p = 1, int l = 1, int r = n) {
    if(l == r) {
        tr[p] = ab[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(p<<1, l, mid);
    build(p<<1|1, mid+1, r);
    pushup(p);
}

void pushdown(int p, int l, int r) {
    int mid = (l + r) >> 1;
    if(tag_times[p]) {
        tag_times[p<<1] += tag_times[p];
        tag_times[p<<1|1] += tag_times[p];
        tr[p<<1] += tag_times[p] * (l + mid) * (mid - l + 1) / 2;
        tr[p<<1|1] += tag_times[p] * (r + mid+1) * (r - mid) / 2;
        tag_times[p] = 0;
    }

    if(tag_add[p]) {
        tag_add[p<<1] += tag_add[p];
        tag_add[p<<1|1] += tag_add[p];
        tr[p<<1] += (mid-l+1) * tag_add[p];
        tr[p<<1|1] += (r - mid) * tag_add[p];
        tag_add[p] = 0;
    }
}
void addtag(int a, int p, int l, int r) {
    tag_times[p] += 1;
    tag_add[p] += 1- a;
    tr[p] += (r - l + 1) * (r + l) / 2;
    tr[p] += (r - l + 1)* ( 1 - a);
}
void update(int a, int b, int p = 1 ,int cl = 1, int cr = n) {
    if(a <= cl && b >= cr) {
        addtag(a, p, cl, cr);
        return;
    }
    pushdown(p, cl, cr);
    int mid = (cl + cr) >> 1;
    if(a <= mid) update(a, b, p<<1, cl, mid);
    if(b > mid) update(a, b, p<<1|1, mid+1, cr);
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
    int m; cin >> n >> m;
    fi(n) cin >> ab[i];
    build();

    fi(m){
        int op, a, b; cin >> op >> a >> b;
        if(op == 1) {
            update(a, b);
        }else {
            cout << query(a, b) << endl;
        }
    }
}


```