好，我们把这页在讲什么、为什么会“突然又有 hold time 需求”捋清楚。

---

## 1. 结构：主从锁存器组成的边沿触发 DFF

图上是典型 **master–slave D 触发器**：

- **master latch** 由 (G') 控制（通常是 CLK 的反相）
    
- **slave latch** 由 (G) 控制（CLK 正相）
    

工作方式：

- CLK=1：master 透明、slave 关闭  
    → master 采样 D
    
- CLK=0：master 关闭、slave 透明  
    → slave 把 master 输出送到 Q  
    所以整体表现成**在时钟边沿采样**（这里是下降沿触发）。
    

---

## 2. 理想情况下，为啥 slave 不应该有 hold 问题？

看下降沿 (1\to 0) 那一刻：

- slave 的门控 (G) 从 1→0  
    → slave “关门”冻结输入数据
    
- 理论上 master 此刻已经关了（因为 (G') 变成 0），  
    它的输出 (Q_M) 应该保持不变  
    → slave 输入不变  
    → **所以看起来不需要 hold time**
    

这就是第一页 bullet 里说的 “SHOULD be no output glitch”。

---

## 3. 现实：master 输出会被时钟变化“污染”（contamination）

关键在 **BUT** 后面那句：

> master output contaminated by change in G input!

意思是：  
虽然 master 在逻辑上“关门”，但时钟（G 或 G'）变化仍会通过 master 内部的组合路径耦合/传播到输出，造成一个**最早到达的非理想扰动**。

这个最早扰动到达 master 输出的时间叫：

[  
t_{cd}^{master}  
]

（contamination delay，污染延迟/最短延迟）

它不是“最终稳定输出”的延迟，而是：

> **输出开始可能变化的最早时间**。

所以 CLK 刚下降时，master 的输出 (Q_M) 可能**很快就抖一下/走向新值**。

---

## 4. 这会导致什么问题？

slave 在下降沿那刻刚要关门，需要满足它自己的保持时间：

[  
t_{hold}^{slave}  
]

即：

> **在关门后的一小段时间内，slave 的 D 输入必须保持稳定**。

但如果 master 的 (Q_M) 在 slave 关门后的很短时间内就被“污染”而改变，那么 slave 就可能采到错误的值或发生毛刺。

于是出现结论：

> **slave 的 hold time 不一定天然满足！**

---

## 5. 解决条件：master 到 slave 的“最短路径延迟”必须够长

图右上角那句：

> The master’s contamination delay must meet the hold time of the slave

翻译成时序约束就是：

[  
t_{cd}^{path} ;\ge; t_{hold}^{slave}  
]

这里的 (t_{cd}^{path}) 是：

- master 输出开始变化的最早时间
    
- 再加上从 master 输出到 slave 输入之间路径的最短延迟
    
- 图里提到还包括一个反相器的延迟（accumulated (t_{cd}) thru inverter）
    

所以最后一句：

> Accumulated (t_{CD}) thru inverter, G → Q path of master must cover slave (t_{HOLD})

意思是：  
**master 的 G→Q 最短污染延迟（加上中间反相器最短延迟）必须至少覆盖 slave 的 hold 窗口。**

---

## 6. 直观比喻

把 slave 想成“关门拍照”的相机：

- 下降沿：相机按下快门开始关门
    
- 要求：**关门后相机前的景象至少保持 (t_{hold}) 不动**
    
- 但 master 这边景象可能因为快门按下瞬间就晃动（污染）
    
- 所以必须保证“晃动传到相机前”之前，相机已经关好门  
    → 就是 (t_{cd}^{path} \ge t_{hold})
    

---

## 7. 小结

这页的核心点：

1. master–slave DFF 虽然看起来天然避免 hold 问题
    
2. 但**时钟边沿会通过 master 的最短污染路径影响其输出**
    
3. 因而 slave 的输入可能在关门后过早变化
    
4. 所以要满足约束：  
    [  
    t_{cd}^{master\rightarrow slave} \ge t_{hold}^{slave}  
    ]
    
5. 实际设计里常用**在 master→slave 路径上刻意加最小延迟**（比如小缓冲/反相器）来保证 hold。
    

---

如果你想的话，我可以结合一个具体波形（画出 master 输出最早污染、slave hold 窗口）再推一遍，会更一眼看懂。