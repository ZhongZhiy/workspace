
/*
  January's Color — 最小代价把 x“熔”为 y
  -------------------------------------------------------
  题意回顾：
  - 给定一棵以 1 为根的树；每个点要么叶子，要么至少两个孩子（无“独生子”）。
  - 你可以：
      1) 花费 c[i] 直接从银行买到 i；
      2) 若手里有同一父亲的两个不同孩子 u,v，可把它们“合成”为父亲 p=fa(u)=fa(v)（免费），并丢掉 u、v。
  - 对于每个询问 (x,y)：起手只有 x，目标是最后只剩 y。求最小额外花费，不行则 -1。

  核心结论（保证正确性）：
  1) 只能向上合成 ⇒ 若 y 不是 x 的祖先，必无解（-1）。
  2) 定义 f[u] = “从零做出 u 的最小代价”。
     - 叶子：f[u] = c[u]（只能买）
     - 非叶：f[u] = min( c[u], 选两个孩子 v,w 的 f[v]+f[w] )。
       因为合成一次即可到父亲，选两个最便宜的孩子即可。
       (题设保证孩子数 ≥ 2，所以“两小值”总存在)
  3) 从 x 沿父链一步步合到 y。设当前在 v，上到 p=parent(v) 需要再拿到 p 的“另一个孩子 s≠v”。
     这步的最小代价就是 w[v] = min_{s 是 p 的孩子且 s≠v} f[s]。
     对每个父亲 p 预处理孩子 f 的最小/次小值，可 O(1) 得到 w[v]。
  4) 对每个询问 (x,y)，若 y 是 x 的祖先，则答案为 x→y 路径（不含 y）每一步的 w[v] 之和。
     用二进制提升维护 up[k][v] 与 sw[k][v]（走 2^k 步的代价和），查询 O(log n)。

  复杂度：
  - 建树与 DP：O(n)
  - 预处理最小/次小 + 二进制提升表：O(n log n)
  - 单次询问：O(log n)
  - 多测累积 (sum n, sum m ≤ 3e5) 可安全通过
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INFLL = (ll)4e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n, m;
        cin >> n >> m;

        // c[i]：直接购买点 i 的成本
        vector<ll> c(n+1);
        for (int i = 1; i <= n; ++i) cin >> c[i];

        // 读入无向树
        vector<vector<int>> adj(n+1);
        for (int i = 0; i < n-1; ++i) {
            int u, v; cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // ---------- 一、把树根在 1 上：求 parent、children、depth、DFS 进出时序 ----------
        vector<int> parent(n+1, 0), depth(n+1, 0);
        vector<vector<int>> children(n+1); // 孩子列表（有向：从父指向子）
        vector<int> tin(n+1), tout(n+1);   // 进入/离开时间戳，用于祖先判断
        vector<int> post; post.reserve(n); // 后序序列（孩子先入，再父入），用于自底向上的 DP
        int timer = 0;

        /*
           用“手动栈”实现的迭代 DFS（避免递归爆栈）：
           st 元素 (u, state)：state=0 表示即将“进入”u，state=1 表示即将“离开”u。
        */
        vector<pair<int,int>> st;
        st.reserve(2*n);
        st.push_back({1, 0}); // 从根 1 开始
        parent[1] = 0; depth[1] = 0;

        while (!st.empty()) {
            auto [u, state] = st.back();
            if (state == 0) {
                // 第一次见到 u：标记进入时间，展开孩子
                st.back().second = 1;      // 下次回来是离开态
                tin[u] = ++timer;
                for (int v : adj[u]) {
                    if (v == parent[u]) continue; // 不走回头路
                    parent[v] = u;
                    depth[v]  = depth[u] + 1;
                    children[u].push_back(v);
                    st.push_back({v, 0});
                }
            } else {
                // 离开 u：记录离开时间，并压入后序数组
                tout[u] = ++timer;
                post.push_back(u);
                st.pop_back();
            }
        }

        // ---------- 二、DP 求 f[u] 与每个父亲的“孩子 f 的两小值” ----------
        /*
           f[u] = 从零做出 u 的最小成本
           叶子：f[u] = c[u]
           内部：f[u] = min( c[u], 选两个孩子的 f 相加的最小值 )
           同时，为了后续求“向上合成一步”的成本 w[v]，对每个父亲 u，
           我们还要记录它孩子 f 的最小值 best1[u]、次小值 best2[u]，以及最小值对应孩子 id1[u]。
        */
        vector<ll> f(n+1, 0);
        vector<ll> best1(n+1, INFLL), best2(n+1, INFLL);
        vector<int> id1(n+1, -1); // best1 对应的孩子 id

        for (int u : post) { // 后序，先处理子，再处理父
            if (children[u].empty()) {
                // 叶子：没有孩子，无法用孩子合成，只能购买
                f[u] = c[u];
                best1[u] = best2[u] = INFLL; // 无孩子，标记为 INF
                id1[u] = -1;
            } else {
                // 内部点：枚举孩子，找两小
                ll a = INFLL, b = INFLL; // a=最小，b=次小
                int who = -1;
                for (int v : children[u]) {
                    ll val = f[v];
                    if (val < a) { b = a; a = val; who = v; }
                    else if (val < b) { b = val; }
                }
                best1[u] = a; best2[u] = b; id1[u] = who;

                // f[u] = min( 直接买 u, 用两最便宜孩子合成 )
                f[u] = min(c[u], a + b);
                // 注：a,b 必然存在，因为题目保证“内部点至少两个孩子”
            }
        }

        // ---------- 三、w[v]：从 v 合成到其父亲 p 所需的最小补卡成本 ----------
        /*
           v -> p=parent(v) 需要再拿到 p 的另一个孩子 s≠v，
           代价就是 s 的“从零做出成本” f[s] 的最小值。
           若 v 不是 p 的 “best1” 孩子，则 w[v] = best1[p]；
           否则需避开 v，用次小值，w[v] = best2[p]。
        */
        vector<ll> w(n+1, 0);
        for (int p = 1; p <= n; ++p) {
            for (int v : children[p]) {
                if (v != id1[p]) w[v] = best1[p];
                else             w[v] = best2[p];
                // 题设保证 p 若有孩子则 ≥2，所以 best2[p] 存在
            }
        }

        // ---------- 四、二进制提升：up[k][v] 与 sw[k][v] ----------
        /*
           up[k][v] = v 往上跳 2^k 层后的祖先（不存在则 0）
           sw[k][v] = 从 v 往上走 2^k 步的总代价（边代价就是每步的 w[当前节点]）
           这样就能 O(log n) 累加 x -> y 的路径代价（仅向上）。
        */
        int LOG = 1;
        while ((1 << LOG) <= n) ++LOG;

        vector<vector<int>> up(LOG, vector<int>(n+1, 0));
        vector<vector<ll>>  sw(LOG, vector<ll>(n+1, 0));

        // k=0：走 1 步（到父亲）
        for (int v = 1; v <= n; ++v) {
            up[0][v] = parent[v];
            sw[0][v] = parent[v] ? w[v] : 0; // 根没有父亲，不存在这条边
        }
        // k>0：倍增合并
        for (int k = 1; k < LOG; ++k) {
            for (int v = 1; v <= n; ++v) {
                int mid = up[k-1][v];
                if (mid) {
                    up[k][v] = up[k-1][mid];
                    sw[k][v] = sw[k-1][v] + sw[k-1][mid];
                } else {
                    up[k][v] = 0;
                    sw[k][v] = sw[k-1][v];
                }
            }
        }

        // 祖先判断：y 是否为 x 的祖先（基于进入/离开时间）
        auto is_anc = [&](int a, int b)->bool {
            // a 是 b 的祖先 ⇔ tin[a] ≤ tin[b] 且 tout[b] ≤ tout[a]
            return tin[a] <= tin[b] && tout[b] <= tout[a];
        };

        // 把 x 提升到 y（要求 y 为 x 的祖先），返回沿途总代价
        auto lift_sum_to = [&](int x, int y)->ll {
            ll res = 0;
            int d = depth[x] - depth[y]; // 需要向上跳的步数
            for (int k = 0; k < LOG; ++k) {
                if (d & (1 << k)) { // 需要跳 2^k
                    res += sw[k][x];
                    x = up[k][x];
                }
            }
            // 跳完应有 x==y
            return res;
        };

        // ---------- 五、处理每个询问 ----------
        while (m--) {
            int x, y; cin >> x >> y;
            if (!is_anc(y, x)) {
                // 不能向下合成 ⇒ 无法得到 y
                cout << -1 << '\n';
            } else {
                // 累加 x->y 的层层“补兄弟”成本
                cout << lift_sum_to(x, y) << '\n';
            }
        }
    }
    return 0;
}
