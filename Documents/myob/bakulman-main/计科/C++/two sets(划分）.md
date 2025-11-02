Your task is to divide the numbers 1,2,...,n into two sets of equal sum.

#### 输入

The only input line contains an integer n（1 ≤ n ≤ 106）.

#### 输出

Print "YES", if the division is possible, and "NO" otherwise.  
After this, if the division is possible, print an example of how to create the sets. First, print the number of elements in the first set followed by the elements themselves in a separate line, and then, print the second set in a similar way.  

#### 样例输入 

【样例1】
7
【样例2】
6

#### 样例输出 

【样例1】
YES
4
1 2 4 7
3
3 5 6
【样例2】
NO


#### 分析
这是要求找整数的划分，满足划分的两个集合值相等，如果$\frac{n(n+1)}{2}$为奇数，那么就没有答案，如果为偶数，那么就存在这样的划分



关键怎么找到这样的划分，可以通过**贪心**的想法，从大到小，如果`sum_set1+k < sum/2`那么就把k放入集合1，否则放入集合2

代码：
```cpp
#include<bits/stdc++.h>

#define f(x) for(int i = 0;i < x;++i)

#define de(x) cout << #x << "=" << (x) << endl;

using namespace std;

#define int long long

signed main(){

  

    ios::sync_with_stdio(0);

    cin.tie(0);

    cout.tie(0);

  
  

    int n;

    cin >> n;  

    int sum = n*(n+1)/2;

    if(sum&1) cout << "NO";

    else{

        int half = sum/2;

        set<int> st, ed;

        int sum_st = 0;

        for(int i = n;i >= 1;--i){

            if(sum_st+i <= half) st.insert(i),sum_st += i;

            else ed.insert(i);

        }

        cout << "YES\n";

        cout << st.size() << '\n';

        for(auto c : st) cout << c << ' ';

        cout << '\n';


        cout << ed.size() << '\n';

        for(auto c : ed) cout << c << ' ';

    }

    return 0;
}
```