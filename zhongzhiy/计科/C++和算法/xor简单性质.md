# 运算性质
1. 与自身异或为0
```cpp
x ^ x = 0
```
2. 与0异或不变
```cpp
x ^ 0 = x
```
3. 与-1的补码（也就是所有位为1）异或为反码
```
x ^ (-1) = ~x
```
4. 交换律
```cpp
x ^ y = y ^ x
```
5. 结合律
```cpp
x ^ (y ^ z) = (x ^ y) ^ z
```
6. 自反
```cpp
x ^ x ^ y = 0 ^ y = y
```
7. 如果`x ^ y = z`, 那么`z ^ x = y`

## 前缀异或和
设
$$
b_{i} = a_{1} \oplus a_{2} \oplus a_{3} \oplus \dots \oplus a_{i} 
$$
那么
$$
b_{j} \oplus b_{i-1} = a{i} \oplus a_{i+1} \oplus a_{i+2} \oplus \dots \oplus a_{j}
$$

$$
a_{i} = b_{i} \oplus b_{i-1}
$$
因为$b_{j} = b_{i-1} \oplus a_{i} \oplus a_{i+1} \oplus \dots \oplus a_j$，而 $b_{i-1} \oplus b_{i-1} = 0$


