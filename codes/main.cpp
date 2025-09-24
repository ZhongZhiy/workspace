#include<climits>
#include<iostream>
#include<cmath>
#include<algorithm>
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

int n, m;
struct node{
	int sum, id;
	node(){}
	node(int sum, int id):sum(sum), id(id){}

	bool operator < (const node& aa) const {
		return sum < aa.sum;
	}
};

const int N = 1e5 + 10;

node head[N];
int a[N];

void solve(){
	head[0].sum = 0;head[0].id = 0;

	fi(n) {
		cin >> a[i];
		head[i].sum = head[i-1].sum + a[i];
		head[i].id = i;
	}

	sort(head, head+n+1);


	fi(m) {
		int tt ; cin >> tt;

		int l = 0, r = 1, sum = 0, min_ = INT_MAX, ansl = 0, ansr = 1, ans = tt;

		while(r <= n){
			if(r < l) swap(l, r);
			if(r == l) r++;
			sum = head[r].sum - head[l].sum;

			if(abs(abs(sum) - tt) < min_){
				ans = abs(sum);
				min_ = abs(sum - tt);
				ansl = head[l].id;
				ansr = head[r].id;
				if(min_ == 0) break;
			}

			if(sum < tt) r++;
			else l++;
		}
		ansr++ ;
		if(ansr < ansl) swap(ansr, ansl);
		cout << ans << ' ' << ansl << ' ' << ansr << endl;

	}
}

signed main() {
	//	freopen("an", "r", stdin);
	caillo;

	while(cin >> n >> m && (n || m)) {
		solve();
	}

	PLEASE_AC;
}
