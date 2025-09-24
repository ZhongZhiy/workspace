# 算法

## 费马小定理求逆元

<!-- notecardId: 1757757906089 -->
```cpp
//当被%的数是素数的时候，用费尔马小定理 a^{b-1} === 1 (mod b), 逆元为a^{b-2}
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
```
