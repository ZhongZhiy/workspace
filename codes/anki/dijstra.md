# 算法

## dijstra的边应该怎么存储

<!-- notecardId: 1762429605154 -->
带权边, 使用结构体存, 不需要排序
```cpp
  struct Edge{
  int u, w;
  Edge(){}
  Edge(int u, int w):u(u), w(w);
};
```

## dijstra优先队列应该怎么存节点信息?

<!-- notecardId: 1762429605164 -->
需要节点的id和到当前节点的距离, 还需要重载比较函数
```cpp
struct Node{
  int id, dis;
  Node(){}
  Node(int id, int dis):id(id), dis(dis){}
  bool operator < (const Node& a) const {return dis > a.dis;}
}
```

## dijstra初始化哪些信息

<!-- notecardId: 1762429605168 -->
初始化所有的举例为无限大或者是`0x3f`
其次, `vis[i]`全部初始化为未访问

## dijstra中优先队列发挥什么作用?

<!-- notecardId: 1762429605171 -->
使用优先队列能够每次取到当前最短的距离的节点
所有`push`的距离只起到排序的作用

## dijstra的while循环中第一步是什么?

<!-- notecardId: 1762429605175 -->
取出堆顶元素的id, 并且`pop`掉, 然后检查是不是第一次访问
```cpp
int u = q.top().id; q.pop();
if(vis[u]) continue;
vis[u] = 1;
```

## dijstra中遍历当前节点的邻接边的时候检测什么?

<!-- notecardId: 1762429605179 -->
检测的是从当前节点到邻接节点是不是比之前到达邻接节点更短, 如果更短就更新距离, 并且把这个新距离放入优先队列
```cpp
for(auto &ed : e[u]){
  int v = ed.v, w = ed.w;
  if(dis[v] > dis[u] + w){
    dis[v] = dis[u] + w;
    q.push({dis[v], v});
  }
}
```
