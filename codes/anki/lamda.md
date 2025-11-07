# 算法

## lamda表达式的语法

<!-- notecardId: 1762429907230 -->
```cpp
[capture list](parameter list) -> return type { function body }
```

## lamda表达式捕获值的类型

<!-- notecardId: 1762429907237 -->
- `[=]`：按值捕获所有外部变量。
- `[&]`：按引用捕获所有外部变量。
- `[x, &y]`：按值捕获 `x`，按引用捕获 `y`。
- `[]`：不捕获任何变量。