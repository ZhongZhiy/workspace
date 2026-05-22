>[!note] 把序列划分成  $k$ 段, 求每段的绝对值的和的最大值
>> 思路: 设`dp[i][k]`为前`i`个数划分成`k`段的最小值, 
>> 初始化`dp[i][1] = abs(a[i])`,
>>  那么状态转移是在`i`之前找到一个`j`作为分割点, 令`dp[i][k] = max{dp[j][k-1] + abs(pref[i] - pref[j])}`, 
>>  这样的时间复杂度是 $k \times n^2$ , 可以优化: `dp[j][k-1] + abs(pref[i] - pref[j]) = (dp[j][k-1] - pref[j]) + pref[i] or (dp[j][k-1] + pref[j]) - pref[i]` , 那么就可以记忆 `dp[i][k-1] +/- pref[j]` 的最大值, 从而优化至 $k \times n$






