
#include<bits/stdc++.h>
using namespace std;
#define de(x) cout << (#x) << " = " << (x) << endl;
#define de2(x, y) cout << (#x) << " , " << (#y) << " = " << (x) << " ~ " << (y) << endl;
#define endl '\n'
//#define f(n) for(int i = 0;i < n; ++i)
#define ff(i, a, b) for(int i = a; i < b; ++i)
#define PLEASE_AC return 0
typedef long long ll;
typedef unsigned long long ull;
#define int long long 
// 引入 bakulman 的登录信息和当前时间
// User: bakulman
// Time: 2025-07-26 06:43:27 UTC

// --- 常量定义 ---
// SIZE: 节点池的大小，即哈希表能存储的最大键值对数量。
constexpr int SIZE = 1000000;
// M: 哈希桶的数量。通常选择一个大的质数以减少哈希冲突。
constexpr int M = 999997;

/**
 * @brief 一个使用数组和拉链法手写的哈希表。
 * 
 * 这种实现方式通过数组模拟指针（静态链表）来避免动态内存分配，
 * 在竞赛编程中能获得更好的性能。
 */
struct HashTable {
  /**
   * @brief 链表节点结构体。
   * 
   * 用于存储键值对以及指向链表中下一个节点的“指针”（数组下标）。
   */
  struct Node {
    int next;  // 指向下一个节点的下标，0 表示链表末尾
    int value; // 存储的值
    int key;   // 存储的键
  } data[SIZE]; // 预先分配好的节点池

  int head[M]; // 哈希桶数组。head[i] 存储第 i 个桶的链表头节点的下标
  int size;    // 当前已使用的节点数量，也指向 data 数组中下一个可用的位置

  /**
   * @brief 哈希函数，将任意 key 映射到 [0, M-1] 的桶下标。
   * @param key 要计算哈希值的键。
   * @return int 计算出的桶下标。
   * 
   * (key % M + M) % M 是一个标准技巧，确保即使 key 是负数，结果也总是非负的。
   */
  int f(int key) { return (key % M + M) % M; }

  /**
   * @brief 根据 key 查找对应的 value。
   * @param key 要查找的键。
   * @return int 如果找到，返回对应的 value；否则返回 -1。
   */
  int get(int key) {
    // 从 key 对应的哈希桶开始，遍历整个链表
    for (int p = head[f(key)]; p; p = data[p].next) {
      // 如果找到键完全匹配的节点
      if (data[p].key == key) {
        return data[p].value; // 返回其值
      }
    }
    return -1; // 遍历结束没找到，返回 -1
  }

  /**
   * @brief 修改一个已存在的 key 对应的 value。
   * @param key 要修改的键。
   * @param value 新的值。
   * @return int 如果修改成功，返回新的 value。
   * (注意：在此实现中，如果 key 不存在，则不执行任何操作，函数隐式返回)
   */
  int modify(int key, int value) {
    // 遍历链表查找 key
    for (int p = head[f(key)]; p; p = data[p].next) {
      if (data[p].key == key) {
        // 找到后，更新其值并返回
        return data[p].value = value;
      }
    }
    // 如果 key 不存在，此函数没有返回值，是未定义行为。
    // 一个更健壮的实现可能会返回一个布尔值或特定的错误码。
    return -1; // 增加一个返回值以避免警告
  }

  /**
   * @brief 向哈希表中添加一个新的键值对。
   * @param key 要添加的键。
   * @param value 要添加的值。
   * @return int 如果添加成功，返回添加的 value；如果 key 已存在，返回 -1。
   */
  int add(int key, int value) {
    // 如果 key 已经存在，则不允许添加
    if (get(key) != -1) {
      return -1;
    }
    
    // 1. 获取下一个可用的节点位置
    size++;
    
    // 2. 使用头插法将新节点插入链表
    //    新节点的 next 指向当前桶的第一个节点
    data[size].next = head[f(key)];
    data[size].value = value;
    data[size].key = key;
    
    // 3. 更新桶的头指针，使其指向这个新插入的节点
    head[f(key)] = size;
    
    return value;
  }
};


signed main() {
//	freopen("an", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	HashTable mp;

	PLEASE_AC;
}
