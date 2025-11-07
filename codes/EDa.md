EDa.md
## 赋值语句
### 块语句
1. 顺序块
```
begin
statement1;
statement2;
end
```
2. 并行块
```
fork
statement1
statement2
end
```

### 赋值语句
1. 门基元赋值语句, `and(outa, a, b, c)`
2. 连续赋值语句 `assign 赋值变量 = 表达式`
> 连续赋值语句的=两边的变量都应该时`wire`型变量
> 输入有变化, 输出就会有变化
3. 过程赋值语句, 给reg型变量赋值
  1. 阻塞 `变量 = 值`, 就是顺序执行赋值, 前面执行后才能执行后面的语句
  2. 非阻塞 `变量 <= 值`, 就是多条赋值语句并行执行

  ## 语句执行
  ### 语句的并行执行
  - 多个always模块
  - always模块中的非阻塞式赋值


## 条件语句
`if else `
2. `case`
```
case (敏感表达式)
  case_item1: statement1;
  case_item2: statement2;
  default: statement3;
endcase
```
> 可用多个敏感表达式拼接
3. casez和casex语句, 对高阻和不确定表达式
- `casex`, 某些

## 循环语句
- `for`
- `while`
- `repeat`
- `forever`

# 第8章
