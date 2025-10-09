

#include<bits/stdc++.h>
using namespace std;
#define de(x) cout << (#x) << " = " << (x) << endl;
#define de2(x, y) cout << (#x) << " , " << (#y) << " = " << (x) << " ~ " << (y) << endl;
#define endl '\n'
#define f(n) for(int i = 0;i < n; ++i)
#define ff(i, a, b) for(int i = a; i < b; ++i)
typedef long long ll;
typedef unsigned long long ull;

constexpr int N = 1e6;
int a[N], b[N], c[N];

string Lplus(string aa, string bb) {
	int la = aa.size(), lb = bb.size();

	for(int i = 0;i < la; ++i) {
		a[i] = aa[la - i - 1] - '0';
	}
	for(int i = 0; i < lb; ++i) b[i] = bb[lb - i - 1] - '0';

	int len = max(la, lb);

	for(int i = 0;i <= len; ++i) {
		c[i] += a[i] + b[i];
		c[i+1] += c[i]/10;
		c[i] %= 10;
	}

	int i = len;
	for(;i > 0 && c[i] == 0;-- i);

	string ans = "";
	for(;i >= 0; --i) ans += c[i] + '0';

	return ans;

}

bool scmp(string aa, string bb) {
	if(aa.size() != bb.size()) return aa.size() > bb.size();

	for(int i = 0; i < aa.size(); ++i) {
		if(aa[i] != bb[i]) return aa[i] > bb[i];
	}
	return true;
}

string Lminus(string aa, string bb) {
	string ans = "";
	if(!scmp(aa, bb)) ans = "-", swap(aa, bb);

	int la = aa.size(), lb = bb.size();
	
	for(int i = 0;i < la; ++i) a[i] = aa[la - i - 1] - '0';
	for(int i = 0; i < lb; ++i) b[i] = bb[lb - i - 1] - '0';

	int len = max(la, lb);

	for(int i = 0; i < len; ++i) {
		c[i] += a[i] - b[i];
		if(c[i] < 0) c[i] += 10, c[i+1]--;
	}

	int i = len;
	for(;i > 0 && c[i] == 0; --i);

	for(;i >= 0; --i) {
		ans += c[i] + '0';
	}

	return ans;
}

string Lsgmlut(string aa, string bb) {
	int lb = bb.size();
	for(int i = 0; i < lb; ++i)  b[i] = bb[lb-i-1] - '0';

	int na = stoi(aa);
	for(int i = 0;i < lb; ++i) {
		c[i] += na * b[i];
		c[i+1] += c[i]/10;
		c[i] %= 10;
	}

	int len = lb;
	while(c[len]) {
		c[len + 1] += c[len] / 10;
		c[len] %= 10;
		len++;
	}

	string ans = "";
	for(int i = len-1;i >= 0; ++i) ans += c[i] + '0';

	for(int i = 0;i < len; ++i) a[i] = b[i] = c[i] = 0;

	return ans;
}
int main() {
//	freopen("an", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int t;
	cin >> t;

	while(t--) {
		int n, nn;
		cin >> n >> nn;

		string s = "1";

		for(int i = 1;i <= n; ++i) {
			s = Lsgmlut(to_string(i), s);
		}

		int cnt = 0;
		for(auto c : s) if(c == nn + '0') cnt++;
		cout << cnt << endl;
	}
	return 0;
}
