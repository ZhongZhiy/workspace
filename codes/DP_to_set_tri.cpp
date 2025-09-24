//三进制状态压缩,  hdu3001
#include<bits/stdc++.h>
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
#define int long long 
const int INF = 0x3f3f3f3f;
int n, m;  //最大10
int bit[12]{0, 1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049};  // 三进制的权值, 和二进制一样
int tri[60000][11];  //tri[i][j]表示i条路径(状态)下, j城市的状态, 为0, 1, 或2
int dp[11][60000];  //dp[i][j]表示从j城市出发, 按照路径i(状态)访问i中所有城市的最小费用
int graph[11][11];  //存图
void make_trb(){
	for(int i = 0;i < 59050; ++i) {   //枚举路径
		int t = i;
		for(int j = 1;j <= 10; ++j) {tri[i][j] = t % 3; t/= 3;}  //计算每种路径i的城市j的状况, 每次/3就是三进制移位
	}
}

int comp_dp() {   //dp实现
	int ans = INF;
	memset(dp, INF, sizeof(dp));  //初始化使用情况
	for(int j = 0;j <= n; ++j)    //初始化每个城市到自己的距离
		dp[j][bit[j]] = 0;

	for(int i = 0;i < bit[n+1];++i) {  //便利所有情况
		int flag = 1;  //标志, 是否走完了
		for(int j = 1; j <= n; ++j) {  //便利城市, 确保以j为起点, j是包含的
			if(tri[i][j] == 0) {   //没有走j城市
				flag = 0;
				continue;
			}
			for(int k = 1;k <= n; ++k) {  //便利i-j的所有城市
				int l = i - bit[j];  //从路径i中去掉城市j
				dp[j][i] = min(dp[j][i], dp[k][l] + graph[k][j]);  //路径i从j为起点的花费 = 从k为起点的不含j的路径与从k到j的最小值
			}
		}
		if(flag)  //访问全部城市的情况, 便利所有城市为起点的最小值
			for(int j = 1;j <= n;++j)
				ans = min(ans, dp[j][i]);

	}
	return ans;
}


signed main() {
	//	freopen("an", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	make_trb();
	while(cin >> n >> m){
		memset(graph, INF, sizeof(graph));
		while(m--) {
			int a, b, c;cin >> a >> b >> c;
			if(c < graph[a][b]) graph[a][b] = graph[b][a] = c;
		}
		int ans = comp_dp();
		if(ans == INF) cout << "-1" << endl;
		else cout << ans << endl;
	}

	PLEASE_AC;
}
