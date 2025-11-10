#import "@preview/codly:1.3.0": *
#import "@preview/codly-languages:0.1.1": *
#show: codly-init.with()

#set page(
  width: 12cm, 
  height: 12cm,
  margin:(
    top: 2cm,
    bottom: 2cm,
    x: 1.5cm,
    y: 1.5cm
    ),
)
= 参考

== document
- title, author, keywords, 都是出现在pdf的metadata
- date: auto
- 使用`#set document(title: [Hello])`使用

== figure
- 图
```typst
#figure(
  image("glacier.jpg", width: 80%),
  caption: "Glacier",
)
```
- table
```typst
#figure(
  table(
    columns: 4,
    [1], [2], [3], [4],
    [y], [0.4], [0.6], [0.8]
  ),
  caption: "table"
)
```

= 函数
#let f(x, y) = [两个数值#(x), 和#(y)在函数中]

#f([hello, world], "0")

== 匿名函数, 也就是函数闭包
#let f = (x, y) => [#(x) and #(y)]
#f([a], [b])


