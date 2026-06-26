使用`let v:Box<[Vec<i32>]> = (0..=n).map(|_| Vec::new()).collect()`
其中`Vec::new()`是个胖指针, 在栈上, 大小确定, 所以