
---

## `-E`：只做 **E**xecute preprocessor（预处理）

- 含义：停在预处理阶段（展开宏、处理 `#include/#define`），不继续编译。
    
- 历史：早期 `cc` 就有 `-E` 选项，E 被普遍理解为 **preprocessor** 的“输出到 stdout（执行预处理）”。  
    你可以把它记成 **E = (pr)Eprocess** 或 **E = Expand macros**。
    

用法：

```bash
gcc -E main.c -o main.i
```

---

## `-S`：输出 **S**ource of assembly（汇编源码）

- 含义：编译到汇编文本 `.s` 就停。
    
- 历史：同样来自 Unix `cc`。S 就是 **Source (assembly)** 的意思：输出汇编源代码，而不是目标文件。
    

```bash
gcc -S main.c -o main.s
```

---

## `-c`：只到 **c**ompile / create object（生成 .o）

- 含义：生成目标文件 `.o`，不链接。
    
- 历史：老 `cc` 时代就叫 “compile only”。  
    `-c` 很直白：**compile**。
    

```bash
gcc -c main.c
```

---

## `-o`：指定 **o**utput file（输出文件名）

- 含义：给最终/中间输出起名。
    
- 历史：这可能是最“古老又通用”的选项之一，几乎所有 Unix 工具都有 `-o`，就是 **output**。
    

```bash
gcc main.c -o main
```

---

## `-I`：**I**nclude path（头文件搜索路径）

- 含义：添加 `#include` 查找目录。
    
- 历史：来自传统 C 编译器选项，I = **Include**。
    

```bash
gcc main.c -I./include
```

---

## `-L`：Library path（库搜索路径）

- 含义：添加链接器查找库的目录。
    
- 历史：`ld`（Unix 链接器）就用 `-L`，gcc 直接沿用。  
    L = **Library**（path）。
    

```bash
gcc main.c -L./lib
```

---

## `-lxxx`：link with **l**ibrary xxx（链接库）

- 含义：让链接器找 `libxxx.so` 或 `libxxx.a`。
    
- 历史：也是 `ld` 的传统。  
    `-lutil` 会匹配 `libutil.*`，这就是 Unix 的库命名约定：以 `lib` 开头。
    

```bash
gcc main.c -lm     # 链接 libm 数学库
```

---

## `-g`：生成 **g**db 调试信息

- 含义：在二进制里塞 DWARF 等调试信息。
    
- 历史：最早是为了 **gdb**（GNU Debugger），所以 g = **gdb** / **debugging**。
    

```bash
gcc -g main.c -o main
```

---

## `-O0/-O1/-O2/-O3`：**O**ptimization level（优化等级）

- 含义：开启优化，数字越大越激进。
    
- 历史：O = **Optimize**。早期编译器就有类似分级优化。
    

```bash
gcc -O2 main.c
```

---

## `-Wall` / `-Wextra`：**W**arnings

- `-Wxxx` 家族都是 warning 开关。
    
- `-Wall` 名字有点误导：不是“所有警告”，而是“常用的一大批警告”。
    
- 历史：W = **Warning**。
    

```bash
gcc -Wall -Wextra main.c
```

---

## `-DNAME[=val]`：**D**efine macro（定义宏）

- 含义：等价于在代码前加 `#define NAME val`
    
- 历史：D = **Define**，也是继承自早期 cc。
    

```bash
gcc -DDEBUG main.c
gcc -DNUM=10 main.c
```

---

## `-Uname`：**U**ndefine macro（取消宏定义）

- 含义：把某个宏取消掉（即便它在代码/命令行里本来有定义）
    
- 历史：U = **Undefine**。
    

```bash
gcc -UDEBUG main.c
```

---

## `-std=c11`：standard（语言标准）

- 含义：指定按哪个 C/C++ 标准编译。
    
- 历史：C 标准化之后加的选项，名字就是 **standard** 缩写。
    

```bash
gcc -std=c11 main.c
```

---

## 为啥都是一个字母？

这真是历史包袱 + Unix 风格：

1. **早期终端打字慢，命令越短越好。**
    
2. 选项来源分散：`cc`、`cpp`（预处理器）、`as`（汇编器）、`ld`（链接器）各有一套，gcc 统一接口时就“全收了”。
    
3. 后来为了兼容老 Makefile/脚本，这些短选项一直保留。
    

---

如果你还想挖更深，比如某个特别怪的选项（`-fPIC`、`-pipe`、`-pedantic` 之类）为啥这么叫，丢给我我继续八卦+解释。