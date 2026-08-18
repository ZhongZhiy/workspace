
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 0x3f3f3f3f;

// 边结构体
struct Edge {
    int to;
    int weight;
};

// Dial 算法封装类
class Dial {
private:
    int n;                      // 节点总数
    int W;                      // 图中边的最大权值
    vector<vector<Edge>> adj;   // 邻接表

public:
    // 构造函数：n 为节点数，max_w 为图中最大边权 W
    Dial(int nodes, int max_w) : n(nodes), W(max_w), adj(nodes + 1) {}

    // 加边接口（支持有向/无向）
    void add_edge(int u, int v, int w) {
        adj[u].push_back({v, w});
    }

    /**
     * @brief 求解单源最短路
     * @param src 起点
     * @param target 终点（可选，默认为 -1 表示计算全图最短路）
     * @return vector<int> 存储起点到各点的最短距离
     */
    vector<int> solve(int src, int target = -1) {
        vector<int> dist(n + 1, INF);

        // 需要 W + 1 个循环桶
        vector<queue<int>> buckets(W + 1);

        // 起点初始化
        dist[src] = 0;
        buckets[0].push(src);

        // 维护桶中当前节点的总数，防止图不连通时在空桶上死循环
        int total_in_queue = 1;

        // current_dist 充当时间秒表，按 0, 1, 2... 单调递增
        for (int current_dist = 0; total_in_queue > 0; ++current_dist) {
            int bucket_idx = current_dist % (W + 1);

            // 处理当前距离对应的桶
            while (!buckets[bucket_idx].empty()) {
                int u = buckets[bucket_idx].front();
                buckets[bucket_idx].pop();
                total_in_queue--;

                // 懒惰删除：若弹出节点的距离不是当前最优解，说明是废数据，跳过
                if (dist[u] < current_dist) continue;

                // 终点剪枝（如果指定了特定目标节点）
                if (u == target) return dist;

                // 遍历邻居节点
                for (const auto& edge : adj[u]) {
                    int v = edge.to;
                    int w = edge.weight;

                    // 松弛操作
                    if (dist[u] + w < dist[v]) {
                        dist[v] = dist[u] + w;
                        // 将新距离放入对应模值的桶中
                        buckets[dist[v] % (W + 1)].push(v);
                        total_in_queue++;
                    }
                }
            }
        }

        return dist;
    }
};

// ==================== 使用样例 ====================
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m , t; cin >> n >> m >> t;
    int w = 2;

    Dial solver(n, w);

    for(int i = 1;i <= m; ++i){
        int u, v, w; cin >> u >> v >> w;
        solver.add_edge(u, v, w);
        solver.add_edge(v, u, w);
    }

    // 求解以 1 为起点的最短路
    vector<int> dist = solver.solve(1, t);

    // 输出起点到各个点的最短路
    cout << dist[t];

    return 0;
}
