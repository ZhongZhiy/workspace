
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
typedef long long ll;
typedef unsigned long long ull;
#define int long long 

const int N = 1e5 + 10;
int n;
vector<int> v[N];


signed main() {
//	freopen("an", "r", stdin);
	caillo;

	cin >> n;
	fi(n - 1){
		int x, y; cin >> x >> y;
		v[x].push_back(y);
		v[y].push_back(x);
	}

	PLEASE_AC;
}
