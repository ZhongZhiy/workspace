[[Makefile 高级语法]]
你能主动说“我还没掌握核心逻辑”，这说明你真的在**理解而不是死记**。  
我们现在来系统、直观地讲透 Makefile 的 5 个核心概念：

> **规则 → 依赖 → 命令 → 变量 → 自动变量 → 伪目标**
> 
> 学完这节，你会彻底明白 “make 是怎么知道该编译什么的”。

---

## 🧩 一、Make 的核心思想：

### **“文件之间的因果关系”**

make 是一个**自动化重建系统**。  
它的逻辑是：

> “如果某个文件 A 依赖于文件 B，而 B 比 A 更新，那我就重新生成 A。”

也就是说：

- make **不会盲目重编译**，它只在“依赖改变”时行动。
    
- 一切行为都由一个文件叫 **Makefile** 来描述。
    

---

## 🧱 二、规则（Rule）

规则是 Makefile 的基本单位。  
它描述了一个目标文件（目标）是如何由其他文件（依赖）生成的。

```makefile
目标: 依赖1 依赖2 ...
<Tab>命令
```

🔹 举例：

```makefile
app: main.o adder.o
	g++ main.o adder.o -o app
```

解释：

- 目标：`app`
    
- 依赖：`main.o`、`adder.o`
    
- 命令：执行 `g++ main.o adder.o -o app`
    
- 如果 `app` 不存在，或某个 `.o` 文件比它新，就会重新执行命令。
    

---

## 🔗 三、依赖（Dependency）

依赖描述“我需要先有谁，才能生成我”。

例子：

```makefile
main.o: main.cpp adder.hpp
	g++ -c main.cpp -o main.o
```

含义：

- 要生成 `main.o`，必须有 `main.cpp` 和 `adder.hpp`。
    
- 如果 `main.cpp` 或 `adder.hpp` 有改动，就重新编译。
    

Make 会自动比较时间戳：

> `如果依赖文件比目标新 → 执行命令`

---

## ⚙️ 四、命令（Command）

命令就是在终端执行的 Shell 命令（每行必须用 **Tab** 缩进）。

例：

```makefile
clean:
	rm -f *.o app
```

💡 小技巧：

- `@` 放在命令前 → 执行但不打印命令
    
- `-` 放在命令前 → 出错也继续执行（忽略错误）
    

例：

```makefile
clean:
	-@rm -f *.o app
```

---

## 📦 五、变量（Variable）

Makefile 的变量就是“可复用的文本片段”，像宏替换。

### 定义：

```makefile
CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall
```

### 使用：

```makefile
$(CXX) $(CXXFLAGS) -c main.cpp -o main.o
```

输出展开为：

```
g++ -std=c++17 -O2 -Wall -c main.cpp -o main.o
```

### 四种常见赋值：

|写法|名称|特点|
|---|---|---|
|`=`|惰性展开（延迟计算）||
|`:=`|立即展开（最常用）||
|`?=`|仅在未定义时赋值||
|`+=`|追加内容||

例：

```makefile
CXXFLAGS += -g
```

---

## ⚡ 六、自动变量（Automatic Variables）

这是 make 在执行命令时自动帮你填充的变量。

|变量|含义|举例值|
|---|---|---|
|`$@`|当前规则的目标|`app`|
|`$<`|第一个依赖|`main.cpp`|
|`$^`|所有依赖（去重）|`main.o adder.o`|
|`$?`|所有比目标新的依赖|`main.o`|

例子：

```makefile
app: main.o adder.o
	g++ $^ -o $@
```

等价于：

```
g++ main.o adder.o -o app
```

---

## 🧹 七、伪目标（Phony Target）

有时我们想定义一些“命令任务”，而不是文件。  
例如：

```makefile
clean:
	rm -f *.o app
```

但如果你目录里刚好有个文件叫 `clean`，make 就会认为它是文件，不执行命令。  
解决办法：声明为伪目标：

```makefile
.PHONY: clean
```

---

## 🔁 八、模式规则（Pattern Rule）

可以写成“通用模板”：

```makefile
%.o: %.cpp
	g++ -c $< -o $@
```

表示：

> 所有 `.o` 文件都由同名 `.cpp` 编译而来。  
> 比如 `main.cpp → main.o`，`adder.cpp → adder.o`。

这让你不需要为每个 `.cpp` 写一条规则。

---

## 🧠 九、Make 的执行流程（总结逻辑）

当你在终端运行：

```bash
make
```

Make 会：

1. 读入 Makefile
    
2. 找到第一个目标（默认目标，一般叫 `all`）
    
3. 检查这个目标的依赖文件
    
4. 如果依赖不存在或比目标新，就去执行命令
    
5. 一直递归检查下去，直到所有都最新为止
    

---

## ✅ 十、小例子整合（最小可运行 Makefile）

```makefile
CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall

app: main.o adder.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f *.o app
```

工作流：

```
main.cpp ─┐
          ├─> main.o ─┐
adder.cpp ─┘          ├─> app
                      └─> 链接命令
```

---

我可以下一步帮你画一张「make 工作机制图」——  
从依赖检查、时间戳比较到执行命令，直观地显示整个流程。  
要我画吗？