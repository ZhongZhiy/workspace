## 题意
求数列中互质的对数

## 题解
对于考虑数$g$, 在数列中有$k$个$g$的倍数, 那么这$k$个数就互不互质, 那么用所有的对数减去不互质的对数就是答案, 但是, 考虑到, 一个数可能是多个数的倍数, 那么就会被减去多次, 那么就需要考虑容斥原理了, 而容斥原理的符号很难处理, 这就需要用到[[莫比乌斯函数]]来处理, 对于



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

const int N = 1e5 + 10;
const int M = 1e6 + 10;

vector<int> primer;
int mu[M], vis[M];
//线性筛莫比乌斯函数, primer = -1, 合数为0, 奇数个primer为-1, 偶数个为1
void precount_mu(int x) {
    mu[1] = 1;
    for(int i = 2;i <= x; ++i) {
        if(!vis[i]) {
            primer.push_back(i);
            mu[i] = -1;
        }
        for(int j = 0;j < primer.size() && i * primer[j] <= x; ++j) {
            vis[i*primer[j]] = 1;
            if(i % primer[j] == 0) {
                mu[i*primer[j]] = 0;
                break;
            }
            mu[i*primer[j]] = - mu[i];
        }
    }
}

int a[M];
signed main() {
    hello;
    int n; cin >> n;
    int mx = 0;

    fi0(n) {
        int t; cin >> t;
        a[t] ++;
        mx = max(mx, t);
    }

    
    
    precount_mu(mx);

    int total_pars = 0;
    for(int i = 1;i <= mx; ++i) {
        if(mu[i] == 0) continue;
        int total = 0;
        for(int j = i;j <= mx; j += i) {
            total += a[j];
        }
        //从total中选两个组合
        int pars = total * (total - 1) / 2;
        total_pars += mu[i] * pars;
    }
    cout << total_pars << endl;
}


```