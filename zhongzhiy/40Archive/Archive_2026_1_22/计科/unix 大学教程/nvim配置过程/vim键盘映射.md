---
tags:
  - vim
---
你贴的这个表格，是 **Neovim 中各类 `map`（键位映射）命令的适用模式一览表**，用于说明每种 `map` 命令在哪些模式下生效，是 Neovim/Vim 非常经典的参考资料，很多教程和 `:h map-overview` 都会提到。

---

j### 🔍 解读这张表

| `map` 命令  | Normal | Insert | Command | Visual | Select | Operator | Terminal | Lang |
| --------- | ------ | ------ | ------- | ------ | ------ | -------- | -------- | ---- |
| `map`     | ✔️     | ❌      | ❌       | ✔️     | ✔️     | ✔️       | ❌        | ❌    |
| `nmap`    | ✔️     | ❌      | ❌       | ❌      | ❌      | ❌        | ❌        | ❌    |
| `imap`    | ❌      | ✔️     | ❌       | ❌      | ❌      | ❌        | ❌        | ❌    |
| `cmapj j` | ❌      | ❌      | ✔️      | ❌      | ❌      | ❌        | ❌        | ❌    |
| `vmapj j` | ❌      | ❌      | ❌       | ✔️     | ✔️     | ❌        | ❌        | ❌    |
| `xmapj`   | ❌      | ❌      | ❌       | ✔️     | ❌      | ❌        | ❌        | ❌    |
| `smapj j` | ❌      | ❌      | ❌       | ❌      | ✔️     | ❌        | ❌        | ❌    |
| `omap`    | ❌      | ❌      | ❌       | ❌      | ❌      | ✔️       | ❌        | ❌    |
| `tmap`    | ❌      | ❌      | ❌       | ❌      | ❌      | ❌        | ✔️       | ❌    |
| `lmap`    | ❌      | ✔️     | ✔️      | ❌      | ❌      | ❌        | ❌        | ✔️   |

---

### 🌟 常见模式解释

| 模式名              | 缩写  | 说明                       |
| ---------------- | --- | ------------------------ |
| Normal mode      | `n` | 普通模式（平时移动光标、执行命令的模式）     |
| Insert mode      | `i` | 插入模式（打字的模式）              |
| Visual mode      | `v` | 可视模式（选中字符）               |
| Visual Block     | `x` | 可视块模式（选中块区域）             |
| Command mode     | `c` | 命令行模式（输入 `:` 后）          |
| Terminal mode    | `t` | 内置终端里的模式                 |
| Operator-pending | `o` | 运算符待定模式（比如 `d` 后等你按移动键）  |
| Select mode      | `s` | 类似 Visual，但多用于菜单、GUI 编辑器 |
j j
---
#### map多模式
默认包括 Normal、Visual、Select、Operator-pending 模式

| 命令         | 模式范围                | 是否递归  | 说明       |
| ---------- | ------------------- | ----- | -------- |
| `map`      | 多模式（n, v, o, s）     | ✅ 是递归 | 遍历解析别的映射 |
| `nmap`     | Normal 模式           | ✅ 是递归 |          |
| `vmap`     | Visual 模式           | ✅ 是递归 |          |
| `xmap`     | Visual Block 模式     | ✅ 是递归 |          |
| `smap`     | Select 模式           | ✅ 是递归 |          |
| `omap`     | Operator-pending 模式 | ✅ 是递归 |          |
| `tmap`     | Terminal 模式         | ✅ 是递归 |          |
| `noremap`  | 多模式                 | ❌ 非递归 | 推荐使用，安全  |
| `nnoremap` | Normal 模式           | ❌ 非递归 | 推荐使用     |