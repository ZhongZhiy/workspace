### **Lambda 表达式简介**

**Lambda 表达式**（也称为匿名函数）是 C++11 引入的一种特性，它可以用来定义**没有名字的内联函数**，主要用于简化代码，特别是短小的回调函数、排序规则等。

### **Lambda 表达式的基本语法**

```cpp
[capture list](parameter list) -> return type { function body }
```

#### 1. **`capture list`（捕获列表）**

- 用来捕获外部作用域的变量。
- 它决定 lambda 内部能否访问外部变量，以及如何访问（按值或按引用）。

#### 2. **`parameter list`（参数列表）**

- 表示传递给 lambda 的参数，就像普通函数的参数列表一样。

#### 3. **`return type`（返回类型）**

- 用 `->` 指定 lambda 的返回值类型。
- 如果省略，编译器会根据 `return` 的表达式推导（从 C++14 开始自动推导）。

#### 4. **`function body`（函数体）**

- 定义了 lambda 的具体实现逻辑，像普通函数的函数体一样。

---

### **基本用法示例**

#### 1. 最简单的 Lambda

```cpp
#include <iostream>
using namespace std;

int main() {
    auto greet = []() {
        cout << "Hello, Lambda!" << endl;
    };
    greet(); // 调用 lambda 表达式
    return 0;
}
```

输出：

```plaintext
Hello, Lambda!
```

#### 2. 带参数的 Lambda

```cpp
#include <iostream>
using namespace std;

int main() {
    auto add = [](int a, int b) -> int {
        return a + b;
    };
    cout << add(3, 4) << endl; // 输出 7
    return 0;
}
```

#### 3. 捕获外部变量

Lambda 表达式可以通过捕获列表访问外部变量。

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 10, y = 20;

    // 按值捕获 x 和 y
    auto sum = [x, y]() -> int {
        return x + y;
    };
    cout << sum() << endl; // 输出 30

    // 按引用捕获 x
    auto increment = [&x]() {
        x++;
    };
    increment();
    cout << x << endl; // 输出 11

    return 0;
}
```

---

### **捕获列表的用法**

#### 捕获列表常见写法：

- `[=]`：按值捕获所有外部变量。
- `[&]`：按引用捕获所有外部变量。
- `[x, &y]`：按值捕获 `x`，按引用捕获 `y`。
- `[]`：不捕获任何变量。

#### 示例：

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 5, b = 10;

    // 按值捕获
    auto by_value = [=]() {
        cout << "a + b = " << a + b << endl;
    };

    // 按引用捕获
    auto by_ref = [&]() {
        a++;
        b++;
        cout << "a = " << a << ", b = " << b << endl;
    };

    by_value(); // 输出 a + b = 15
    by_ref();   // 修改 a 和 b，输出 a = 6, b = 11

    return 0;
}
```

---

### **实际应用场景**

#### 1. **排序规则**

Lambda 常用于 STL 算法（如 `std::sort`），自定义比较规则：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> v = {5, 3, 8, 1, 2};

    // 按降序排序
    sort(v.begin(), v.end(), [](int a, int b) {
        return a > b; // 返回 true 表示 a 应排在 b 之前
    });

    for (int x : v) {
        cout << x << " ";
    }
    // 输出：8 5 3 2 1

    return 0;
}
```

---

#### 2. **STL 遍历**

简化代码逻辑，例如遍历和处理容器：

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {1, 2, 3, 4, 5};

    // 使用 lambda 打印每个元素的平方
    for_each(v.begin(), v.end(), [](int x) {
        cout << x * x << " ";
    });
    // 输出：1 4 9 16 25

    return 0;
}
```

---

#### 3. **多线程**

Lambda 表达式常用于并发编程，传递给线程函数：

```cpp
#include <iostream>
#include <thread>
using namespace std;

void thread_func() {
    cout << "Hello from thread!" << endl;
}

int main() {
    // 使用 lambda 启动线程
    thread t([]() {
        cout << "Lambda thread started!" << endl;
    });

    t.join(); // 等待线程完成
    return 0;
}
```

输出：

```plaintext
Lambda thread started!
```

---

### **C++11、C++14 和 C++17 的 Lambda 变化**

#### 1. **C++11**

- 必须显式指定返回类型，除非只有单一的 `return` 语句。

#### 2. **C++14**

- 支持返回类型自动推导。
- 支持在 lambda 参数列表中定义变量类型为 `auto`。

#### 3. **C++17**

- 支持 **捕获解构**：

```cpp
#include <iostream>
using namespace std;

int main() {
    pair<int, int> p = {1, 2};

    auto print = [x = p.first, y = p.second]() {
        cout << "x = " << x << ", y = " << y << endl;
    };

    print(); // 输出：x = 1, y = 2

    return 0;
}
```

---

### **总结**

1. Lambda 表达式简化了代码编写，特别是短小的函数。
    
2. 它支持捕获外部变量（按值或按引用）。
    
3. 常见的应用场景包括：
    
    - 自定义排序规则
    - STL 容器操作
    - 多线程编程
4. 写法灵活，适合现代 C++ 编程风格！