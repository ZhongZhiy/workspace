[[约数计算]]
值得注意的是, 计算约数相乘时: $$mut = n^{\frac{cnt}{2} mod (M-1) mod M}$$
$\frac{cnt}{2}mo d (M-1)$, 由于$M -1$不是素数, 不能用费马小定理算$2$的逆元, 需要在统计$cnt$的途中处理$2$
当$n$是完全平方的时候, $m ut = \sqrt{ n }^{cnt}$

## 参考代码
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

const int M = 1e9 + 7;
int qpow(int base, int pow) {
    int res = 1;
    while(pow) {
        if(pow&1) res = (res * base) % M;
        base = (base * base) % M;
        pow >>= 1;
    }
    return res;
}

int rev(int x) {
    return qpow(x, M-2);
}

int muts(int a, int b){
    a %= M;
    b %= M;
    int res = 0;
    while(b) {
        if(b&1) res = (res + a) % M;
        a = (a + a) % M;
        b >>= 1;
    }
    return res;
}

signed main() {
    hello;
    int n; cin >> n;
    vi a(n+1), b(n+1);
    int cnt = 1, sum = 1, mut = 1, pcnt = 1;
    int od = 0, onl = 0;
    fi(n){
        cin >> a[i] >> b[i];
        cnt = (cnt * (1 + b[i])) % M;
        if(!onl && b[i]&1) {
            pcnt = (pcnt * (1+b[i])/2 %(M-1));
            // de(pcnt )
            onl = 1;
        }else
            pcnt = (pcnt * (1 + b[i])) % (M - 1);
        if(b[i]&1) od = 1;
    }

    fi(n) {
        sum = muts(muts(qpow(a[i], b[i]+1)-1 + M, rev(a[i]-1)) , sum);
    }

    int num = 1;
    if(od) {
        int pow = pcnt;
        // de2(num, pow)
        fi(n){
            num = muts(num ,qpow(a[i], b[i]));
        }
        mut = qpow(num, pow);
    }else {
        fi(n) {
            num = muts(num, qpow(a[i], b[i]/2));
        }
        int pow = pcnt;
        mut = qpow(num, pow);
    }
    // de2(num, pow)
    cout << cnt << ' ' << sum << ' ' << mut << endl;


}


```