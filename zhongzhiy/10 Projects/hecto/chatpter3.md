使用`clippy`让代码看起来符合rust习惯, 命令:
`cargo clippy -- -W clippy::all -W clippy::pedantic -W clippy::nursery -W clippy::cargo -W clippy::restihriction`
还可以添加`#![warn(clippy::all, clippy::pedantic)]`来激活警告


有一些神奇的转移序列[Digital VT100 User Guide: Programmer Information](http://vt100.net/docs/vt100-ug/chapter3.html)

关于crossterm
raw模式就是关闭了回显(echo), 回车处理, 特殊键处理, 换行(`\n`只换行, 需要`\r\n`才会换行回车)

[代码异味 - 维基百科，自由的百科全书](https://zh.wikipedia.org/zh-cn/%E4%BB%A3%E7%A0%81%E5%BC%82%E5%91%B3)

- 一个类型的方法是分散在不同的 Trait 里的。如果你发现一个方法明明有却调不动，往往是因为没 `use` 对应的 Trait。
    
- **泛型的威力**：Rust 的核心逻辑是“寻找共性”。`Stdout`、`File`、`TcpStream` 都有 `flush()`，因为它们都实现了 `Write`。

在release下会让一些错误继续进行, 而debug模式会严格报错, 比如整数溢出

可以使用saturate进行饱和计算, 而不是溢出

使用`///`文档注释可以让开发者看到提示

显式得禁用一些clippy的安全提示

实现文档`cargo doc --open`