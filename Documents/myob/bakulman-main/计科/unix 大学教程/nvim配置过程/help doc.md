---
tags:
  - vim
---
以下是上传文件内容的中文翻译：

---

# Neovim 帮助文档

## 欢迎使用 Neovim 帮助系统！

### 如何导航：
- 使用光标键或以下按键移动：
  - `h` 向左
  - `j` 向下
  - `k` 向上
  - `l` 向右

### 关闭帮助窗口：
- 输入 `:q<Enter>` 即可关闭当前帮助窗口。

### 退出 Neovim：
- 输入 `:qa!<Enter>` 可以退出所有窗口（注意：这会丢失所有未保存的更改）。

### 跳转到特定主题：
- 将光标放在一个标签上（例如 `|bars|`），然后按下 **CTRL-]**。
- 或者用鼠标双击某个标签，例如 `|bars|`。
- 返回上一页：按 **CTRL-O**，重复按下可以继续回退。

### 获取特定帮助：
你可以通过给 `:help` 命令添加参数直接跳转到某个特定的帮助主题。你还可以在前面加上上下文前缀来指定帮助的主题类型：

| 主题类型         | 前缀     | 示例                     |
|------------------|----------|--------------------------|
| 正常模式命令      | (无)     | `:help x`                |
| 可视模式命令      | `v_`     | `:help v_u`              |
| 插入模式命令      | `i_`     | `:help i_<Esc>`           |
| 命令行模式命令    | `:`      | `:help :quit`             |
| 命令行编辑        | `c_`     | `:help c_<Del>`           |
| Vim 命令参数      | `-`      | `:help -r`               |
| 选项              | `'`      | `:help 'textwidth'`       |
| 正则表达式        | `/`      | `:help /[`                |

更多信息请参见：
- `|help-summary|`：更多上下文说明和帮助总结
- `|notation|`：帮助语法解释

### 搜索帮助内容：
- 输入 `:help word` 然后按 **CTRL-D** 可查看与 "word" 相关的帮助条目。
- 或者使用 `:helpgrep word` 来搜索关键词。

### 开始学习 Neovim：
- 如果你是新手，建议尝试 **Vim 教程**，这是一个30分钟的交互式课程，适合学习基本命令，请参考 `|vimtutor|`。
- 或阅读用户手册：`|usr_01.txt|`

Neovim 是从 Vi 编辑器改进而来的，由 Bram Moolenaar 和众多贡献者共同开发。感谢所有为此项目做出贡献的人！

---

## Neovim 文档目录

### 关于 Neovim
- `|news|`：新版本更新日志
- `|nvim|`：从 Vim 过渡到 Neovim
- `|vim-differences|`：Neovim 与 Vim 的区别
- `|faq|`：常见问题解答
- `|user-manual|`：用户手册（教你如何完成各种编辑任务）
- `|quickref|`：常用命令概览
- `|tutor|`：30 分钟交互式入门教程
- `|copying|`：版权信息
- `|iccf|`：支持乌干达贫困儿童的公益信息
- `|sponsor|`：赞助 Neovim 开发
- `|www|`：Neovim 在互联网上的资源
- `|bugs|`：错误报告提交方式
- `|support|`：支持的平台列表

### 基础编辑
- `|intro|`：Neovim 入门介绍及帮助文档中的符号说明
- `|helphelp|`：如何使用帮助文档
- `|index|`：所有命令索引
- `|tips|`：使用 Neovim 的一些技巧
- `|message.txt|`：错误信息及其解释
- `|uganda.txt|`：Neovim 发行版相关信息

### 高级功能
- `|cmdline|`：命令行编辑
- `|options|`：所有选项的详细描述
- `|pattern-searches|`：正则表达式和搜索命令
- `|key-mapping|`：按键映射（快捷键）、缩写
- `|tags|`：标签和特殊搜索
- `|windows|`：窗口和缓冲区操作
- `|tabpage|`：标签页命令
- `|spell|`：拼写检查
- `|diff|`：文件比较
- `|folding|`：折叠文本块
- `|terminal|`：内嵌终端模拟器

### API（扩展/脚本/插件开发）
- `|api|`：通过 RPC、Lua 和 Vimscript 访问 Neovim API
- `|ui|`：Neovim UI 协议
- `|lua-guide|`：Neovim Lua 使用指南
- `|lua|`：Lua API
- `|luaref|`：Lua 参考手册
- `|luvref|`：Luv（`vim.uv`）参考手册
- `|autocmd|`：事件处理程序
- `|job-control|`：启动并控制多个进程
- `|channel|`：Neovim 异步 I/O
- `|vimscript|`：Vimscript 参考
- `|vimscript-functions|`：Vimscript 函数
- `|testing.txt|`：Vimscript 测试函数
- `|remote-plugin|`：Neovim 远程插件
- `|health|`：健康检查

### 编程语言支持
- `|lsp|`：语言服务器协议（LSP）
- `|diagnostic-api|`：诊断框架
- `|treesitter|`：增量语法解析
- `|indent.txt|`：C 语言及其他语言的自动缩进
- `|syntax|`：语法高亮
- `|filetype|`：针对特定文件类型的设置
- `|quickfix|`：快速编辑-编译-修复循环命令
- `|ft_ada.txt|`：Ada 文件类型插件
- `|ft_hare.txt|`：Hare 文件类型插件
- `|ft_ps1.txt|`：PowerShell 文件类型插件
- `|ft_raku.txt|`：Raku 文件类型插件
- `|ft_rust.txt|`：Rust 文件类型插件
- `|ft_sql.txt|`：SQL 文件类型插件

### 用户界面（UI）
- `|tui|`：内置终端用户界面
- `|gui|`：外部图形用户界面
- `|signs|`：作为窗口装饰显示的标记（即“侧边栏”）

### 多语言支持
- `|digraph|`：可用的双字符输入列表
- `|mbyte.txt|`：多字节文本支持
- `|mlang.txt|`：非英语语言支持
- `|rileft.txt|`：从右向左的编辑模式
- `|arabic.txt|`：阿拉伯语支持和编辑
- `|hebrew.txt|`：希伯来语支持和编辑
- `|russian.txt|`：俄语支持和编辑
- `|vietnamese.txt|`：越南语支持和编辑

### 互操作性（Interop）
- `|provider|`：内置远程插件主机
- `|if_perl|`：Perl 接口
- `|if_pyth|`：Python 接口
- `|if_ruby|`：Ruby 接口

### 版本相关
- `|deprecated|`：即将被移除的废弃特性
- `|vi-differences|`：Vim 与 Vi 的区别

### 开发 Neovim
- `|dev|`：Neovim 的开发
- `|dev-arch|`：内部架构、模块和数据结构
- `|dev-style|`：开发风格指南
- `|dev-theme|`：设计指南（配色方案等）
- `|dev-tools|`：开发 Neovim 的工具和技术
- `|dev-vimpatch|`：合并来自 Vim 的补丁

### 标准插件列表
- `|pi_gzip.txt|`：读取和写入压缩文件
- `|pi_msgpack.txt|`：Msgpack 工具
- `|pi_paren.txt|`：高亮匹配括号
- `|pi_spec.txt|`：用于 RPM spec 文件的工作插件
- `|pi_tar.txt|`：Tar 文件浏览器
- `|pi_zip.txt|`：Zip 归档浏览器
- `|netrw|`：网络文件读写

### 本地新增插件
- `|lazy.nvim.txt|`：Neovim 的现代插件管理器
- `|which-key.nvim.txt|`：Neovim 快捷键提示插件
- `|plenary-test|`
- `|todo-comments.nvim.txt|`：Neovim 中的 TODO 注释追踪
- `|guess_indent.txt|`：自动检测缩进风格
- `|mini.ai|`：扩展和创建 a/i 文本对象
- `|mini.align|`：交互式对齐文本
- `|mini.animate|`：动画化常见的 Neovim 动作
- `|mini.base16|`：Base16 配色方案生成
- `|mini.basics|`：常见配置预设
- `|mini.bracketed|`：使用方括号向前/向后跳转
- `|mini.bufremove|`：删除缓冲区
- `|mini.clue|`：显示下一个按键提示
- `|mini.colors|`：调整和保存任意配色方案
- `|mini.comment|`：注释代码行
- `|mini.completion|`：补全和签名帮助
- `|mini.cursorword|`：自动高亮光标下的单词
- `|mini.deps|`：插件管理器
- `|mini.diff|`：处理 diff 块
- `|mini.doc|`：生成 Neovim 帮助文件
- `|mini.extra|`：Mini.nvim 的额外功能
- `|mini.files|`：浏览和操作文件系统
- `|mini.fuzzy|`：模糊匹配
- `|mini.git|`：Git 集成
- `|mini.hipatterns|`：高亮文本中的模式
- `|mini.hues|`：生成可配置的配色方案
- `|mini.icons|`：图标提供者
- `|mini.indentscope|`：可视化缩进范围
- `|mini.jump|`：跳转到下一个/上一个单个字符
- `|mini.jump2d|`：在可见行之间跳转
- `|mini.keymap|`：特殊按键映射
- `|mini.map|`：缓冲区文本概览窗口
- `|mini.misc|`：杂项函数
- `|mini.notify|`：显示通知
- `|mini.operators|`：文本编辑操作符
- `|mini.pairs|`：自动括号配对
- `|mini.pick|`：任意选择器
- `|mini.sessions|`：会话管理
- `|mini.snippets|`：管理并展开代码片段
- `|mini.splitjoin|`：拆分和合并参数
- `|mini.starter|`：启动屏幕
- `|mini.statusline|`：状态栏
- `|mini.surround|`：环绕操作
- `|mini.tabline|`：标签栏
- `|mini.test|`：测试 Neovim 插件
- `|mini.trailspace|`：高亮并移除尾随空格
- `|mini.visits|`：跟踪并重用文件系统访问记录
- `|mini.nvim|`：最小、独立且快速的 Lua 模块集合
- `|lazydev.nvim.txt|`
- `|luasnip.txt|`
- `|blink-cmp.txt|`
- `|fidget-api.txt|`
- `|fidget-option.txt|`
- `|fidget.txt|`：用于 Neovim 通知和 LSP 进度消息的可扩展 UI
- `|mason-lspconfig.nvim|`
- `|mason.nvim|`
- `|lspconfig-all|`
- `|lspconfig.txt|`
- `|nvim-treesitter|`
- `|gitsigns.txt|`
- `|tokyonight.nvim.txt|`
- `|netrw.txt|`
- `|matchit.txt|`

---

### 示例帮助：Bars
现在你已经通过 **CTRL-]** 或双击鼠标跳转到了这里，可以使用以下方式返回：
- **CTRL-T**
- **CTRL-O**
- **g<RightMouse>**
- **<C-RightMouse>**

请注意，标签是用 `|` 包裹的，但在启用高亮的情况下，这些 `|` 字符会被隐藏，这样更便于阅读命令。

你可以在任意词上使用 **CTRL-]**，即使这个词没有包裹在 `|` 中，Neovim 也会尝试查找它的帮助信息。特别是对于单引号中的选项，例如 `'hlsearch'`。

--- 

如果你需要某一部分的详细翻译或有具体问题，请告诉我！