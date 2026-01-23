---
tags:
  - vim
---

### 翻译为中文				*<Leader>* *mapleader*

要定义一个使用 `"g:mapleader"` 变量的映射，可以使用特殊的字符串 `<Leader>`。它会被替换为 `"g:mapleader"` 的字符串值。如果 `"g:mapleader"` 没有被设置或者为空，那么会使用反斜杠 `\` 作为替代。例如：  
```vim
	map <Leader>A  oanother line<Esc>
```
其作用等同于：
```vim
	map \A  oanother line<Esc>
```

但在执行以下命令后：
```vim
	let mapleader = ","
```
它的作用就变成了：
```vim
	map ,A  oanother line<Esc>
```

请注意，`"g:mapleader"` 的值是在映射定义时使用的。在此之后更改 `"g:mapleader"` 不会影响已经定义好的映射。

--- 