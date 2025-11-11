## **P: Apple Division** 的中文翻译：

--- 
### 问题 P：苹果分配（Apple Division） 
**时间限制**：1.000 秒 **内存限制**：128 MB 
#### 题目描述
有$n$个苹果，每个苹果的重量已知。你的任务是将这些苹果分成两组，使得这两组苹果的重量之差尽可能小。 
#### 输入
第一行输入一个整数$n$（$1 \leq n \leq 20$）：表示苹果的数量。 第二行输入$n$个整数$p_1, p_2, \ldots, p_n$（$1 \leq p_i \leq 10^9$）：表示每个苹果的重量。 
#### 输出
输出一个整数：表示两组苹果的最小重量差。 
#### 样例输入 
``` 5 3 2 7 4 1 ``` 
#### 样例输出 
``` 1 ``` 
#### 提示说明 
其中一组包含重量为 2、3 和 4 的苹果（总重量为 9），另一组包含重量为 1 和 7 的苹果（总重量为 8）。两者之差为 1。 

---
## 分析：
这道题就是对所有数进行排列，找到其中的某种特别排列（两组差最小）
#### 错误思路：贪心
从大到小把和小于总和一半的放在一组。但是在某些情况下，不是最优解

#### 正确思路
搜索所有方法，选择其中最小的方案
#### 方法一**方法1：位掩码 (Bitmasking)**

1.  **迭代所有子集**：我们可以用一个从$0$到$2^n - 1$的整数（掩码）来代表一种分配方案。掩码的每一位（从第 0 位到第$n-1$位）对应一个苹果。
    *   如果掩码的第$i$位是 0，则第$i$个苹果分到第一组。
    *   如果掩码的第$i$位是 1，则第$i$个苹果分到第二组。

2.  **计算两组的重量和**：对于每个掩码：
    *   初始化两组的重量和 `sum1 = 0` 和 `sum2 = 0`。
    *   遍历所有苹果（从$i=0$到$n-1$）：
        *   检查掩码的第$i$位：`if ((mask >> i) & 1)`
            *   如果为 1 (true)，将苹果$p_i$的重量加到 `sum2`。
            *   如果为 0 (false)，将苹果$p_i$的重量加到 `sum1`。
    *   计算当前分配方案下的重量差：`abs(sum1 - sum2)`。

3.  **找到最小差值**：维护一个变量 `min_difference`，初始化为一个非常大的数。对于每种分配方案，用其重量差更新 `min_difference`：`min_difference = min(min_difference, abs(sum1 - sum2))`。

4.  **最终结果**：迭代完所有$2^n$个掩码后，`min_difference` 就是答案。

**优化 (Slight Optimization for Sum Calculation)**

我们可以只计算其中一个组的重量和。例如，我们计算所有被掩码选中的苹果（位为1的苹果）的总重量 `current_sum_group1`。
那么另一组的重量就是 `total_sum - current_sum_group1`，其中 `total_sum` 是所有苹果的总重量。
差值就是 `abs(current_sum_group1 - (total_sum - current_sum_group1))`
即 `abs(2 * current_sum_group1 - total_sum)`。

**步骤 (Steps using Bitmasking with Optimization):**

1.  读取输入$n$和$n$个苹果的重量$p_1, \ldots, p_n$。
2.  计算所有苹果的总重量 `total_sum`。
3.  初始化 `min_difference = total_sum` (或者一个非常大的 `long long` 值，因为重量差可能很大)。
4.  循环变量 `mask` 从$0$到$(1 \ll n) - 1$(即$2^n - 1$):
    a.  初始化当前子集的重量和 `current_subset_sum = 0`。
    b.  循环变量 `i` 从$0$到$n-1$:
        i.  如果掩码 `mask` 的第 `i` 位是 1 (即 `(mask >> i) & 1` 为真):
            将第$i$个苹果的重量$p_i$加到 `current_subset_sum`。
    c.  计算此子集形成的其中一组与总和形成的另一组之间的差：
        `difference = abs(current_subset_sum - (total_sum - current_subset_sum))`
        或者更简洁地：`difference = abs(2 * current_subset_sum - total_sum)`。
    d.  更新最小差值：`min_difference = min(min_difference, difference)`。
5.  输出 `min_difference`。
让我们用位掩码方法给出一个具体的实现框架。

**C++ 实现框架 (Bitmasking)**

```cpp name=apple_division.cpp
#include <iostream>
#include <vector>
#include <numeric> // For std::accumulate
#include <algorithm> // For std::min and std::abs
#include <climits> // For LLONG_MAX

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    std::vector<long long> p(n);
    long long total_sum = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> p[i];
        total_sum += p[i];
    }

    long long min_difference = LLONG_MAX; // Initialize with a very large value

    // Iterate through all possible subsets for the first group
    // (1 << n) is 2^n
    for (int i = 0; i < (1 << n); ++i) {
        long long current_subset_sum = 0;
        // For each mask 'i', determine which apples go into this subset
        for (int j = 0; j < n; ++j) {
            // If the j-th bit is set in mask 'i'
            if ((i >> j) & 1) {
                current_subset_sum += p[j];
            }
        }

        // sum_group1 = current_subset_sum
        // sum_group2 = total_sum - current_subset_sum
        // difference = abs(sum_group1 - sum_group2)
        //            = abs(current_subset_sum - (total_sum - current_subset_sum))
        //            = abs(2 * current_subset_sum - total_sum)
        long long difference = std::abs(2 * current_subset_sum - total_sum);
        min_difference = std::min(min_difference, difference);
    }

    std::cout << min_difference << std::endl;

    return 0;
}

```
这个C++代码实现了使用位掩码的思路。它计算所有可能的子集和，然后通过该子集和与总和的关系来确定两组的差，并找到最小的那个差值。
#### **方法2：递归 (Recursion / Backtracking)**

我们可以编写一个递归函数来决定每个苹果放入哪个组。

`solve(index, sum_group1, sum_group2)`:
*   `index`: 当前正在考虑的苹果的索引。
*   `sum_group1`: 到目前为止，第一组的累计重量。
*   `sum_group2`: 到目前为止，第二组的累计重量。

**递归步骤:**

1.  **基本情况 (Base Case)**: 如果 `index == n` (所有苹果都已分配完毕):
    *   计算差值 `abs(sum_group1 - sum_group2)`。
    *   用这个差值更新全局的 `min_difference`。
    *   返回。

2.  **递归调用 (Recursive Step)**:
    *   **选项1**: 将第 `index` 个苹果放入第一组:
        `solve(index + 1, sum_group1 + p[index], sum_group2)`
    *   **选项2**: 将第 `index` 个苹果放入第二组:
        `solve(index + 1, sum_group1, sum_group2 + p[index])`

**初始调用**: `solve(0, 0, 0)`

同样，这个递归方法也会探索$2^n$种可能性。也可以使用上面提到的优化，只跟踪一个组的和以及总和。

`solve_optimized(index, current_sum_group1, total_sum)`:
*   **基本情况**: `index == n`:
    *   `difference = abs(current_sum_group1 - (total_sum - current_sum_group1))`
    *   更新 `min_difference`。
*   **递归调用**:
    *   `solve_optimized(index + 1, current_sum_group1 + p[index], total_sum)` (苹果 `index` 放入我们正在追踪的组)
    *   `solve_optimized(index + 1, current_sum_group1, total_sum)` (苹果 `index` 放入另一组)

**数据类型注意事项**
*   苹果的重量$p_i$可以达到$10^9$。
*  $n$最大为 20。
*   总重量可以达到$20 \times 10^9 = 2 \times 10^{10}$，这会超出标准的 32 位整数 (`int`) 的范围。因此，存储重量和以及差值时，应使用 64 位整数 (`long long` in C++)。

**选择哪种方法？**
对于$N \le 20$，位掩码通常更简洁易写。递归方法在概念上可能更直接一些，但代码稍长。两者效率相当。

代码：
```cpp
#include <iostream>
#include <vector>
#include <numeric>   // For std::accumulate (though we'll sum manually for practice)
#include <algorithm> // For std::min and std::abs
#include <climits>   // For LLONG_MAX

// 全局变量或通过引用传递来存储最小差值
long long min_global_difference;
std::vector<long long> weights; // 存储苹果重量
int num_apples;
long long total_weight_sum;

// DFS 函数
// index: 当前正在考虑的苹果的索引
// current_sum_group1: 到目前为止，第一组的累计重量
void solve_dfs(int index, long long current_sum_group1) {
    // 基本情况：所有苹果都已分配完毕
    if (index == num_apples) {
        long long sum_group2 = total_weight_sum - current_sum_group1;
        long long current_difference = std::abs(current_sum_group1 - sum_group2);
        // 或者更简洁地: long long current_difference = std::abs(2 * current_sum_group1 - total_weight_sum);
        min_global_difference = std::min(min_global_difference, current_difference);
        return;
    }

    // 递归步骤：对于当前苹果 weights[index]

    // 选项1: 将当前苹果放入第一组
    solve_dfs(index + 1, current_sum_group1 + weights[index]);

    // 选项2: 将当前苹果放入第二组 (即不将其加入 current_sum_group1)
    solve_dfs(index + 1, current_sum_group1);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cin >> num_apples;

    weights.resize(num_apples);
    total_weight_sum = 0;
    for (int i = 0; i < num_apples; ++i) {
        std::cin >> weights[i];
        total_weight_sum += weights[i];
    }

    min_global_difference = LLONG_MAX; // 初始化最小差值为一个非常大的数

    // 初始调用 DFS
    // 从第0个苹果开始，第一组的初始和为0
    solve_dfs(0, 0);

    std::cout << min_global_difference << std::endl;

    return 0;
}
```
