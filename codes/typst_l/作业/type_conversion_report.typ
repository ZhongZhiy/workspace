#align(
  center,
  [
    #set text(25pt)
    #v(1fr)
  C语言中类型转换规则的调研报告
  #v(1fr)
  ]
)
#pagebreak()

#counter(page).update(1)
#set page(
  numbering: "1/1",
  header:[
    #set text(8pt)
    _finished by 钟智勇_
  ]
)
== 1. 调研目标与方法

#set par(justify: true)
#set page(

)
#align[
*目标*：系统梳理并验证C语言在表达式求值与语义相关的类型转换规则，重点覆盖：
]


- 整型提升（integer promotions）
- 通常算术转换（usual arithmetic conversions）
- 条件运算符 `?:` 的类型合并
- 赋值转换与显式强制类型转换（cast）
- 位运算/移位中的转换与实现定义行为
- 浮点求值与 `float`/`double`/`long double` 的提升
- 指针与空指针常量、`void*` 的转换
- 函数实参在原型存在时/缺失时的不同处理

*方法*：


1. 查阅《C11/C17 标准》与权威教材对相关规则的定义；
2. 选取 GCC/Clang/MSVC 三类主流编译器，在常见数据模型（LP64 与 LLP64）下编译运行验证程序；
3. 记录程序打印的“表达式结果类型”与“求值结果”，对照标准规则进行分析。

> 说明：不同平台的数据模型可能不同（例如 Linux/macOS 通常为 *LP64：`long` 64位*，Windows/MSVC 常为 *LLP64：`long` 32位*）。因此报告中给出“示例输出”，并注明“以某平台为例”；读者需在自己的平台实际运行并粘贴结果。





---

== 2. C语言中的核心类型转换规则（精要）

=== 2.1 整型提升（Integer Promotions）
- `signed char`、`unsigned char`、`short`、`unsigned short`、`_Bool`/`bool` 等 *较小整型* 在参与多数一元/二元运算（如 `+ - ~ !` 或与更高rank的整型混合运算）前，会 *先提升* 为 `int` 或 `unsigned int`；




- 提升目标取决于 `int` 能否表示原类型的所有值：能，则提升为 `int`；否则为 `unsigned int`。
#figure(
  image("images/1.png")
)
==== 结果分析
1. `signed char`类型是1字节的, 当使用`+`和`~`一元运算符后就会自动提升为4字节
2. 同样对于2字节`unsigned short`, 在计算过程中就会提升为4字节的类型
=== 2.2 通常算术转换（Usual Arithmetic Conversions）
- 发生于多数 *二元算术运算*（`+ - * / %`，以及比较运算）以使两侧操作数转为“*共同实数类型*”；




- 若任何一侧为 *长精度浮点*，遵循：`long double` > `double` > `float`（`float` 常先提升为 `double`）；


- 若都是整数：先做整型提升，再按 *整数转换等级（rank）与有符号/无符号* 规则合并：


  - 同rank且一方无符号：若无符号类型能表示有符号的全部值，则转为无符号；否则两者都转为对应的无符号类型；
  - rank不同：较低rank提升到较高rank；若一方为无符号且rank更高，结果通常为*该无符号更高rank类型*。

#figure(
  image("images/2.png")
)
==== 结果分析
1. int + unsigned int → int 被转换成 unsigned int，结果是一个大无符号数。\

2. long + unsigned long → long 被转换成 unsigned long，结果同样是大无符号数。

3. int + long → int 转换成 long，结果类型为 long。

4. unsigned int + unsigned long → 较低等级的无符号类型转换为更高等级 unsigned long。

5. float + int → int 转换成 float。

6. float + double → float 转换成 double。

7. double + long double → double 转换成 long double。

从 sizeof 的结果也能看出：

- 整数混合结果是 4 字节（int 或 unsigned int）；

- 浮点混合提升到 8 字节（double）；

- 若涉及 long double，则结果为 16 字节。

=== 2.3 条件运算符 `?:`
- 第二、第三操作数需进行*类型合并*：


  - 若有一方为浮点，则按 2.2 规则合并至共同浮点类型；
  - 若为整数，按整型提升与通常算术转换合并；
  - 若为指针，遵循可转换性（例如 `T*` 与 `void*` 可合并为 `void*`，限定符按最严格合并）。

#figure(
  image("images/3.png")
)
==== 结果分析
1. (true ? i : ui) int 与 unsigned int 混合时，int 会提升为 unsigned int，所以结果为一个大的无符号数（负数被解释为大正数）。

2. (false ? f : d) float 被提升为 double，最终结果类型为 double。

3. (i ? d : ld) double 与 long double 合并为 long double 类型。

4. 指针类型 (true ? p : vp) int* 与 void* 可合并为 void*，结果类型为 void*。

5. (false ? a : b) 普通整型选择分支正确（选择右边的 b）。

sizeof 检查:

- sizeof(true ? i : ui) = 4 → 结果是 unsigned int；

- sizeof(false ? f : d) = 8 → 结果是 double；

- sizeof(i ? d : ld) = 16 → 结果是 long double。

=== 2.4 赋值与显式强制类型转换（Cast）
- 赋值目标类型决定转换：可能 *截断*（如 `double→int` 去小数）、*取模*（如 `int→unsigned char` 取 `mod 2^8`）、或 *值改变/未定义*（越界时可能实现定义或未定义，具体看标准条款）；





- Cast 显式进行相同规则的转换，但并不改变底层对象的比特宽度（只是结果值的解释）。


#figure(
  image("images/4.png")
)

==== 结果分析
1. (int)123.75 → 小数部分被截断（不四舍五入），结果为 123。

2. (unsigned int)-1 → 有符号数被解释为无符号数，结果是 2^32 - 1 = 4294967295。

3. (unsigned char)300 → 取模 2^8 = 256，结果为 300 - 256 = 44。

4. (double)LLONG_MAX → 超出 double 的精度范围，低位丢失精度（结果可能不完全准确）。

5. 隐式赋值 int j = f; → 隐式执行了 (int)f，小数部分被去掉，结果为 3。

6. (int)4000000000U → 超出 int 能表示范围，结果为实现定义（在大多数系统上出现负数）。

=== 2.5 位运算与移位
- 位运算 `& | ^ ~`、移位 `<< >>` 先进行整型提升；
- 对 *有符号右移* 的行为（算术右移是否保留符号位）为 *实现定义*；对 *无符号右移* 为逻辑右移（高位补0）。

#figure(
  image("images/5.png")
)


==== 结果分析
1. 按位与（&） m & n → 因 n=-1 的二进制为全1，结果等于 m 本身。

2. 按位或（|） 只要有一边为 1，结果为 1。m | 1 使最低位变为 1。

3. 按位异或（^） 不同为 1，相同为 0。0xFFFF0000 ^ 0x1 = 0xFFFF0001。

4. 取反（~） 所有位取反。1 → 0xFFFFFFFE。

5. 左移（<<） 1 << 8 → 0x100（即乘以 2⁸ = 256）。

6. 右移（>>）无符号数 高位补 0 → 0xFFFF0000 >> 1 = 0x7FFF8000。

7. 右移（>>）有符号数 高位补符号位（算术右移）。-1 >> 1 仍为 -1 (0xFFFFFFFF)。
