
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

string name;
int r0, c0, r1, c1, r2, c2, di;
const char* dirs = "NESW";
const char* turns = "FLR";
int dir_id(char c){
	switch(c) {
		case 'N':
			return 0;
		case 'E':
			return 1;
		case 'S':
			return 2;
		default:
			return 3;
	}
}
int turn_id(char c) {
	switch(c) {
		case 'F':return 0;
		case 'L':return 1;
		default:return 2;
	}
}

const int dr[]{-1, 0, 1, 0};
const int dc[]{0, 1, 0, -1};

struct Node {
	int r, c, dir;
	Node(){}
	Node(int r, int c, int dir):r(r), c(c), dir(dir){}
};
Node walk(const Node &u, int turn) {
	int dir = u.dir;
	if(turn == 1) dir = (dir + 3) % 4;
	if(turn == 2) dir = (dir + 1) % 4;
	return Node(u.r+dr[dir], u.c + dc[dir], dir);
}

const int N = 20;
int d[N][N][N], dir, has_edge[N][N][N][N];
Node p[N][N][N];
bool inside(int r, int c) {
	return r >= 1 && r <= 9 && c >= 1 && c <= 9;
}

void read_node()  {
	cin >> name;
	cin >> r0 >> c0 >> di >> r2 >> c2;
	Node v = walk(Node(r0, c0, di));
	
	int a, b;
	while(cin >> a && a) {
		cin >> b;
		string dd;
		while(cin >> dd && dd != "*") {
			for(int i = 0;i < dd.size(); ++i) {
				if(i != 0) {
					has_edge[a][b][dir_id(dd[0])][turn_id(dd[i])] = 1;
				} 
			}
		}

	}

}
void print_ans(Node u) {
	vector<Node> nodes;
	for(;;) {
		nodes.push_back(u);
		if(d[u.r][u.c][u.dir] == 0) break;
		u = p[u.r][u.c][u.dir];
	}
	nodes.push_back(Node(r0, c0, dir));

	int cnt = 0;
	for(int i = nodes.size()-1; i >= 0; i--) {
		if(cnt % 10 == 0) cout << " ";
		cout << " (" << nodes[i].r << "," << nodes[i].c << ")";
		if(++cnt % 10 == 0) cout << endl;
	}
	if(nodes.size() % 10 != 0) cout << endl;
}
void solve() {
	queue<Node> q;
	memset(d, -1, sizeof(d));
	Node u(r1, c1, dir);
	d[u.r][u.c][u.dir] = 0;
	q.push(u);
	while(!q.empty()) {
		Node u = q.front();q.pop();
		if(u.r == r2 && u.c == c2) {print_ans(u);return;}
		for(int i = 0;i < 3; ++i) {
			Node v = walk(u, i);
			if(has_edge[u.r][u.c][u.dir][i] && inside(v.r, v.c) && d[v.r][v.c][v.dir] < 0) {
				d[v.r][v.c][v.dir] = d[u.r][u.c][u.dir] + 1;
				p[v.r][v.c][v.dir] = u;
				q.push(v);
			}
		}
	}
}


signed main() {
//	freopen("an", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);


	while(cin >> s && s != "END") {
		
	}

	PLEASE_AC;
}
