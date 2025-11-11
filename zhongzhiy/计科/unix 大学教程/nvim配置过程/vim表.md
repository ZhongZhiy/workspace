---
tags:
  - vim
---
在 Neovim 的 Lua 配置和脚本中，`vim` 这个全局表 (table) 是你与 Neovim 编辑器核心功能交互的主要入口点。它包含了大量的子模块、函数和变量，允许你控制编辑器的几乎所有方面。

可以把 `vim` 表想象成一个巨大的命名空间，里面分门别类地放着各种工具和设置。以下是 `vim` 表中一些最重要和常用的部分：

1.  **选项 (Options)**:
    *   `vim.opt`: 用于设置和获取 Neovim 的选项 (options)。这是推荐的方式，它通常能正确处理全局选项和局部选项 (global-local options)。
        *   示例: `vim.opt.number = true` (显示行号)
        *   示例: `vim.opt.tabstop = 4` (设置 Tab 宽度)
    *   `vim.o`: 另一个访问选项的方式，主要用于全局选项。
        *   示例: `vim.o.hlsearch = true` (高亮搜索结果)
    *   `vim.go`: 仅访问选项的全局值。
    *   `vim.bo`: 访问缓冲区局部 (buffer-local) 选项。
        *   示例: `vim.bo[buffer_nr].tabstop = 2` (为特定缓冲区设置 Tab 宽度)
    *   `vim.wo`: 访问窗口局部 (window-local) 选项。

2.  **变量 (Variables)**:
    *   `vim.g`: 访问全局变量 (global variables)。
        *   示例: `vim.g.my_plugin_enabled = 1`
    *   `vim.b`: 访问缓冲区局部变量 (buffer-local variables)。
        *   示例: `vim.b[buffer_nr].is_dirty = true`
    *   `vim.w`: 访问窗口局部变量 (window-local variables).
    *   `vim.t`: 访问标签页局部变量 (tabpage-local variables).
    *   `vim.v`: 访问 Vim 内部变量 (internal Vim variables)，如 `v:count`, `v:errmsg` 等。
        *   示例: `print(vim.v.version)` (打印 Vim 版本号)

3.  **函数 (Functions)**:
    *   `vim.fn`: 调用 Vimscript 内建函数和用户自定义的 Vimscript 函数。
        *   示例: `local current_line = vim.fn.getline('.')` (获取当前行内容)
        *   示例: `local file_path = vim.fn.expand('%:p')` (获取当前文件的完整路径)
    *   Neovim 还提供了很多直接的 Lua API 函数，通常在 `vim.api` 中，或者直接在 `vim` 下面 (如 `vim.cmd`, `vim.inspect`)。

4.  **命令 (Commands)**:
    *   `vim.cmd(command_string)`: 执行 Vim 的 Ex 命令 (命令行模式下的命令)。
        *   示例: `vim.cmd('colorscheme tokyonight')` (设置颜色主题)
        *   示例: `vim.cmd('edit newfile.txt')` (编辑新文件)

5.  **Neovim API (`vim.api`)**:
    *   这是 Neovim 提供的一套强大、稳定且结构化的接口，用于与编辑器核心进行交互。这些 API 函数通常以 `nvim_` 开头 (例如 `nvim_get_current_line`, `nvim_set_keymap`)。
    *   在 Lua 中，你可以通过 `vim.api.<function_name_without_nvim_prefix>()` 来调用它们。
        *   示例: `local line = vim.api.nvim_get_current_line()`
        *   示例: `vim.api.nvim_set_keymap('n', '<leader>w', ':w<CR>', { noremap = true, silent = true })`
    *   `vim.api` 是编写复杂插件和进行深度定制的核心。

6.  **按键映射 (Key Mapping)**:
    *   `vim.keymap.set(mode, lhs, rhs, opts)`: 设置按键映射 (推荐的现代方式)。
        *   示例: `vim.keymap.set('n', '<Space>f', '<cmd>Telescope find_files<CR>', { desc = "Find files" })`

7.  **LSP (Language Server Protocol)**:
    *   `vim.lsp`: 包含与 LSP 客户端交互的函数和模块，用于代码补全、诊断、跳转等。
        *   示例: `vim.lsp.buf_attach_client()`
        *   示例: `vim.lsp.codelens.run()`

8.  **高亮 (Highlighting)**:
    *   `vim.highlight`: 包含与高亮组相关的工具。
    *   创建和修改高亮通常通过 `vim.api.nvim_set_hl()`。
        *   示例: `vim.api.nvim_set_hl(0, 'MyCustomError', { fg = 'Red', bold = true })`

9.  **自动命令 (Autocommands)**:
    *   `vim.autocmd`: 包含与自动命令相关的工具。
    *   创建自动命令组和自动命令通常通过 `vim.api.nvim_create_augroup()` 和 `vim.api.nvim_create_autocmd()`。
        *   示例: `local my_group = vim.api.nvim_create_augroup("MyPluginEvents", { clear = true })`
        *   示例: `vim.api.nvim_create_autocmd("BufWritePre", { pattern = "*.js", command = "lua print('Saving JavaScript file')", group = my_group })`

10. **其他实用工具**:
    *   `vim.inspect(object)`: 将 Lua 对象转换为可读的字符串表示，非常适合调试。
        *   示例: `print(vim.inspect({ a = 1, b = { c = "hello" } }))`
    *   `vim.loop`: 访问 LibUV 事件循环，用于异步操作。
    *   `vim.fs`: 文件系统相关的实用函数。
    *   `vim.ui`: 用于覆盖 Neovim 的标准 UI 元素，如 `vim.ui.select` (选择列表) 和 `vim.ui.input` (用户输入)。
    *   `vim.diagnostic`: 用于处理和显示代码诊断信息 (错误、警告等)。
    *   `vim.notify(message, level, opts)`: 显示通知。
    *   `vim.version()`: 返回一个包含版本信息的表。
    *   `vim.env`: 访问环境变量。

**如何探索 `vim` 表？**

1.  **使用 `:help`**:
    *   `:help lua-stdlib` (查看 Neovim 为 Lua 提供的标准库扩展)
    *   `:help api` (查看完整的 `vim.api` 文档)
    *   `:help vim.opt` (查看选项相关的帮助)
2.  **使用 `vim.inspect`**:
    你可以在你的 `init.lua` 或通过 `:lua` 命令来打印 `vim` 表的部分内容进行探索，例如：
    ```lua
    :lua print(vim.inspect(vim.opt))
    :lua print(vim.inspect(vim.lsp))
    ```
    (注意：直接 `print(vim.inspect(vim))` 可能会输出非常非常多的内容，因为它太庞大了。)

总而言之，`vim` 表是你在 Neovim 中使用 Lua 进行编程的基石。通过它，你可以获取信息、修改设置、执行命令、调用函数，并与编辑器的各个子系统进行交互。