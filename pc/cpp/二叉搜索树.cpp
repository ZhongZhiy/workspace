#include <climits>
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

constexpr int N = 1e3 + 10, INF = INT_MAX;
struct BST{
    int l, r;
    int val;
} a[N];
int tot, root;

int New(int val) {
    a[++tot].val = val;
    return tot;
}

void Build() {
    New(-INF), New(INF);
    root = 1, a[1].r = 2;
}

int Get(int p, int val){
    if(p == 0) return 0;
    if(val == a[p].val) return p;
    return val < a[p].val ? Get(a[p].l, val) : Get(a[p].r, val);
}

void Insert(int &p, int val){
    if(p == 0) {
        p = New(val);
        return;
    }
    if(val == a[p].val) return;
    if(val > a[p].val) Insert(a[p].l, val);
    else Insert(a[p].r, val);
}

int GetNext(int val) {
    int ans = 2; // a[2].val == INF
    int p = root;
    while(p) {
        if(val == a[p].val){
            if(a[p].r > 0) {
                p = a[p].r;
                while(a[p].l > 0) p = a[p].l;
                ans = p;
            }
            break;
        }
        if(a[p].val > val && a[p].val < a[ans].val) ans = p;
        p = val < a[p].val ? a[p].l : a[p].r;
    }
    return ans;
}

void Remove(int &p, int val) {
    if(p == 0) return;
    if(val == a[p].val){
        if(a[p].l == 0){
            p = a[p].r;
        } else if(a[p].r == 0){
            p  = a[p].l;
        }else {
            int next = a[p].r;
            while(a[next].l > 0) next = a[next].l;
            Remove(a[p].r, a[next].val);
            a[next].l = a[p].l, a[next].r = a[p].r;
            p = next;
        }
        return;
    }
    if(val < a[p].val) {
        Remove(a[p].l, val);
    }else {
        Remove(a[p].r, val);
    }
}



signed main() {
    hello;

    // Build();
    int n; cin >> n;
    if(n == 1){
        int val; cin >> val;
        cout << val << endl;
        cout << "YES\n";
    }else if(n >= 2){
        int val1, val2; cin >> val1 >> val2;
        New(val1); New(val2);
        root = 1;
        if(val1 < val2) a[root].l = 2;
        else a[root].r = 2;
        for(int i = 3;i <= n; ++i) {
            int val ; cin >> val;
            Insert(root, val);
        }
        queue<int> q;
        q.push(root);
        int cnt = 0;
        vi ans;

        bool fs = 1;
        bool ok = 0;
        while(!q.empty()) {
            int id = q.front(); q.pop();
            if(id) ans.push_back(a[id].val);
            if(!id && fs){
                fs = 0;
                if(ans.size() == tot){
                    ok = 1;
                }else ok = 0;
                break;
            }
            q.push(a[id].l);
            q.push(a[id].r);
        }

        while(!q.empty()) q.pop();
        ans.clear();
        q.push(root);

        while(!q.empty()) {
            int id = q.front();
            q.pop();
            ans.push_back(a[id].val);
            if(a[id].l) q.push(a[id].l);
            if(a[id].r) q.push(a[id].r);
        }
        for(int i = 0;i < ans.size(); ++i) cout << (i ? " " : "") << ans[i];
        cout << endl;
        cout << (ok?"YES\n":"NO\n");
    }
    world;
}
