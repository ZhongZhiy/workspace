---
title: CSES Edit Distance
date: 2026-01-25
categories:
tags:
  - 算法
  - DP
status:
difficulty: 🟡 中等
link: https://cses.fi/problemset/result/16045328/
---

# CSES Edit Distance
## 题意

> [!abstract] 题目关键信息
> 给定两个字符串, 有$3$个操作, 增添一个字符, 删除一个字符, 修改一个字符, 两个字符串的距离就是使用最少的这三个操作让两个字符相等的个数
##  题解
定义状态: `dp[i][j]`为字符串`s`前`i`个字符和字符串`t`前`j`个字符的距离
状态转移: 
如果`s[i] == s[j]`, 那么`dp[i][j] =  dp[i-1][j-1]`
如果`s[i] != s[j]`, 那么: 
	使用添加, 也就是在`s[i-1]`后面添加一个`t[j]`, 那么现在$s$前$i$个的状态就等于$t$前$j-1$个的状态,  `dp[i][j] = 1 + dp[i][j-1]`
	使用删除, 也就是在`s[i]`除删除一个字符, 删除后就等于`dp[i][j] = 1+ dp[i-1][j]`
	使用修改, 也就是把`s[i]`改为`t[j]`, `dp[i][j] = 1 + dp[i-1][j-1]`

初始化: 对于`dp[i][0]`和`dp[0][j]`进行初始化
注意使用`long long`的话会爆内存
##  参考代码
> [!example] 
```cpp fold

// 只需要记录最核心的代码块或模板
```
