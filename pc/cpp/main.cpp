#include <algorithm>
#include <cctype>
#include <climits>
#include <functional>
#include <numeric>
#include <queue>
#include <set>
#include <vector>
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
/*
(\_/)                /\_/\         (o_o)
( ._.)   \(o_o)/    (-.-  )       /(   )\
/ >*                /< *< \        ^^ ^^
*/
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
#define fj0(n) for(int j = 0;j < n; ++j)
#define all(x) (x).begin(), (x).end()
#define hello ios::sync_with_stdio(0); cin.tie(0);cout.tie(0);
#define world return 0;
#define int long long
#define F first
#define S second
typedef __int128 i128;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef long long ll;

constexpr int N = 60;
bool flag;
int a[N+1], tmp[N+1];

void insert(int x){
    for(int i = N; ~i; i--){
        if(x & (1LL<<i)){
            if(!a[i]){
                a[i] = x; return;
            }else x ^= a[i];
        }
    }
    flag = true;
}

bool check(int x){
    for(int i = N; ~i; --i){
        if(x & (1LL<<i)){
            if(!a[i]) return false;
            else x ^= a[i];
        }
    }
    return 1;
}

int query(int k){
    int res = 0;
    int cnt = 0;
    k -= flag;
    if(!k)return 0;
    for(int i = 0;i <= N; ++i){
        for(int j = i - 1; ~j; j--){
            if(a[i] & (1LL<<j)){
                a[i] ^= a[j];
            }
        }
        if(a[i])tmp[cnt++] = a[i];
    }
    if(k >= (1LL<<cnt)) return -1;
    for(int i = 0;i < cnt; ++i) {
        if(k & (1LL<<i)) res ^= tmp[i];
    }
    return res;
}

int get_max(int x){
    for(int i = N; ~i; --i){
        if(a[i] && x < (x^(1LL<<i))) x ^= (1LL<<i);
    }
    return x;
}

void solve(){
    memset(a, 0, sizeof(a));
    memset(tmp, 0, sizeof(tmp));
    int n, len, q; cin >> n >> len >> q;
    fi(n){
        int x; cin >> x;
        insert(x);
    }
    fi(q){
        int x; cin >> x;
        int res = get_max(x);
        cout << res << endl;
    }


}

signed main() {
    hello;
    //freopen("cpp/input.txt", "r", stdin);
    int t = 1;
    cin >> t;
    while(t--) solve();
    return 0;
}
