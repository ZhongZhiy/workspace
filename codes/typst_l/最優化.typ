#set page(
  numbering: "1",
)
#let preface(
) = {
  if(counter(page) == 1) {
    [hello world]
  }
}
#preface()
$ Delta f(x) = ((partial f(x))/ (partial x_1), (partial f(x))/ (partial x_2), dots, (partial f(x))/(partial x_n))^T $

#pagebreak()
因爲梯度指向遞增方向, 所以儅$ Delta f(x^k)^T p < 0 $
時, p就是下降方向

1. 