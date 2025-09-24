

//求逆元的模板
#include<bits/stdc++.h>
using namespace std;
#define de(x) cout << (#x) << " = " << (x) << endl;
#define de2(x, y) cout << (#x) << " , " << (#y) << " = " << (x) << " ~ " << (y) << endl;
#define endl '\n'
#define f(n) for(int i = 0;i < n; ++i)
#define ff(i, a, b) for(int i = a; i < b; ++i)
#define PLACE_AC return 0
typedef long long ll;
typedef unsigned long long ull;
#define int long long 

const int M = 1e9 + 7;

//当被%的数是素数的时候，用费尔马小定理 a^{b-1} === 1 (mod b)
int qpow(int a, int b) {
	int ans = 1;  //记录答案
	a = ((a % b) + b ) % b;  //确保为正数

	int power = b-2;  //指数
	while(power) {
		if(power & 1) ans = (a * ans) % b;
		a = (a * a) % b;
		power >>= 1;
	}
	return ans;
}
//拓展欧几里得算法，不要求b为素数，但是要求a, b互素
void exgcd(int a, int b, int &x, int &y) {
	if(b == 0) {  //基准情况
		x = 1, y = 0;
		return;
	}

	exgcd(b, a%b, y, x);  //巧妙交换
	y -= a/b * x;   //x_current = y_next, y_current = x_next - a/b * y_next;转化一下就是这样了，不然多写两部也可以
}


signed main() {
//	freopen("an", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);


	PLACE_AC;
}
