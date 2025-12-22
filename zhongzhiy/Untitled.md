下面按和前两份**完全一样的作业格式**，把你给的 `switch-case` 版本汇编（函数 `f`）做成**逐条解析说明文档**：每条指令解释功能，并把它对应回 `switch(x){case...}` 的语义。并结合课件里“switch 可用比较跳转链 or 跳转表”的观点指出：**你这份是比较跳转链（不是 jump table）**。

---

# 说明文档：switch-case 语句（switch.c / switch.asm）

## 1. 实验目的

编写包含 **switch-case** 的 C 程序，生成可执行文件并反汇编；对自己编写部分（主要是 `f(int x)`）的机器级代码逐条解析，说明 switch-case 在机器级如何通过 **cmp + 条件跳转（jcc）+ 无条件跳转（jmp）** 实现。

---

## 2. 高级语言逻辑（与汇编对应）

从你给出的赋值常量可以还原出 switch 大致逻辑：

- case 0 → r = 0x0b = 11
    
- case 1 → r = 0x16 = 22
    
- case 2 → r = 0x21 = 33
    
- case 3 → r = 0x2c = 44
    
- default → r = 0x63 = 99
    

等价于：

```c
int f(int x) {
    int r = 0;
    switch (x) {
        case 0: r = 11; break;
        case 1: r = 22; break;
        case 2: r = 33; break;
        case 3: r = 44; break;
        default: r = 99; break;
    }
    return r;
}
```

---

## 3. 课件要点对应（你这份属于哪种实现）

课件中提到 switch 的实现常见两类：  
1）**比较/跳转链**（case 较少或编译策略如此）  
2）**跳转表（jump table）**（case 多且连续时常见）

你这段汇编没有 `jmp [table + index*8]` 这类“间接跳转表”指令，而是大量 `cmp + je/jg + jmp`，因此属于：  
✅ **比较 + 条件跳转链（if-else 级联实现的 switch）**。

---

## 4. 反汇编逐条解析：函数 f

### 汇编片段

（你提供的原样）

```
0000000000001119 <f>:
1119: 55                    push   rbp
111a: 48 89 e5              mov    rbp,rsp
111d: 89 7d ec              mov    DWORD PTR [rbp-0x14],edi
1120: c7 45 fc 00 00 00 00  mov    DWORD PTR [rbp-0x4],0x0
1127: 83 7d ec 03           cmp    DWORD PTR [rbp-0x14],0x3
112b: 74 3b                 je     1168 <f+0x4f>
112d: 83 7d ec 03           cmp    DWORD PTR [rbp-0x14],0x3
1131: 7f 3e                 jg     1171 <f+0x58>
1133: 83 7d ec 02           cmp    DWORD PTR [rbp-0x14],0x2
1137: 74 26                 je     115f <f+0x46>
1139: 83 7d ec 02           cmp    DWORD PTR [rbp-0x14],0x2
113d: 7f 32                 jg     1171 <f+0x58>
113f: 83 7d ec 00           cmp    DWORD PTR [rbp-0x14],0x0
1143: 74 08                 je     114d <f+0x34>
1145: 83 7d ec 01           cmp    DWORD PTR [rbp-0x14],0x1
1149: 74 0b                 je     1156 <f+0x3d>
114b: eb 24                 jmp    1171 <f+0x58>
114d: c7 45 fc 0b 00 00 00  mov    DWORD PTR [rbp-0x4],0xb
1154: eb 23                 jmp    1179 <f+0x60>
1156: c7 45 fc 16 00 00 00  mov    DWORD PTR [rbp-0x4],0x16
115d: eb 1a                 jmp    1179 <f+0x60>
115f: c7 45 fc 21 00 00 00  mov    DWORD PTR [rbp-0x4],0x21
1166: eb 11                 jmp    1179 <f+0x60>
1168: c7 45 fc 2c 00 00 00  mov    DWORD PTR [rbp-0x4],0x2c
116f: eb 08                 jmp    1179 <f+0x60>
1171: c7 45 fc 63 00 00 00  mov    DWORD PTR [rbp-0x4],0x63
1178: 90                    nop
1179: 8b 45 fc              mov    eax,DWORD PTR [rbp-0x4]
117c: 5d                    pop    rbp
117d: c3                    ret
```

---

## 5. 逐条解释（按“栈帧/参数/分支判定/case赋值/统一出口返回”）

1. 栈帧建立 + 保存参数
	- `1119: push rbp`  
    保存调用者的 `rbp`，为建立 `f` 的栈帧做准备。
    
	- `111a: mov rbp, rsp`  
    建立 `f` 的栈帧基址，后续用 `[rbp-偏移]` 访问局部变量与保存的参数。
    
	- `111d: mov DWORD PTR [rbp-0x14], edi`  
    把传入参数 `x`（第 1 个整型参数寄存器 `edi`）保存到栈帧位置 `[rbp-0x14]`。
    
	- `1120: mov DWORD PTR [rbp-0x4], 0x0`  
    初始化局部变量 `r = 0`（`r` 存在 `[rbp-0x4]`）。
    


2. 分支判定区（cmp + jcc 组成的“switch 判断链”）

	- `1127: cmp [rbp-0x14], 0x3`  
    比较 `x` 和 3。
    
	- `112b: je 1168`  
    若 `x == 3`，跳到 1168（case 3：赋值 44）。
    
	- `112d: cmp [rbp-0x14], 0x3`  
    再比较一次 `x` 和 3（编译器在 -O0 下常出现重复比较，逻辑上是冗余但合法）。
    
	- `1131: jg 1171`  
    若 `x > 3`，跳到 1171（default：赋值 99）。  
    说明：case 只覆盖 0~3，`x>3` 必走 default。
    
	- `1133: cmp [rbp-0x14], 0x2`  
    比较 `x` 和 2。
    
	- `1137: je 115f`  
    若 `x == 2`，跳到 115f（case 2：赋值 33）。
    
	- `1139: cmp [rbp-0x14], 0x2`  
    再次比较 `x` 和 2（同样属于 -O0 下的重复判断风格）。
    
	- `113d: jg 1171`  
    若 `x > 2`，跳到 default（1171）。  
    因为在这里已经排除了 `x==3`，若还 `x>2`，只可能是 `x==3` 或 `x>3`，两者都应 default/或上面已处理 3，这里统一导向 default。
    
	- `113f: cmp [rbp-0x14], 0x0`  
    比较 `x` 和 0。
    
	- `1143: je 114d`  
    若 `x == 0`，跳到 114d（case 0：赋值 11）。
    
	- `1145: cmp [rbp-0x14], 0x1`  
    比较 `x` 和 1。
    
	- `1149: je 1156`  
    若 `x == 1`，跳到 1156（case 1：赋值 22）。
    
	- `114b: jmp 1171`  
    前面都没匹配上（既不是 0/1/2/3，也不是大于范围被抓到），就无条件跳到 default（1171）。  
    这覆盖了例如 `x < 0` 的情况：也应走 default。
    


3. 各 case 的赋值段（对应 switch 的 case 代码块）

	- `114d: mov [rbp-0x4], 0xb`  
    case 0：`r = 11`（0x0b）。
    
	- `1154: jmp 1179`  
    跳到统一出口（相当于 C 里的 `break;`，避免“落入”后续 case）。
    



	- `1156: mov [rbp-0x4], 0x16`  
    case 1：`r = 22`（0x16）。
    
	- `115d: jmp 1179`  
    跳到统一出口（break）。
    

	- `115f: mov [rbp-0x4], 0x21`  
    case 2：`r = 33`（0x21）。
    
	- `1166: jmp 1179`  
    跳到统一出口（break）。
    

	- `1168: mov [rbp-0x4], 0x2c`  
    case 3：`r = 44`（0x2c）。
    
	- `116f: jmp 1179`  
    跳到统一出口（break）。
    

4. default 段

	- `1171: mov [rbp-0x4], 0x63`  
    default：`r = 99`（0x63）。
    
	- `1178: nop`  
    空操作，占位指令，对程序逻辑无影响（常见于对齐/调试/填充）。
    

5. 统一出口：返回值与退栈

	- `1179: mov eax, DWORD PTR [rbp-0x4]`  
    把 `r` 取到 `eax`，作为函数返回值（返回值寄存器）。
    
	- `117c: pop rbp`  
    恢复调用者 `rbp`，撤销当前函数栈帧。
    
	- `117d: ret`  
    返回到调用者。
    

## 6. 结构总结：switch 在机器级的实现方式

- 该 `switch` 并未使用跳转表（jump table），而是用**比较/跳转链**实现：
    
    - `cmp x, 常量`
        
    - `je case`（相等跳转）
        
    - `jg default`（超范围跳转）
        
    - `jmp default`（全部不匹配跳 default）
        
- 每个 case 末尾 `jmp 1179` 相当于 C 里的 `break`，避免继续执行后续 case。
    

---

## 7. main 函数说明（你给的 main 很简化）

```
000000000000117e <main>:
117e: push rbp
117f: mov rbp,rsp
1182: mov eax,0x0
1187: pop rbp
1188: ret
```

该 `main` 只建立/撤销栈帧并返回 0，说明此可执行文件主要用于展示 `f` 的 switch-case 机器级实现（`main` 未实际调用 `f`，可能是编译时的简化版本或示例截取）。

---

如果你想让说明文档更“像老师要求的解析报告”，我也可以把上面内容进一步补上两张“结构对照图”的文字版（如：判定链流程图、case→出口跳转图），让它更符合“图片信息很多”的课件风格。