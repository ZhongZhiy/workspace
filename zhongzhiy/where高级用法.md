好的，我们现在进入 Typst 样式系统中最强大的部分：  
**`.where(...)` + lambda** 与 **使用选择器定制表格、公式、图片的样式**。

这是写论文模板、课程模板、书籍模板必备的技能。

接下来我会：

1. 讲 `.where(...)` 里如何用 **lambda**
    
2. 给你 **实战例子**（表格、公式、图片）
    

---

# 🟦 1. `.where(...)` + lambda 是什么？

普通 `.where`：

```typst
heading.where(level: 2)
```

是“字段等于”。  
但字段也可以是复杂对象，如：

- `body`（内容 content）
    
- `caption`（图标题）
    
- `kind`（图像分类）
    
- `stroke`（线条）
    
- `align`（表格对齐）
    

这时你可以在 `.where(...)` 里写 **lambda 函数**：

```typst
heading.where(body: b => 条件表达式)
```

含义：

> 传入字段值，如果 lambda 返回 `true`，就选中。

---

# 🟦 2. 基础示例：匹配标题内容包含某个词

```typst
#show heading.where(body: b => b.text.contains("苹果")): h => {
  text(fill: red)[h.body]
}
```

解释：

- `.where(body: b => ...)`：匹配标题内容
    
- `b.text.contains("苹果")`：如果标题中出现“苹果”，就选中
    
- 效果：标题中含“苹果”的标题变红
    

---

# 🟦 3. `.where` 高级用法总结表

|用法|示例|作用|
|---|---|---|
|比较字段|`.where(level: 2)`|精确匹配|
|用 lambda 判断|`.where(body: b => ...)`|复杂判断|
|匹配多个字段|`.where(level: 1, outlined: true)`|多条件|
|针对内容操作|`.where(body: b => …)`|对内容做判断|
|嵌套字段判断|`.where(caption: c => c != none)`|有无标题|

---

# 🟦 Part 2：用 `.where` 自定义表格样式（🔥常用）

Typst 的 `table` 元素字段包括：

- `columns`
    
- `rows`
    
- `align`
    
- `stroke`
    
- `inset`
    
- `body`
    

我们用 `.where` 定制：

---

## ✔ 示例 1：给所有 3 列的表格设置统一边框

```typst
#show table.where(columns: 3): t => {
  table(
    stroke: (all: 1pt + black),
    inset: 5pt,
  )[t.body]
}
```

匹配：`columns == 3` 的表格。

---

## ✔ 示例 2：所有表格自动居中、加标题样式

```typst
#show figure.where(kind: "table"): fig => {
  align(center)[
    fig.body
    text(size: 10pt, weight: "semibold")[#fig.caption]
  ]
}
```

`figure.where(kind: "table")` 表示“表格图元”。

---

# 🟦 Part 3：自定义公式（math）样式

数学公式 Typst 对应元素是：

- `math.equation`
    
- `math.frac`
    
- `math.integral`
    
- 等等…
    

你可以用 `.where(...)` 选择特定公式。

---

## ✔ 示例 1：给所有行间公式添加编号格式

```typst
#show math.equation.where(block: true): eq => {
  align(center)[
    eq.body
    text(size: 10pt, fill: gray)[(Eq.~#counter(math-eq))]
  ]
}
```

选择器解释：

- `math.equation`：选中 equation 元素
    
- `.where(block: true)` → 行间公式（display style）
    

---

## ✔ 示例 2：所有分数变大、变粗

```typst
#show math.frac: f => {
  math.frac(
    stroke: 1pt + blue,
    f.num,
    f.denom,
  )
}
```

---

# 🟦 Part 4：自定义所有图片（image）样式

图片元素 `image` 字段包括：

- `path`
    
- `width`
    
- `height`
    
- `alt`
    

---

## ✔ 示例 1：所有图片自动缩放为页面宽度 80%

```typst
#show image: img => {
  image(img.path, width: 80%)
}
```

---

## ✔ 示例 2：为所有带 caption 的图片统一风格

图像在 Typst 里通常是 `figure` 元素：

```typst
#show figure.where(kind: "image"): fig => {
  align(center)[
    fig.body
    text(size: 9pt, fill: gray)[图 #fig.caption]
  ]
}
```

---

# 🟦 Part 5：`.where` 与 lambda 的强化示例（很强）

---

## ✔ 示例：让表格如果包含负数，则整行染红

```typst
#show table.where(body: rows => {
  rows.any(row => row.any(cell => cell.text.starts-with("-")))
}): t => {
  rect(fill: lightpink)[t]
}
```

解释：

- `rows.any` → 是否有某行满足条件
    
- `row.any` → 是否有某个单元格满足
    
- `cell.text.starts-with("-")` → 是否是负数
    

这就是 `.where + lambda` 的最强组合。

---

# 🟦 最终总结

### ✔ `.where()` 的强大点在于它能够使用 **lambda 函数做复杂过滤**

### ✔ 可以用来选择：

- 特定内容的标题
    
- 指定行数/列数的表格
    
- 特定类型的图片/公式
    
- 带 caption 的 figure
    
- 含某个字符的段落
    

### ✔ 这是 Typst 模板系统的本质：

通过选择器 + 样式函数，修改所有元素的渲染方式。

---

# 🔥 如果你愿意，我可以帮你写：

### ▸ 一个 **毕业论文模板** 的完整 `.where` 样式系统

### ▸ 表格（Table）、图（Figure）、公式（Equation）统一样式

### ▸ 根据你学校要求自动化格式

只需要一句话：  
**“帮我写一套论文格式的 `show` 系统模板”**  
我就给你一整套可直接用的。