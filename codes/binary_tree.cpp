//Uva122
#include <vector>
#include <queue>
#include <string>
#include <cctype>
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

const int root = 1;
const int N = 1e5 + 10;
int lef[N], righ[N], vis[N], val[N];
int idx;
void newtree() {
	idx = root;
	lef[root] = 0;
	righ[root] = 0;
	vis[root] = false;
}

int newnode() {
	int u = ++idx;
	lef[u] = righ[u] = 0;
	vis[u] = false;
	return u;
}
bool failed = false;
void addnode(string s) {
	int u = root;
	int num = 0;
	for(int i = 0;i < s.size(); ++i) {
		if(s[i] == 'L') {
			if(lef[u] == 0) lef[u] = newnode();
			u = lef[u];
		}
		if(s[i] == 'R') {
			if(righ[u] == 0) righ[u] = newnode();
			u = righ[u];
		}
		if(isdigit(s[i])) {
			int tp = 0;
			while(isdigit(s[i])) {
				tp = tp * 10 + s[i] - '0';
				i++;
			}
			i--;
			num = tp;
		}
	}
	if(vis[u]) failed = true;
	vis[u] = true;
	val[u] = num;
}

vector<int> ans;
bool bfs() {
	ans.clear();
	queue<int> q;
	q.push(root);

	while(!q.empty()) {
		int u = q.front();q.pop();
		
		if(!vis[u]) return false;
		ans.push_back(val[u]);
		if(lef[u] != 0) q.push(lef[u]);
		if(righ[u] != 0) q.push(righ[u]);

	}
	return true;
}

signed main() {
//	freopen("an", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	string s;
	newtree();
	while(cin >> s) {
		if(s == "()") {
			if(failed || !bfs()) cout << "not complete";
			else {
				for(int i = 0;i < ans.size(); ++i) {cout << ans[i];if(i != ans.size()-1) cout << ' ';}
			}
			cout << endl;
			failed = false;
			newtree();
		}
		else
		addnode(s);
	}

	PLEASE_AC;
}
