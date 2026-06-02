#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;

// 常用宏定义，这里代码里出现了 over，通常是作者定义的 for 循环宏
#define over(i, s, t) for(int i = s; i <= t; ++i)

const int N = 1e5 + 7;
const int M = 2007;

struct Seg {
    int lc, rc; // 左右儿子编号
    int dat;    // 该区间内救济粮的最大数量
    int pos;    // 数量最多的救济粮种类编号（离散化后的索引）
} tree[N * 70]; // 动态开点线段树空间，通常开 N * logN * 4 左右

int fa[N][20], deep[N]; // LCA 倍增数组和深度数组
int root[N], ans[N];    // 每个点的线段树根节点，以及最终答案
int ver[N << 1], nex[N << 1], head[N]; // 链式前向星存图
int X[N], Y[N], Z[N], val[N]; // 存输入数据及离散化用的数组
int n, m, tot, t, num, cnt;
queue<int> q; // BFS 预处理 LCA 专用

// 链式前向星加边
void add(int u, int v) {
    ver[++tot] = v;
    nex[tot] = head[u];
    head[u] = tot;
}

// 使用 BFS 预处理 LCA 倍增表
void bfs() {
    q.push(1);
    deep[1] = 1;
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i; i = nex[i]) {
            int v = ver[i];
            if (deep[v]) continue; // 已访问过
            deep[v] = deep[u] + 1;
            fa[v][0] = u;
            // 倍增公式：v 的 2^j 祖先是 (v 的 2^(j-1) 祖先) 的 2^(j-1) 祖先
            for (int j = 1; j <= t; ++j)
                fa[v][j] = fa[fa[v][j - 1]][j - 1];
            q.push(v);
        }
    }
}

// 倍增求 LCA
int lca(int x, int y) {
    if (deep[x] > deep[y]) swap(x, y);
    // 先跳到同一深度
    for (int i = t; i >= 0; i--)
        if (deep[fa[y][i]] >= deep[x]) y = fa[y][i];
    if (x == y) return x;
    // 一起向上跳，直到刚好在 LCA 下方
    for (int i = t; i >= 0; i--)
        if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}

// 动态开点线段树插入/修改
// p: 当前节点, l, r: 种类区间, val: 种类编号, delta: 修改量(+1/-1)
void Insert(int &p, int l, int r, int val, int delta) {
    if (!p) p = ++num; // 如果节点不存在，动态开点
    if (l == r) {
        tree[p].dat += delta;
        // 如果数量 > 0，记录位置，否则清零
        tree[p].pos = tree[p].dat ? l : 0;
        return;
    }
    int mid = (l + r) >> 1;
    if (val <= mid) Insert(tree[p].lc, l, mid, val, delta);
    else Insert(tree[p].rc, mid + 1, r, val, delta);

    // 更新当前节点：维护最大值及对应位置
    // 注意这里用 >= 保证了如果数量相等，优先取左儿子（即种类编号更小的）
    if (tree[tree[p].lc].dat >= tree[tree[p].rc].dat) {
        tree[p].dat = tree[tree[p].lc].dat;
        tree[p].pos = tree[tree[p].lc].pos;
    } else {
        tree[p].dat = tree[tree[p].rc].dat;
        tree[p].pos = tree[tree[p].rc].pos;
    }
}

// 线段树合并
int Merge(int p, int q, int l, int r) {
    if (!p) return q;
    if (!q) return p;
    if (l == r) {
        tree[p].dat += tree[q].dat;
        tree[p].pos = tree[p].dat ? l : 0;
        return p;
    }
    int mid = (l + r) >> 1;
    tree[p].lc = Merge(tree[p].lc, tree[q].lc, l, mid);
    tree[p].rc = Merge(tree[p].rc, tree[q].rc, mid + 1, r);

    // 合并后同样要更新最大值信息
    if (tree[tree[p].lc].dat >= tree[tree[p].rc].dat) {
        tree[p].dat = tree[tree[p].lc].dat;
        tree[p].pos = tree[tree[p].lc].pos;
    } else {
        tree[p].dat = tree[tree[p].rc].dat;
        tree[p].pos = tree[tree[p].rc].pos;
    }
    return p;
}

// DFS 自底向上合并
void dfs(int u) {
    for (int i = head[u]; i; i = nex[i]) {
        int v = ver[i];
        if (deep[v] <= deep[u]) continue; // 防止往回跳
        dfs(v);
        root[u] = Merge(root[u], root[v], 1, cnt); // 合并子树到当前节点
    }
    ans[u] = tree[root[u]].pos; // 记录当前节点最多的种类索引
}

int main() {
    scanf("%d%d", &n, &m);
    t = (int)(log(n) / log(2)) + 1;
    over(i, 1, n - 1) {
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, y); add(y, x);
    }

    bfs(); // 预处理 LCA

    // 输入 m 次操作并离散化救济粮种类
    over(i, 1, m) {
        scanf("%d%d%d", &X[i], &Y[i], &Z[i]);
        val[i] = Z[i];
    }
    sort(val + 1, val + m + 1);
    cnt = unique(val + 1, val + 1 + m) - (val + 1); // 种类去重

    over(i, 1, m) {
        int x = X[i], y = Y[i];
        // 找到 Z[i] 离散化后的位置
        int z = lower_bound(val + 1, val + 1 + cnt, Z[i]) - val;
        int p = lca(x, y);

        // 树上差分：x+1, y+1, lca-1, fa[lca]-1
        Insert(root[x], 1, cnt, z, 1);
        Insert(root[y], 1, cnt, z, 1);
        Insert(root[p], 1, cnt, z, -1);
        if (fa[p][0]) Insert(root[fa[p][0]], 1, cnt, z, -1);
    }

    dfs(1); // 递归合并并计算答案

    over(i, 1, n) {
        // 输出时将离散化索引映射回原始种类编号
        printf("%d\n", ans[i] ? val[ans[i]] : 0);
    }
    return 0;
}
