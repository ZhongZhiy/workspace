写个`module.rs`作为解析博客title和日期, 使用`string.strip_prefix("Title: ")`函数去掉开头, 取title

路由（Router）”**。 路由在后端框架里的本质，就是**一张「路径」对应「执行函数」的映射表：
```rust
// 1. Router::new()：在内存里新建一张空白的“交通路线图”。
let app: Router = Router::new()
    // 2. .route("/", ...)：在路线图上钉上一个显眼的路标，写着：“如果有人找『/』（首页）”
    // 3. get(...)：并且对方用的是『GET』方式（也就是只读取网页，不提交数据）
    .route("/", get(move || async move {
        // 4. 执行这段被“注入”进来的代码，从内存里掏出 blog 飞升后的数据，组装成 HTML 扔给用户
        format!("<h1>{}</h1>", blog.title)
    }));
```

## tokio
**工作窃取算法（Work-Stealing Scheduler）**。如果某个 CPU 核心闲下来了，它会自动去别的核心那里“偷”任务来干，绝不让 CPU 摸鱼。

在 Tokio 的世界里，所有的异步函数都带有一个关键字 `async fn`。当你调用一个异步函数时，它**不会立刻执行**，而是返回一个名为 `Future`（未来凭证）的包裹。

当编译器看到你的函数里带有 `async` 和 `.await` 时，它会把你的整个函数悄悄编译成一个**隐式的结构体**。这个结构体里有一个状态字段，记录着你当前干到哪了：

```rust
// 编译器在底层为你自动生成的“冷冻快照结构体”
enum MainFunctionStateMachine {
    Start,               // 还没开工
    WaitingForListener,  // 薯条在油锅里，正在等 TcpListener 返回 【当前卡在这里】
    Finished,            // 全部完工
}
```

[快速开始 \| Askama 非官方不完全文档](https://rust.wjjss.com/askama/quick-start.html)`Askama` 的官方核心源码里，定义了一个至高无上的特质，名字就叫 `Template`：

Rust

```
// Askama 官方库里的核心 Trait 简化模型
pub trait Template {
    // 核心接口 1：渲染成 String
    fn render(&self) -> Result<String, askama::Error>;

    // 核心接口 2：直接把 HTML 文本写入到一个缓存器（Buffer）里，追求极致性能
    fn render_into(&self, writer: &mut desert::Write) -> Result<(), askama::Error>;
}
```


## **`DirEntry`**。
它不是一个单纯的字符串，而是一个**复合结构体**。它里面包含了这个文件的三大核心信息：

- **`entry.path()`**：文件的完整路径（比如 `"./posts/hello.md"`）。
    
- **`entry.file_name()`**：纯文件名（比如 `"hello.md"`）。
    
- **`entry.metadata()`**：文件的元数据（比如这个文件有多大、创建时间是哪天）。


我们用放大镜看看 `fs::read_dir` 里的**双层包裹**设计：

Rust

```rust
// 第一层包裹：打开文件夹可能会失败（比如 posts/ 文件夹根本不存在，或者被你删了）
let entries = fs::read_dir("./posts").unwrap(); 

for entry_result in entries {
    // 第二层包裹：在循环读取的过程中，可能读到一半硬盘被拔掉了，或者文件损坏了
    let entry: DirEntry = entry_result.unwrap(); 
    
    // 这时候，我们才真正拿到了安全的 entry 实体！
}
```


## `PathBuf` 路径智能管理器

通过 `entry.path()` 拿到的返回值类型叫 **`PathBuf`（路径缓存区）**。

在低级系统编程里，路径绝对不能当成普通 `String` 字符串来处理。因为 Windows 用反斜杠 `\`，Linux 用正斜杠 `/`。如果你用字符串拼接（比如 `dir + "/" + file`），你的程序换个操作系统就会直接崩溃。

`PathBuf` 是一个**专门管理操作系统路径的智能集装箱**。它自带了一系列高明的接口：

- **`path.is_file()`**：判断这到底是真正的文件，还是一个嵌套的子文件夹。
    
- **`path.extension()`**：获取文件的后缀名。我们可以用它来做判断：**只有当后缀名正好是 `"md"` 的时候，我们才去读它**，从而完美过滤掉垃圾文件（比如 `.DS_Store` 或 `.gitignore`）。


```rust
let id: String = file_path
    .file_stem()         // 1. 物理动作：切掉肉，只留下骨头，拿到 &OsStr 类型的 "hello"
    .unwrap()            // 2. 解包：确保这个路径确实指代一个文件（而不是空路径）
    .to_string_lossy()   // 3. 施展魔法：带有损失保障地、强行转换成合法的 UTF-8 文本
    .to_string();        // 4. 收尾：把临时的 Cow 指针彻底变成拥有独立所有权的全局内存 String
```



## Arc<T> and RwLock<T>
- **`Arc<T>` 解决的是“这块内存在多线程里到底属于谁”的问题。** 它只管多线程计数和内存生命周期的销毁，但它有一条铁律：**它包裹的数据 `T` 默认是不可变的（Read-Only）**。
- **`RwLock<T>` 解决的是“多线程怎么安全地去修改这块内存”的问题。** 它通过红绿灯机制提供可变性，但它有一条铁律：**它自己没有跨线程复制所有权的能力**。

所以，在工业界，如果你想让 Axum 线程和 Notify 线程同时拥有一块能随时修改的文章大仓库，你必须把它们像套娃一样死死套在一起，形成一个完全体类型：

```rust
SharedState=Arc<RwLock<Vec<Post>>>
```

### RwLock
本质是一个并发状态机, 维护一个状态变量, 

读锁(可共享锁), `db.read().await`,  状态机中读计数 + 1

写锁(排他锁), `db.blocking_write()`, 或`write().await`, 会阻止新的读锁, 和等待原来的读锁释放

使用

```rust
let db_clone = Arc::clone(&db);  //这个没什么歧义
let db_clone = db.clone();   //两个意思一样
```