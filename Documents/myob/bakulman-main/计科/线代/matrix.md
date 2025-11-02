## 代数余子式的$A_{ij}$=什么
若把三阶行列式D中元素$a_{ij}$所在的第i行与第j列划去，剩余的元素按原来的相对位置组成一个二阶行列式，称为元素$a_{ij}$的**余子式**，称为$M_{ij}$.  $A_{ij}=(-1)^{i+j}M_{ij}$的**代数余子式**

## n阶行列式简记为
$D=|a_{ij}|_{n}$

## 对n阶行列式的展开怎么操作
对某一行或者某一列展开就是$D = \sum_{i = 1}^n a_{ki}A_{ki}$这是对k行展开

## 由行列式展开定理，如果行列式有一行或者一列为0，那么D = ？

行列式就为0

## n阶下三角行列式的值为？
$$D = \left |\begin{array}{cccccc}
a1  \\
*&a_{2} \\
* &*&a_{3} \\
*&*& & \\
*&  &&          &   *a_{n}\\
\end{array} \right | = a_{1}a_{2}a_{3}\dots a_{n}$$

## 转置行列式$D^{T}$的形式为？
所以数字关于主对角线翻折

## 行列式性质
1. 值相关
2. 提公因式
3. 换行
4. 行列式的加法
5. 行列式的倍加
%


6. 行列式转置后不变，也就是，行列式的行和列是等价的
7. 对行列式，可以按行（列）提出公因数。
8. **互换行列式的任意两行（或两列），行列式的值变号**
	1. **推论** **1** **：若行列式中有某两行（列）相同，则此行列式为零。**
	2. **推论** **2** **：若行列式中有某两行（列）元素对应成比例，则此行列式为零。**
9. **性质** **4** **：若行列式的某一行（或某一列）的每一元素均表为两个数的和，则行列式可以按该行（列）拆成两个行列式相加。**
10. $$
\left |\begin{array}
a_{1}+a_{2}&b_{1}+b_{2} \\
c_{1}+c_{2}&d_{1}+d_{2} \\
\end{array}\right |
= \left |\begin{array}
a_{1}&b_{1} \\
c_{1}+c_{2}&d_{1}+d_{2} \\

\end{array}\right | +
\left |\begin{array}
a_{2}&b_{2} \\
c_{1}+c_{2}&d_{1}+d_{2} \\

\end{array} \right | = 
\left | \begin{array}
a_{1}& b_{1} \\
c_{1} & d_{1} \\

\end{array} \right | + 
\left | \begin{array}
q_{1}&b_{1} \\
c_{2}  & d_{2} \\

\end{array} \right | + 
\left | \begin{array}
a_{2}& b_{2} \\
c_{1}& d_{1} \\

\end{array} \right | + 

\left | \begin{array}
a_{2}& b_{2} \\
c_{2}& d_{2} \\

\end{array} \right |
$$
1. **性质** **5** **：把行列式** **D** **的某一行（列）的** **k** **倍加到另一行（列）上，行列式的值不变。
2. **行列式D中任意一行（列）各元素与另一行（列）对应元素的代数余子式的乘积之和必等于零。


## 计算行列式的方法
1. 化为三角行列式
2. 把某一行或者列化为0，进行降阶
3. 提公因式优化
4. 加边法，构造$n+1$阶行列式
eg(加边法)：
$D= \begin{vmatrix} 1 & 2 & 3 \\ 4 & 5 & 6 \\ b & b & b \end{vmatrix} = D' = \begin{vmatrix} 1 & 2 & 3 & b \\ 4 & 5 & 6 & b \\ b & b & b & b \\ 1 & 1 & 1 & 0 \end{vmatrix}$
按最后一行展开得到：
$\begin{vmatrix} 2 & 3 & b \\ 5 & 6 & b \\ b & b & b \end{vmatrix} - 1 \cdot \begin{vmatrix} 1 & 3 & b \\ 4 & 6 & b \\ b & b & b \end{vmatrix} + 1 \cdot \begin{vmatrix} 1 & 2 & b \\ 4 & 5 & b \\ b & b & b \end{vmatrix}$
可以按照b展开，得到二阶行列式，比较好算

## 克拉默法则求解方程组？
方程组的系数构成一个行列式，这个行列式的值不为0，那么该方程组有解，解的形式为$x_{i}= \frac{D_{i}}{D}$,其中$D_{i}$是把D中第j列换成方程组的常数项$b_{1}b_{2}b_{3}b_{4}b_{5}b_{6}b_{n}$后所得到的n阶行列式。
## 齐次线性方程组出来全为0的解，还有非零解的条件为？
$D = 0$有非零解的充分必要条件是系数行列式等于零。

## 增光矩阵是什么？
就是在系数矩阵后面再添加一列常数
例如：
$$\begin{cases}
2x_{1} + 5x_{2} = b_{1} \\
4x_{1}+2x_{2} = b_{2} \\
\end{cases} \implies 

\begin{bmatrix}
2&5 \\
4&2
\end{bmatrix} \implies
\begin{bmatrix}
2&5&b_{1} \\
4&2&b_{2}
\end{bmatrix}
\text{就是增广矩阵}
$$

## 矩阵的几个称呼意义：
1. $A = (a_{ij})_{m \times n}$
2. 零矩阵$O_{m\times n}$
3. n阶矩阵，n阶方阵
4. n维行向量
5. m维列向量

%
1. 就是$n\times m$的矩阵
2. 全是0的向量
3. $m = n$的向量
4. $m =1$时的向量，只有一行

## 对角矩阵是什么
只有对角线上的数不是0的矩阵
$$
D = \begin{bmatrix} d_1 & 0 & 0 & \dots & 0 \\ 0 & d_2 & 0 & \dots & 0 \\ 0 & 0 & d_3 & \dots & 0 \\ \vdots & \vdots & \vdots & \ddots & \vdots \\ 0 & 0 & 0 & \dots & d_n \end{bmatrix}
$$

## 数量矩阵是什么
就是对角线上的数一样的对角矩阵
$$
S = \begin{bmatrix} c & 0 & 0 & \dots & 0 \\ 0 & c & 0 & \dots & 0 \\ 0 & 0 & c & \dots & 0 \\ \vdots & \vdots & \vdots & \ddots & \vdots \\ 0 & 0 & 0 & \dots & c \end{bmatrix}
$$
## 上三角矩阵是什么
上三角矩阵是指**主对角线以下的元素全部为零**的方阵。

## 矩阵的加法是怎么运算的，有什么样的性质

矩阵的加法一定是同形矩阵对应元素相加，和一般加法性质一样

## 矩阵的乘法怎么运算，有什么性质
矩阵的乘法$A\times B$必须要**A的每一行与B的每一列相乘再相加**，
$$  A=\begin{bmatrix} 1 & 2 \\ 3 & 4 \end{bmatrix}, \quad B = \begin{bmatrix} 2 & 0 \\ 1 & 3 \end{bmatrix} 

$$
$$
AB = \begin{bmatrix} 1 \times 2 + 2 \times 1 & 1 \times 0 + 2 \times 3 \\ 3 \times 2 + 4 \times 1 & 3 \times 0 + 4 \times 3 \end{bmatrix}
$$

1. 满足不交换律$AB \neq BA$
2. 满足结合律，也就是运算顺序不重要$(AB)C=A(BC)$
3. 满足分配率，也就是可以拆括号$A(B+C) = AB + AC$ 
4. $A = AE = EA = A$
## 线性方程组的矩阵表示

$$
\begin{cases} 2x + 3y = 5 \\ 4x - y = 1 \end{cases}
$$

等于
$$
\begin{bmatrix} 2 & 3 \\ 4 & -1 \end{bmatrix} \begin{bmatrix} x \\ y \end{bmatrix} = \begin{bmatrix} 5 \\ 1 \end{bmatrix}
$$




## 矩阵的幂的性质
设 AA 是一个 nn 阶方阵（即 AA 是一个 $n \times n$ 矩阵），那么矩阵 AA 的 **m 次幂** 记作：

$A^m = \underbrace{A \cdot A \cdots A}_{m \text{ 个 } A}$
1. 和一般幂运算相似的地方，加和乘$A^m \cdot A^n = A^{m+n}$，$(A^m)^n = A^{m \cdot n}$
2. 单位矩阵$I_n^m = I_n$
3. **逆矩阵的幂**（若 AA 可逆）：
    
    - $(A^m)^{-1} = (A^{-1})^m$。
        
    - $A^{-m} = (A^{-1})^m$。
4. 对角线矩阵的幂$D^m = \begin{bmatrix} \lambda_1^m & 0 & 0 \\ 0 & \lambda_2^m & 0 \\ 0 & 0 & \lambda_3^m \end{bmatrix}$


## 证明$(A+B)^2 = A^2 + 2AB + B^2  \text{等价于} AB = BA$

$(A+B)(A+B) = A(A+B) + B(A+B) = A^2 + AB + BA + B^2$ 所以$AB = BA$
