
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


const int N = 1e4 + 10;
int in_order[N], post_order[N], lch[N], rch[N];
int n;

bool read_list(int *a) { //读入到指定数组中
	string s;
	if(!getline(cin, s)) return false;
	stringstream ss(s);  //把一行读入到流中,convient to get node
	n = 0;  //count 
	int x;
	while(ss >> x) a[n++] = x;  //read to post_order arr
	return n > 0;
}

int build(int l1, int r1, int l2, int r2) {
	if(l1 > r1) return 0; //空数
	int root = post_order[r2];  //the late factor of post_order is the root
	int p = l1;  //the location of the root in the in_order
	while(root != in_order[p]) p++;  //find the root, 
	int cnt = p - l1;  //the left tree's node number
	lch[root] = build(l1, p-1, l2, l2+cnt-1);
	rch[root] = build(p+1,r1, l2+cnt,r2-1);
	return root;
}
int best, best_sum;
void dfs(int u, int sum) {
	sum+= u;
	if(!lch[u] && !rch[u]) {
		if(sum < best_sum || (sum == best_sum && u < best)) {
			best = u;best_sum = sum;
		}
	}
	
	if(lch[u]) dfs(lch[u], sum);
	if(rch[u]) dfs(rch[u], sum);
}
signed main() {
//	freopen("an", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	while(read_list(in_order)) {  //读取中序遍历
		read_list(post_order);
		build(0, n-1, 0, n-1); //建树, 
		best_sum = 1000000000;
		dfs(post_order[n-1], 0);
		cout << best << '\n';
	}


	PLEASE_AC;
}
