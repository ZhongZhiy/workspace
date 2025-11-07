#import "@preview/codly:1.3.0": *
#import "@preview/codly-languages:0.1.1": *
#show: codly-init.with()

// #set page(
//   width: 12cm, 
//   height: 12cm,
//   margin:(
//     top: 2cm,
//     bottom: 2cm,
//     x: 1.5cm,
//     y: 1.5cm
//     ),
// )
#set page(header:()
  if page() > 1 [
    _Lisa Strassner's Thesis_ \
    #h(lfr) \
    National Academy of Sciences
  ]
))

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
