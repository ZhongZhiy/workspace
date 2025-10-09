
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

constexpr int N = 1e6 + 10;
int spf[N];
void pre_spf(){  //预处理, 用ai氏筛找spf
	for(int i = 2;i < N; ++i){
		if(!spf[i]){
			spf[i] = i;
			if(i * i > N) continue;
			for(int j = i * i; j < N; j += i){
				if(!spf[j]) spf[j] = i;
			}
		}
	}

	spf[1] = 1;
}

int last[N], seen[N], nop[N];  //last[p]是p上次出现的位置, seen[p]是记录p是不是第一次出现, nop[p]是记录不包含p的区间个数
signed main() {
//	freopen("an", "r", stdin);
	caillo;

	pre_spf();

	int n; cin >> n;

	vector<int> visited;  //记录所有出现的素数, 用于计算最后一段gap
	for(int i = 1;i <= n; ++i){
		int x; cin >> x;
		if(x == 1) continue;
		vector<int> primes;  //记录这数包含的素数
		while(x > 1){  //找素数
			int p = spf[x];
			primes.push_back(p);
			while(x % p == 0) x /= p;  //清除这个数的p因子
		}

		for(auto p : primes){  //计算从上一个位置到这位置的p的gap
			if(!seen[p]){seen[p] = 1;visited.push_back(p);}
			int gap = i - last[p] - 1;
			if(gap > 0) nop[p] += gap * (gap + 1) / 2;
			last[p] = i;
		}
	}

	for(auto p : visited){  //计算最后的gap
		int gap = n - last[p];
		if(gap > 0) nop[p] += gap * (gap + 1) / 2;
	}

	int t = n * (n + 1) >> 1;
	int ans = 0;
	for(auto p : visited) ans += (t - nop[p]);

	cout << ans << endl;

	PLEASE_AC;
}
