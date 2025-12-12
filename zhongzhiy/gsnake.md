我用你现在这版 `snake_game` 给你一点一点拆开讲，覆盖你提到的几个关键点：**方向控制、计时、随机苹果、下一步位置、吃到自己、吃到苹果**，都直接对应到代码哪一段。

下面讲的代码都出自这个模块（略掉了一些不相关的定义）：

```verilog
module snake_game #(
    parameter integer MOVE_DIV = 50_000_000,
    parameter integer MAX_LEN  = 16
)(
    input              clk,
    input              rst,
    input              pause,
    input      [3:0]   dir_sw,
    output reg [63:0]  bitmap,
    output reg [7:0]   score_bcd,
    output reg         game_over
);
```

模块里主要维护这些状态：

- 当前方向：`dir`
    
- 蛇头坐标：`head_x`, `head_y`
    
- 蛇身体：`snake_x[0..MAX_LEN-1]`, `snake_y[0..MAX_LEN-1]`（0 是头）
    
- 当前长度：`snake_len`
    
- 苹果坐标：`food_x`, `food_y`
    
- 得分：`score_bcd`（BCD）
    
- 定时计数器：`move_cnt`
    
- 随机数寄存器：`rand_reg`
    

---

## 1. 方向控制是怎么做的？

### 1.1 外部输入 → 内部方向编码

我们约定：

- `dir_sw[0]`：左
    
- `dir_sw[1]`：右
    
- `dir_sw[2]`：上
    
- `dir_sw[3]`：下
    

内部用一个 2bit 的 `dir` 表示当前方向：

```verilog
localparam [1:0] DIR_UP    = 2'b00;
localparam [1:0] DIR_DOWN  = 2'b01;
localparam [1:0] DIR_LEFT  = 2'b10;
localparam [1:0] DIR_RIGHT = 2'b11;

reg [1:0] dir;      // 当前方向
```

### 1.2 dir_next：带优先级和防掉头的组合逻辑

我们不直接对 `dir` 赋值，而是算出一个 `dir_next`（下一步要用的方向）：

```verilog
reg [1:0] dir_next;

always @(*) begin
    // 默认保持当前方向
    dir_next    = dir;
    head_x_next = head_x;
    head_y_next = head_y;

    // 方向输入优先级：上 > 下 > 左 > 右，并禁止 180° 掉头
    if (dir_sw[2]) begin // 上
        if (dir != DIR_DOWN)
            dir_next = DIR_UP;
    end else if (dir_sw[3]) begin // 下
        if (dir != DIR_UP)
            dir_next = DIR_DOWN;
    end else if (dir_sw[0]) begin // 左
        if (dir != DIR_RIGHT)
            dir_next = DIR_LEFT;
    end else if (dir_sw[1]) begin // 右
        if (dir != DIR_LEFT)
            dir_next = DIR_RIGHT;
    end
    ...
end
```

这里做了几件事：

1. **优先级控制**
    
    - 多个开关同时拨动时，判断顺序是：  
        **上 → 下 → 左 → 右**
        
    - 谁先命中就用谁。
        
2. **禁止 180° 掉头**
    
    - 正在向上（`dir == DIR_UP`）时，如果你突然按“下”，因为 `dir != DIR_UP` 不满足，就**不允许改成向下**；
        
    - 正在向左，按右也会被忽略；
        
    - 这样避免蛇直接拐回头撞到自己。
        
3. 若没有按键变化，则 `dir_next` 保持为当前 `dir`。
    

在时序逻辑里，只有在真正移动的那个时刻才把 `dir_next` 写回 `dir`：

```verilog
if (move_tick && !pause) begin
    ...
    dir <= dir_next;
    ...
end
```

---

## 2. 计时：什么时候移动一步？

我们希望蛇不是每个时钟都动，而是“几百毫秒动一步”。这里用分频计数器实现。

```verilog
reg  [25:0] move_cnt;
wire        move_tick = (move_cnt == MOVE_DIV - 1);
```

- `move_cnt` 从 0 加到 `MOVE_DIV-1`；
    
- 当等于 `MOVE_DIV-1` 时产生一个周期的高电平 `move_tick` —— 这就是“移动一次”的节拍。
    

计数器更新逻辑：

```verilog
always @(posedge clk or posedge rst) begin
    if (rst)
        move_cnt <= 26'd0;
    else if (pause)
        move_cnt <= move_cnt;          // 暂停时停在原计数值
    else if (move_tick)
        move_cnt <= 26'd0;
    else
        move_cnt <= move_cnt + 1'b1;
end
```

- **复位**：清零。
    
- **暂停**：`pause=1` 时保持不变，节拍不再产生，蛇也不会动。
    
- **正常运行**：
    
    - 每个时钟加一；
        
    - 加到 `MOVE_DIV-1` 时下一拍清零，从头计数。
        

然后所有“与移动有关”的状态更新都写成 `if (move_tick && !pause)`：

```verilog
if (move_tick && !pause) begin
    // 蛇移动
    // 吃苹果检测
    // 咬到自己检测
end
```

这样就保证 **蛇每隔固定时间才移动一步**，而不是每拍都动。

---

## 3. 随机生成苹果（简单 LFSR）

### 3.1 伪随机数发生器

用一个 8bit 的 LFSR：

```verilog
reg [7:0] rand_reg;
always @(posedge clk or posedge rst) begin
    if (rst)
        rand_reg <= 8'h1;
    else if (move_tick && !pause)
        rand_reg <= {rand_reg[6:0],
                     rand_reg[7] ^ rand_reg[5] ^ rand_reg[4] ^ rand_reg[3]};
end
```

特点：

- `rand_reg` 每**移动一步**更新一次；
    
- `rand_reg[7] ^ rand_reg[5] ^ rand_reg[4] ^ rand_reg[3]` 是典型 LFSR 的反馈项；
    
- 这样跑出来是一串“看起来挺随机”的数，不需要真的 RNG。
    

### 3.2 苹果坐标从随机数里切出来

在“吃到苹果”的那一刻，我们更新苹果位置：

```verilog
if (will_eat) begin
    ...
    // 产生新的食物位置（简单随机）
    food_x <= rand_reg[2:0];
    food_y <= rand_reg[5:3];
end
```

- `food_x` 用 `rand_reg[2:0]` → 范围 0~7；
    
- `food_y` 用 `rand_reg[5:3]` → 范围 0~7。
    

所以苹果始终被放在 8×8 的某一个格子上。

> 注：这份代码没有专门避免“苹果刷在蛇身上”，实际游戏中概率很低，即使刷在身上，下一次移动马上就“吃到”。

---

## 4. 下一步位置怎么算？（带穿墙）

在同一个 `always @(*)` 组合逻辑里，除了方向，还算出头的下一步坐标 `head_x_next` / `head_y_next`：

```verilog
// 计算下一步头坐标（到边界会从另一侧出来）
case (dir_next)
    DIR_UP: begin
        head_x_next = head_x;
        head_y_next = (head_y == 3'd0) ? 3'd7 : head_y - 1'b1;
    end
    DIR_DOWN: begin
        head_x_next = head_x;
        head_y_next = (head_y == 3'd7) ? 3'd0 : head_y + 1'b1;
    end
    DIR_LEFT: begin
        head_x_next = (head_x == 3'd0) ? 3'd7 : head_x - 1'b1;
        head_y_next = head_y;
    end
    DIR_RIGHT: begin
        head_x_next = (head_x == 3'd7) ? 3'd0 : head_x + 1'b1;
        head_y_next = head_y;
    end
    default: begin
        head_x_next = head_x;
        head_y_next = head_y;
    end
endcase
```

这个 `? :` 很关键，就是实现**穿墙**：

- 往上走：
    
    - 如果 `head_y==0`，再往上则 `head_y_next=7`（从顶部穿到最底）；
        
    - 否则正常 `head_y-1`。
        
- 往左走：
    
    - `head_x==0` 时再往左变成 `7`；
        
- 往右走：
    
    - `head_x==7` 时再往右变成 `0`；
        
- 往下走类似。
    

**所以这张 8×8 图是一个“环形世界”**，从左边出去从右边进来，从上边出去从下边进来。

---

## 5. 吃到自己（自碰撞）

吃到自己的关键就是判断：**下一步蛇头位置是否与身体的任意一节重合**。

仍然在组合逻辑里：

```verilog
// 咬到自己判断
body_collide = 1'b0;
for (i = 0; i < MAX_LEN; i = i + 1) begin
    if (i < snake_len) begin
        if (head_x_next == snake_x[i] && head_y_next == snake_y[i])
            body_collide = 1'b1;
    end
end
```

- 用 `for` 遍历所有实际蛇身段（`i < snake_len`）；
    
- 如果下一步头坐标和某一节 `(snake_x[i], snake_y[i])` 相等，就说明自撞；
    
- 得出一个组合信号 `body_collide`，在时序逻辑里使用。
    

### 5.1 自撞后的处理（game_over + 重新开始）

在时序 always 块里：

```verilog
always @(posedge clk or posedge rst) begin
    if (rst) begin
        ... // 初始化蛇、苹果、得分、game_over=0
    end else begin
        // 默认 game_over 置0，只有这一步咬到自己时拉高
        game_over <= 1'b0;

        // 暂停时冻结游戏
        if (move_tick && !pause) begin
            // 咬到自己 -> 重新开始，并给出 game_over 脉冲
            if (body_collide) begin
                game_over <= 1'b1;

                dir       <= DIR_RIGHT;
                head_x    <= 3'd3;
                head_y    <= 3'd3;
                snake_len <= 5'd3;

                snake_x[0] <= 3'd3; snake_y[0] <= 3'd3;
                snake_x[1] <= 3'd2; snake_y[1] <= 3'd3;
                snake_x[2] <= 3'd1; snake_y[2] <= 3'd3;
                for (i = 3; i < MAX_LEN; i = i + 1) begin
                    snake_x[i] <= 3'd0;
                    snake_y[i] <= 3'd0;
                end

                food_x <= 3'd5;
                food_y <= 3'd1;

                score_bcd <= 8'd0;
            end else begin
                // 正常移动 / 吃苹果逻辑
                ...
            end
        end
    end
end
```

这里做了两件事：

1. 如果 `body_collide == 1`：
    
    - `game_over <= 1`：这就是你 LED 全亮用的那个“游戏结束脉冲”；
        
    - 重新设置蛇在中间一条水平线；
        
    - 重置苹果位置；
        
    - 分数清零。
        
2. 否则走“正常移动 + 吃苹果逻辑”。
    

---

## 6. 吃到苹果（成长 + 加分 + 新苹果）

在组合逻辑里先判断一下下一步头位置是否等于苹果：

```verilog
// 是否吃到食物（下一头位置 == 食物位置）
will_eat = (head_x_next == food_x && head_y_next == food_y);
```

然后在时序逻辑的“正常移动”分支里处理：

```verilog
// 正常移动一步
dir <= dir_next;

// 从尾到头依次移动
for (i = MAX_LEN-1; i > 0; i = i - 1) begin
    if (i < snake_len) begin
        snake_x[i] <= snake_x[i-1];
        snake_y[i] <= snake_y[i-1];
    end
end

// 更新头位置
snake_x[0] <= head_x_next;
snake_y[0] <= head_y_next;
head_x     <= head_x_next;
head_y     <= head_y_next;

// 吃到食物
if (will_eat) begin
    // 长度+1（不超过 MAX_LEN）
    if (snake_len < MAX_LEN)
        snake_len <= snake_len + 1'b1;

    // BCD 得分 +1（最大到 99，之后饱和）
    if (score_bcd[3:0] == 4'd9) begin
        score_bcd[3:0] <= 4'd0;
        if (score_bcd[7:4] == 4'd9)
            score_bcd[7:4] <= 4'd9;
        else
            score_bcd[7:4] <= score_bcd[7:4] + 1'b1;
    end else begin
        score_bcd[3:0] <= score_bcd[3:0] + 1'b1;
    end

    // 产生新的食物位置（简单随机）
    food_x <= rand_reg[2:0];
    food_y <= rand_reg[5:3];
end
```

顺序是：

1. **整条蛇移动**：
    
    - 从尾到头 `for (i = MAX_LEN-1; i > 0; i--)`，把 `snake[i]` 赋成 `snake[i-1]` → 身体跟着头移动。
        
    - 最前面的 `snake[0]`（头）赋值为新的坐标 `head_x_next/head_y_next`。
        
2. 如果 `will_eat` 为真（也就是**新的头坐标刚好等于苹果坐标**）：
    
    - `snake_len++`：蛇变长；
        
    - `score_bcd++`：分数加一（BCD 两位十进制，最大 99）；
        
    - 用新的随机数设置下一颗苹果的位置。
        

---

## 7. 点阵显示：把蛇和苹果“画”出来

最后，用 `bitmap[63:0]` 表示一张 8×8 的图：

- 每一位代表一个点；
    
- 映射方式是：`index = y*8 + x`。
    

```verilog
always @(*) begin
    bitmap = 64'b0;

    // 蛇身体
    for (i = 0; i < MAX_LEN; i = i + 1) begin
        if (i < snake_len) begin
            idx = snake_y[i] * 8 + snake_x[i]; // bit = y*8 + x
            bitmap[idx] = 1'b1;
        end
    end

    // 食物
    idx = food_y * 8 + food_x;
    bitmap[idx] = 1'b1;
end
```

点阵驱动模块 `matrix_driver` 再按行扫描 `bitmap`，把这些 1/0 变成点阵实际的行列电平。

---

## 总结成一句话的“流程图”

每隔一段时间（由 `MOVE_DIV` 决定）：

1. 根据拨码开关 + 当前方向，算出 **dir_next**（禁止掉头+优先级）；
    
2. 根据当前坐标 + dir_next，算出 **下一步头坐标**（包含穿墙逻辑）；
    
3. 判断：
    
    - `will_eat`：下一步头是否在苹果上；
        
    - `body_collide`：下一步头是否撞到身体；
        
4. 若 `body_collide`：
    
    - `game_over` 拉高一拍；
        
    - 恢复初始蛇、食物、分数；
        
5. 否则：
    
    - 整条蛇移动一步（数组移位 + 更新 `head_x/head_y`）；
        
    - 若 `will_eat`：长度加一、分数加一、随机刷新苹果；
        
6. 最后根据蛇和苹果的坐标，把 `bitmap` 填好，交给点阵驱动模块显示。
    

如果你希望，我可以再画一个 8×8 的表格加上几步 head_x/head_y 的变化，手推一小段“走、吃苹果、撞自己”的具体例子，帮你更直观地理解这个状态机在干什么。