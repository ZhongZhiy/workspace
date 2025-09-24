#include<bits/stdc++.h>
using namespace std;

// 使用 long long 避免潜在的整数溢出，尽管此题中 int 足够
#define int long long 
#define PLEASE_AC return 0

// 节点结构体，存储值和原始索引以保证在 set 中的唯一性
struct node {
    int val, id;
    node(int v, int d): val(v), id(d) {}

    // 自定义比较运算符，用于 set 排序
    bool operator<(const node& other) const {
        if (val != other.val) {
            return val < other.val;
        }
        return id < other.id;
    }
};

// 全局变量存储两个堆
set<node> lower_half, upper_half;
int k;

// 平衡函数：确保 lower_half 的大小为 (k+1)/2
void balance_heaps() {
    while (lower_half.size() > (k + 1) / 2) {
        upper_half.insert(*lower_half.rbegin());
        lower_half.erase(prev(lower_half.end()));
    }
    while (lower_half.size() < (k + 1) / 2) {
        if (upper_half.empty()) break;
        lower_half.insert(*upper_half.begin());
        upper_half.erase(upper_half.begin());
    }
}

// 插入新元素
void add(const node& n) {
    // 如果新元素小于等于 lower_half 的最大值，则它属于较小的一半
    if (!lower_half.empty() && n.val <= lower_half.rbegin()->val) {
        lower_half.insert(n);
    } else {
        upper_half.insert(n);
    }
    balance_heaps();
}

// 删除旧元素
void remove(const node& n) {
    if (lower_half.count(n)) {
        lower_half.erase(n);
    } else {
        upper_half.erase(n);
    }
    balance_heaps();
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // 初始化第一个窗口
    for (int i = 0; i < k; ++i) {
        add({a[i], i});
    }

    // 输出第一个窗口的中位数
    cout << lower_half.rbegin()->val;

    // 滑动窗口
    for (int i = k; i < n; ++i) {
        // 删除离开窗口的元素 a[i-k]
        remove({a[i - k], i - k});
        // 添加进入窗口的新元素 a[i]
        add({a[i], i});
        // 输出当前窗口的中位数
        cout << " " << lower_half.rbegin()->val;
    }

    cout << endl;

    PLEASE_AC;
}
