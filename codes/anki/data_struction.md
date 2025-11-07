# CS61a

## 数据抽象（Data Abstraction）的核心思想是什么？

<!-- notecardId: 1761920590845 -->
将“数据的表示方式”和“数据的操作方式”分离。



## 抽象数据类型（ADT）的目的是什么？

<!-- notecardId: 1761920590871 -->
让我们能够以统一的方式操作复合对象，而不必关心其底层表示。



## 数据抽象的两个部分是？

<!-- notecardId: 1761920590875 -->
1. 数据的表示（representation）  
2. 数据的操作（manipulation）



## 数据抽象的好处是什么？

<!-- notecardId: 1761920590880 -->
更改表示方式不会影响使用方式，从而提高模块化和可维护性。



## 数据抽象通过什么机制实现？

<!-- notecardId: 1761920590882 -->
通过函数形成的抽象屏障（abstraction barrier）。



## 在有理数抽象中，构造函数是什么？

<!-- notecardId: 1761920590885 -->
rational(n, d)



## 在有理数抽象中，选择器有哪些？

<!-- notecardId: 1761920590889 -->
numer(x)、denom(x)



## rational 的意义是什么？

<!-- notecardId: 1761920590892 -->
构造一个分数 n/d 的数据结构。



## numer 的作用？

<!-- notecardId: 1761920590895 -->
返回有理数的分子。



## denom 的作用？

<!-- notecardId: 1761920590898 -->
返回有理数的分母。



## add_rational 的作用？
计算两个有理数的和。



## mul_rational 的作用？
计算两个有理数的积。



## equal_rational 的作用？
判断两个有理数是否相等。



## rational 函数返回的数据结构是什么？

<!-- notecardId: 1761920590911 -->
一个包含 [n, d] 的列表。



## rational 数据结构可以改成其他形式吗？

<!-- notecardId: 1761920590914 -->
可以，只要同时修改选择器函数，外部不会受影响。



## Abstraction Barrier 的作用？

<!-- notecardId: 1761920590923 -->
分离程序各部分，使得修改实现不会破坏接口。



## 当程序越过 abstraction barrier 直接访问底层结构会怎样？

<!-- notecardId: 1761920590926 -->
会违反抽象屏障（violating abstraction barrier）。



## 举例说明违反抽象屏障的情况。

<!-- notecardId: 1761920590929 -->
直接用 `[1,2]` 表示分数，而不是通过 rational() 构造。



## 改变 rational 实现时，为何 add_rational 等函数无需修改？
因为这些函数依赖的是抽象接口，而非底层表示。



## Python 中如何用列表表示 pair？

<!-- notecardId: 1761920590935 -->
pair = [1, 2]



## 如何从 pair 中取出元素？

<!-- notecardId: 1761920590938 -->
使用 pair[0] 和 pair[1]。



## Python 中可用哪个函数访问列表元素？

<!-- notecardId: 1761920590942 -->
operator.getitem(pair, index)



## 如何将 rational 约分为最简形式？

<!-- notecardId: 1761920590945 -->
在构造时用 gcd 计算最大公约数。



## rational 约分实现中 gcd 的作用？

<!-- notecardId: 1761920590948 -->
用于将分子分母同时除以最大公约数。



## abstraction barrier 的分层思想体现了什么编程原则？

<!-- notecardId: 1761920590951 -->
封装（encapsulation）与模块化（modularity）。



## 当使用高级接口而不是底层数据结构时，能获得什么好处？

<!-- notecardId: 1761920590953 -->
更高的可维护性和灵活性。



## 数据抽象的行为是通过什么定义的？

<!-- notecardId: 1761920590957 -->
通过一组构造器、选择器和行为约束条件。



## Data abstraction recognized by its behavior 的含义？

<!-- notecardId: 1761920590960 -->
数据抽象的本质是行为而非实现。



## “改动一层不会影响其他层”这一特性体现了什么？

<!-- notecardId: 1761920590963 -->
抽象屏障的正确使用。



## 数据抽象中“接口与实现分离”的实质是什么？

<!-- notecardId: 1761920590967 -->
调用方只需依赖函数行为，不依赖数据结构细节。



## 当 rational 的底层表示从列表改为元组时，需要改动哪些函数？

<!-- notecardId: 1761920590970 -->
只需修改 rational、numer、denom 的实现。



## add_rational 和 mul_rational 应该依赖于哪些函数？
依赖 numer、denom、rational，不直接访问列表。



## 为什么要避免直接操作数据结构的内部？

<!-- notecardId: 1761920590975 -->
因为那样会破坏抽象屏障，降低可维护性。



## abstraction barrier 在大型项目中的意义？

<!-- notecardId: 1761920590978 -->
帮助团队在不同抽象层上独立开发。



## Abstraction barrier 图中的每一层线代表什么？

<!-- notecardId: 1761920590981 -->
代表抽象层之间的接口边界。



## 违反 abstraction barrier 的后果？

<!-- notecardId: 1761920590984 -->
程序修改或扩展时更易出错。



## Data representation 改变的目的是什么？

<!-- notecardId: 1761920590987 -->
让程序在不改变接口的前提下获得性能或表示优化。



## 设计 rational 时，哪个函数相当于“构造器”？

<!-- notecardId: 1761920590991 -->
rational()



## 设计 rational 时，哪些函数相当于“选择器”？

<!-- notecardId: 1761920590994 -->
numer() 和 denom()。



## equal_rational 实现等价于数学上的什么？
判断 $\frac{a}{b} = \frac{c}{d}$。



## rational 抽象屏障中最底层的部分是什么？

<!-- notecardId: 1761920591001 -->
数据表示层（representation layer）。



## abstraction barrier 最顶层的部分是什么？

<!-- notecardId: 1761920591004 -->
操作层（functions manipulating data）。



## add_rational 函数调用 rational() 的目的？
保证返回结果遵循抽象接口。



## 为什么要通过 rational() 创建结果，而不是直接返回列表？

<!-- notecardId: 1761920591011 -->
保持接口一致性，防止外部依赖数据表示。



## “函数 enforcing abstraction barrier” 的含义？

<!-- notecardId: 1761920591014 -->
函数负责维护抽象边界，不允许跨层访问。


---
