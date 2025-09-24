//树状数组模板
#include<bits/stdc++.h>
using namespace std;
#define de(x) cout << (#x) << " = " << (x) << endl;
#define de2(x, y) cout << (#x) << " , " << (#y) << " = " << (x) << " ~ " << (y) << endl;
#define endl '\n'
#define f(n) for(int i = 0;i < n; ++i)
#define ff(i, a, b) for(int i = a; i < b; ++i)
typedef long long ll;
typedef unsigned long long ull;

constexpr int N = 2e5 + 100;
int tree[N], n;

inline int lowbit(int x) {return x & -x;}

inline void update(int i, int x) {
	for(int pos = i;pos <= n; pos += lowbit(pos)) {
		tree[pos] += x;
	}
}

inline int query(int x) {
	int ans = 0;
	for(int pos = x; pos; pos -= lowbit(pos)) {
		ans += tree[pos];
	}
	return ans;
}

inline int query(int x, int y) {
	return query(y) - query(x - 1);
}

int main() {
//	freopen("an", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int t;
	cin>> t;
	while(t--) {
		int  q;
		cin >> n >> q;

		for(int i = 1;i <= n; ++i) {
			int score;
			cin >> score;

			update(i, score);
		}

		int cnt = 0, ans  = 0;
		for(int i = 1; i <= q; ++i) {
			int op, x, y;
			cin >> op >> x >> y;

			if(op == 1) {
				update(x, y - query(x,x));
			}
			else {
				cnt++;
				int kd = query(y)/100 - query(x-1)/100;
				if(cnt == 1) ans = kd;
				else ans ^= kd * cnt;
			}
		}

		cout << ans << endl;


	}

	return 0;
}
