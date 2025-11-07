
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

const int N = 1e6 + 10;
int a[N];
void solve(){
	int n; cin >> n;
	fi(n) cin >> a[i];
	int m; cin >> m;

	fi(m){
		string s; cin >> s;
		// de2(i, s)
		if(s.size() != n){
			cout << "NO\n";
			continue;
		}
		de2(i, s)

		map<char, int> mp;
		bool si = 0;
		for(int j = 0;j < n; ++j){
			if(mp.count(s[j]) == 0) mp[s[j]] = a[j];
			else {
				if(mp[s[j]] != a[j]){
					cout << "NO\n";
					si = 1;
					break;
				}
			}
		}

		if(si) continue;

		map<int, char> mm;
		fj(n){
			if(mm.count(a[j]) == 0) mm[a[j]] = s[j-1];
			else{
				if(mm[a[j]] != s[j-1]){
					cout << "NO\n";
					si = 1;
					break;
				}
			}
		}

		if(!si) 
			cout << "YES\n";
	}
}
signed main() {
//	freopen("an", "r", stdin);
	caillo;
	int t; cin >> t;
	while(t--) solve();


	PLEASE_AC;
}

