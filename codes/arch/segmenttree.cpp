//hdu4027 线段树
#include<algorithm>
#include<cmath>
#include<iostream>
using namespace std;
#define de(x) cout << (#x) << " = " << (x) << endl;
#define de2(x, y) cout << (#x) << " , " << (#y) << " = " << (x) << " ~ " << (y) << endl;
#define endl '\n'
#define f(n) for(int i = 0;i < n; ++i)
#define ff(i, a, b) for(int i = a; i < b; ++i)
#define PLACE_AC return 0
typedef long long ll;
typedef unsigned long long ull;
#define int long long 

const int N = 1e5 + 10;
int tree[N<<2], val[N<<2], tag[N<<2];
int n;
void build(int p = 1, int l = 1, int r = n) {
	tag[p] = 0;

	if(l == r) {
		tree[p] = val[r];
		return;
	}

	int mid = (l + r) >> 1;
	build(p<<1, l, mid);
	build(p<<1|1, mid+1, r);
	tree[p] = tree[p<<1] + tree[p<<1 | 1];
}


void update(int l, int r,int p = 1, int pl = 1, int pr = n) {
	if(tree[p] == pr - pl + 1 || (l > pr || r < pl)) return;

	if(pr == pl) {tree[p] = (int)sqrt(tree[p]);return;}
	
	int mid = (pl + pr) >> 1;
	if(l <= mid) update(l, r, p<<1, pl, mid);
	if(r > mid) update(l, r, p<<1 | 1, mid + 1, pr);
	tree[p] = tree[p<<1] + tree[p<<1 | 1];
}

int query(int l, int r, int p = 1, int pl = 1, int pr = n) {
	if(l <= pl && r >= pr) return tree[p];

	int res = 0;
	int mid = (pl + pr) >> 1;
	if(l <= mid) res += query(l, r, p << 1, pl, mid);
	if(r > mid) res += query(l, r, p<<1|1, mid+1, pr);
	return res;
}


signed main() {
//	freopen("an", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int cases = 1;
	while(cin >> n) {
		cout << "Case #" << cases << ":" << endl;
		cases++;
		for(int i = 1; i <= n; ++i) cin >> val[i];
		int m;
		cin >> m;

		build();

		f(m) {
			int t, x, y;
			cin >> t >> x >> y;

			if(x > y) swap(x, y);
			if(t == 0) update(x, y);
			else cout << query(x, y) << endl;
		}
	}
	PLACE_AC;
}
