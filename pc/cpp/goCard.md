go的基本类型:
```go
bool
string
int int8 int16 int32 int64
uint uint8 uint16 uint32 uint64 uintptr
byte
rune
float32 float64
complex64 complex128
```
其中`byte`和`rune`分别是什么类型?
??
```go
byte //alias for uint8
rune //alias for int32
```

---

怎么批量声明变量, 使用一个`var`
??
可以像导入语句一样
```go
var (
	ToBe bool = fasle
	MaxInt uint64 = 1<<64 - 1
	z complex64 = cmplx.Sqrt(-5 + 12i)
)

---

变量声明没有确切的初始值会怎么初始化变量
??
会赋予他们*零值*
数字类为 0,
布尔类为 false,
字符串为 ""(空字符串)
切片的为 `nil`

---

go怎么进行类型转换
??
使用`T(v)`类型包裹值, 且必须显式转换
```go
var i int = 42
var j uint = uint(i)
k := float64(i)
```

---

go怎么声明常量
??
使用`const`关键字, 不可以使用`:=`语法

---

go的条件循环， while循环， 以及无限循环是怎么写的？
??
```go
//一般for循环
for var i int = 1; i > 10; i -= 1 {
	
}

//while循环
for i > 10 {
	
}

//无限循环
for {
	
}
```

---

go的if语句怎么使用局部变量？
??
```go
if v := 12 ; v > pow(i) {
	return v
}else {
	v -= 1
}
```

---

go怎么编写干净简洁的长if-then-else链?
??
使用没有条件的Switch
```go
func main() {
	t := time.Now()
	switch {
		case t.Hour() < 12:
			fmt.Println("Good morning!")
		case t.Hour() < 17:
			fmt.Println("good afternoon")
		default:
			fmt.Println("good evening")
	}
}

---

`defer`推迟函数执行, 直到周围函数返回, 多个`defer`推迟运算的返回值是什么顺序
```go
func main() {
	fmt.Println("counting")

	for i := 0; i < 10; i++ {
		defer fmt.Println(i)
	}
	fmt.Println("done")
}
```
这个函数返回什么?

??
有个`defer`栈, 最后按照先进后出的顺序返回值
返回:
```go
counting
done
9
8
7
6
5
4
3
2
1
0
```

---

**数组字面量**和**切片**的区别
??
1. 视觉上: 
```go
a := [3]int{1, 2, 3}  // 数组 (Array)：括号里有数字（或 ...）
b := []int{1, 2, 3}   // 切片 (Slice)：括号里是空的
```
2. 本质区别是: 数组字面量是值, 而切片只是引用

---

go怎么声明数组?
??
`var arr [10]int`
`arr := [10]int {1, 2, }`

---

go用`make`创建len为3，cap为5的int数组的切片？
??
```go
a := make([]int, 3, 5)
```

---

go的方法既可以是值接收器, 也可以是指针接收器, 类似rust中的?
??
类似于rust中的`&self`, 和自解引用情况

---

`import`位置在哪里?
??
`import`必须紧跟在`package`之后

---

go怎么处理无用变量?
??
使用`_`

---

go使用原生字符串字面量的语法?
??
使用反引号包裹, 原生字符串不可以使用转义字符

---

go的**嵌入**功能?
??
类似于继承, 嵌入后的struct就可以拥有别嵌入的接口
