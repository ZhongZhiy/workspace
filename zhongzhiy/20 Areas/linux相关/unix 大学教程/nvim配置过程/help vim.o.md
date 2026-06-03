---
tags:
  - vim
---


---

### *vim.o*
获取或设置 |选项|（options）。其行为类似于 `:set` 命令，因此针对缓冲区/窗口的作用域选项将默认作用于当前缓冲区/窗口。如果访问了无效的键，将会报错。

#### 示例： 
```lua
    vim.o.cmdheight = 4
    print(vim.o.columns)
    print(vim.o.foo)     -- 错误：无效的键
```

---

如果你还有其他需要翻译的内容，请继续告诉我！