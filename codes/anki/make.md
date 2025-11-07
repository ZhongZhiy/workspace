# make.

## Make 的核心思想是什么？

<!-- notecardId: 1760340530363 -->

“文件之间的因果关系”：如果依赖文件更新，则重新生成目标。



## Make 是什么系统？

<!-- notecardId: 1760340530369 -->

一个自动化的重建系统。



## make 什么时候会重新编译？

<!-- notecardId: 1760340530372 -->

当依赖文件比目标文件更新时。



## Makefile 的作用是什么？

<!-- notecardId: 1760340530375 -->

描述文件之间的依赖关系和生成方式。



## 一条 Makefile 规则由哪三部分组成？

<!-- notecardId: 1760340530379 -->

目标（target）、依赖（dependency）、命令（command）。



## 规则的基本格式是什么？

<!-- notecardId: 1760340530383 -->

```
目标: 依赖1 依赖2 ...
<Tab>命令
```



## 规则中的“目标”指什么？

<!-- notecardId: 1760340530387 -->

要生成的文件。



## 规则中的“依赖”指什么？

<!-- notecardId: 1760340530390 -->

生成目标所需的文件。



## 规则中的“命令”指什么？

<!-- notecardId: 1760340530394 -->

生成目标所需执行的 shell 命令。



## make 如何判断是否执行命令？

<!-- notecardId: 1760340530398 -->

比较目标与依赖的时间戳，若依赖较新则执行命令。



## 命令前的 `@` 有什么作用？

<!-- notecardId: 1760340530401 -->

执行但不打印命令。



## 命令前的 `-` 有什么作用？

<!-- notecardId: 1760340530404 -->

出错时忽略错误并继续执行。



## 变量在 Makefile 中的作用是什么？

<!-- notecardId: 1760340530408 -->

存储并复用文本片段或参数。



## 变量的引用语法是什么？

<!-- notecardId: 1760340530410 -->

`$(变量名)`



## `=` 与 `:=` 的区别是什么？

<!-- notecardId: 1760340530414 -->

`=` 为惰性展开，`:=` 为立即展开。



## `$@` 表示什么？

<!-- notecardId: 1760340530417 -->

当前规则的目标文件名。



## `$<` 表示什么？

<!-- notecardId: 1760340530421 -->

第一个依赖文件。



## `$^` 表示什么？

<!-- notecardId: 1760340530424 -->

所有依赖文件（去重后）。



## 什么是伪目标（Phony Target）？

<!-- notecardId: 1760340530428 -->

不对应实际文件，只执行命令的目标。



## 如何声明伪目标？

<!-- notecardId: 1760340530431 -->

使用 `.PHONY: 目标名`



## 模式规则（Pattern Rule）用于什么？

<!-- notecardId: 1760340530433 -->

定义通用模板规则（如 `%.o: %.cpp`）。



## `%.o: %.cpp` 表示什么意思？

<!-- notecardId: 1760340530436 -->

所有 `.o` 文件由同名 `.cpp` 文件编译生成。



## make 的执行流程第一步是什么？

<!-- notecardId: 1760340530440 -->

读取并解析 Makefile。



## make 的执行流程第二步是什么？

<!-- notecardId: 1760340530442 -->

寻找第一个目标（默认目标）。



## make 的执行流程第三步是什么？

<!-- notecardId: 1760340530445 -->

检查目标的依赖是否存在或是否比目标新。



## make 的执行流程第四步是什么？

<!-- notecardId: 1760340530449 -->

若依赖更新，则执行相应命令。



## make 的执行流程最后一步是什么？

<!-- notecardId: 1760340530451 -->

递归构建所有依赖，直到全部最新。



## Makefile 中如何编写条件语句？

<!-- notecardId: 1760340530454 -->

使用 `ifeq` / `ifneq` / `else` / `endif`。



## `ifeq (A, B)` 的作用是什么？

<!-- notecardId: 1760340530457 -->

当 A 等于 B 时执行其内的代码块。



## `ifneq (A, B)` 的作用是什么？

<!-- notecardId: 1760340530460 -->

当 A 不等于 B 时执行其内的代码块。



## 条件语句在 Makefile 中常用于什么？

<!-- notecardId: 1760340530463 -->

控制编译模式、系统差异、文件存在性等。



## 在 Makefile 中如何根据操作系统选择命令？

<!-- notecardId: 1760340530466 -->

```makefile
ifeq ($(OS),Windows_NT)
	RM := del
else
	RM := rm -f
endif
```



## `foreach` 的语法是什么？

<!-- notecardId: 1760340530469 -->

`$(foreach var, list, expression)`



## `foreach` 的作用是什么？

<!-- notecardId: 1760340530473 -->

遍历一个列表并展开生成新的文本。



## `foreach` 会执行命令吗？

<!-- notecardId: 1760340530475 -->

不会，只进行文本展开。如需执行需加分号或放在命令行中。



## `$(subst from,to,text)` 的作用是什么？

<!-- notecardId: 1760340530478 -->

在 `text` 中将所有 `from` 替换为 `to`。



## `$(patsubst pattern,replacement,text)` 的作用是什么？

<!-- notecardId: 1760340530481 -->

对 `text` 中匹配 `pattern` 的部分按模式替换为 `replacement`。



## `$(filter pattern,text)` 的作用是什么？

<!-- notecardId: 1760340530485 -->

保留与 `pattern` 匹配的单词。



## `$(filter-out pattern,text)` 的作用是什么？

<!-- notecardId: 1760340530488 -->

排除与 `pattern` 匹配的单词。



## `$(sort list)` 的作用是什么？

<!-- notecardId: 1760340530491 -->

对列表排序并去除重复项。



## `$(wildcard pattern)` 的作用是什么？

<!-- notecardId: 1760340530495 -->

返回匹配 `pattern` 的文件名列表。



## `$(dir names)` 的功能是什么？

<!-- notecardId: 1760340530498 -->

提取文件路径中的目录部分。



## `$(notdir names)` 的功能是什么？

<!-- notecardId: 1760340530501 -->

提取文件路径中的文件名部分。



## `$(basename names)` 的功能是什么？

<!-- notecardId: 1760340530505 -->

去掉文件扩展名。



## `$(addprefix prefix,names)` 的作用是什么？

<!-- notecardId: 1760340530507 -->

为每个元素添加指定前缀。



## `$(addsuffix suffix,names)` 的作用是什么？

<!-- notecardId: 1760340530510 -->

为每个元素添加指定后缀。



## `include` 在 Makefile 中的作用是什么？

<!-- notecardId: 1760340530514 -->

包含并加载其他 Makefile 文件，实现多文件组织。



## `$(MAKE) -C dir` 表示什么意思？

<!-- notecardId: 1760340530518 -->

进入目录 `dir` 执行 make。



## 什么是 order-only 依赖？

<!-- notecardId: 1760340530520 -->

依赖只保证存在性，不会触发目标重新构建。



## 如何声明 order-only 依赖？

<!-- notecardId: 1760340530523 -->

在依赖前加 `|`，例如：

```makefile
target: normal | order_only
```



## `define` … `endef` 用于什么？

<!-- notecardId: 1760340530526 -->

定义多行模板或代码块。



## `$(call name,arg1,...)` 的作用是什么？

<!-- notecardId: 1760340530529 -->

调用模板或函数并传入参数。



## `$(eval text)` 的作用是什么？

<!-- notecardId: 1760340530533 -->

让传入的文本立即被当作 Makefile 语句执行。



## `eval` 与 `call` 结合的作用是什么？

<!-- notecardId: 1760340530536 -->

动态生成并生效新的规则。



## `$(info text)` 的作用是什么？

<!-- notecardId: 1760340530538 -->

打印普通提示信息。



## `$(warning text)` 的作用是什么？

<!-- notecardId: 1760340530541 -->

打印警告信息但不中断执行。



## `$(error text)` 的作用是什么？

<!-- notecardId: 1760340530544 -->

打印错误信息并终止执行。



## Makefile 高级语法中主要的几类功能是什么？

<!-- notecardId: 1760340530547 -->

条件控制、循环展开、文本处理、模块化、动态规则与调试输出。
