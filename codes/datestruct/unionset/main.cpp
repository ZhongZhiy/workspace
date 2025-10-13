
#include<bits/stdc++.h>
using namespace std;
#define i128 __int128
#define de(x) cout << (#x) << " = " << (x) << endl;
#define de2(x, y) cout << (#x) << " , " << (#y) << " = " << (x) << " ~ " << (y) << endl;
#define endl '\n'
#define fi(x) for(int i = 1; i <= x; ++i)
#define fi0(x) for(int i = 0; i < x; ++i)
#define fj(n) for(int j = 1; j <= n; ++j)
#define fj0(n) for(int j = 0; j < n; ++j)
#define caillo ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define PLEASE_AC return 0
#define startime auto start = chrono::high_resolution_clock::now();
#define endtime auto end = chrono::high_resolution_clock::now();
#define runningtime cout << "running time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count()<<" ms\n";
typedef long long ll;
typedef unsigned long long ull;
#define int long long 

constexpr int N = 1005;
int t, n, m;
int fa[N];

void init(){
	for(int i = 0;i < N; ++i) fa[i] = i;
}

int find(int x){
	if(fa[x] != x)
		fa[x] = find(fa[x]);
	return fa[x];
}

void merge(int x, int y){
	fa[find(x)] = find(y);
}

void solve(){
	init();
	cin >> n>> m;
	fi(m){
		int x, y; cin >> x >> y;
		merge(x, y);
	}

	int cnt = 0;
	fi(n){
		if(fa[i] == i) cnt ++;
	}

	cout << cnt;
}

signed main() {
//	freopen("an", "r", stdin);
	caillo;

	cin >> t;
	while(t--) {solve();if(t != 0) cout << endl;}

	PLEASE_AC;
}
