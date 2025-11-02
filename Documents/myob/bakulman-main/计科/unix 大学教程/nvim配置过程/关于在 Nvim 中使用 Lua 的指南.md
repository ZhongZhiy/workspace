---
tags:
  - vim
---
我已经将你提供的关于 Neovim 使用 Lua 的英文文档内容翻译为中文。以下是完整的翻译：

---

# 知识库

## 来自 [File](Pasted_Text_1748774265752.txt) 的内容（翻译成中文）：

```
                            NVIM 参考手册
                          关于在 Nvim 中使用 Lua 的指南
                                       输入 |gO| 查看目录。
==============================================================================
简介                                                         *lua-guide*
本指南将介绍在 Nvim 中使用 Lua 的基础知识。它并不是对所有可用功能的详尽百科全书，也不会详细说明所有复杂细节。你可以把它当作一个“生存工具包”——让你能够舒适地开始在 Nvim 中使用 Lua 所需的基本知识。

需要注意的是，这并不是一份关于 Lua 语言本身的指南。相反，这是关于如何通过 Lua 语言以及我们提供的函数来配置和修改 Nvim 的指南。如果你想了解更多关于 Lua 本身的内容，请参阅 |luaref| 和 |lua-concepts|。

同样，本指南假设你已经熟悉了 Nvim 的一些基础知识（命令、选项、映射、自动命令），这些内容在 |user-manual| 中有详细介绍。
------------------------------------------------------------------------------
关于 API 的一些说明                                            *lua-guide-api*
本指南的目的是介绍通过 Lua 与 Nvim 进行交互的不同方式（即“API”）。这个 API 包含三个不同的层次：
1. 继承自 Vim 的“Vim API”：包括 |Ex-commands| 和 |builtin-functions|，以及 Vimscript 中的 |user-function|。这些可以通过 |vim.cmd()| 和 |vim.fn| 分别访问，相关内容将在下面的 |lua-guide-vimscript| 中讨论。
2. 用 C 编写的“Nvim API”，用于远程插件和 GUI；详见 |api|。这些函数可以通过 |vim.api| 访问。
3. 专门为 Lua 编写和设计的“Lua API”。这些是 `vim.*` 下其他可通过 Lua 访问的函数；详见 |lua-stdlib|。

这一区分非常重要，因为 API 函数继承了其原始层的行为：例如，Nvim API 函数始终需要指定所有参数，即使 Lua 本身允许省略参数（未指定的参数会作为 `nil` 传递）；而 Vim API 函数可以使用 0 基索引，即使 Lua 数组默认使用 1 基索引。

通过这种方式，几乎所有的交互都可以通过 Lua 完成，而无需从头编写全新的 API。因此，除非在功能或性能上有显著优势，否则函数通常不会在不同层级之间重复（例如，你可以直接通过 |nvim_create_autocmd()| 映射 Lua 函数，但不能通过 |:autocmd| 实现）。

如果实现相同功能有多种方法，本指南只会涵盖从 Lua 使用最方便的方法。
==============================================================================
使用 Lua                                                  *lua-guide-using-Lua*
要从 Nvim 命令行运行 Lua 代码，请使用 |:lua| 命令：
>vim
    :lua print("Hello!")
<
注意：每个 |:lua| 命令都有自己的作用域，使用 `local` 关键字声明的变量在该命令之外无法访问。以下示例将不起作用：
>vim
    :lua local foo = 1
    :lua print(foo)
    " 打印 "nil" 而不是 "1"
<
你也可以使用 `:lua=`，它等价于 `:lua vim.print(...)`，可以方便地检查变量或表的值：
>vim
    :lua =package
<
要运行外部文件中的 Lua 脚本，你可以像处理 Vimscript 文件一样使用 |:source| 命令：
>vim
    :source ~/programs/baz/myluafile.lua
<
最后，你可以在 Vimscript 文件中包含 Lua 代码，只需将其放入 |:lua-heredoc| 块中：
>vim
    lua << EOF
      local tbl = {1, 2, 3}
      for k, v in ipairs(tbl) do
        print(v)
      end
    EOF
<
------------------------------------------------------------------------------
启动时使用 Lua 文件                                    *lua-guide-config*
Nvim 支持使用 `init.vim` 或 `init.lua` 作为配置文件，但不能同时使用两者。你应该将它们放在你的 |config| 目录中（运行 `:echo stdpath('config')` 可查看路径）。请注意你也可以在 `init.vim` 中使用 Lua，在 `init.lua` 中使用 Vimscript，这部分内容将在下文介绍。

如果你希望在 |startup| 时自动运行任何其他 Lua 脚本，只需将其放在你的 |'runtimepath'| 中的 `plugin/` 目录下即可。
------------------------------------------------------------------------------
Lua 模块                                                  *lua-guide-modules*
如果你想按需加载 Lua 文件，可以将它们放在你的 |'runtimepath'| 中的 `lua/` 目录下，并使用 `require` 加载。（这相当于 Vimscript 中的 |autoload| 机制。）

假设你有如下目录结构：
>
    ~/.config/nvim
    |-- after/
    |-- ftplugin/
    |-- lua/
    |   |-- myluamodule.lua
    |   |-- other_modules/
    |       |-- anothermodule.lua
    |       |-- init.lua
    |-- plugin/
    |-- syntax/
    |-- init.vim
<
那么以下 Lua 代码将加载 `myluamodule.lua`：
>lua
    require("myluamodule")
<
注意 `.lua` 扩展名被省略了。
类似地，加载 `other_modules/anothermodule.lua` 的方式如下：
>lua
    require('other_modules/anothermodule')
    -- 或者
    require('other_modules.anothermodule')
<
注意，“子模块”只是子目录；`.` 等价于路径分隔符 `/`（即使在 Windows 上也是如此）。
包含 |init.lua| 文件的文件夹可以直接通过 `require` 加载，不需要指定文件名：
>lua
    require('other_modules') -- 加载 other_modules/init.lua
<
要求不存在的模块或包含语法错误的模块会导致当前执行脚本中止。可以使用 `pcall()` 来捕获此类错误。以下示例尝试加载 `module_with_error`，并在成功时调用其函数，否则打印错误信息：
>lua
    local ok, mymod = pcall(require, 'module_with_error')
    if not ok then
      print("模块出错")
    else
      mymod.func()
    end
<
与 |:source| 不同，|require()| 不仅会搜索 |'runtimepath'| 下的所有 `lua/` 目录，还会在首次使用时缓存模块。因此，第二次调用 `require()` 将不会再次执行脚本，而是返回已缓存的文件。要重新运行文件，你需要手动先将其从缓存中删除：
>lua
    package.loaded['myluamodule'] = nil
    require('myluamodule')    -- 再次从磁盘读取并执行模块
<
------------------------------------------------------------------------------
另请参见：
• |lua-module-load|
• |pcall()|
==============================================================================
从 Lua 使用 Vim 命令和函数                  *lua-guide-vimscript*
所有 Vim 命令和函数都可以从 Lua 中访问。
------------------------------------------------------------------------------
Vim 命令                                            *lua-guide-vim-commands*
要从 Lua 运行任意 Vim 命令，将其作为字符串传递给 |vim.cmd()|：
>lua
    vim.cmd("colorscheme habamax")
<
注意特殊字符需要用反斜杠转义：
>lua
    vim.cmd("%s/\\Vfoo/bar/g")
<
另一种方法是使用由双括号 `[[ ]]` 分隔的字面字符串（见 |lua-literal|）：
>lua
    vim.cmd([[%s/\Vfoo/bar/g]])
<
使用字面字符串的另一个好处是它可以跨多行；这允许你将多个命令传递给单个 `vim.cmd()` 调用：
>lua
    vim.cmd([[
      highlight Error guibg=red
      highlight link Warning Error
    ]])
<
这与 |:lua-heredoc| 正好相反，它允许你在 `init.lua` 中包含 Vimscript 代码。

如果你想以编程方式构建 Vim 命令，以下形式可能会很有用（所有这些都等价于上面相应的行）：
>lua
    vim.cmd.colorscheme("habamax")
    vim.cmd.highlight({ "Error", "guibg=red" })
    vim.cmd.highlight({ "link", "Warning", "Error" })
<
------------------------------------------------------------------------------
Vimscript 函数                                    *lua-guide-vim-functions*
使用 |vim.fn| 从 Lua 调用 Vimscript 函数。Lua 和 Vimscript 之间的数据类型会自动转换：
>lua
    print(vim.fn.printf('Hello from %s', 'Lua'))
    local reversed_list = vim.fn.reverse({ 'a', 'b', 'c' })
    vim.print(reversed_list) -- { "c", "b", "a" }
    local function print_stdout(chan_id, data, name)
      print(data[1])
    end
    vim.fn.jobstart('ls', { on_stdout = print_stdout })
<
这适用于 |builtin-functions| 和 |user-function|。
注意哈希符号 (`#`) 在 Lua 中不是有效的标识符字符，因此例如 |autoload| 函数必须使用以下语法调用：
>lua
    vim.fn['my#autoload#function']()
<
------------------------------------------------------------------------------
另请参见：
• |builtin-functions|: 所有 Vimscript 函数的字母列表
• |function-list|:     按主题分组的所有 Vimscript 函数列表
• |:runtime|:          在 |'runtimepath'| 中运行匹配模式的所有 Lua 脚本
• |package.path|:      `require()` 搜索的所有路径列表
==============================================================================
变量                                                  *lua-guide-variables*
变量可以通过以下封装器设置和读取，它们直接对应于其 |variable-scope|：
• |vim.g|:   全局变量 (|g:|)
• |vim.b|:   当前缓冲区的变量 (|b:|)
• |vim.w|:   当前窗口的变量 (|w:|)
• |vim.t|:   当前标签页的变量 (|t:|)
• |vim.v|:   预定义的 Vim 变量 (|v:|)
• |vim.env|: 编辑器会话中定义的环境变量

数据类型会自动转换。例如：
>lua
    vim.g.some_global_variable = {
      key1 = "value",
      key2 = 300
    }
    vim.print(vim.g.some_global_variable)
    --> { key1 = "value", key2 = 300 }
<
你可以通过索引封装器来指定特定的缓冲区（通过编号）、窗口（通过 |window-ID|）或标签页：
>lua
    vim.b[2].myvar = 1               -- 设置缓冲区编号 2 的 myvar
    vim.w[1005].myothervar = true    -- 设置窗口 ID 1005 的 myothervar
<
某些变量名称可能包含不能用于 Lua 标识符的字符。你仍然可以通过使用以下语法操作这些变量：
>lua
    vim.g['my#variable'] = 1
<
注意你不能直接更改数组变量的字段。以下方式无效：
>lua
    vim.g.some_global_variable.key2 = 400
    vim.print(vim.g.some_global_variable)
    --> { key1 = "value", key2 = 300 }
<
相反，你需要创建一个中间的 Lua 表并修改它：
>lua
    local temp_table = vim.g.some_global_variable
    temp_table.key2 = 400
    vim.g.some_global_variable = temp_table
    vim.print(vim.g.some_global_variable)
    --> { key1 = "value", key2 = 400 }
<
要删除变量，只需将其设置为 `nil`：
>lua
    vim.g.myvar = nil
<
------------------------------------------------------------------------------
另请参见：
• |lua-vim-variables|
==============================================================================
选项                                                      *lua-guide-options*
有两种互补的方式通过 Lua 设置 |options|。
------------------------------------------------------------------------------
vim.opt
在 `init.lua` 中设置全局和局部选项的最便捷方式是通过 `vim.opt` 及其相关封装器：
• |vim.opt|:        行为类似于 |:set|
• |vim.opt_global|: 行为类似于 |:setglobal|
• |vim.opt_local|:  行为类似于 |:setlocal|

例如，以下 Vimscript 命令：
>vim
    set smarttab
    set nosmarttab
<
等价于：
>lua
    vim.opt.smarttab = true
    vim.opt.smarttab = false
<
特别是，它们允许通过 Lua 表轻松处理类似列表、映射和集合的选项：代替
>vim
    set wildignore=*.o,*.a,__pycache__
    set listchars=space:_,tab:>~
    set formatoptions=njt
<
你可以使用：
>lua
    vim.opt.wildignore = { '*.o', '*.a', '__pycache__' }
    vim.opt.listchars = { space = '_', tab = '>~' }
    vim.opt.formatoptions = { n = true, j = true, t = true }
<
这些封装器还提供了类似于 Vimscript 中 `:set+=`、`:set^=` 和 `:set-=` 的方法：
>lua
    vim.opt.shortmess:append({ I = true })
    vim.opt.wildignore:prepend('*.o')
    vim.opt.whichwrap:remove({ 'b', 's' })
<
代价是你不能直接访问选项值，而必须使用 |vim.opt:get()|：
>lua
    print(vim.opt.smarttab)
    --> {...} (大表)
    print(vim.opt.smarttab:get())
    --> false
    vim.print(vim.opt.listchars:get())
    --> { space = '_', tab = '>~' }
<
------------------------------------------------------------------------------
vim.o
出于这个原因，存在一种更直接的变量式访问方式，使用 `vim.o` 及其相关封装器，类似于你可以通过 `:echo &number` 和 `:let &listchars='space:_,tab:>~'` 获取和设置选项：
• |vim.o|:  行为类似于 |:set|
• |vim.go|: 行为类似于 |:setglobal|
• |vim.bo|: 用于缓冲区作用域的选项
• |vim.wo|: 用于窗口作用域的选项（可以双重索引）

例如：
>lua
    vim.o.smarttab = false -- :set nosmarttab
    print(vim.o.smarttab)
    --> false
    vim.o.listchars = 'space:_,tab:>~' -- :set listchars='space:_,tab:>~'
    print(vim.o.listchars)
    --> 'space:_,tab:>~'
    vim.o.isfname = vim.o.isfname .. ',@-@' -- :set isfname+=@-@
    print(vim.o.isfname)
    --> '@,48-57,/,.,-,_,+,,,#,$,%,~,=,@-@'
    vim.bo.shiftwidth = 4 -- :setlocal shiftwidth=4
    print(vim.bo.shiftwidth)
    --> 4
<
就像变量一样，你可以分别为缓冲区和窗口选项指定缓冲区编号或 |window-ID|。如果没有提供编号，则使用当前缓冲区或窗口：
>lua
    vim.bo[4].expandtab = true -- 在缓冲区 4 中设置 expandtab 为 true
    vim.wo.number = true       -- 在当前窗口中设置 number 为 true
    vim.wo[0].number = true    -- 同上
    vim.wo[0][0].number = true -- 仅在当前窗口的当前缓冲区中设置 number 为 true
    print(vim.wo[0].number)    --> true
<
------------------------------------------------------------------------------
另请参见：
• |lua-options|
==============================================================================
映射                                                    *lua-guide-mappings*
你可以将 Vim 命令或 Lua 函数映射到按键序列。
------------------------------------------------------------------------------
创建映射                                       *lua-guide-mappings-set*
使用 |vim.keymap.set()| 创建映射。该函数接受三个必需参数：
• {mode} 是一个字符串或字符串表，表示映射生效的模式前缀。前缀是 |:map-modes| 中列出的，或者 `"!"` 对应 |:map!|，空字符串对应 |:map|。
• {lhs} 是一个字符串，表示应触发映射的按键序列。
• {rhs} 是一个包含 Vim 命令的字符串或一个 Lua 函数，当输入 {lhs} 时执行。
  空字符串等效于 |<Nop>|，禁用某个键。

示例：
>lua
    -- Vim 命令的普通模式映射
    vim.keymap.set('n', '<Leader>ex1', '<cmd>echo "Example 1"<cr>')
    -- Vim 命令的普通模式和命令行模式映射
    vim.keymap.set({'n', 'c'}, '<Leader>ex2', '<cmd>echo "Example 2"<cr>')
    -- Lua 函数的普通模式映射
    vim.keymap.set('n', '<Leader>ex3', vim.treesitter.start)
    -- 带参数的 Lua 函数的普通模式映射
    vim.keymap.set('n', '<Leader>ex4', function() print('Example 4') end)
<
你可以通过以下方式映射 Lua 模块中的函数：
>lua
    vim.keymap.set('n', '<Leader>pl1', require('plugin').action)
<
注意，这会在定义映射时加载插件。如果你想延迟加载到映射执行时（如 |autoload| 函数），则将其包裹在 `function() end` 中：
>lua
    vim.keymap.set('n', '<Leader>pl2', function() require('plugin').action() end)
<
第四个可选参数是一个表，包含修改映射行为的键，如那些来自 |:map-arguments| 的键。以下是最有用的选项：
• `buffer`: 如果给出，仅在指定编号的缓冲区中设置映射；`0` 或 `true` 表示当前缓冲区。
>lua
    -- 为当前缓冲区设置映射
    vim.keymap.set('n', '<Leader>pl1', require('plugin').action, { buffer = true })
    -- 为缓冲区编号 4 设置映射
    vim.keymap.set('n', '<Leader>pl1', require('plugin').action, { buffer = 4 })
<
• `silent`: 如果设置为 `true`，则抑制输出如错误消息。
>lua
    vim.keymap.set('n', '<Leader>pl1', require('plugin').action, { silent = true })
<
• `expr`: 如果设置为 `true`，则不执行 {rhs}，而是使用其返回值作为输入。特殊 |keycodes| 会自动转换。例如，以下映射仅在弹出菜单中将 `<down>` 替换为 `<c-n>`：
>lua
    vim.keymap.set('c', '<down>', function()
      if vim.fn.pumvisible() == 1 then return '<c-n>' end
      return '<down>'
    end, { expr = true })
<
• `desc`: 当使用例如 |:map| 列出映射时显示的描述字符串。这对于 Lua 函数作为 {rhs} 时很有用，否则它们只会显示为 `Lua: <number> <source file>:<line>`。因此插件在创建映射时应始终使用此选项。
>lua
    vim.keymap.set('n', '<Leader>pl1', require('plugin').action,
      { desc = 'Execute action from plugin' })
<
• `remap`: 默认情况下，所有映射都是非递归的（即 |vim.keymap.set()| 行为类似于 |:noremap|）。如果 {rhs} 本身是一个应该执行的映射，则设置 `remap = true`：
>lua
    vim.keymap.set('n', '<Leader>ex1', '<cmd>echo "Example 1"<cr>')
    -- 添加较短的映射
    vim.keymap.set('n', 'e', '<Leader>ex1', { remap = true })
<
  注意：即使默认 `remap = false`，|<Plug>| 映射也会始终展开：
>lua
    vim.keymap.set('n', '[%', '<Plug>(MatchitNormalMultiBackward)')
<
------------------------------------------------------------------------------
删除映射                                       *lua-guide-mappings-del*
使用 |vim.keymap.del()| 可以删除特定映射：
>lua
    vim.keymap.del('n', '<Leader>ex1')
    vim.keymap.del({'n', 'c'}, '<Leader>ex2', {buffer = true})
<
------------------------------------------------------------------------------
另请参见：
• `vim.api.`|nvim_get_keymap()|:     返回所有全局映射
• `vim.api.`|nvim_buf_get_keymap()|: 返回缓冲区的所有映射
==============================================================================
自动命令                                            *lua-guide-autocommands*
|autocommand| 是一个 Vim 命令或 Lua 函数，每当一个或多个 |events| 被触发时自动执行，例如当文件被读取或写入时，或者当窗口被创建时。这些可以通过 Nvim API 从 Lua 访问。
------------------------------------------------------------------------------
创建自动命令                             *lua-guide-autocommand-create*
使用 `vim.api.`|nvim_create_autocmd()| 创建自动命令。该函数有两个必需参数：
• {event}: 一个字符串或字符串表，包含应触发命令或函数的事件。
• {opts}:  一个表，包含控制事件触发时应发生情况的键。

最重要的选项是：
• `pattern`:  一个字符串或字符串表，包含 |autocmd-pattern|。
            注意：像 `$HOME` 和 `~` 这样的环境变量不会自动扩展；你需要显式使用 `vim.fn.`|expand()|。
• `command`:  一个包含 Vim 命令的字符串。
• `callback`: 一个 Lua 函数。

你必须且只能指定 `command` 和 `callback` 中的一个。如果省略 `pattern`，则默认为 `pattern = '*'`。

示例：
>lua
    vim.api.nvim_create_autocmd({"BufEnter", "BufWinEnter"}, {
      pattern = {"*.c", "*.h"},
      command = "echo 'Entering a C or C++ file'",
    })
    -- 使用 Lua 函数编写的相同自动命令
    vim.api.nvim_create_autocmd({"BufEnter", "BufWinEnter"}, {
      pattern = {"*.c", "*.h"},
      callback = function() print("Entering a C or C++ file") end,
    })
    -- 用户事件 MyPlugin 触发
    vim.api.nvim_create_autocmd("User", {
      pattern = "MyPlugin",
      callback = function() print("My Plugin Works!") end,
    })
<
Nvim 总是会使用一个包含有关触发自动命令信息的表来调用 Lua 函数。最有用的键包括：
• `match`: 匹配 `pattern` 的字符串（见 |<amatch>|）
• `buf`:   触发事件的缓冲区编号（见 |<abuf>|）
• `file`:  触发事件的缓冲区文件名（见 |<afile>|）
• `data`:  一个表，包含某些事件传递的其他相关数据

例如，这允许你为某些文件类型设置缓冲区局部映射：
>lua
    vim.api.nvim_create_autocmd("FileType", {
      pattern = "lua",
      callback = function(args)
        vim.keymap.set('n', 'K', vim.lsp.buf.hover, { buffer = args.buf })
      end
    })
<
这意味着如果你的回调本身需要一个（甚至可选的）参数，你必须将其包裹在 `function() end` 中以避免错误：
>lua
    vim.api.nvim_create_autocmd('TextYankPost', {
      callback = function() vim.hl.on_yank() end
    })
<
（由于在 Lua 函数定义中可以省略未使用的参数，这等价于 `function(args) ... end`。）

除了使用模式外，你还可以使用 `buffer` 创建缓冲区局部自动命令（见 |autocmd-buflocal|）；在这种情况下，不能使用 `pattern`：
>lua
    -- 为当前缓冲区设置自动命令
    vim.api.nvim_create_autocmd("CursorHold", {
      buffer = 0,
      callback = function() print("hold") end,
    })
    -- 为缓冲区编号 33 设置自动命令
    vim.api.nvim_create_autocmd("CursorHold", {
      buffer = 33,
      callback = function() print("hold") end,
    })
<
类似于映射，你可以（也应该）使用 `desc` 添加描述：
>lua
    vim.api.nvim_create_autocmd('TextYankPost', {
      callback = function() vim.hl.on_yank() end,
      desc = "Briefly highlight yanked text"
    })
<
最后，你可以使用 `group` 键对自动命令进行分组；下一节将详细介绍这一点。
------------------------------------------------------------------------------
对自动命令进行分组                             *lua-guide-autocommands-group*
自动命令组可用于将相关的自动命令组织在一起；见 |autocmd-groups|。这对于组织自动命令尤其有用，特别是防止自动命令多次设置。

组可以通过 `vim.api.`|nvim_create_augroup()| 创建。该函数有两个必需参数：一个包含组名的字符串和一个决定是否清除现有组（即删除所有分组的自动命令）的表。该函数返回一个数字，即组的内部标识符。组可以通过此标识符或名称指定（但前提是组已被创建）。

例如，常见的 Vimscript 模式是在可能重新加载的文件中定义自动命令：
>vim
    augroup vimrc
      " 删除所有 vimrc 自动命令
      autocmd!
      au BufNewFile,BufRead *.html set shiftwidth=4
      au BufNewFile,BufRead *.html set expandtab
    augroup END
<
这等价于以下 Lua 代码：
>lua
    local mygroup = vim.api.nvim_create_augroup('vimrc', { clear = true })
    vim.api.nvim_create_autocmd({ 'BufNewFile', 'BufRead' }, {
      pattern = '*.html',
      group = mygroup,
      command = 'set shiftwidth=4',
    })
    vim.api.nvim_create_autocmd({ 'BufNewFile', 'BufRead' }, {
      pattern = '*.html',
      group = 'vimrc',  -- 等价于 group=mygroup
      command = 'set expandtab',
    })
<
对于给定的名称，自动命令组是唯一的，因此你可以在其他文件中重用它们：
>lua
    local mygroup = vim.api.nvim_create_augroup('vimrc', { clear = false })
    vim.api.nvim_create_autocmd({ 'BufNewFile', 'BufRead' }, {
      pattern = '*.c',
      group = mygroup,
      command = 'set noexpandtab',
    })
<
------------------------------------------------------------------------------
删除自动命令                            *lua-guide-autocommands-delete*
你可以使用 `vim.api.`|nvim_clear_autocmds()| 删除自动命令。该函数接受一个必填参数，即描述要删除的自动命令的键表：
>lua
    -- 删除所有 BufEnter 和 InsertLeave 自动命令
    vim.api.nvim_clear_autocmds({event = {"BufEnter", "InsertLeave"}})
    -- 删除所有使用 "*.py" 模式的自动命令
    vim.api.nvim_clear_autocmds({pattern = "*.py"})
    -- 删除组 "scala" 中的所有自动命令
    vim.api.nvim_clear_autocmds({group = "scala"})
    -- 删除当前缓冲区中的所有 ColorScheme 自动命令
    vim.api.nvim_clear_autocmds({event = "ColorScheme", buffer = 0 })
<
注意：只有在指定了 `group` 键的情况下才会删除组中的自动命令，即使其他选项匹配也是如此。
------------------------------------------------------------------------------
另请参见
• |nvim_get_autocmds()|:  返回所有匹配的自动命令
• |nvim_exec_autocmds()|: 执行所有匹配的自动命令
==============================================================================
用户命令                                           *lua-guide-commands*
|user-commands| 是自定义的 Vim 命令，调用 Vimscript 或 Lua 函数。与内置命令一样，它们可以有参数、作用于范围，或具有参数的自定义补全。由于这些主要对插件有用，我们将仅介绍这一高级主题的基础知识。
------------------------------------------------------------------------------
创建用户命令                           *lua-guide-commands-create*
用户命令可以通过 |nvim_create_user_command()| 创建。该函数接受三个必填参数：
• 一个字符串，表示命令的名称（必须以大写字母开头，以区别于内置命令）；
• 一个包含 Vim 命令的字符串或在调用命令时执行的 Lua 函数；
• 一个包含 |command-attributes| 的表；此外，它还可以包含键 `desc`（描述命令的字符串）、`force`（设置为 `false` 以避免替换已存在的同名命令）和 `preview`（用于 |:command-preview| 的 Lua 函数）。

示例：
>lua
    vim.api.nvim_create_user_command('Test', 'echo "It works!"', {})
    vim.cmd.Test()
    --> It works!
<
（注意第三个参数是必需的，即使没有属性。）

Lua 函数被调用时传入一个包含参数和修饰符的单一表参数。最重要的是：
• `name`: 命令名称的字符串
• `fargs`: 包含命令参数（按空格分割）的表（见 |<f-args>|）
• `bang`: 如果命令带有 `!` 修饰符执行，则为 `true`（见 |<bang>|）
• `line1`: 命令范围的起始行号（见 |<line1>|）
• `line2`: 命令范围的最终行号（见 |<line2>|）
• `range`: 命令范围中的项目数：0、1 或 2（见 |<range>|）
• `count`: 提供的任何计数（见 |<count>|）
• `smods`: 包含命令修饰符的表（见 |<mods>|）

例如：
>lua
    vim.api.nvim_create_user_command('Upper',
      function(opts)
        print(string.upper(opts.fargs[1]))
      end,
      { nargs = 1 })
    vim.cmd.Upper('foo')
    --> FOO
<
`complete` 属性除了 |:command-complete| 中列出的属性外，还可以接受一个 Lua 函数：
>lua
    vim.api.nvim_create_user_command('Upper',
      function(opts)
        print(string.upper(opts.fargs[1]))
      end,
      { nargs = 1,
        complete = function(ArgLead, CmdLine, CursorPos)
          -- 返回补全候选作为类列表表
          return { "foo", "bar", "baz" }
        end,
    })
<
使用 `vim.api.`|nvim_buf_create_user_command()| 创建缓冲区局部用户命令。这里第一个参数是缓冲区编号（`0` 表示当前缓冲区）；其余参数与 |nvim_create_user_command()| 相同：
>lua
    vim.api.nvim_buf_create_user_command(0, 'Upper',
      function(opts)
        print(string.upper(opts.fargs[1]))
      end,
      { nargs = 1 })
<
------------------------------------------------------------------------------
删除用户命令                           *lua-guide-commands-delete*
用户命令可以使用 `vim.api.`|nvim_del_user_command()| 删除。唯一参数是命令名称：
>lua
    vim.api.nvim_del_user_command('Upper')
<
要删除缓冲区局部用户命令，请使用 `vim.api.`|nvim_buf_del_user_command()|。这里第一个参数是缓冲区编号（`0` 表示当前缓冲区），第二个是命令名称：
>lua
    vim.api.nvim_buf_del_user_command(4, 'Upper')
<
==============================================================================
致谢                                                      *lua-guide-credits*
本指南很大程度上借鉴了 nanotee 的 Lua 指南：
https://github.com/nanotee/nvim-lua-guide
感谢 @nanotee！
vim:tw=78:ts=8:sw=4:sts=4:et:ft=help:norl:
```

如果你有任何问题或需要进一步帮助，请告诉我！