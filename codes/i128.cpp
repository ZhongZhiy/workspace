
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
#define PLEASE_AC return 0
typedef long long ll;
typedef unsigned long long ull;
#define int long long 
ostream &operator<<(ostream &os, i128 n) {
	if(n == 0) {
		return os << 0;
	}
	string s;
	while(n > 0) {
		s += char('0' + n % 10);
		n /= 10;
	}
	reverse(s.begin(), s.end());
	return os << s;
}

i128 toi128(const string &s) {
	i128 n = 0;
	for(auto c : s) {
		n = n * 10 + (c - '0');
	}
	return n;
}

i128 sqrti128(i128 n) {
	i128 lo = 0, hi = 1E16;
	while(lo < hi) {
		i128 x = (lo + hi + 1) / 2;
		if(x * x <= n) {
			lo = x;
		} else {
			hi = x - 1;
		}
	}
	return lo;
}

i128 gcd(i128 a, i128 b) {
	while(b) {
		a %= b;
		swap(a, b);
	}
	return a;
}


signed main() {
	//	freopen("an", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int a = 7, b = 49;
	cout << gcd(a, b);


	PLEASE_AC;
}
