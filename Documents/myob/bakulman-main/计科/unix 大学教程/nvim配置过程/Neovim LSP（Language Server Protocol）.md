---
tags:
  - vim
---
以下是 Neovim LSP（Language Server Protocol）文档的完整中文翻译：

---

# Neovim 用户文档

> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [neovim.io](https://neovim.io/doc/user/lsp.html)

Neovim 支持语言服务器协议 (LSP)，这意味着它作为客户端与 LSP 服务器通信，并包含一个 Lua 框架 `vim.lsp` 来构建增强的 LSP 工具。

LSP 支持诸如跳转到定义、查找引用、悬停提示、补全、重命名、格式化、重构等功能，这些功能基于语义化的项目整体分析（不同于 [ctags](https://neovim.io/doc/user/tagsrch.html#ctags)）。

Neovim 提供了一个 LSP 客户端，但服务器是由第三方提供的。按照以下步骤获取 LSP 功能：

1. 使用 [vim.lsp.config()](https://neovim.io/doc/user/lsp.html#vim.lsp.config()) 为 LSP 客户端定义配置。示例：
   ```lua
   vim.lsp.config['luals'] = {
     -- 启动服务器的命令和参数。
     cmd = { 'lua-language-server' },
     -- 自动附加的文件类型。
     filetypes = { 'lua' },
     -- 设置“根目录”为当前缓冲区文件所在目录中包含“.luarc.json”或“.luarc.jsonc”的父目录。
     -- 共享根目录的文件将复用相同的 LSP 服务器连接。
     -- 嵌套列表表示相同优先级，请参见 |vim.lsp.Config|。
     root_markers = { { '.luarc.json', '.luarc.jsonc' }, '.git' },
     -- 发送给服务器的具体设置。该模式由服务器定义。例如 lua-language-server 的模式可以在这里找到 https://raw.githubusercontent.com/LuaLS/vscode-lua/master/setting/schema.json
     settings = {
       Lua = {
         runtime = {
           version = 'LuaJIT',
         }
       }
     }
   }
   ```

2. 使用 [vim.lsp.enable()](https://neovim.io/doc/user/lsp.html#vim.lsp.enable()) 启用配置。示例：
   ```lua
   vim.lsp.enable('luals')
   ```

3. 重启 Nvim 或使用 `:edit` 重新加载缓冲区。

4. 检查 LSP 是否在缓冲区中处于活动状态 ("attached")：
   ```
   :checkhealth vim.lsp
   ```

5. （可选）配置键映射和自动命令以使用 LSP 功能。[lsp-attach](https://neovim.io/doc/user/lsp.html#lsp-attach)

当 Nvim LSP 客户端启动时，它会启用诊断 [vim.diagnostic](https://neovim.io/doc/user/diagnostic.html#vim.diagnostic)（请参阅 [vim.diagnostic.config()](https://neovim.io/doc/user/diagnostic.html#vim.diagnostic.config()) 以自定义）。它还会设置各种默认选项，如果满足以下两个条件，则这些选项不会被恢复：(1) 语言服务器支持该功能；(2) 选项为空或由内置运行时（ftplugin）文件设置。

### 全局默认值
[grr](#grr) [gra](#gra) [grn](#grn) [gri](#gri) [i_CTRL-S](#i_CTRL-S) 这些全局键映射会在 Nvim 启动时无条件创建：

[lsp-defaults-disable](#lsp-defaults-disable)  
要删除或覆盖 BUFFER-LOCAL 默认值，请定义一个 [LspAttach](https://neovim.io/doc/user/lsp.html#LspAttach) 处理程序：
```lua
vim.api.nvim_create_autocmd('LspAttach', {
  callback = function(args)
    -- 取消设置 'formatexpr'
    vim.bo[args.buf].formatexpr = nil
    -- 取消设置 'omnifunc'
    vim.bo[args.buf].omnifunc = nil
    -- 取消 K 键绑定
    vim.keymap.del('n', 'K', { buffer = args.buf })
  end,
})
```

你可以通过 `vim.lsp.config()` 静态配置 LSP 行为，也可以通过 [lsp-attach](https://neovim.io/doc/user/lsp.html#lsp-attach) 或 [Client:on_attach()](https://neovim.io/doc/user/lsp.html#Client%3Aon_attach()) 动态配置。

使用 [vim.lsp.config()](https://neovim.io/doc/user/lsp.html#vim.lsp.config()) 来定义并选择性地启用 LSP 配置。这基本上是对 [vim.lsp.start()](https://neovim.io/doc/user/lsp.html#vim.lsp.start()) 的封装，允许你共享和合并配置（可能由 Nvim 或第三方插件提供）。

当 LSP 客户端启动时，它会通过以下方式解析其配置（按优先级递增顺序）：

1. 为 `'*'` 名称定义的配置。
2. 从 ['runtimepath'](https://neovim.io/doc/user/options.html#'runtimepath') 中名为 `name` 的服务器的 `<rtp>/lsp/<name>.lua` 文件返回的所有表合并而来的配置。
3. 在其他任何地方定义的配置。

**注意：** 配置的合并语义遵循 [vim.tbl_deep_extend()](https://neovim.io/doc/user/lua.html#vim.tbl_deep_extend()) 的行为。

示例：给定以下配置...
```lua
-- 在 init.lua 中定义
vim.lsp.config('*', {
  capabilities = {
    textDocument = {
      semanticTokens = {
        multilineTokenSupport = true,
      }
    }
  },
  root_markers = { '.git' },
})

-- 在 <rtp>/lsp/clangd.lua 中定义
return {
  cmd = { 'clangd' },
  root_markers = { '.clangd', 'compile_commands.json' },
  filetypes = { 'c', 'cpp' },
}

-- 在 init.lua 中定义
vim.lsp.config('clangd', {
  filetypes = { 'c' },
})
```
...合并后的结果是：
```lua
{
  -- 来自 <rtp>/lsp/clangd.lua 的 clangd 配置
  cmd = { 'clangd' },
  -- 来自 <rtp>/lsp/clangd.lua 的 clangd 配置
  -- 覆盖了 init.lua 中的 "*" 配置
  root_markers = { '.clangd', 'compile_commands.json' },
  -- 来自 init.lua 中的 clangd 配置
  -- 覆盖了 <rtp>/lsp/clangd.lua 中的 clangd 配置
  filetypes = { 'c' },
  -- 来自 init.lua 中的 "*" 配置
  capabilities = {
    textDocument = {
      semanticTokens = {
        multilineTokenSupport = true,
      }
    }
  }
}
```

[lsp-attach](#lsp-attach)  
要使用 Nvim 提供的功能之外的 LSP 功能，可以在 [Client:on_attach()](https://neovim.io/doc/user/lsp.html#Client%3Aon_attach()) 或 [LspAttach](https://neovim.io/doc/user/lsp.html#LspAttach) 上设置键映射和选项。并非所有语言服务器都提供相同的能力；在你的 LspAttach 处理程序中检查 `supports_method()`。[lsp-lint](#lsp-lint) [lsp-format](#lsp-format) 示例：启用自动补全和自动格式化（“linting”）：
```lua
vim.api.nvim_create_autocmd('LspAttach', {
  group = vim.api.nvim_create_augroup('my.lsp', {}),
  callback = function(args)
    local client = assert(vim.lsp.get_client_by_id(args.data.client_id))
    if client:supports_method('textDocument/implementation') then
      -- 创建 vim.lsp.buf.implementation 的键映射 ...
    end
    -- 启用自动补全。注意：使用 CTRL-Y 选择项目。|complete_CTRL-Y|
    if client:supports_method('textDocument/completion') then
      -- 可选：触发每次按键的自动补全。可能会很慢！
      -- local chars = {}; for i = 32, 126 do table.insert(chars, string.char(i)) end
      -- client.server_capabilities.completionProvider.triggerCharacters = chars
      vim.lsp.completion.enable(true, client.id, args.buf, {autotrigger = true})
    end
    -- 在保存时自动格式化（“lint”）。
    -- 如果服务器支持 "textDocument/willSaveWaitUntil"，通常不需要这样做。
    if not client:supports_method('textDocument/willSaveWaitUntil')
        and client:supports_method('textDocument/formatting') then
      vim.api.nvim_create_autocmd('BufWritePre', {
        group = vim.api.nvim_create_augroup('my.lsp', {clear=false}),
        buffer = args.buf,
        callback = function()
          vim.lsp.buf.format({ bufnr = args.buf, id = client.id, timeout_ms = 1000 })
        end,
      })
    end
  end,
})
```

要在给定服务器中查看能力，在启用了 LSP 的缓冲区中尝试以下命令：
```
:lua =vim.lsp.get_clients()[1].server_capabilities
```

常见问题解答 [lsp-faq](#lsp-faq)
-----------------------
Q: 如何强制重新加载 LSP？
A: 停止所有客户端，然后重新加载缓冲区。
```
:lua vim.lsp.stop_client(vim.lsp.get_clients())
:edit
```

Q: 为什么补全不起作用？
A: 在你想要使用 LSP 的缓冲区中，检查 ['omnifunc'](https://neovim.io/doc/user/options.html#'omnifunc') 是否设置为 "v:lua.vim.lsp.omnifunc": `:verbose set omnifunc?`
一些其他插件可能覆盖了该选项。为了避免这种情况，你可以在 [after-directory](https://neovim.io/doc/user/options.html#after-directory) ftplugin 中设置该选项，例如 "after/ftplugin/python.vim"。

Q: 如何同步运行请求（例如在文件保存前进行格式化）？
A: 检查函数是否有 `async` 参数并将值设为 false。例如代码格式化：
```
" 在保存 *.rs（Rust）文件之前自动格式化它们
" (async = false 是 format 的默认值)
autocmd BufWritePre *.rs lua vim.lsp.buf.format({ async = false })
```

[lsp-vs-treesitter](#lsp-vs-treesitter)
Q: LSP 和 Treesitter 有何不同？
A: LSP 需要客户端和语言服务器。语言服务器使用语义分析来理解整个项目的代码。这使得语言服务器能够跨文件重命名、在外部库中查找定义等。
[treesitter](https://neovim.io/doc/user/treesitter.html#treesitter) 是一种语言解析库，提供了出色的工具用于增量解析文本和处理错误。这使其非常适合编辑器用于当前文件的理解，如语法高亮、简单的跳转定义等。

[lsp-core](https://neovim.io/doc/user/lsp.html#lsp-core) API 提供了创建和管理客户端的核心函数。[lsp-buf](https://neovim.io/doc/user/lsp.html#lsp-buf) 函数执行对附加到当前缓冲区的 LSP 客户端的操作。

[lsp-method](#lsp-method)  
LSP 规范定义的请求和通知称为“LSP 方法”。这些方法由 Lua [lsp-handler](https://neovim.io/doc/user/lsp.html#lsp-handler) 函数处理。
[vim.lsp.handlers](https://neovim.io/doc/user/lsp.html#vim.lsp.handlers) 全局表定义了默认的处理器（仅适用于服务器到客户端的请求/通知，不适用于客户端到服务器）。**注意：** 依赖于服务器支持；如果服务器不支持它们，它们将不会运行。
你可以通过以下命令列出它们：
```
:lua vim.print(vim.tbl_keys(vim.lsp.handlers))
```
它们也列在下面。
`'callHierarchy/incomingCalls'`
`'callHierarchy/outgoingCalls'`
`'client/registerCapability'`
`'client/unregisterCapability'`
`'signature_help'`
`'textDocument/codeLens'`
`'textDocument/completion'`
`'textDocument/diagnostic'`
`'textDocument/documentHighlight'`
`'textDocument/documentSymbol'`
`'textDocument/formatting'`
`'textDocument/hover'`
`'textDocument/inlayHint'`
`'textDocument/publishDiagnostics'`
`'textDocument/rangeFormatting'`
`'textDocument/rename'`
`'textDocument/signatureHelp'`
`'typeHierarchy/subtypes'`
`'typeHierarchy/supertypes'`
`'window/logMessage'`
`'window/showDocument'`
`'window/showMessage'`
`'window/showMessageRequest'`
`'window/workDoneProgress/create'`
`'workspace/applyEdit'`
`'workspace/configuration'`
`'workspace/executeCommand'`
`'workspace/inlayHint/refresh'`
`'workspace/semanticTokens/refresh'`
`'workspace/symbol'`
`'workspace/workspaceFolders'`

[lsp-handler](#lsp-handler)  
LSP 处理器是处理 Nvim 对服务器发出的请求的响应的函数。（通知是即发即弃的：没有响应，因此无法处理。[lsp-notification](https://neovim.io/doc/user/lsp.html#lsp-notification)）
每个响应处理器具有以下签名：
```
function(err, result, ctx)
```
参数：
`{err}` (`table|nil`) 错误信息字典，或 `nil` 如果请求完成。
`{result}` (`Result|Params|nil`) [lsp-response](https://neovim.io/doc/user/lsp.html#lsp-response) 的 `result` 键或 `nil` 如果请求失败。
`{ctx}` (`table`) 与处理器关联的调用状态表，包含以下键：
`{bufnr}` (`Buffer`) 缓冲区句柄。
`{params}` (`table|nil`) 请求参数表。
`{version}` (`number`) 请求时的文档版本。处理器可以比较这个值与当前文档版本以检查响应是否“陈旧”。另请参阅 [b:changedtick](https://neovim.io/doc/user/vimeval.html#b%3Achangedtick)。
返回：
两个值 `result, err` 其中 `err` 形状像 RPC 错误：
```
{ code, message, data? }
```

[vim.lsp.handlers](#vim.lsp.handlers)
直接调用 [Client:request()](https://neovim.io/doc/user/lsp.html#Client%3Arequest()) 中的 LSP 方法。这是唯一覆盖默认客户端到服务器请求处理的方式（通过绕过 `vim.lsp.buf` 和相关接口）。
```
local client = assert(vim.lsp.get_clients()[1])
client:request('textDocument/definition')
```

设置 `vim.lsp.handlers` 中的一个字段。此全局表包含 [lsp-method](https://neovim.io/doc/user/lsp.html#lsp-method) 名称到处理器的默认映射。（**注意：** 仅适用于服务器到客户端的请求/通知，不适用于客户端到服务器。）示例：
```
vim.lsp.handlers['textDocument/publishDiagnostics'] = my_custom_diagnostics_handler
```

传递 `{handlers}` 参数到 [vim.lsp.start()](https://neovim.io/doc/user/lsp.html#vim.lsp.start())。此参数设置特定服务器的默认 [lsp-handler](https://neovim.io/doc/user/lsp.html#lsp-handler)。（**注意：** 仅适用于服务器到客户端的请求/通知，不适用于客户端到服务器。）示例：
```
vim.lsp.start {
  ..., 
  handlers = {
    ['textDocument/publishDiagnostics'] = my_custom_diagnostics_handler
  },
}
```

传递 `{handler}` 参数到 [vim.lsp.buf_request_all()](https://neovim.io/doc/user/lsp.html#vim.lsp.buf_request_all())。此参数设置 [lsp-handler](https://neovim.io/doc/user/lsp.html#lsp-handler) 仅针对给定请求(s)。示例：
```
vim.lsp.buf_request_all(
  0,
  'textDocument/publishDiagnostics',
  my_request_params,
  my_handler
)
```

例如 `vim.lsp.protocol.ErrorCodes` 允许通过数字或名称反向查找：
```
vim.lsp.protocol.TextDocumentSyncKind.Full == 1
vim.lsp.protocol.TextDocumentSyncKind[1] == "Full"
```

参考高亮显示：
[hl-LspReferenceText](#hl-LspReferenceText)  
LspReferenceText 用于高亮显示“文本”引用 [hl-LspReferenceRead](#hl-LspReferenceRead)  
LspReferenceRead 用于高亮显示“读取”引用 [hl-LspReferenceWrite](#hl-LspReferenceWrite)  
LspReferenceWrite 用于高亮显示“写入”引用 [hl-LspReferenceTarget](#hl-LspReferenceTarget)  
LspReferenceTarget 用于高亮显示引用目标（例如在悬停范围内）[hl-LspInlayHint](#hl-LspInlayHint)  
LspInlayHint 用于高亮显示内联提示

与 [lsp-codelens](https://neovim.io/doc/user/lsp.html#lsp-codelens) 功能相关的高亮组。
LspCodeLensSeparator [hl-LspCodeLensSeparator](#hl-LspCodeLensSeparator)  
用于颜色分隔符在两个或多个代码镜头之间。

当可用时，LSP 客户端使用 [lsp-semantic_tokens](https://neovim.io/doc/user/lsp.html#lsp-semantic_tokens) 高亮代码，这是 LSP 服务器提供源代码信息的另一种方式。请注意，这是对 treesitter 语法高亮的补充；语义高亮不会替换语法高亮。

服务器通常为源代码中的每个标识符提供一个令牌。该令牌将具有一个 `type`（如“函数”或“变量”），以及 0 个或多个 `modifier`（如“只读”或“已弃用”）。标准类型和修饰符在此描述：[https://microsoft.github.io/language-server-protocol/specification/#textDocument_semanticTokens](https://microsoft.github.io/language-server-protocol/specification/#textDocument_semanticTokens) LSP 服务器也可能使用非规范的类型和修饰符。

LSP 客户端为每个令牌添加一个或多个高亮。高亮组派生自令牌的类型和修饰符：
`@lsp.type.<type>.<ft>` 用于类型
`@lsp.mod.<mod>.<ft>` 用于每个修饰符
`@lsp.typemod.<type>.<mod>.<ft>` 用于每个修饰符 使用 [:Inspect](https://neovim.io/doc/user/lua.html#%3AInspect) 查看特定令牌的高亮。使用 [:hi](https://neovim.io/doc/user/syntax.html#%3Ahi) 或 [nvim_set_hl()](https://neovim.io/doc/user/api.html#nvim_set_hl()) 更改语义高亮的外观：
```
hi @lsp.type.function guifg=Yellow        " 函数名是黄色
hi @lsp.type.variable.lua guifg=Green     
hi @lsp.mod.deprecated gui=strikethrough  
hi @lsp.typemod.function.async guifg=Blue 
```
值 [vim.hl.priorities](https://neovim.io/doc/user/lua.html#vim.hl.priorities)`.semantic_tokens` 是 `@lsp.type.*` 高亮的优先级。`@lsp.mod.*` 和 `@lsp.typemod.*` 高亮的优先级分别高出一和二。

你可以通过清除高亮组禁用语义高亮：
```
vim.api.nvim_set_hl(0, '@lsp.type.function', {})
for _, group in ipairs(vim.fn.getcompletion("@lsp", "highlight")) do
  vim.api.nvim_set_hl(0, group, {})
end
```
你可能希望将这些放在 [ColorScheme](https://neovim.io/doc/user/autocmd.html#ColorScheme) 自动命令中。

以下是 Nvim 中使用的查询的标准捕获，根据当前配色方案高亮（在其中一个上使用 [:Inspect](https://neovim.io/doc/user/lua.html#%3AInspect) 查看确切定义）：
@lsp.type.class 声明或引用类类型的标识符 @lsp.type.comment 表示注释的令牌 @lsp.type.decorator 声明或引用装饰器和注解的标识符 @lsp.type.enum 声明或引用枚举类型的标识符 @lsp.type.enumMember 声明或引用枚举属性、常量或成员的标识符 @lsp.type.event 声明事件属性的标识符 @lsp.type.function 声明函数的标识符 @lsp.type.interface 声明或引用接口类型的标识符 @lsp.type.keyword 表示语言关键字的令牌 @lsp.type.macro 声明宏的标识符 @lsp.type.method 声明成员函数或方法的标识符 @lsp.type.modifier 表示修饰符的令牌 @lsp.type.namespace 声明或引用命名空间、模块或包的标识符 @lsp.type.number 表示数字字面量的令牌 @lsp.type.operator 表示运算符的令牌 @lsp.type.parameter 声明或引用函数或方法参数的标识符 @lsp.type.property 声明或引用成员属性、成员字段或成员变量的标识符 @lsp.type.regexp 表示正则表达式字面量的令牌 @lsp.type.string 表示字符串字面量的令牌 @lsp.type.struct 声明或引用结构体类型的标识符 @lsp.type.type 声明或引用未涵盖的类型的标识符 @lsp.type.typeParameter 声明或引用类型参数的标识符 @lsp.type.variable 声明或引用本地或全局变量的标识符

@lsp.mod.abstract 抽象类型和成员函数 @lsp.mod.async 异步函数 @lsp.mod.declaration 符号的声明 @lsp.mod.defaultLibrary 标准库中的符号 @lsp.mod.definition 符号的定义，例如在头文件中 @lsp.mod.deprecated 不应再使用的符号 @lsp.mod.documentation 文档中出现的符号 @lsp.mod.modification 分配变量引用的地方 @lsp.mod.readonly 只读变量和成员字段（常量） @lsp.mod.static 类成员（静态成员）

LspAttach [LspAttach](#LspAttach)  
在 LSP 客户端执行“初始化”并附加到缓冲区之后。[autocmd-pattern](https://neovim.io/doc/user/autocmd.html#autocmd-pattern) 是缓冲区名称。客户端 ID 在 Lua 处理程序 [event-data](https://neovim.io/doc/user/api.html#event-data) 参数中传递。
示例：
```
vim.api.nvim_create_autocmd('LspAttach', {
  callback = function(ev)
    local client = vim.lsp.get_client_by_id(ev.data.client_id)
  end
})
```
**注意：** 如果 LSP 服务器执行动态注册，能力可能在 LspAttach 之后的任何时间注册。在这种情况下，你可能需要处理“registerCapability”事件。
示例：
```
vim.lsp.handlers['client/registerCapability'] = (function(overridden)
  return function(err, res, ctx)
    local result = overridden(err, res, ctx)
    local client = vim.lsp.get_client_by_id(ctx.client_id)
    if not client then
      return
    end
    for bufnr, _ in pairs(client.attached_buffers) do
    end
    return result
  end
end)(vim.lsp.handlers['client/registerCapability'])
```

LspDetach [LspDetach](#LspDetach)  
在 LSP 客户端从缓冲区分离之前。[autocmd-pattern](https://neovim.io/doc/user/autocmd.html#autocmd-pattern) 是缓冲区名称。客户端 ID 在 Lua 处理程序 [event-data](https://neovim.io/doc/user/api.html#event-data) 参数中传递。
示例：
```
vim.api.nvim_create_autocmd('LspDetach', {
  callback = function(args)
    local client = vim.lsp.get_client_by_id(args.data.client_id)
    if client:supports_method('textDocument/formatting') then
      vim.api.nvim_clear_autocmds({
        event = 'BufWritePre',
        buffer = args.buf,
      })
    end
  end,
})
```

LspNotify [LspNotify](#LspNotify)  
在每次成功发送到 LSP 服务器的通知后触发。客户端 ID、LSP 方法和参数在 Lua 处理程序 [event-data](https://neovim.io/doc/user/api.html#event-data) 表参数中发送。
示例：
```
vim.api.nvim_create_autocmd('LspNotify', {
  callback = function(args)
    local bufnr = args.buf
    local client_id = args.data.client_id
    local method = args.data.method
    local params = args.data.params
    if method == 'textDocument/...' then
      update_buffer(bufnr)
    end
  end,
})
```

LspProgress [LspProgress](#LspProgress)  
在收到服务器的进度通知时触发。可以通过 [vim.lsp.Client](https://neovim.io/doc/user/lsp.html#vim.lsp.Client) 的 `progress` 环形缓冲区轮询通知，或者使用 [vim.lsp.status()](https://neovim.io/doc/user/lsp.html#vim.lsp.status()) 获取聚合消息。
如果服务器发送了“工作进度”，则 `pattern` 设置为 `kind`（`begin`, `report` 或 `end` 中的一个）。
Lua 处理程序 [event-data](https://neovim.io/doc/user/api.html#event-data) 参数有 `client_id` 和 `params` 属性，其中 `params` 是服务器发送的请求参数（见 `lsp.ProgressParams`）。
示例：
```
autocmd LspProgress * redrawstatus
```

LspRequest [LspRequest](#LspRequest)  
对于发送到 LSP 服务器的每个请求，当请求的状态发生更改时触发此事件。状态可以是 `pending`, `complete` 或 `cancel`，并在传递给回调函数的 `data` 表中发送。
当初始请求发送时触发（`{type}` == `pending`）并且当 LSP 服务器响应时触发（`{type}` == `complete`）。如果使用 `client.cancel_request(request_id)` 请求取消，则此事件将触发 `{type}` == `cancel`。
Lua 处理程序 [event-data](https://neovim.io/doc/user/api.html#event-data) 参数有客户端 ID、请求 ID 和请求（参见 [vim.lsp.Client](https://neovim.io/doc/user/lsp.html#vim.lsp.Client), `{requests}` 字段）。如果请求类型是 `complete`，则在处理事件处理器后，请求将从客户端的待处理请求表中删除。
示例：
```
vim.api.nvim_create_autocmd('LspRequest', {
  callback = function(args)
    local bufnr = args.buf
    local client_id = args.data.client_id
    local request_id = args.data.request_id
    local request = args.data.request
    if request.type == 'pending' then
      track_pending(client_id, bufnr, request_id, request)
    elseif request.type == 'cancel' then
      track_canceling(client_id, bufnr, request_id, request)
    elseif request.type == 'complete' then
      track_finish(client_id, bufnr, request_id, request)
    end
  end,
})
```

LspTokenUpdate [LspTokenUpdate](#LspTokenUpdate)  
当可见的语义令牌由 LSP 服务器发送或更新时，或者当现有令牌首次可见时。[autocmd-pattern](https://neovim.io/doc/user/autocmd.html#autocmd-pattern) 是缓冲区名称。Lua 处理程序 [event-data](https://neovim.io/doc/user/api.html#event-data) 参数有客户端 ID 和令牌（见 [vim.lsp.semantic_tokens.get_at_pos()](https://neovim.io/doc/user/lsp.html#vim.lsp.semantic_tokens.get_at_pos())）。
示例：
```
vim.api.nvim_create_autocmd('LspTokenUpdate', {
  callback = function(args)
    local token = args.data.token
    if token.type == 'variable' and not token.modifiers.readonly then
      vim.lsp.semantic_tokens.highlight_token(
        token, args.buf, args.data.client_id, 'MyMutableVariableHighlight'
      )
    end
  end,
})
```

字段：
`{cmd}` (`string[]|fun(dispatchers: vim.lsp.rpc.Dispatchers): vim.lsp.rpc.PublicClient`) 见 `cmd` 在 [vim.lsp.ClientConfig](https://neovim.io/doc/user/lsp.html#vim.lsp.ClientConfig) 中。
`{filetypes}` (`string[]`) 客户端将附加的文件类型，如果通过 `vim.lsp.enable()` 激活。如果没有提供，客户端将附加到所有文件类型。
`{reuse_client}` (`fun(client: vim.lsp.Client, config: vim.lsp.ClientConfig): boolean`) 决定是否重用客户端的谓词。用于所有正在运行的客户端。默认实现如果名称和 root_dir 匹配则重用客户端。
`{root_dir}` (`string|fun(bufnr: integer, on_dir:fun(root_dir?:string))`) [lsp-root_dir()](#lsp-root_dir()) LSP 服务器将基于其 workspaceFolders, rootUri, 和 rootPath 初始化的目录。函数形式接收缓冲区编号和 `on_dir` 回调，必须调用它来提供 root_dir，否则 LSP 将不会为该缓冲区激活。因此，`root_dir()` 函数可以动态决定每个缓冲区是否激活（或跳过）LSP。见 [vim.lsp.enable()](https://neovim.io/doc/user/lsp.html#vim.lsp.enable()) 中的示例。
`{root_markers}` (`(string|string[])[]`) 目录标记（例如 '.git/'），LSP 服务器将基于其 workspaceFolders, rootUri, 和 rootPath 初始化。如果提供了 `root_dir` 则忽略此字段。
列表顺序决定优先级。为了表示“相同优先级”，指定名称在一个嵌套列表中（`{ { 'a', 'b' }, ... }`）。每个条目是一个一个或多个标记的集合。对于每个集合，Nvim 将向上搜索每个包含在集合中的标记。如果找到标记，则包含该标记的目录用作根目录。如果未找到集合中的任何标记，则重复下一个集合的过程。
示例：
```
root_markers = { 'stylua.toml', '.git' }
```
找到第一个包含文件 `stylua.toml` 的父目录。如果没有找到，找到第一个包含文件或目录 `.git` 的父目录。
示例：
```
root_markers = { { 'stylua.toml', '.luarc.json' }, '.git' }
```
找到第一个包含 `stylua.toml` 或 `.luarc.json` 的父目录。如果没有找到，找到第一个包含文件或目录 `.git` 的父目录。

buf_attach_client(`{bufnr}`, `{client_id}`) [vim.lsp.buf_attach_client()](#vim.lsp.buf_attach_client())  
实现 `textDocument/did…` 通知以跟踪任何语言服务器的缓冲区。
如果不调用此函数，服务器将不会收到缓冲区更改的通知。
参数：
`{bufnr}` (`integer`) 缓冲区句柄，或 0 表示当前
`{client_id}` (`integer`) 客户端 ID
返回：
(`boolean`) 成功 `true` 如果客户端附加成功；否则 `false`

buf_detach_client(`{bufnr}`, `{client_id}`) [vim.lsp.buf_detach_client()](#vim.lsp.buf_detach_client())  
从指定缓冲区分离客户端。**注意：** 虽然服务器被告知文本文档（缓冲区）已关闭，但它仍可能发送通知，即使它忽略了此通知。
参数：
`{bufnr}` (`integer`) 缓冲区句柄，或 0 表示当前
`{client_id}` (`integer`) 客户端 ID

buf_is_attached(`{bufnr}`, `{client_id}`) [vim.lsp.buf_is_attached()](#vim.lsp.buf_is_attached())  
检查缓冲区是否附加到特定客户端。
参数：
`{bufnr}` (`integer`) 缓冲区句柄，或 0 表示当前
`{client_id}` (`integer`) 客户端 ID

buf_notify(`{bufnr}`, `{method}`, `{params}`) [vim.lsp.buf_notify()](#vim.lsp.buf_notify())  
发送通知到服务器
参数：
`{bufnr}` (`integer?`) 缓冲区编号
`{method}` (`string`) 请求方法名称
`{params}` (`any`) 发送到服务器的参数
返回：
(`boolean`) 成功 `true` 如果有任何客户端返回 `true`; 否则 `false`

[vim.lsp.buf_request_all()](#vim.lsp.buf_request_all())  
buf_request_all(`{bufnr}`, `{method}`, `{params}`, `{handler}`) 发送异步请求到所有附加到缓冲区的客户端，并执行 `handler` 回调与组合结果。
参数：
`{bufnr}` (`integer`) 缓冲区句柄，或 0 表示当前。
`{method}` (`string`) LSP 方法名称
`{params}` (`table|(fun(client: vim.lsp.Client, bufnr: integer): table?)?`) 发送到服务器的参数。也可以作为函数传递，返回参数表用于参数特定于客户端的情况。
`{handler}` (`function`) 所有请求完成后调用的回调。服务器结果作为 `client_id:result` 映射传递。
返回：
(`function`) cancel 取消所有请求的函数。

[vim.lsp.buf_request_sync()](#vim.lsp.buf_request_sync())  
buf_request_sync(`{bufnr}`, `{method}`, `{params}`, `{timeout_ms}`) 发送请求到所有服务器并等待所有服务器的响应。
参数：
`{bufnr}` (`integer`) 缓冲区句柄，或 0 表示当前。
`{method}` (`string`) LSP 方法名称
`{params}` (`table|(fun(client: vim.lsp.Client, bufnr: integer): table?)?`) 发送到服务器的参数。也可以作为函数传递，返回参数表用于参数特定于客户端的情况。
`{timeout_ms}` (`integer?`, 默认: `1000`) 等待结果的最大毫秒数。
返回（多个）：
(`table<integer, {error: lsp.ResponseError?, result: any}>?`) 结果客户端 ID：请求结果。(`string?`) err 在超时、取消或错误时，`err` 是描述失败原因的字符串，且 `result` 为 nil。

commands [vim.lsp.commands](#vim.lsp.commands)  
客户端侧处理器的注册表（表），用于不在 LSP 规范中的自定义服务器命令。
如果 LSP 响应包含 `vim.lsp.commands` 中找不到的命令，则该命令将通过 LSP 服务器使用 `workspace/executeCommand` 执行。
表中的每个键是一个唯一的命令名称，每个值是一个函数，当 LSP 动作（代码动作、代码镜头等）触发该命令时调用。
参数 1 是 `Command`:
```
Command
title: String
command: String
arguments?: any[]
```
示例：
```
vim.lsp.commands['java.action.generateToStringPrompt'] = function(_, ctx)
  require("jdtls.async").run(function()
    local _, result = request(ctx.bufnr, 'java/checkToStringStatus', ctx.params)
    local fields = ui.pick_many(result.fields, 'Include item in toString?', function(x)
      return string.format('%s: %s', x.name, x.type)
    end)
    local _, edit = request(ctx.bufnr, 'java/generateToString', { context = ctx.params; fields = fields; })
    vim.lsp.util.apply_workspace_edit(edit, offset_encoding)
  end)
end
```

config(`{name}`, `{cfg}`) [vim.lsp.config()](#vim.lsp.config())  
设置 LSP 客户端的默认配置（如果特殊名称 "*" 被使用，则为所有客户端）。
也可以通过表索引（`vim.lsp.config[…]`）访问以获取解析的配置，或重新定义配置（而不是“合并”配置链）。
示例：
为所有客户端添加根标记：
```
vim.lsp.config('*', {
  root_markers = { '.git', '.hg' },
})
```
为所有客户端添加能力：
```
  vim.lsp.config('*', {
  capabilities = {
    textDocument = {
      semanticTokens = {
        multilineTokenSupport = true,
      }
    }
  }
})
```
为 "clangd" 添加根标记和能力：
```
  vim.lsp.config('clangd', {
  root_markers = { '.clang-format', 'compile_commands.json' },
  capabilities = {
    textDocument = {
      completion = {
        completionItem = {
          snippetSupport = true,
        }
      }
    }
  }
})
```
（重新）定义 "clangd" 配置（覆盖解析的链）：
```
  vim.lsp.config.clangd = {
  cmd = {
    'clangd',
    '--clang-tidy',
    '--background-index',
    '--offset-encoding=utf-8',
  },
  root_markers = { '.clangd', 'compile_commands.json' },
  filetypes = { 'c', 'cpp' },
}
```
获取 "luals" 的解析配置：
```
local cfg = vim.lsp.config.luals
```
属性：
Since: 0.11.0
参数：
`{name}` (`string`)

enable(`{name}`, `{enable}`) [vim.lsp.enable()](#vim.lsp.enable())  
基于 [lsp-config](https://neovim.io/doc/user/lsp.html#lsp-config) `filetypes`, `root_markers` 和 `root_dir` 字段自动启动 LSP。
示例：
```
vim.lsp.enable('clangd')
vim.lsp.enable({'luals', 'pyright'})
```
示例：要动态决定是否激活 LSP，定义一个 [lsp-root_dir()](https://neovim.io/doc/user/lsp.html#lsp-root_dir()) 函数，仅当你希望该配置激活时调用 `on_dir()`：
```
vim.lsp.config('lua_ls', {
  root_dir = function(bufnr, on_dir)
    if not vim.fn.bufname(bufnr):match('%.txt$') then
      on_dir(vim.fn.getcwd())
    end
  end
})
```
属性：
Since: 0.11.0
参数：
`{name}` (`string|string[]`) 客户端名称。
`{enable}` (`boolean?`) `true|nil` 启用，`false` 禁用。

foldclose(`{kind}`, `{winid}`) [vim.lsp.foldclose()](#vim.lsp.foldclose())  
关闭 `{kind}` 类型的所有折叠在 `{winid}` 窗口中。
要自动折叠导入，可以在打开文件时使用自动命令：
```
vim.api.nvim_create_autocmd('LspNotify', {
  callback = function(args)
    if args.data.method == 'textDocument/didOpen' then
      vim.lsp.foldclose('imports', vim.fn.bufwinid(args.buf))
    end
  end,
})
```
属性：
Since: 0.11.0
参数：
`{kind}` (`lsp.FoldingRangeKind`) 要关闭的类型，可以是 "comment", "imports" 或 "region"。
`{winid}` (`integer?`) 默认为当前窗口。

foldexpr(`{lnum}`) [vim.lsp.foldexpr()](#vim.lsp.foldexpr())  
提供内置客户端和 `foldexpr` 函数之间的接口。
要使用，请设置 ['foldmethod'](https://neovim.io/doc/user/options.html#'foldmethod') 为 "expr" 并设置 ['foldexpr'](https://neovim.io/doc/user/options.html#'foldexpr') 的值：
```
vim.o.foldmethod = 'expr'
vim.o.foldexpr = 'v:lua.vim.lsp.foldexpr()'
```
或者在 [LspAttach](https://neovim.io/doc/user/lsp.html#LspAttach) 自动命令中检查 "textDocument/foldingRange" 能力。示例：
```
vim.o.foldmethod = 'expr'
vim.o.foldexpr = 'v:lua.vim.treesitter.foldexpr()'
vim.api.nvim_create_autocmd('LspAttach', {
  callback = function(args)
    local client = vim.lsp.get_client_by_id(args.data.client_id)
    if client:supports_method('textDocument/foldingRange') then
      local win = vim.api.nvim_get_current_win()
      vim.wo[win][0].foldexpr = 'v:lua.vim.lsp.foldexpr()'
    end
  end,
})
```
参数：
`{lnum}` (`integer`) 行号

foldtext() [vim.lsp.foldtext()](#vim.lsp.foldtext())  
提供一个 `foldtext` 函数，显示检索到的 `collapsedText`，如果 `collapsedText` 未提供，默认为第一行折叠内容。

formatexpr(`{opts}`) [vim.lsp.formatexpr()](#vim.lsp.formatexpr())  
提供内置客户端和 `formatexpr` 函数之间的接口。
目前仅支持单个客户端。这可以通过 `setlocal formatexpr=v:lua.vim.lsp.formatexpr()` 设置，或者更典型地在 `on_attach` 中通过 `vim.bo[bufnr].formatexpr = 'v:lua.vim.lsp.formatexpr(#{timeout_ms:250})'` 设置。
参数：
`{opts}` (`table?`) 包含以下字段的表：
`{timeout_ms}` (`integer`, 默认: 500ms) 格式化请求的超时周期。.
参数：
`{client_id}` (`integer`) 客户端 ID
返回：
(`integer[]`) 缓冲区 ID 列表

get_client_by_id(`{client_id}`) [vim.lsp.get_client_by_id()](#vim.lsp.get_client_by_id())  
通过 ID 获取客户端，如果 ID 无效或客户端已停止则返回 nil。返回的客户端可能尚未完全初始化。
参数：
`{client_id}` (`integer`) 客户端 ID
返回：
(`vim.lsp.Client?`) rpc 对象
属性：
Since: 0.10.0
参数：
`{filter}` (`table?`) 用于过滤返回客户端的键值对。
`{id}` (`integer`) 仅返回具有给定 ID 的客户端
`{bufnr}` (`integer`) 仅返回附加到此缓冲区的客户端
`{name}` (`string`) 仅返回具有给定名称的客户端
`{method}` (`string`) 仅返回支持给定方法的客户端

get_log_path() [vim.lsp.get_log_path()](#vim.lsp.get_log_path())  
获取 LSP 客户端使用的日志文件路径。
返回：
(`string`) 日志文件路径

is_enabled(`{name}`) [vim.lsp.is_enabled()](#vim.lsp.is_enabled())  
检查给定 LSP 配置是否已启用（全局，而非每缓冲区）。
参数：
`{name}` (`string`) 配置名称
参数：
`{findstart}` (`integer`) 0 或 1，决定行为
`{base}` (`integer`) findstart=0，要匹配的文本
返回：
(`integer|table`) 由 `{findstart}` 决定：
findstart=0: 完成开始的列，或 -2 或 -3
findstart=1: 匹配项列表（实际上只是调用 [complete()](https://neovim.io/doc/user/vimfn.html#complete()))

levels by name: "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "OFF"
级别数字从 "TRACE" 开始为 0
使用 `lsp.log_levels` 进行反向查找。
参数：
`{level}` (`integer|string`) 不区分大小写的级别名称或数字

start(`{config}`, `{opts}`) [vim.lsp.start()](#vim.lsp.start())  
创建一个新的 LSP 客户端并启动语言服务器，或重用已运行的客户端（如果找到匹配 `name` 和 `root_dir` 的客户端）。将当前缓冲区附加到客户端。
示例：
```
vim.lsp.start({
   name = 'my-server-name',
   cmd = {'name-of-language-server-executable'},
   root_dir = vim.fs.root(0, {'pyproject.toml', 'setup.py'}),
})
```
有关所有可用选项，请参见 [vim.lsp.ClientConfig](https://neovim.io/doc/user/lsp.html#vim.lsp.ClientConfig)。最重要的包括：
`name` LSP 客户端的任意名称。对于每个语言服务器应唯一。
`cmd` 命令字符串[] 或函数。
`root_dir` 项目根目录的路径。默认情况下，此值用于决定是否重用现有客户端。上面的示例使用 [vim.fs.root()](https://neovim.io/doc/user/lua.html#vim.fs.root()) 从当前目录开始向上遍历文件系统，直到找到 `pyproject.toml` 或 `setup.py` 文件为止。
`workspace_folders` `{ uri:string, name: string }` 表列表，指定语言服务器使用的项目根文件夹。如果 `nil`，属性从 `root_dir` 推导出来以便于使用。
语言服务器使用此信息发现项目元数据，如项目依赖关系，它们倾向于索引项目文件夹中的内容。
为确保语言服务器仅对它能处理的语言启动，请在 [FileType](https://neovim.io/doc/user/autocmd.html#FileType) 自动命令中调用 [vim.lsp.start()](https://neovim.io/doc/user/lsp.html#vim.lsp.start())。可以使用 [:au](https://neovim.io/doc/user/autocmd.html#%3Aau), [nvim_create_autocmd()](https://neovim.io/doc/user/api.html#nvim_create_autocmd()) 或将调用放入 `ftplugin/<filetype_name>.lua`（见 [ftplugin-name](https://neovim.io/doc/user/usr_05.html#ftplugin-name)）。
参数：
`{config}` (`vim.lsp.ClientConfig`) 服务器的配置。见 [vim.lsp.ClientConfig](https://neovim.io/doc/user/lsp.html#vim.lsp.ClientConfig)。
`{opts}` (`table?`) 可选关键字参数。
`{reuse_client}` (`fun(client: vim.lsp.Client, config: vim.lsp.ClientConfig): boolean`) 用于决定是否重用客户端的谓词。用于所有正在运行的客户端。默认实现如果工作区文件夹（或 root_dir）都包含在客户端的工作区文件夹中，则重用客户端。
`{bufnr}` (`integer`) 要附加的缓冲区句柄（0 表示当前）。
`{attach}` (`boolean`) 是否将客户端附加到缓冲区（默认 true）。如果设置为 `false`，则忽略 `reuse_client` 和 `bufnr`。
`{silent}` (`boolean`) 如果 LSP 服务器启动失败，抑制错误报告（默认 false）。
返回：
(`integer?`) client_id

status() [vim.lsp.status()](#vim.lsp.status())  
消费所有客户端的最新进度消息并将其格式化为字符串。如果没有客户端或没有新消息，则为空。
你还可以在 [vim.lsp.Client](https://neovim.io/doc/user/lsp.html#vim.lsp.Client) 对象上使用 `stop()` 函数。要停止所有客户端：
```
vim.lsp.stop_client(vim.lsp.get_clients())
```
默认情况下要求服务器关闭，除非此客户端已经请求停止，否则尝试强制关闭。
参数：
`{client_id}` (`integer|integer[]|vim.lsp.Client[]`) ID、ID 列表或 [vim.lsp.Client](https://neovim.io/doc/user/lsp.html#vim.lsp.Client) 对象列表
`{force}` (`boolean?`) 强制关闭

tagfunc(`{pattern}`, `{flags}`) [vim.lsp.tagfunc()](#vim.lsp.tagfunc())  
提供内置客户端和 ['tagfunc'](https://neovim.io/doc/user/options.html#'tagfunc') 之间的接口。
当与正常模式命令一起使用时（例如 [CTRL-]](https://neovim.io/doc/user/tagsrch.html#CTRL-%5D)），这将调用 "textDocument/definition" LSP 方法以查找光标下的标签。否则，使用 "workspace/symbol"。如果没有从任何 LSP 服务器返回结果，则回退到使用内置标签。
参数：
`{pattern}` (`string`) 用于查找工作区符号的模式
返回：
(`table[]`) 标签列表。匹配的标签

字段：
`{attached_buffers}` (`table<integer,true>`)
`{capabilities}` (`lsp.ClientCapabilities`) 客户端（编辑器或工具）在启动时提供的能力。
`{commands}` (`table<string,fun(command: lsp.Command, ctx: table)>`) 客户端命令。见 [vim.lsp.ClientConfig](https://neovim.io/doc/user/lsp.html#vim.lsp.ClientConfig)。
`{dynamic_capabilities}` (`lsp.DynamicCapabilities`) 启动后运行时提供的能力。
`{flags}` (`table`) 客户端的标志表。当前（实验性）标志包括：
`{allow_incremental_sync}` (`boolean`, 默认: `true`) 允许使用增量同步缓冲区编辑
`{debounce_text_changes}` (`integer`, 默认: `150`) 将 `didChange` 通知到服务器去抖动给定的毫秒数。如果为 `nil`，则不进行去抖动。
`{exit_timeout}` (`integer|false`, 默认: `false`) 在发送 "shutdown" 请求后等待服务器退出的最长时间（以毫秒为单位），然后再发送 kill -15。如果设置为 false，nvim 在向服务器发送 "shutdown" 请求后立即退出。
`{get_language_id}` (`fun(bufnr: integer, filetype: string): string`) 见 [vim.lsp.ClientConfig](https://neovim.io/doc/user/lsp.html#vim.lsp.ClientConfig)。
`{id}` (`integer`) 分配给客户端的 ID。
`{initialized}` (`true?`)
`{requests}` (`table<integer,{ type: string, bufnr: integer, method: string}?>`) 发送到服务器的当前挂起请求。条目是键值对，键是请求 ID，值是带有 `type`, `bufnr` 和 `method` 键值对的表。`type` 是 "pending" 表示活跃请求，或 "cancel" 表示取消请求。当从服务器收到回复时，它将是 "complete" 临时的，同时执行 [LspRequest](https://neovim.io/doc/user/lsp.html#LspRequest) 自动命令。
`{rpc}` (`vim.lsp.rpc.PublicClient`) RPC 客户端对象，用于低级交互。见 [vim.lsp.rpc.start()](https://neovim.io/doc/user/lsp.html#vim.lsp.rpc.start())。
`{server_capabilities}` (`lsp.ServerCapabilities?`) 初始化时发送的服务器响应，描述服务器能力。
`{server_info}` (`lsp.ServerInfo?`) 初始化时发送的服务器响应，描述服务器信息（例如版本）。
`{request}` (`fun(self: vim.lsp.Client, method: string, params: table?, handler: lsp.Handler?, bufnr: integer?): boolean, integer?`) 见 [Client:request()](https://neovim.io/doc/user/lsp.html#Client%3Arequest())。
`{request_sync}` (`fun(self: vim.lsp.Client, method: string, params: table, timeout_ms: integer?, bufnr: integer?): {err: lsp.ResponseError?, result:any}?, string?`) 见 [Client:request_sync()](https://neovim.io/doc/user/lsp.html#Client%3Arequest_sync())。
`{notify}` (`fun(self: vim.lsp.Client, method: string, params: table?): boolean`) 见 [Client:notify()](https://neovim.io/doc/user/lsp.html#Client%3Anotify())。
`{cancel_request}` (`fun(self: vim.lsp.Client, id: integer): boolean`) 见 [Client:cancel_request()](https://neovim.io/doc/user/lsp.html#Client%3Acancel_request())。
`{stop}` (`fun(self: vim.lsp.Client, force: boolean?)`) 见 [Client:stop()](https://neovim.io/doc/user/lsp.html#Client%3Astop())。
`{exec_cmd}` (`fun(self: vim.lsp.Client, command: lsp.Command, context: {bufnr?: integer}?, handler: lsp.Handler?)`) 见 [Client:exec_cmd()](https://neovim.io/doc/user/lsp.html#Client%3Aexec_cmd())。
`{on_attach}` (`fun(self: vim.lsp.Client, bufnr: integer)`) 见 [Client:on_attach()](https://neovim.io/doc/user/lsp.html#Client%3Aon_attach())。
`{supports_method}` (`fun(self: vim.lsp.Client, method: string, bufnr: integer?)`) 见 [Client:supports_method()](https://neovim.io/doc/user/lsp.html#Client%3Asupports_method())。

字段：
`{before_init}` (`fun(params: lsp.InitializeParams, config: vim.lsp.ClientConfig)`) 在 LSP "initialize" 阶段之前调用的回调，其中 `params` 包含发送到服务器的参数，`config` 是传递给 [vim.lsp.start()](https://neovim.io/doc/user/lsp.html#vim.lsp.start()) 的配置。你可以使用此回调修改发送之前的参数。
`{capabilities}` (`lsp.ClientCapabilities`) 替换 [vim.lsp.protocol.make_client_capabilities()](https://neovim.io/doc/user/lsp.html#vim.lsp.protocol.make_client_capabilities()) 中定义的默认能力，传递给语言服务器初始化。提示：使用 make_client_capabilities() 并修改其结果。
**注意：** 要发送空字典，请使用 [vim.empty_dict()](https://neovim.io/doc/user/lua.html#vim.empty_dict())，否则它将编码为数组。
`{cmd}` (`string[]|fun(dispatchers: vim.lsp.rpc.Dispatchers): vim.lsp.rpc.PublicClient`) 启动语言服务器的命令字符串[]（按 [jobstart()](https://neovim.io/doc/user/vimfn.html#jobstart()) 中的处理方式，必须是绝对路径或在 `$PATH` 中，shell 构造如 "~" 不扩展），或创建 RPC 客户端的函数。函数接收 `dispatchers` 表并返回带有成员函数 `request`, `notify`, `is_closing` 和 `terminate` 的表。见 [vim.lsp.rpc.request()](https://neovim.io/doc/user/lsp.html#vim.lsp.rpc.request()), [vim.lsp.rpc.notify()](https://neovim.io/doc/user/lsp.html#vim.lsp.rpc.notify())。对于 TCP，有一个内置的 RPC 客户端工厂：[vim.lsp.rpc.connect()](https://neovim.io/doc/user/lsp.html#vim.lsp.rpc.connect())
`{cmd_cwd}` (`string`, 默认: cwd) 启动 `cmd` 进程的目录。与 `root_dir` 无关。
`{cmd_env}` (`table`) 启动 LSP 进程时传递的环境变量。非字符串值强制转换为字符串。示例：
```
{ PORT = 8080; HOST = '0.0.0.0'; }
```
`{commands}` (`table<string,fun(command: lsp.Command, ctx: table)>`) 客户端命令。命令名到用户定义函数的映射。传递给 `start()` 的命令优先于全局命令注册表。每个键必须是唯一命令名，值是在任何 LSP 动作（代码动作、代码镜头等）触发命令时调用的函数。
`{detached}` (`boolean`, 默认: true) 将服务器进程守护化，使其与 Nvim 分开运行。Nvim 将在退出时关闭进程，但如果 Nvim 未能干净退出，这可能导致遗留的服务器进程。
`{flags}` (`table`) 客户端的标志表。当前（实验性）标志包括：
`{allow_incremental_sync}` (`boolean`, 默认: `true`) 允许使用增量同步缓冲区编辑
`{debounce_text_changes}` (`integer`, 默认: `150`) 将 `didChange` 通知到服务器去抖动给定的毫秒数。如果为 `nil`，则不进行去抖动。
`{exit_timeout}` (`integer|false`, 默认: `false`) 发送 "shutdown" 请求后等待服务器干净退出的最长时间（以毫秒为单位）。如果设置为 false，nvim 在发送 "shutdown" 请求后立即退出。
`{get_language_id}` (`fun(bufnr: integer, filetype: string): string`) 语言 ID 作为字符串。默认为缓冲区文件类型。
`{handlers}` (`table<string,function>`) LSP 方法名到 [lsp-handler](https://neovim.io/doc/user/lsp.html#lsp-handler)s 的映射。
`{init_options}` (`lsp.LSPObject`) 作为 `initializationOptions` 传递的值。见 LSP 规范中的 `initialize`。
`{name}` (`string`)（默认: client-id）日志和用户消息中的名称。
`{offset_encoding}` (`'utf-8'|'utf-16'|'utf-32') LSP 规范中称为“位置编码”。LSP 服务器期望的编码，用于通信。未验证。可以在 `on_init` 中修改发送到服务器前的文本。
`{on_attach}` (`elem_or_list<fun(client: vim.lsp.Client, bufnr: integer)>) 当客户端附加到缓冲区时调用的回调。
`{on_error}` (`fun(code: integer, err: string)`) 客户端操作抛出错误时调用的回调。`code` 是描述错误的数字。根据错误种类可能传递其他参数。见 `vim.lsp.rpc.client_errors` 可能的错误。使用 `vim.lsp.rpc.client_errors[code]` 获取人类友好名称。
`{on_exit}` (`elem_or_list<fun(code: integer, signal: integer, client_id: integer)>) 客户端退出时调用的回调。
code: 进程退出代码
signal: 终止所用信号的数字（如果有）
client_id: 客户端句柄
`{on_init}` (`elem_or_list<fun(client: vim.lsp.Client, init_result: lsp.InitializeResult)>) 在 LSP "initialize" 后调用的回调，其中 `result` 是包含 `capabilities` 和服务器可能发送的任何其他内容的表。例如，clangd 发送 `init_result.offsetEncoding` 如果 `capabilities.offsetEncoding` 发送给了它。你只能在此修改 `client.offset_encoding`，在发送任何通知之前。
`{root_dir}` (`string`) LSP 服务器在其上基于 workspaceFolders, rootUri, 和 rootPath 初始化的目录。
`{settings}` (`lsp.LSPObject`) 由客户端决定的语言服务器特定设置。如果通过 `workspace/configuration` 请求发送给 LS。
`{trace}` (`'off'|'messages'|'verbose'`, 默认: "off") 直接传递给语言服务器的初始化请求。无效/空值将被忽略。
`{workspace_folders}` (`lsp.WorkspaceFolder[]`) 传递给语言服务器的工作区文件夹列表。为了向后兼容，rootUri 和 rootPath 从该列表的第一个工作区文件夹推导而来。如果客户端支持工作区文件夹但未配置任何文件夹，则可以为 null。见 LSP 规范中的 `workspaceFolders`。
`{workspace_required}` (`boolean`)（默认 false）服务器需要工作区（无“单文件”支持）。**注意：** 没有工作区时，跨文件特性（导航、悬停）可能有效或无效，取决于语言服务器，即使服务器不需要工作区。

Client:cancel_request(`{id}`) [Client:cancel_request()](#Client%3Acancel_request())  
取消具有给定请求 ID 的请求。
参数：
`{id}` (`integer`) 要取消的请求 ID
返回：
(`boolean`) 表示通知是否成功的状态。

Client:exec_cmd(`{command}`, `{context}`, `{handler}`) [Client:exec_cmd()](#Client%3Aexec_cmd())  
执行 lsp 命令，要么通过客户端命令函数（如果可用），要么通过服务器支持的 workspace/executeCommand。
参数：
`{command}` (`lsp.Command`)
`{context}` (`{ bufnr?: integer }?`)
`{handler}` (`lsp.Handler?`) 仅当是服务器命令时调用
返回：
(`boolean`) 如果客户端已停止或正在停止，则为 true；否则为 false

Client:notify(`{method}`, `{params}`) [Client:notify()](#Client%3Anotify())  
发送通知到 LSP 服务器。
参数：
`{method}` (`string`) LSP 方法名。
`{params}` (`table?`) LSP 请求参数。
返回：
(`boolean`) 表示通知是否成功的状态。如果是 false，则客户端已关闭。

Client:on_attach(`{bufnr}`) [Client:on_attach()](#Client%3Aon_attach())  
运行客户端配置中的 on_attach 函数（如果已定义）。对缓冲区局部设置有用。
参数：
`{bufnr}` (`integer`) 缓冲区编号

Client:request(`{method}`, `{params}`, `{handler}`, `{bufnr}`) [Client:request()](#Client%3Arequest())  
发送请求到服务器。
这是对 `{client.rpc.request}` 的薄包装，带有一些额外的能力检查和处理程序可用性检查。
参数：
`{method}` (`string`) LSP 方法名。
`{params}` (`table?`) LSP 请求参数。
`{handler}` (`lsp.Handler?`) 此方法的 [lsp-handler](https://neovim.io/doc/user/lsp.html#lsp-handler)。
`{bufnr}` (`integer?`)（默认: 0）缓冲区句柄，或 0 表示当前。
返回（多个）：
(`boolean`) 表示请求是否成功的状态。如果是 `false`，则始终为 `false`（客户端已关闭）。(`integer?`) request_id 可用于 [Client:cancel_request()](https://neovim.io/doc/user/lsp.html#Client%3Acancel_request())。请求失败时为 nil。

Client:request_sync(`{method}`, `{params}`, `{timeout_ms}`, `{bufnr}`) [Client:request_sync()](#Client%3Arequest_sync())  
发送请求到服务器并同步等待响应。
参数：
`{method}` (`string`) LSP 方法名。
`{params}` (`table`) LSP 请求参数。
`{timeout_ms}` (`integer?`) 最大等待结果的时间（以毫秒为单位）。默认为 1000
`{bufnr}` (`integer?`)（默认: 0）缓冲区句柄，或 0 表示当前。
返回（多个）：
(`{err: lsp.ResponseError?, result:any}?`) 来自 [lsp-handler](https://neovim.io/doc/user/lsp.html#lsp-handler) 的 `result` 和 `err`。请求失败时为 nil (`string?`) err 超时、取消或错误时的 `err` 是描述失败原因的字符串。

Client:stop(`{force}`) [Client:stop()](#Client%3Astop())  
停止客户端，可选地强制停止。
默认情况下，它将请求服务器关闭。如果你请求停止以前已请求关闭的客户端，它将自动升级并强制关闭。
参数：
`{force}` (`boolean?`)

Client:supports_method(`{method}`, `{bufnr}`) [Client:supports_method()](#Client%3Asupports_method())  
检查客户端是否支持给定的方法。对于未知的 off-spec 方法始终返回 true。
**注意：** 一些语言服务器能力可能是文件特定的。
参数：
`{method}` (`string`)
`{bufnr}` (`integer?`)

Client:stop(`{force}`) [Client:stop()](#Client%3Astop())  
停止客户端，可选地强制停止。
默认情况下，它将请求服务器关闭。如果你请求停止以前已请求关闭的客户端，它将自动升级并强制关闭。
参数：
`{force}` (`boolean?`)

Client:supports_method(`{method}`, `{bufnr}`) [Client:supports_method()](#Client%3Asupports_method())  
检查客户端是否支持给定的方法。对于未知的 off-spec 方法始终返回 true。
**注意：** 一些语言服务器能力可能是文件特定的。
参数：
`{method}` (`string`)
`{bufnr}` (`integer?`)

The `vim.lsp.buf_…` functions perform operations for LSP clients attached to the current buffer.

Fields:
`{on_list}` (`fun(t: vim.lsp.LocationOpts.OnList)`) list-handler replacing the default handler. Called for any non-empty result. This table can be used with [setqflist()](https://neovim.io/doc/user/vimfn.html#setqflist()) or [setloclist()](https://neovim.io/doc/user/vimfn.html#setloclist())。例如：
```
local function on_list(options)
  vim.fn.setqflist({}, ' ', options)
  vim.cmd.cfirst()
end
vim.lsp.buf.definition({ on_list = on_list })
vim.lsp.buf.references(nil, { on_list = on_list })
```
`{loclist}` (`boolean`) 是否在默认处理程序中使用 [location-list](https://neovim.io/doc/user/quickfix.html#location-list) 或 [quickfix](https://neovim.io/doc/user/quickfix.html#quickfix) 列表。
```
vim.lsp.buf.definition({ loclist = true })
vim.lsp.buf.references(nil, { loclist = false })
```
Fields:
`{reuse_win}` (`boolean`) 如果缓冲区已打开，则跳转到现有窗口。
Fields:
`{title}` (`string`) 列表标题。
`{context}` (`{ bufnr: integer, method: string }`) `lsp-handler` 中 `ctx` 的子集。
Fields:
`{silent}` (`boolean`)
Fields:
`{silent}` (`boolean`)
[vim.lsp.buf.add_workspace_folder()](#vim.lsp.buf.add_workspace_folder())  
add_workspace_folder(`{workspace_folder}`) 将路径处的文件夹添加到工作区文件夹。如果未提供 `{path}`，用户将被提示输入路径使用 [input()](https://neovim.io/doc/user/vimfn.html#input())。
参数：
`{workspace_folder}` (`string?`)

code_action(`{opts}`) [vim.lsp.buf.code_action()](#vim.lsp.buf.code_action())  
选择光标位置可用的代码操作（LSP："textDocument/codeAction" 请求）。
参数：
`{opts}` (`table?`) 包含以下字段的表：
`{context}` (`lsp.CodeActionContext`) 对应 LSP 规范中的 `CodeActionContext`：
`{diagnostics}` (`table`) LSP `Diagnostic[]`。如果没有提供，则从当前位置推断。
`{only}` (`table`) 用于过滤代码操作的 LSP `CodeActionKind` 列表。大多数语言服务器支持如 `refactor` 或 `quickfix` 的值。
`{triggerKind}` (`integer`) 请求代码操作的原因。
`{filter}` (`fun(x: lsp.CodeAction|lsp.Command):boolean`) 接收 `CodeAction` 并返回布尔值的谓词。
`{apply}` (`boolean`) 如果为 true，并且只有一个剩余操作（经过过滤后），则应用该操作而不询问用户。
`{range}` (`{start: integer[], end: integer[]}`) 要请求代码操作的范围。在可视模式下默认为选定区域。表必须包含 `start` 和 `end` 键，带有 `{row,col}` 元组，使用标记索引。见 [api-indexing](https://neovim.io/doc/user/api.html#api-indexing)
另请参阅：
vim.lsp.protocol.CodeActionTriggerKind
declaration(`{opts}`) [vim.lsp.buf.declaration()](#vim.lsp.buf.declaration())  
跳转到光标下符号的声明。
definition(`{opts}`) [vim.lsp.buf.definition()](#vim.lsp.buf.definition())  
跳转到光标下符号的定义。
document_highlight() [vim.lsp.buf.document_highlight()](#vim.lsp.buf.document_highlight())  
发送请求到服务器解析文档高亮显示当前文本文档位置。该请求可以通过键映射或事件如 `CursorHold` 触发，例如：
```
autocmd CursorHold  <buffer> lua vim.lsp.buf.document_highlight()
autocmd CursorHoldI <buffer> lua vim.lsp.buf.document_highlight()
autocmd CursorMoved <buffer> lua vim.lsp.buf.clear_references()
```
format(`{opts}`) [vim.lsp.buf.format()](#vim.lsp.buf.format())  
使用附加（和可选过滤的）语言客户端格式化缓冲区。
参数：
`{opts}` (`table?`) 包含以下字段的表：
`{timeout_ms}` (`integer`, 默认: `1000`) 阻塞格式化请求的时间（以毫秒为单位）。如果 async=true 无效果。
`{bufnr}` (`integer`, 默认: 当前缓冲区) 限制格式化到附加到给定缓冲区的客户端。
`{filter}` (`fun(client: vim.lsp.Client): boolean?`) 用于过滤客户端的谓词。接收客户端作为参数并必须返回布尔值。匹配谓词的客户端包括在内。例如：
```
vim.lsp.buf.format {
  filter = function(client) return client.name ~= "ts_ls" end
}
```
`{async}` (`boolean`, 默认: false) 如果为 true 方法不会阻塞。异步格式化期间编辑缓冲区可能导致意外更改。
`{id}` (`integer`) 限制格式化到 ID 与字段匹配的客户端（client.id）。
`{name}` (`string`) 限制格式化到名称与字段匹配的客户端（client.name）。
`{range}` (`{start:[integer,integer],end:[integer, integer]}|{start:[integer,integer],end:[integer,integer]}[]`, 默认: 当前选择在可视模式下，其他模式为 nil，格式化整个缓冲区) 要格式化的范围。表必须包含 `start` 和 `end` 键，带有 `(1,0)` 索引的 `{row,col}` 元组。也可以是包含 `start` 和 `end` 键的表列表，这种情况下需要支持 `textDocument/rangesFormatting`。
hover(`{config}`) [vim.lsp.buf.hover()](#vim.lsp.buf.hover())  
在浮动窗口中显示光标下符号的悬停信息。移动光标时窗口将被关闭。调用两次函数将进入浮动窗口（因此默认情况下，“KK”将打开悬停窗口并聚焦）。
在浮动窗口中，所有命令和映射都可以正常使用，除了“q”关闭窗口。你可以像对待其他缓冲区一样滚动内容。
**注意：**
要禁用悬停高亮，请在配置中添加以下内容：
```
vim.api.nvim_create_autocmd('ColorScheme', {
  callback = function()
    vim.api.nvim_set_hl(0, 'LspReferenceTarget', {})
  end,
})
```
implementation(`{opts}`) [vim.lsp.buf.implementation()](#vim.lsp.buf.implementation())  
在 quickfix 窗口中列出光标下符号的所有实现。
incoming_calls() [vim.lsp.buf.incoming_calls()](#vim.lsp.buf.incoming_calls())  
在 [quickfix](https://neovim.io/doc/user/quickfix.html#quickfix) 窗口中列出光标下符号的所有调用站点。如果符号可以解析为多个项目，用户可以在 [inputlist()](https://neovim.io/doc/user/vimfn.html#inputlist()) 中选择一个。
outgoing_calls() [vim.lsp.buf.outgoing_calls()](#vim.lsp.buf.outgoing_calls())  
在 [quickfix](https://neovim.io/doc/user/quickfix.html#quickfix) 窗口中列出由光标下符号调用的所有项目。如果符号可以解析为多个项目，用户可以在 [inputlist()](https://neovim.io/doc/user/vimfn.html#inputlist()) 中选择一个。
references(`{context}`, `{opts}`) [vim.lsp.buf.references()](#vim.lsp.buf.references())  
在 quickfix 窗口中列出光标下符号的所有引用。
参数：
`{context}` (`lsp.ReferenceContext?`) 请求上下文
[vim.lsp.buf.remove_workspace_folder()](#vim.lsp.buf.remove_workspace_folder())  
remove_workspace_folder(`{workspace_folder}`) 从工作区文件夹中移除路径处的文件夹。如果 `{path}` 未提供，用户将被提示输入路径使用 [input()](https://neovim.io/doc/user/vimfn.html#input())。
参数：
`{workspace_folder}` (`string?`)

rename(`{new_name}`, `{opts}`) [vim.lsp.buf.rename()](#vim.lsp.buf.rename())  
重命名光标下符号的所有引用。
参数：
`{new_name}` (`string?`) 如果未提供，用户将被提示输入新名称使用 [vim.ui.input()](https://neovim.io/doc/user/lua.html#vim.ui.input())。
`{opts}` (`table?`) 额外选项：
`{overwrite}` (`boolean`)
`{ignoreIfExists}` (`boolean`)
[vim.lsp.util.show_document()](#vim.lsp.util.show_document())  
show_document(`{location}`, `{position_encoding}`, `{opts}`) 显示文档并可选跳转到位置。
参数：
`{location}` (`lsp.Location|lsp.LocationLink`)
`{position_encoding}` (`'utf-8'|'utf-16'|'utf-32'?`)
`{opts}` (`table?`) 包含以下字段的表：
`{reuse_win}` (`boolean`) 如果缓冲区已打开，则跳转到现有窗口。
`{focus}` (`boolean`) 是否尽可能聚焦/跳转到位置（默认: true）
返回：
(`boolean`) `true` 如果成功

[vim.lsp.util.symbols_to_items()](#vim.lsp.util.symbols_to_items())  
symbols_to_items(`{symbols}`, `{bufnr}`, `{position_encoding}`) 将符号转换为快速修复列表项。
参数：
`{symbols}` (`lsp.DocumentSymbol[]|lsp.SymbolInformation[]`) 符号列表
`{bufnr}` (`integer?`) 缓冲区句柄或 0 表示当前，缺省为当前
`{position_encoding}` (`'utf-8'|'utf-16'|'utf-32'?`) 缺省为缓冲区的第一个客户端
返回：
(`vim.quickfix.entry[]`) 见 [setqflist()](https://neovim.io/doc/user/vimfn.html#setqflist())

The `vim.lsp.log` module provides logging for the Nvim LSP client.
When debugging language servers, it is helpful to enable extra-verbose logging of the LSP client RPC events. Example:
```
vim.lsp.set_log_level 'trace'
require('vim.lsp.log').set_format_func(vim.inspect)
```
Then try to run the language server, and open the log with:
```
:lua vim.cmd('tabnew ' .. vim.lsp.get_log_path())
```
(Or use `:LspLog` if you have nvim-lspconfig installed.)
**Note:**
Remember to DISABLE verbose logging ("debug" or "trace" level), else you may encounter performance issues.
"ERROR" messages containing "stderr" only indicate that the log was sent to stderr. Many servers send harmless messages via stderr.

Return:
(`string`) log filename
Return:
(`integer`) current log level
Parameters:
`{handle}` (`function`) apply to logging arguments, pass vim.inspect for multi-line formatting
Parameters:
`{level}` (`integer`) log level
Return:
(`boolean`) true if would log, false if not

Fields:
`{request}` (`fun(method: string, params: table?, callback: fun(err?: lsp.ResponseError, result: any), notify_reply_callback?: fun(message_id: integer)):boolean,integer?`) 见 [vim.lsp.rpc.request()](https://neovim.io/doc/user/lsp.html#vim.lsp.rpc.request())
`{is_closing}` (`fun(): boolean`) Indicates if the RPC is closing.
`{terminate}` (`fun()`) Terminates the RPC client.
connect(`{host_or_path}`, `{port}`) [vim.lsp.rpc.connect()](#vim.lsp.rpc.connect())  
Create a LSP RPC client factory that connects to either:
a named pipe (windows)
a domain socket (unix)
a host and port via TCP
Return a function that can be passed to the `cmd` field for [vim.lsp.start()](https://neovim.io/doc/user/lsp.html#vim.lsp.start()).
Parameters:
`{host_or_path}` (`string`) 连接到的主机或管道域套接字的路径
`{port}` (`integer?`) TCP 端口。如果不存在，第一个参数必须是管道
Return:
(`fun(dispatchers: vim.lsp.rpc.Dispatchers): vim.lsp.rpc.PublicClient`)

Parameters:
`{err}` (`table`) 错误对象
Return:
(`string`) error_message 格式化错误消息

notify(`{method}`, `{params}`) [vim.lsp.rpc.notify()](#vim.lsp.rpc.notify())  
发送通知到 LSP 服务器。
参数：
`{method}` (`string`) 调用的 LSP 方法
`{params}` (`table?`) 调用的 LSP 方法参数
Return:
(`boolean`) `true` 如果通知可以发送，`false` 如果不能

[vim.lsp.rpc.request()](#vim.lsp.rpc.request())  
request(`{method}`, `{params}`, `{callback}`, `{notify_reply_callback}`) 发送请求到 LSP 服务器并在响应时运行 `{callback}`。
参数：
`{method}` (`string`) 调用的 LSP 方法
`{params}` (`table?`) 调用的 LSP 方法参数
`{callback}` (`fun(err: lsp.ResponseError?, result: any)`) 调用的回调
`{notify_reply_callback}` (`fun(message_id: integer)?`) 请求不再挂起时调用的回调
Return (multiple):
(`boolean`) success `true` 如果请求可以发送，`false` 如果不能 (`integer?`) message_id 如果请求可以发送，`nil` 如果不能

[vim.lsp.rpc.rpc_response_error()](#vim.lsp.rpc.rpc_response_error())  
rpc_response_error(`{code}`, `{message}`, `{data}`) 创建 RPC 响应表 `error` 发送到 LSP 响应。
参数：
`{code}` (`integer`) RPC 错误代码定义，见 `vim.lsp.protocol.ErrorCodes`
`{message}` (`string?`) 发送到服务器的任意消息
`{data}` (`any?`) 发送到服务器的任意数据
Return:
(`lsp.ResponseError`)

See also:
lsp.ErrorCodes 见 `vim.lsp.protocol.ErrorCodes`

start(`{cmd}`, `{dispatchers}`, `{extra_spawn_params}`) [vim.lsp.rpc.start()](#vim.lsp.rpc.start())  
启动 LSP 服务器进程并创建 LSP RPC 客户端对象与其交互。与生成的进程通信通过 stdio 进行。对于通过 TCP 的通信，手动启动进程并使用 [vim.lsp.rpc.connect()](https://neovim.io/doc/user/lsp.html#vim.lsp.rpc.connect())
参数：
`{cmd}` (`string[]`) 启动 LSP 服务器的命令。
`{dispatchers}` (`table?`) LSP 消息类型的调度器。
`{notification}` (`fun(method: string, params: table)`)
`{server_request}` (`fun(method: string, params: table): any?, lsp.ResponseError?`)
`{on_exit}` (`fun(code: integer, signal: integer)`)
`{on_error}` (`fun(code: integer, err: any)`)
`{extra_spawn_params}` (`table?`) LSP 服务器进程的额外上下文。
`{cwd}` (`string`) LSP 服务器进程的工作目录
`{detached}` (`boolean`) 将 LSP 服务器进程与当前进程分离
`{env}` (`table<string,string>`) LSP 服务器进程的额外环境变量。见 [vim.system()](https://neovim.io/doc/user/lua.html#vim.system())

Return:
(`lsp.ClientCapabilities`)

Parameters:
`{server_capabilities}` (`table`) 服务器支持的能力表
Return:
(`lsp.ServerCapabilities?`) 能力表归一化