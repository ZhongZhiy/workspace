
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

constexpr int N = 1e5 + 10, M = 1e4 + 7;
int sum[N<<2], sumde[N<<2], sumth[N<<2], tadd[N<<2], tmul[N<<2], tch[N<<2], a[N];
int n, m;

void init(){
	for(int i = 0;i < (N<<2); ++i){
		sum[i] = sumde[i] = sumth[i] = tadd[i] = tmul[i] = tch[i] = 0;
	}
}
void pushup(int p){
	sum[p] = sum[p<<1] + sum[p<<1|1] % M;
	sumde[p] = sumde[p<<1] + sumde[p<<1|1] % M;
	sumth[p] = sumth[p<<1] + sumth[p<<1|1] % M;
}

void build(int p = 1, int l = 1, int r = n){
	if(l == r) {
		sum[p] = a[l];
		sumde[p] = a[l] * a[l] % M;
		sumth[p] = sumde[p] * a[l] % M;
		return;
	}

	int mid = (l + r) >> 1;
	build(p<<1, l, mid);
	build(p<<1|1, mid+1, r);
	pushup(p);
}

void chtag(int p, int l, int r, int d){
	tadd[p] = 0;
	tch[p] = d;
	int len = r - l + 1;
	sum[p] = d * len % M;
	sumde[p] = d*d % M*len % M;
	sumth[p] = d*d%M*d%M*len%M;
}

void addtag(int p, int l, int r, int d){
	if(tch[p]){
		chtag(p, l, r, d+tch[p]);
		return;
	}

	tadd[p] += d;
	tadd[p] %= M;
	sumth[p] += 3 * d%M  * sumde[p]%M + 3 * d%M * d%M * sum[p]%M + d * d%M * d%M * (r - l + 1)%M;
	sumth[p] %= M;
	sumde[p] += 2 * d%M  * sum[p]%M + d * d%M * (r - l + 1)%M;
	sumde[p] %= M;
	sum[p] += d * (r - l + 1)%M;
	sum[p] %= M;
}

void multag(int p, int l, int r, int d){
	if(tch[p]){
		chtag(p, l, r, d*tch[p]);
		return;
	}

	tadd[p] *= d;
	tadd[p] %= M;
	sum[p] *= d;
	sum[p] %= M;
	sumde[p] *= d * d;
	sumde[p] %= M;
	sumth[p] *= d * d * d;
	sumth[p] %= M;
}


void pushdown(int p, int l, int r) {
	if(l == r) return;
	int mid = (l + r) >> 1;
	int lenl = (mid - l + 1);
	int lenr = (r - mid);
	if(tch[p]){
		tch[p<<1] = tch[p]%M;
		sum[p<<1] = tch[p] * lenl%M;
		sumde[p<<1] = sum[p<<1] * tch[p] * lenl%M;
		sumth[p<<1] = sumde[p<<1] * tch[p]%M;

		tch[p<<1|1] = tch[p]%M;
		sum[p<<1|1] = tch[p] * lenr%M;
		sumde[p<<1|1] = sum[p<<1|1] * tch[p] %M;
		sumth[p<<1|1] = sumde[p<<1|1] * tch[p]%M;
		tch[p] = 0;
		return;
	}

	if(tadd[p]){
		sum[p<<1] += tadd[p] * lenl%M;
		sum[p<<1] %= M;
		sumde[p<<1] += tadd[p] * tadd[p]  %M * lenl%M;
		sumde[p<<1] %= M;
		sumth[p<<1] += tadd[p] * tadd[p] %M* tadd[p] %M* lenl%M;
		sumth[p<<1] %= M;
		tadd[p<<1] += tadd[p];
		tadd[p<<1] %= M;

		sum[p<<1|1] += tadd[p] * lenr%M;
		sum[p<<1|1] %= M;
		sumde[p<<1|1] += tadd[p] * tadd[p]%M * lenr%M;
		sumde[p<<1|1] %= M;
		sumth[p<<1|1] += tadd[p] * tadd[p]%M * tadd[p]%M * lenr%M;
		sumth[p<<1|1] %= M;
		tadd[p<<1|1] += tadd[p];
		tadd[p<<1|1] %= M;
		tadd[p] = 0;
	}
}
void update_add(int l, int r, int d, int p = 1, int cl = 1, int cr = n) {
	if(l <= cl && r >= cr){
		addtag(p, cl, cr, d);
		return;
	}
	pushdown(p, cl, cr);

	int mid = (cl + cr) >> 1;
	if(mid <= l) update_add(l, r, d, p<<1, cl, mid);
	if(mid > r) update_add(l, r, d, p<<1|1, mid +1 , cr);
	pushup(p);
}

void update_mul(int l, int r, int d, int p = 1, int cl = 1, int cr = n) {
	if(l <= cl && r >= cr) {
		multag(p, cl, cr, d);
		return;
	}

	pushdown(p, cl, cr);
	int mid = (cl + cr) >> 1;

	if(mid <= l) update_mul(l, r, d, p<<1, cl, mid);
	if(mid > l) update_mul(l, r, d, p<<1|1, mid + 1, cr);
	pushup(p);
}

void update_ch(int l, int r, int d, int p = 1, int cl = 1, int cr = n){
	if(l <= cl && r >= cr){
		chtag(p, cl, cr, d);
		return;
	}
	pushdown(p, cl, cr);
	int mid = (cl + cr) >> 1;
	if(mid <= l) update_ch(l, r, d, p<<1, cl, mid);
	if(mid > l) update_ch(l, r, d, p<<1|1, mid + 1, cr);
	pushup(p);
}

int query_sum(int l, int r, int p = 1, int cl = 1, int cr = n){
	if(l <= cl && r >= cr){
		return sum[p] % M;
	}
	pushdown(p, cl, cr);

	int mid = (cl + cr) >> 1;
	int ans = 0;
	if(mid <= l) ans += query_sum(l, r, p<<1, cl, mid) % M;
	if(mid > r) ans += query_sum(l, r, p<<1|1, mid+1, cr) % M;
	return ans % M;
}

int query_sumde(int l, int r, int p = 1, int cl = 1, int cr = n){
	if(l <= cl && r >= cr){
		return sumde[p] % M;
	}
	pushdown(p, cl, cr);

	int mid = (cl + cr) >> 1;
	int ans = 0;
	if(mid <= l) ans += query_sumde(l, r, p<<1, cl, mid) % M;
	if(mid > r) ans += query_sumde(l, r, p<<1|1, mid+1, cr) % M;
	return ans % M;
}


int query_sumth(int l, int r, int p = 1, int cl = 1, int cr = n){
	if(l <= cl && r >= cr){
		return sumth[p] % M;
	}
	pushdown(p, cl, cr);
	// return 0;

	int mid = (cl + cr) >> 1;
	int ans = 0;
	// if(mid <= l) ans += query_sumth(l, r, p<<1, cl, mid) % M;
	if(mid > r) ans += query_sumth(l, r, p<<1|1, mid+1, cr) % M;
	return ans % M;
}

int query(int l, int r, int d){
	if(d == 1) return query_sum(l, r);
	else if(d == 2) return query_sumde(l, r);
	else if(d == 3) return query_sumth(l, r);
	return 0;
}
signed main() {
//	freopen("an", "r", stdin);
	caillo;

	while(cin >> n >> m && (n || m)){
		init();
		build();
		// continue;

		fi(m){
			int o, x, y, c; cin >> o >> x >> y>> c;
			if(o == 1) update_add(x, y, c);
			else if(o == 1) update_mul(x, y, c);
			else if(o == 2) update_ch(x, y, c);
			else if(o == 4) cout << query(x, y, c) << endl;
		}
	}


	PLEASE_AC;
}
