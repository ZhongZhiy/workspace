
## 一、 整体物理架构（Physical Topology）

在物理层面，整个系统由两个独立运行的实体通过**虚拟网络**进行常驻通信：

- **宿主机环境（Linux Host）**：运行我们的 Rust 编译出的二进制高并发网关/服务。它内部由 **Tokio 异步引擎**驱动，维护着一个高效的线程池。
    
- **容器化环境（Docker Container）**：独立隔离运行的 PostgreSQL 15 数据库实例，内部自带强一致性的存储引擎、锁机制、我们即将编写的 **T-SQL 触发器**与**存储过程**。
    
- **通信管道（TDS/PG Protocol）**：Rust 通过 `127.0.0.1:5432` 拨通网络电话，`sqlx::PgPool` 保持常驻的高性能连接池。
    

## 二、 软件逻辑架构：现代干净架构（Clean Architecture）

为了做到“高内聚、低耦合”，确保以后更换数据库或者更换前端时代码不用重写，我们采用工业界标准的**四层洋葱架构**：



```
 ┌─────────────────────────────────────────────────────────┐
 │               应用外壳层 (Application / Shell)          │
 │                 - main.rs (启动引导/配置加载)           │
 └────────────────────────────┬────────────────────────────┘
                              ▼
 ┌─────────────────────────────────────────────────────────┐
 │               业务逻辑层 (Service / Domain)             │
 │                 - ticket_service.rs (售票/退票编排)     │
 │                 - stats_service.rs  (统计报表唤醒)     │
 └────────────────────────────┬────────────────────────────┘
                              ▼
 ┌─────────────────────────────────────────────────────────┐
 │               数据持久化层 (Infrastructure / Data)       │
 │                 - db/client.rs (DbStorage / 仓储实现)    │
 └────────────────────────────┬────────────────────────────┘
                              ▼
 ┌─────────────────────────────────────────────────────────┐
 │               物理数据层 (Database Engine)              │
 │                 - PostgreSQL (Tables / Triggers / Procs)│
 └─────────────────────────────────────────────────────────┘
```

### 1. 核心分层职责拆解

- **领域模型层 (`src/models/`) — 系统的“肉身”**
    
    - 只定义纯粹的数据结构（如 `Train`, `Ticket`, `Clerk`）。它们不夹杂任何 SQL 语句，也不关心自己是怎么被存进数据库的。它们是纯净的 Rust 结构体。
        
- **数据访问层 (`src/db/` / `DbStorage`) — 系统的“手脚”**
    
    - 这就是我们正在写的 **Repository（仓储）模式**。它唯一的工作就是当好“翻译官”。把上层传过来的 Rust 变量绑定（`.bind()`）到 SQL 语句中发给 PG，或者把 PG 回传的 Row 反序列化成 `models` 里的结构体。它**不处理业务逻辑**（比如它不关心火车票有没有卖超，它只管奉命插入）。
        
- **业务服务层 (`src/services/`) — 系统的“大脑”**
    
    - 这里是核心业务规则的所在地（例如 `TicketService`）。当有人发起买票时，大脑会按顺序调度手脚：先去数据库查这个人合不合法，再去发起数据库事务（Transaction）尝试写入车票。
        
- **全局异常层 (`src/error.rs`) — 系统的“神经网”**
    
    - 定义了统领全军的 `SystemError`。将底层网络的断开、数据库的冲突（`23505`）、业务上的超卖，全部强类型化。
        

## 三、 数据流向生命周期（Data Flow）

当一个买票请求（例如：业务员 1 号购买 G1024 车次车票）涌入系统时，架构内部的异步数据流向如下：

1. **控制权触发**：`main.rs` 接收到指令，调用 `TicketService::buy_ticket(clerk_id, train_id)`。
    
2. **业务组装**：`TicketService` 开启一个 SQL 事务，将请求下发给 `DbStorage::insert_ticket(...)`。
    
3. **异步网络外发**：`DbStorage` 使用 `sqlx` 准备好语句，遇到 `.await`。**Tokio 运行时瞬间将该任务挂起**，腾出 CPU。数据包跨越 5432 端口飞向 Docker。
    
4. **数据库原子操作（核心）**：
    
    - PostgreSQL 接收到数据，首先检查外键（车次和员工是否存在），通过。
        
    - 执行 `INSERT INTO tickets`。
        
    - **触发器爆发**：数据库内部的 `AFTER INSERT` 触发器瞬间被激活，自动去修改 `trains` 表的 `remaining_seats = remaining_seats - 1`。
        
    - 如果发现减完后座位 $< 0$，触发器直接掀桌子，抛出数据库异常。
        
5. **异常回传与融化**：数据包顺着网络管道回传。Tokio 唤醒 Rust 的挂起任务。`.await` 融化外壳，`DbStorage` 通过 `map_database_error` 捕获异常，将其翻译为 `Err(SystemError::SeatInsufficient)` 并一路向上抛回。
    

> ### 💡 架构师的至理名言
> 
> “好的架构，就是把变化隔离。数据库怎么变，不影响业务怎么写；业务怎么变，不影响数据怎么存。”

有了这幅宏观的透视地图，你现在的每一行代码都有了归宿：写 SQL 建表是在筑基，写 `DbStorage` 是在搭桥。

宏观架构完全闭环。**你准备好带着这幅全景图，重新回到本地战场，把 Milestone 1 的代码（`error.rs` 和 `DbStorage` 的实现）敲出来并提交给我评审了吗？**



# 解开`fn code(&self) -> Option<std::borrow::Cow<'_, str>>`
`Cow`是clone on write, 它是为了**压榨极致性能**而生的。

- 如果数据库返回的错误码在内存里是个静态常量，`Cow` 就直接**复用**这个引用，不花一分钱内存。
    
- 如果是动态生成的，`Cow` 才会去堆上开辟空间。
    
- **代价**：它既不是普通的 `String`，也不是普通的 `&str`，它是一个包裹着字符串的**智能指针外壳**。

`.as_deref()` 是标准库里针对 `Option` 专门量身定制的转换函数。它的魔力在于：**它可以把一个包裹着昂贵/复杂智能指针的 `Option<外壳>`，扁平化地融化成一个包裹着最基础切片的 `Option<&底片>`**



# 用Axum 写Web
axum 有个 `trait` 是`IntoResponse`, 用来处理自定义错误

[[网络响应]]

## 编译期的大胜利

当你把这一段特征实现写完之后，你会发现一个极其震撼的爽点： 你看你之前写的 `sell_ticket` 函数：


```rust
pub async fn sell_ticket(...) -> Result<()>
```

因为这里的 `Result<()>` 里的错误项就是 `SystemError`。而在 Axum 里，如果 `E` 实现了 `IntoResponse`，那么 `Result<T, E>` 也会**自动自动实现 `IntoResponse`**！

这意味着以后你的 Web 处理器（Handler）可以直接这样写，连错误解包都省了：
	 


```rust
pub async fn buy_ticket_api(State(storage): State<Arc<DbStorage>>) -> Result<impl IntoResponse> {
    storage.sell_ticket(...).await?; // 🟢 发生错误时，一个问号直接原地飞回前端！
    Ok(StatusCode::OK)
}
```

把 `src/error.rs` 成功换上去之后，执行一下 `cargo check`。如果顺利通过，代表我们的 Web 神经网已经彻底接通。

## 解读代码`pub type Result<T> = std::result::Result<T, SystemError>;`
对应返回类型
```sh
实际代码：
Ok(( StatusCode::CREATED, Json(json!({ ... })) ))
 │ └──────────────┬────────────────────────┘
 │                │ 这是一个 (StatusCode, Json) 元组
 │                ▼
 │         由于 Json: IntoResponse，
 │         所以根据 Axum 铁律，整个元组也实现了 IntoResponse 特征！
 ▼
满足了 Result<T, E> 中的成功变体 T

最终等价于：
Result< 某个实现了IntoResponse的元组, SystemError >
```



### 1. 核心概念：HTTP 是结构体

- **`HttpRequest` (输入)**：前端发来的包裹，里面装著纯文本数据（如：请求路径 `/api/v1/tickets` 和买票的 JSON 数据）。
    
- **`HttpResponse` (输出)**：后端回传的信件，里面装著状态码（如 `200` 成功）和结果数据。
    
- **Web 服务器的本质**：就是一个简单的数据转换函数 $\text{HttpRequest} \longrightarrow \text{HttpResponse}$。
    

### 2. 核心工具：Tower::Service

- **为什么需要它**：真实的 Web 业务不能靠一个函数写完，需要经过日志、限流、鉴权等多个“关卡”。
    
- **它是什么**：它是 Tokio 团队定义的一个标准 Rust 特征（Trait）。它规范了一个统一的异步接口 `call`，让任何结构体只要实现了它，就能变成一个标准的“加工关卡”。
    

### 3. 核心架构：洋葱（套娃）模型

- **工作原理**：Axum 框架通过 `Tower::Service` 把各个独立的关卡像洋葱一样层层套起来。
    
- **数据流向**：
    
    1. **请求（Request）**：自外向内穿过【日志外壳】$\rightarrow$【限流外壳】$\rightarrow$ 到达【核心业务】。
        
    2. **响应（Response）**：在核心业务生成后，再自内向外反向穿出，最终返回给前端。


## 网页是以本地文件（或者另一个端口）打开的，而 Axum 跑在 `8080`，现代浏览器的安全策略（同源策略）会无情地**拦截**这种跨端口的抓取请求。

添加`tower-http`通行数据

