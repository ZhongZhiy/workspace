
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

const int N = 3e5 + 10;
int a[N];
void solve(){
	int n; cin >> n;
	fi(n) cin >> a[i];
	int mx = 0;
	vector<int> ans;
	fi(n){
		if(a[i] > mx)
			mx = a[i];
		else if(a[i] < mx)
			ans.push_back(mx-a[i]);
	}
	sort(ans.begin(), ans.end());
	int total = 0, sz = ans.size() + 1;
	for(int i = 0;i < ans.size(); ++i){
     		int cn = 0;
     		if(i == 0) cn = ans[0];
     		else cn = ans[i] - ans[i-1];
		total += (sz-i) * cn;
	}
	cout << total << endl;
}

signed main() {
//	freopen("an", "r", stdin);
	caillo;
	int t; cin >> t;
	while(t--) solve();


	PLEASE_AC;
}
