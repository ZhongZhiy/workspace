
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

int t;
int n, m;
constexpr int N= 1e5 + 10, M = 998244353;
int a[N];
int two[N<<2], three[N<<2], tag_two[N<<2], tag_three[N<<2];
void build(int p = 1, int l = 1, int r= n){
	tag_three[p] = tag_two[p] = 0;
	if(l == r){
		three[p] = two[p] = 0;
		return;
	}

	int mid = (l + r) >> 1;
	build(p<<1, l, mid);
	build(p<<1|1, mid+1, r);
	three[p] = min(three[p<<1], three[p<<1|1]);
	two[p] = min(two[p<<1], two[p<<1|1]);
}

void pushdown(int p, int l, int r){
	if(l == r) return;
	two[p<<1] += tag_two[p];
	tag_two[p<<1] += tag_two[p];

	three[p<<1] += tag_three[p];
	tag_three[p<<1] += tag_three[p];

	two[p<<1|1] += tag_two[p];
	tag_two[p<<1|1] += tag_two[p];

	three[p<<1|1] += tag_three[p];
	tag_three[p<<1|1] += tag_three[p];
	
	tag_two[p] = tag_three[p] = 0;
}

void update(int l, int r, int x, int p = 1, int cl = 1, int cr = n){
	if(l <= cl && r >= cr) {
		if(x == 2) two[p]++, tag_two[p]++;
		else three[p]++, tag_three[p]++;
		return;
	}

	pushdown(p, cl, cr);
	int mid = (cl + cr) >> 1;
	if(l <= mid) update(l, r, x, p<<1, cl, mid);
	if(r > mid) update(l, r, x, p<<1|1, mid + 1, cr);

	three[p] = min(three[p<<1], three[p<<1|1]);
	two[p] = min(two[p<<1], two[p<<1|1]);
}

int qpow(int base, int factor){
	int ans = 1;
	while(factor){
		if(factor&1) ans = ans * base % M;
		base = base * base % M;
		factor >>= 1;
	}
	return ans % M;
}

void solve(){
	cin >> n >> m;
	build(1, 1, n);
	fi(m){
		int l, r, x; cin >> l >> r >> x;
		update(l, r, x, 1, 1, n);
	}

	cout << qpow(2, two[1]) % M * qpow(3, three[1]) % M << endl;
}

signed main() {
	// freopen("an", "r", stdin);
	caillo;

	cin >> t;
	while(t--) solve();

	PLEASE_AC;
}
