#include <bits/stdc++.h>
using namespace std;

static const uint32_t MOD  = 1u << 20;        // 2^20
static const uint32_t MASK = MOD - 1;
static const uint32_t YMOD = 1u << 19;        // y 的有效模（2^19）
static const uint32_t YM   = YMOD - 1;
static const int K = 19;                      // 最高阶 e_19
static const int L = K + 1;

// 每个阶的掩码：e_k 存在模 2^(20-k)
uint32_t EMASK[L]; // EMASK[k] = (1u << (20 - k)) - 1

// 组合数 C[n][r]（r <= 19），模 2^20
vector<array<uint32_t, L>> C;

struct Node {
    uint32_t e[L];   // e[0..19]，e_k 按 2^(20-k) 存储
    uint32_t lazy;   // 累积平移量 y（模 2^19）
    Node(){ memset(e, 0, sizeof(e)); lazy = 0; }
};

int n, q;
vector<Node> seg;

// 把 a_i 转为叶子：a_i = 1 + 2 t_i => e0=1, e1=t_i
static inline Node make_leaf(uint32_t a) {
    Node nd;
    uint32_t t = ((a - 1u) >> 1) & YM;  // t in [0, 2^19)
    nd.e[0] = 1u & EMASK[0];
    nd.e[1] = t  & EMASK[1];
    // 其余 0
    return nd;
}

// 合并：e_k = sum_{i=0..k} L.e_i * R.e_{k-i}，并按 EMASK[k] 截断
static inline void pull(Node &res, const Node &Lft, const Node &Rgt) {
    for (int k = 0; k <= K; ++k) {
        unsigned long long s = 0;
        for (int i = 0; i <= k; ++i)
            s += (unsigned long long)Lft.e[i] * Rgt.e[k - i];
        res.e[k] = (uint32_t)(s & EMASK[k]);
    }
}

// 对节点 p（长度 len）施加“整段平移” t += y
static inline void apply(int p, int len, uint32_t y) {
    if (!y) return;
    // 预先计算 y^r (mod 2^20)
    uint32_t yPow[L]; yPow[0] = 1u;
    for (int r = 1; r <= K; ++r)
        yPow[r] = (uint32_t)(((unsigned long long)yPow[r-1] * y) & MASK);

    uint32_t old[L]; memcpy(old, seg[p].e, sizeof(old));

    for (int k = 0; k <= K; ++k) {
        unsigned long long s = 0;
        for (int i = 0; i <= k; ++i) {
            int r = k - i;
            if (len - i < r) continue; // 组合数为 0
            s += (unsigned long long)old[i] * C[len - i][r] * yPow[r];
        }
        seg[p].e[k] = (uint32_t)(s & EMASK[k]);
    }
    seg[p].lazy = (seg[p].lazy + y) & YM; // 累加懒标记（模 2^19）
}

// 下推懒标记
static inline void push(int p, int l, int r) {
    uint32_t y = seg[p].lazy;
    if (!y) return;
    int m = (l + r) >> 1;
    apply(p<<1,   m - l + 1, y);
    apply(p<<1|1, r - m,     y);
    seg[p].lazy = 0;
}

// 建树
void build(int p, int l, int r, const vector<uint32_t>& a) {
    if ((int)seg.size() <= p) seg.resize(p + 1);
    if (l == r) { seg[p] = make_leaf(a[l]); return; }
    int m = (l + r) >> 1;
    build(p<<1, l, m, a);
    build(p<<1|1, m+1, r, a);
    pull(seg[p], seg[p<<1], seg[p<<1|1]);
}

// 区间加：x=2y（y = x>>1，模 2^19）
void update(int p, int l, int r, int ql, int qr, uint32_t y) {
    if (qr < l || r < ql) return;
    if (ql <= l && r <= qr) {
        apply(p, r - l + 1, y);
        return;
    }
    push(p, l, r);
    int m = (l + r) >> 1;
    update(p<<1,   l,   m, ql, qr, y);
    update(p<<1|1, m+1, r, ql, qr, y);
    pull(seg[p], seg[p<<1], seg[p<<1|1]);
}

// 求一个整段节点对应乘积：sum_k 2^k * e_k (mod 2^20)
static inline uint32_t node_value(int p) {
    unsigned long long s = 0;
    for (int k = 0; k <= K; ++k)
        s += (unsigned long long)(1u << k) * seg[p].e[k];
    return (uint32_t)(s & MASK);
}

// 区间查询
uint32_t query(int p, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return 1u;
    if (ql <= l && r <= qr) return node_value(p);
    push(p, l, r);
    int m = (l + r) >> 1;
    uint32_t Lhs = query(p<<1,   l,   m, ql, qr);
    uint32_t Rhs = query(p<<1|1, m+1, r, ql, qr);
    return (uint32_t)(((unsigned long long)Lhs * Rhs) & MASK);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    vector<uint32_t> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        uint32_t x; cin >> x;
        a[i] = x & MASK;  // 初始即 < 2^20 且为奇数
    }

    // 预计算每阶掩码
    for (int k = 0; k <= K; ++k) EMASK[k] = (1u << (20 - k)) - 1u;

    // 预处理组合数 C[i][r]（r<=19），模 2^20
    C.assign(n + 1, {});
    C[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        C[i][0] = 1;
        int up = min(i, L - 1);
        for (int r = 1; r <= up; ++r)
            C[i][r] = (C[i-1][r] + C[i-1][r-1]) & MASK;
    }

    seg.resize(4 * n + 5);
    build(1, 1, n, a);

    while (q--) {
        int typ; cin >> typ;
        if (typ == 1) {
            int l, r; uint32_t x; cin >> l >> r >> x;
            uint32_t y = (x >> 1) & YM; // 只需模 2^19
            update(1, 1, n, l, r, y);
        } else {
            int l, r; cin >> l >> r;
            cout << query(1, 1, n, l, r) << '\n';
        }
    }
    return 0;
}

