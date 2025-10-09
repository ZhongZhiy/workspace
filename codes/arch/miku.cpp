#include<cmath>
#include<iostream>
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
typedef long long ll;
typedef unsigned long long ull;
#define int long long 

const int N = 1e5 + 10;

int lg[10*N], a[N], head[N], lghead[N*10];

void init(){
	for(int i = 2;i < 10*N; ++i) {
		lg[i] = lg[i/2] + 1;
		lghead[i] = lghead[i-1] + lg[i];
	}
}

inline int getlg(int x){
	if(x < 10*N) return lg[x];
	return log2(x);
}

int n, ans = 0;

void solve(){
	cin >> n;

	ans = 0;
	fi(n){cin >> a[i]; head[i] = head[i-1] + a[i];}

	for(int i = 1;i <= n; ++i)
		for(int j = i;j <= n; ++j) {
			ans += (getlg(head[j] - head[i-1])+1) * (i+ j);
		}

	cout << ans << endl;
		
}

signed main() {
//	freopen("an", "r", stdin);
	caillo;

	init();

	int t; cin >> t;

	while(t--) solve();


	PLEASE_AC;
}
