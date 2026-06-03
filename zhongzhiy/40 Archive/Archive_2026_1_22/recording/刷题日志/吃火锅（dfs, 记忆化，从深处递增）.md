---
tags:
  - 算法
---
## 问题 D: 吃火锅

时间限制: 1.000 Sec  内存限制: 128 MB  


#### 题目描述

在仙界传说中，太乙真人极为热爱美食，尤其钟情于传说中的“神仙火锅”。据说这火锅的食材并非随意摆放，而是以一种神秘的阵法排列在一张n×n的大桌上。每个区域内的火锅食材都有一个“香辣值”，用一个正整数表示，象征着食材的独特风味和辣度。  
太乙真人决定开启他的火锅盛宴，但他有一个独特的品尝规矩：  
每次换到下一个食材区域时，必须确保该区域的香辣值严格高于上一个区域，这样才能层层递进，激发出火锅的绝妙风味。也就是说，太乙真人只能沿着一条香辣值不断上升的路径前进，尽情品味每一处美味。  
你的任务是：给定火锅桌上各区域的香辣值（构成一个n×n的矩阵），请你帮助太乙真人找出一条符合规则的路径，使他能品尝到尽可能多的不同食材区域，并计算出这条路径包含的区域数。  

#### 输入

第一行输入一个整数n，表示火锅桌上区域的规模，即食材被排列成n×n的格子。  
接下来的n行中，每行包含n个用空格分隔的正整数，分别代表各个区域中火锅食材的香辣值，数值不超过106。  

#### 输出

输出一个整数，表示太乙真人依照规定能够连续品尝到的最大区域数（即火锅食材区域的最长连续路径长度）。

#### 样例输入 Copy

4
14 9 12 10
1 11 5 4
7 15 2 13
6 3 16 8

#### 样例输出 Copy

4

#### 提示

对于 10% 的数据 1 ≤ n ≤ 10  
对于 50% 的数据 1 ≤ n ≤ 50  
对于 100% 的数据 1 ≤ n ≤ 500  

## 题解
这是一个经典的寻找矩阵中最长递增路径的问题。我们可以使用动态规划（具体来说是记忆化搜索）来解决。

**思路：**

1.  **定义状态**：
    `dp[r][c]` 表示从格子 `(r, c)` 出发，能够走出的最长递增路径的长度。

2.  **状态转移**：
    要计算 `dp[r][c]`，我们需要考虑从 `(r, c)` 能移动到的所有相邻格子 `(nr, nc)`（上下左右四个方向）。
    如果 `grid[nr][nc] > grid[r][c]`（即香辣值严格递增），那么我们可以从 `(r, c)` 移动到 `(nr, nc)`。
    此时，从 `(r, c)` 出发的一条可能路径长度就是 `1 + dp[nr][nc]`（1 代表当前格子 `(r, c)`，`dp[nr][nc]` 代表从 `(nr, nc)` 出发的最长路径）。
    我们需要在所有合法的相邻格子中，选择能使 `1 + dp[nr][nc]` 最大的那个。
    所以，`dp[r][c] = 1 + max(dp[nr][nc])` 对于所有满足条件的邻居 `(nr, nc)`。
    如果没有任何一个邻居的香辣值比 `grid[r][c]` 更大，那么从 `(r, c)` 出发的最长路径就只包含它自己，长度为 `1`。

3.  **记忆化搜索**：
    直接用递归实现上述状态转移可能会导致大量的重复计算。例如，计算 `dp[x][y]` 时可能需要 `dp[a][b]`，计算 `dp[p][q]` 时也可能需要 `dp[a][b]`。
    为了避免重复计算，我们使用一个二维数组 `memo[n][n]`（与 `dp` 数组含义相同）来存储已经计算过的 `dp[r][c]` 的值。
    `memo` 数组可以初始化为一个特殊值（比如 0 或 -1），表示该状态尚未计算。
    当需要计算 `dp[r][c]` 时：
    *   首先检查 `memo[r][c]` 是否已经被计算过。如果是，直接返回存储的值。
    *   否则，按照状态转移规则计算 `dp[r][c]`，将结果存入 `memo[r][c]`，然后返回结果。

4.  **最终答案**：
    我们需要找到整个矩阵中所有 `dp[r][c]` 的最大值。因为太乙真人可以从任何一个格子开始他的品尝路径。
    所以，遍历所有格子 `(i, j)`，计算 `dp[i][j]`（通过调用记忆化搜索函数），并取它们中的最大值。

**算法步骤：**

1.  读取输入的 `n` 和 `n x n` 的香辣值矩阵 `grid`。
2.  初始化一个 `n x n` 的 `memo` 数组，所有元素设为 0（表示未计算，因为路径长度至少为1，所以0可以作为未计算的标志）。
3.  定义一个递归函数 `dfs(r, c, grid, memo)`:
    a.  如果 `memo[r][c]` 不为 0，说明 `dp[r][c]` 已经计算过，直接返回 `memo[r][c]`。
    b.  初始化 `max_len_from_here = 1` (路径至少包含当前格子 `(r,c)`）。
    c.  定义四个方向的偏移量 `dr = [-1, 1, 0, 0]` 和 `dc = [0, 0, -1, 1]`。
    d.  遍历四个方向：
        i.  计算邻居坐标 `nr = r + dr[k]`, `nc = c + dc[k]`。
        ii. 如果邻居 `(nr, nc)` 在矩阵范围内 (`0 <= nr < n`, `0 <= nc < n`) 并且 `grid[nr][nc] > grid[r][c]`：
            `max_len_from_here = max(max_len_from_here, 1 + dfs(nr, nc, grid, memo))`
    e.  将计算得到的 `max_len_from_here` 存入 `memo[r][c]`。
    f.  返回 `memo[r][c]`。
4.  初始化一个变量 `overall_max_path = 0`。
5.  遍历矩阵中的每一个格子 `(i, j)` 从 `(0,0)` 到 `(n-1, n-1)`：
    a.  `overall_max_path = max(overall_max_path, dfs(i, j, grid, memo))`
6.  输出 `overall_max_path`。

**时间复杂度**：
每个 `dp[r][c]` 状态只会被实际计算一次。计算每个状态时，会查看最多4个邻居。因此，总的时间复杂度是 O(N\*N)，其中 N 是矩阵的边长。

**空间复杂度**：
O(N\*N) 用于存储香辣值矩阵 `grid` 和记忆化数组 `memo`。递归栈的深度在最坏情况下也可能是 O(N\*N)。

**C++ 实现：**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<vector<int>> grid;
vector<vector<int>> memo;

// 方向数组：上, 下, 左, 右
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

bool is_valid(int r, int c) {
    return r >= 0 && r < n && c >= 0 && c < n;
}

int dfs(int r, int c) {
    // 如果已经计算过，直接返回结果
    if (memo[r][c] != 0) {
        return memo[r][c];
    }

    // 当前路径至少包含本格子，长度为1
    int max_len_from_here = 1;

    for (int i = 0; i < 4; ++i) {
        int nr = r + dr[i];
        int nc = c + dc[i];

        if (is_valid(nr, nc) && grid[nr][nc] > grid[r][c]) {
            max_len_from_here = max(max_len_from_here, 1 + dfs(nr, nc));
        }
    }

    memo[r][c] = max_len_from_here;
    return memo[r][c];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    grid.resize(n, vector<int>(n));
    memo.resize(n, vector<int>(n, 0)); // 初始化memo为0

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
        }
    }

    int overall_max_path = 0;
    if (n > 0) { // 处理n=0的边缘情况，虽然题目约束1<=n
        overall_max_path = 1; // 至少可以吃一个
         for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                overall_max_path = max(overall_max_path, dfs(i, j));
            }
        }
    } else {
        overall_max_path = 0; // 如果n=0，没有食材
    }


    cout << overall_max_path << endl;

    return 0;
}
```
**对 `overall_max_path` 初始值的修正和说明：**
题目中说明香辣值为正整数，所以至少能品尝一个区域，路径长度至少为1。
如果 `n=0`（虽然题目约束 `1 <= n <= 500`），路径长度为0。
如果 `n > 0`，即使所有格子都不能形成递增路径（例如所有值都相同），从任何一个格子出发的路径长度都是1。所以 `overall_max_path` 应该至少初始化为1（如果 `n > 0`）。
在循环中调用 `dfs` 后，`dfs` 返回的最小值也是1，所以 `max` 操作会正确处理。
因此，如果 `n > 0`，`overall_max_path` 可以初始化为0，然后循环会找到至少为1的值；或者初始化为1，然后循环更新。
我的代码中，如果 `n>0`，`overall_max_path` 初始化为1，然后通过循环计算 `dfs` 并取最大值。如果 `n=0`，则为0。这是合理的。
如果 `n=1`，`dfs(0,0)` 会返回1，`overall_max_path` 会是1。

**样例测试：**
输入：
```
4
14 9 12 10
1 11 5 4
7 15 2 13
6 3 16 8
```
`dfs` 将会被调用。
例如，从 (1,0) 的 1 开始：
1 -> 11 (0,1) -> 12 (0,2)  (长度3)  (1->11->14 (0,0) 也是长度3)
1 -> 7 (2,0) -> 15 (2,1) -> 16 (3,2) (长度4: 1-7-15-16)
...
最终应该找到最长的路径。
对于 (1,0) 值为 1，`dfs(1,0)`:
  -> `dfs(0,1)` (11):
    -> `dfs(0,0)` (14): returns 1
    -> `dfs(0,2)` (12):
      -> `dfs(0,0)` (14): returns 1. path: 12->14 (len 2 for 12).
      -> `dfs(2,2)` (2) (no, 2<12)
      -> `dfs(0,3)` (10) (no, 10<12)
      ...
      `memo[0][2]` = 2 (12->14)
    `memo[0][1]` = max(1, 1+`dfs(0,0)`=2, 1+`dfs(0,2)`=3, ...)
... 这个过程会找到从每个点出发的最长路径。

最终答案为 4 (例如路径: 1 -> 7 -> 15 -> 16)。


## 我的代码
```cpp
#include <bits/stdc++.h>
#define de(x) cout << #x <<"="<< (x) << endl;
using namespace std;
#define int long long
const int N = 505;
int v[N][N], memo[N][N];
int n, ans = 0;

bool check(int x, int y){
    return x >= 1 && x <= n && y >= 1 && y <= n;
}

int tx[]{1, 0, -1, 0};
int ty[]{0, -1, 0, 1};

int dfs(int x, int y){       //返回数字
    if(memo[x][y]){          //如果有走过的话就直接返回
        return memo[x][y];
    }

    int len = 1;             //最后到最深处就为1

    for(int i = 0;i < 4;i ++ ){
        int nx = x + tx[i];
        int ny = y + ty[i];

        if(check(nx, ny) && v[nx][ny] > v[x][y]) {  //只能沿着增大的方向走，所以不用回溯
            len = max(len, dfs(nx, ny)+1);          //从最深处到这里的距离
        }


    }
    memo[x][y] = len;
    return len;



}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);


    cin >> n;

    for(int i = 1;i <= n; ++i)
    {
        for(int j = 1;j <= n;++j ){
            cin >> v[i][j];
        }
    }


    for(int i = 1;i <= n; ++i)
    {
        for(int j = 1;j <= n;++j ){
            ans = max(ans, dfs(i, j));
        }
    }

    cout << ans;



    return 0;
}

```