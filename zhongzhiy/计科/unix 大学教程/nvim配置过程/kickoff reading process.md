---
tags:
  - vim
---
`<space>sh`to search help
`:help`to get help
`:checkhealth`get errors info

[[help mapleader]]
[[help vim.o]]
[[剪切板同步设置]]
[[断行显示]]
[[显示空白符]]
[[诊断信息快捷键leader + q]]
`vim.keymap.set('t', '<Esc><Esc>', '<C-\\><C-n>', { desc = 'Exit terminal mode' })
`退出内置terminal
跳转终端
```lua
-- Keybinds to make split navigation easier.
--  Use CTRL+<hjkl> to switch between windows
--
--  See `:help wincmd` for a list of all window commands
vim.keymap.set('n', '<C-h>', '<C-w><C-h>', { desc = 'Move focus to the left window' })
vim.keymap.set('n', '<C-l>', '<C-w><C-l>', { desc = 'Move focus to the right window' })
vim.keymap.set('n', '<C-j>', '<C-w><C-j>', { desc = 'Move focus to the lower window' })
vim.keymap.set('n', '<C-k>', '<C-w><C-k>', { desc = 'Move focus to the upper window' })

-```

[[使用插件包管理工具配置插件]]
[[可以选择插件加载的时间]]
[[插件which-key]]
[[插件的依赖项配置]]
[[使用telescope查找命令]]

在kickoff配置`init.lua`中有配置telescope插件的详细教程
使用`leadership`可以搜索文件，命令，帮助，打开文件(/)

[[LSP的键盘映射]]
光标停留高亮，感觉挺有用的在文档598行

格式化代码的插件，在init749行，使用`space + f`触发，禁用了对c/c++

使用[[默认键位的补全]]
很强的一系列插件https://github.com/echasnovski/mini.nvim
语法高亮：用 `nvim-treesitter` 插件为 Neovim 提供基于 Tree-sitter 的语法高亮和智能缩进功能。它会自动安装所需的语言解析器，并对某些特殊语言（如 Ruby）使用 Vim 原生高亮作为补充。你还可以进一步探索其他模块来提升编码效率，例如文本对象、上下文展示等。

## vidiu
1. 可以在命令模式下直接使用命令修改配置`lua vim.o.number=false`
2. 
