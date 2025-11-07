

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define int long long 

const int N = 2e5 + 10;
int t, n;
int f[N][21], lg[N];

void pre(){
	for(int i = 2;i <= n; ++i)  //预处理log2
		lg[i] = lg[i/2] + 1;

	for(int i = 1;i <= n; ++i)  //读入
		cin >> f[i][0];

	for(int i = 1;i <= 20; ++i)  //处理最大值
		for(int j = 1;j + (1 << i) - 1 <= n; ++j)
			f[j][i] = max(f[j][i-1], f[j+(1<<(i-1))][i-1]);
}

int find(int l, int r){  //返回[l, r]的最大值
	int s = lg[r - l + 1];
	return max(f[l][s], f[r-(1<<s) + 1][s]);
}


void solve(){
	cin >> n;
	
	pre();
}

signed main() {
//	freopen("an", "r", stdin);
	caillo;

	cin >> t;
	while(t--) solve();


	PLEASE_AC;
}
