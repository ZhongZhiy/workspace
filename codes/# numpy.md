# numpy
## numpy的安装
`pip install numpy`
`import numpy as np`
## numpy语法
### narray
`numpy.array(object, dtype = None, copy = True, order = None, subok = False, ndmin = 0)`
- `dtype`数据类型
- `copy`是否复制数据
- `order`, c为行向量, f为列向量, a为任意方向
- 'ndmin`最小的维度
```py
a = np.array([1,  2,  3], dtype = complex)  #[1.+0.j 2.+0.j 3.+0.j]
a = np.array([1, 2, 3, 4, 5], ndmin =  2)  #[[1 2 3 4 5]]
```

### `dtype`
`dtype`是numpy数组的属性，用于获取或设置数组的数据类型。
```py
student = np.dtype([('name','S20'), ('age', 'i1'), ('marks', 'f4')]) 
a = np.array([('abc', 21, 50),('xyz', 18, 75)], dtype = student) 

```