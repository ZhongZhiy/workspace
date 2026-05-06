
#import "@preview/cmarker:0.1.8"
#set page(
  paper: "a4",
)
#set text(
  font: ("Microsoft YaHei", "New Computer Modern"),
  lang: "zh",
  region: "cn"
)


#align(center)[
  #set text(size: 30pt,weight: "bold")
  计算机系统导论实验报告
  #v(2fr)
  实验名称: 二进制程序分析综合实验（IA-32）
  #v(2fr)
  班级: 计算2403
  #v(2fr)
  姓名: 钟智勇
  #v(2fr)
  日期: 2026年1月7日
  #v(3fr)
]
#pagebreak()
/*

1、	明确实验任务、实验目标
2、	详细记录实验过程，自己是如何完成整个实验的，
实验过程中遇到什么问题，是怎么解决的？
完成该实验需要掌握哪些知识？
最后有什么收获，心得体会。

*/
#outline()
#set page(
  numbering: "1/1"
)
#set heading(numbering: "1.1")

= 二进制程序分析综合实验
== 二进制程序基本组成与字符串比较
#cmarker.render(read("sy2_1.md"))

== 浮点数表示
#cmarker.render(read("sy2_2.md"))

== 循环结构的机器级表示
#cmarker.render(read("sy2_3.md"))

== 选择（条件分支）结构的机器级表示
#cmarker.render(read("sy2_4.md"))

== 递归过程调用
#cmarker.render(read("sy2_5.md"))

== 数组的存储与访问
#cmarker.render(read("sy2_6.md"))

== 数组
#cmarker.render(read("sy2_7.md"))

== 结构与链表
#cmarker.render(read("sy2_8.md"))
