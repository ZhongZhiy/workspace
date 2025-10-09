
#include<bits/stdc++.h>
#include <chrono>
using namespace std;
#define i128 __int128
#define de(x) cout << (#x) << " = " << (x) << endl;
#define de2(x, y) cout << (#x) << " , " << (#y) << " = " << (x) << " ~ " << (y) << endl;
#define endl '\n'
#define fi(x) for(int i = 1; i <= x; ++i)
#define fi0(x) for(int i = 0; i < x; ++i)
#define fj(n) for(int j = 1; j <= n; ++j)
#define fj0(n) for(int j = 0; j < n; ++j)
#define startime auto start = chrono::high_resolution_clock::now();
#define endtime auto end = chrono::high_resolution_clock::now();
#define runningtime cout << "running time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count()<<" ms\n";
#define caillo ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define PLEASE_AC return 0
typedef long long ll;
typedef unsigned long long ull;
#define int long long 

int t, m, n;
const int M = 998244353;
int qpow(int base, int factor){
	int pow = 1;
	while(factor){
		if(factor&1) pow = pow * base % M;
		base = base * base % M;
		factor >>= 1;
	}
	return pow % M;
}

int inv(int k){
	return qpow(k, M-2);
}
int p[22], q[22], idxp, idxq;
int ans = 0;
bool vis[20];

void dfs(int x, int idx, int val, int pi, int pid, int alph){

	// for(int i = idx + 1;i <= m; ++i){
	// 	if(!vis[i]){
	// 		vis[i] = 1;
	// 		dfs(x+1, i, val, pi*p[i]%M, pid * (p[i]-1)%M, alph*q[i] % M);
	// 		vis[i] = 0;
	// 	}
	// }
	//
	ans += val * inv(pi) % M * pid % M * alph % M;
	ans %= M;
	return;
}


const int N = 2e6;
int dp[N];

void solve(){
	cin >> m;
	
	memset(vis, 0, sizeof(ans));
	n = 1;
	idxp = idxq = 0;
	fi(m){
		int pp, qq; cin >> pp >> qq;
		p[++idxp] = pp;
		q[++idxq] = qq;
		n = n * qpow(pp, qq) % M;
	}

	ans = 0;
	dfs(0, 0, n, 1, 1, 1);
	cout << ans << endl;
}

signed main() {
	// freopen("an", "r", stdin);
	startime;

	caillo;
	cin >> t;
	while(t--) solve();
	endtime;
	runningtime;


	PLEASE_AC;
}
