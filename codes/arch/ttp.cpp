
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

int n, m;
struct Node{
	int date;
	Node *next;
};




signed main() {
//	freopen("an", "r", stdin);
	caillo;

	cin >> n>> m;
	Node *head, *prev, *p, *now;
	head = new Node; head->date = 1, head->next = nullptr;
	now = head;
	for(int i = 2;i <= n; i++){
		p = new Node;
		p->date = i;p->next = nullptr;
		now->next = p;
		now = p;
	}
	now->next = head;

	prev = now; now = head;

	while(--n){
		for(int i = 1;i < m; ++i){
			prev = now;
			now = now->next;
		}
		cout << now->date << ' ';
		prev->next = now->next;
		delete now;
		now = prev->next;
	}
	cout << now->date << ' ';
	delete now;

	PLEASE_AC;
}
