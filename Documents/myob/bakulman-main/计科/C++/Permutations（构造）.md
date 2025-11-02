#### 题目描述

A permutation of integers 1,2,...,n is called beautiful if there are no adjacent elements whose difference is 1.  
Given n, construct a beautiful permutation if such a permutation exists.  

#### 输入

The only input line contains an integer $n（1 ≤ n ≤ 10^6$）.

#### 输出

Print a beautiful permutation of integers 1,2,...,n. If there are several solutions, you may print any of them. If there are no solutions, print "NO SOLUTION".

#### 样例输入 

【样例1】
5
【样例2】
3

#### 样例输出 

【样例1】
4 2 5 3 1
【样例2】
NO SOLUTION


#### 题解
题意：是要求构造1到n的一个数列，数列相邻项差不为1，
wrong：我想把数列后半段穿插到前半段的空隙中，结果导致$n=4$的时候没有正确答案，
correct：把奇偶分开，偶数一块奇数一块，这样简单地就构造出来了

代码：
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    if (n == 1) {
        cout << "1" << endl;
    } else if (n == 2 || n == 3) {
        cout << "NO SOLUTION" << endl;
    } else {
        // Print all even numbers first
        for (int i = 2; i <= n; i += 2) {
            cout << i << " ";
        }
        // Print all odd numbers next
        for (int i = 1; i <= n; i += 2) {
            cout << i << " ";
        }
        cout << endl;
    }

    return 0;
}
```