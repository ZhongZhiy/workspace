
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

const int N = 505;
int mp[N][N], ans[N][N], dist[N][N];
struct Node{
	int to, dis;
	Node(){}
	Node(int to, int dis):to(to), dis(dis){};
	bool operator < (const Node& a) const {
		return dis > a.dis;
	}
};

priority_queue<Node> Q;
void dijistra(){
	Q.push({1, 0});

	while(!Q.empty()){
		
	}
}


signed main() {
//	freopen("an", "r", stdin);
	caillo;


	PLEASE_AC;
}
