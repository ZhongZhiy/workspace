//排兵布阵hdu4539
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
#define de(x) cout << (#x) << " = " << (x) << endl;
#define de2(x, y) cout << (#x) << " , " << (#y) << " = " << (x) << " ~ " << (y) << endl;
#define endl '\n'
#define fi(x) for(int i = 1; i <= x; ++i)
#define fi0(x) for(int i = 0; i < x; ++i)
#define fj(n) for(int j = 1; j <= n; ++j)
#define fj0(n) for(int j = 0; j < n; ++j)
#define PLEASE_AC return 0
typedef long long ll;
typedef unsigned long long ull;
//使用ll会超空间
int mp[200][15];   //存图
int dp[105][200][200];  //状态,第i行, 在合法状态j下, i-1行的状态为k
int n, m;
int sta[200];   //每行m列最初的满足条件的情况
int init_line(int t) {  //预处理最初每行满足条件的情况
	int M = 0;
	for(int i = 0;i < t; i++) {
		if((i&(i >> 2)) == 0 && (i & (i << 2)) == 0)  //这个状态下和所有的士兵和相邻的两个士兵没有冲突的情况
			sta[M++] = i;  //满足条件的情况数量和情况
	}
	return M;
}

int count_line(int i , int x) {  //第i行状态x的士兵数
	int sum = 0;
	for(int j = m-1;j >= 0;j--) {
		if(x&1) sum += mp[i][j];  //这个数字, 如果这个状态下, 在题给条件mp下可以放士兵就放一个, 计数为1
		x >>= 1;
	}
	return sum;
}

signed main() {
//	freopen("an", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	while(cin >> n >> m) {
		int M = init_line(1<<m);  //计算每行最多满足的个数
		for(int i = 0;i < n;++i)   //读入
			for(int j = 0;j < m;++j) cin >> mp[i][j];

		int ans = 0;
		memset(dp, 0, sizeof(dp));  //初始化
		for(int i = 0;i < n; ++i)   //0到n-1行
			for(int j = 0;j < M; ++j)  //j是所有满足情况的个数, 也就是遍历所有当前i行可以选择的情况
				for(int k = 0;k < M;k++) {  //枚举i-1行的安排
					if(i == 0) {
						dp[i][j][k] = count_line(i, sta[j]);  //第一行,不管k, 状态就是sta[j]
						ans = max(ans, dp[i][j][k]);
						continue;
					}
					if((sta[j]&(sta[k]>>1)) || (sta[j]&(sta[k]<<1)))  //i行状态j和i-1行状态k有冲突,就跳过
						continue;
					int tmp = 0;  //i和i-1行没有冲突, 就将枚举i-2行的状态
					for(int p = 0;p < M; p++) {
						if((sta[p]&(sta[k]>>1)) || (sta[p]&(sta[k]<<1))) continue;  //i-1行和i-2行有冲突的情况, 就跳过
						if((sta[j]&sta[p])) continue;  //i行和i-2行冲突了, 也就是有士兵站位相同了
						tmp = max(tmp, dp[i-1][k][p]);  //找到所有i-2行满足的情况i-1行最大值
					}
					dp[i][j][k] = tmp + count_line(i, sta[j]);  //第i行状态为j, i-1行状态为k的最大值就是
					ans = max(ans, dp[i][j][k]);
				}
		cout << ans << endl;
	}


	PLEASE_AC;
}
