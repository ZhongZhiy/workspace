
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
#define startime auto start = chrono::high_resolution_clock::now();
#define endtime auto end = chrono::high_resolution_clock::now();
#define runningtime cout << "running time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count()<<" ms\n";
typedef long long ll;
typedef unsigned long long ull;
#define int long long 

const int N = 1e5;
struct Stack{
	int st[N];
	int idx = 0;
	bool empty(){return idx <= 0;}
	void pop() {idx--;}
	void push(int x){st[++idx] = x;}
	int top(){return st[idx];}
	int size(){return idx;}
};

Stack ch;


signed main() {
	caillo;

	char s[10000]; scanf("%s", s);

	int len = strlen(s);
	bool st = 0;
	for(int i = 0;i < len; ++i){
		if((s[i] == '-' && !st) || s[i] >= '0' && s[i] <= '9'){
			int sg = 1, tp = 0, j = 0;
			if(s[i] == '-') sg = -1, i++;
			for(j = i;j < len; ++j){
				if(s[j] >= '0' && s[j] <= '9') 
					tp = tp * 10 + s[j] - '0';
				else 
					break;
			}
			i = j - 1;
			st = 1;
			cout << tp*sg; 
			if(i != len - 1 || !ch.empty()) cout << ' ';
		} else if(s[i] == '(') {
			ch.push(s[i]);
			st = 0;
		} else if(s[i] == ')'){
			while(!ch.empty() && ch.top() != '(') {
				cout << (char)ch.top();
				if(i != len - 1) cout << ' ';
				ch.pop();
			}
			if(!ch.empty() && ch.top() == '(') ch.pop();
			st = 1;
		} else if(s[i] == '*' || s[i] == '/'){
			st = 1;
			while(!ch.empty() && (ch.top() == '*' || ch.top() == '/')) {
				cout << (char)ch.top();
				if(i != len - 1) cout << ' ';
				ch.pop();
			}
			ch.push(s[i]);
		} else if(s[i] == '+' || s[i] == '-'){
			st = 1;
			while(!ch.empty() && (ch.top() == '*' || ch.top() == '/' || ch.top() == '+' || ch.top() == '-')) {
				cout << (char)ch.top();
				if(i != len - 1) cout << ' ';
				ch.pop();
			}
			ch.push(s[i]);
		}
	}
	while(!ch.empty()) {
		cout << (char)ch.top();
		ch.pop();
		if(!ch.empty()) cout << ' ';
	}




	PLEASE_AC;
}
