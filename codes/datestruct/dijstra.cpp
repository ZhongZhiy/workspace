
#include<bits/stdc++.h>
using namespace std;
#define i128 __int128

#define DEBUG
#ifdef DEBUG
	#define de(x) cout << (#x) << " = " << (x) << endl;
	#define de2(x, y) cout << (#x) << " , " << (#y) << " = " << (x) << " ~ " << (y) << endl;
#else
	#define de(x)
	#define de2(x, y)
#endif
#define endl '\n'
#define fi(x) for(int i = 1; i <= x; ++i)
#define fi0(x) for(int i = 0; i < x; ++i)
#define fj(n) for(int j = 1; j <= n; ++j)
#define caillo ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define PLEASE_AC return 0
typedef long long ll;
typedef unsigned long long ull;
#define int long long 

constexpr int N = 105;
vector<int> e[N];
int degree[N], vis[N];
int n, m;

struct Node{
	int id, dg;
	Node(){}
	Node(int id, int dg):id(id), dg(dg){}
	bool operator < (const Node& a)const{return dg < a.dg;}
};

signed main() {
//	freopen("an", "r", stdin);
	caillo;

	cin >> n >> m;
	vector<string> name; fi(n){string s; cin >> s; name.push_back(s);}

	fi(m){
		int x, y; ;cin >> x >> y;
		e[x].push_back(y);
		degree[y]++;
	}

	vector<int> st;
	fi(n) if(!degree[i-1]) st.push_back(i-1);

	if(st.empty()){
		cout << "该图拓扑序存在性为 0";
	}else{
		vector<int> ans;
		int idx = 0;
		priority_queue<Node, vector<Node> > q;
		for(auto c : st) q.push({c, 0});
		while(!q.empty()){
			int id = q.top().id; q.pop();
			if(vis[id]) continue;
			vis[id] = 1;
			ans.push_back(id);
			for(auto v : e[id]){
				degree[v]--;
				if(!degree[v]) q.push({v, 0});
			}
		}
		if(ans.size() == n) {
			for(auto c : ans) cout << name[c] << ' ';
		}else cout << "该图拓扑序存在性为 0";
	}

	PLEASE_AC;
}
