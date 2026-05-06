#import "@preview/fletcher:0.5.8" as fletcher: diagram, node, edge
#set page(
    fill: rgb(224, 247, 229),
)

#let flexible-graph(
  nodes-pos: (:),
  edges: (),
) = {
  diagram(
    node-stroke: 1pt,
    node-fill: none,
    label-sep: 0.0em, //label 距离边
    spacing: 2cm,
    {
      // 1. 放置节点
      for (name, pos) in nodes-pos {
        node(pos,[#name] , name: label(name), shape:circle)
      }

      // 2. 放置边
      for e in edges {
        // 解包前两个参数为起点和终点
        let u = e.at(0)
        let v = e.at(1)
        // 尝试获取第三个参数作为标签，如果没有则为 none
        let label-val = if e.len() > 2 { e.at(2) } else { none }

        // 转换为 label 引用节点 [cite: 118, 230]
        let from = label(str(u))
        let to = label(str(v))

        if u == v {
          // 自环处理 [cite: 331]
          edge(from, to,label: label-val, "-|>", bend: 135deg)
        } else {
          // 普通边：fletcher 会自动识别 label-val 是否为内容 [cite: 364, 506]
          edge(from, to, label: label-val, "-|>")
        }
      }
    }
  )
}

// 调用示例
#flexible-graph(
  nodes-pos: (
    "1": (0,0),
    "3": (1,0),
    "2": (0.5, 1),
    "4": (2,1),
    "5": (1, 1.5),
  ),
  edges: (
    (1, 2), // 只有两个参数：无编号边
    (2, 3),// 三个参数：带数学公式编号
    (3, 1),  // 三个参数：带字符串编号
    (3, 4),
    (2,4),
    (4,5),
    (5,2),
  )
)
