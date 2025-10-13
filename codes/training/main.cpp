
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
const int N = 1e7;
int a[N], b[N], c[N];
int ca, cb, cc;


signed main() {
//	freopen("an", "r", stdin);
	caillo;

	int t;
	while(cin >> t && t != -1){
		a[++ca] = t;
	}
	while(cin >> t && t != -1){
		b[++cb] = t;
	}
	if(!ca && !cb) cout << "NULL";
	else {
		int l = 1, r = 1;
		while(l <= ca || r <= cb){
			if(l <= ca && a[l] <= b[r]) c[++cc] = a[l++];
			else c[++cc] = b[r++];
		}

		fi(cc){
			cout << c[i];
			if(i!= cc) cout << ' ';
		}
	}

	PLEASE_AC;
}
