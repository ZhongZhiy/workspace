`stringstream` 是 C++ 标准库中的一个类，位于 `<sstream>` 头文件中。它用于操作字符串流，可以将字符串解析为多个部分，或者将数据转换为字符串。

`stringstream ss(line);` 的作用是将一个字符串 `line` 转换为字符串流 `ss`，然后可以从这个流中逐步读取数据，就像处理输入流（如 `cin`）一样。

---

### **常见用途**

#### 1. **字符串分割**

从一个字符串中提取单词或数据段：

```cpp
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    string line = "123 456 789";
    stringstream ss(line); // 将字符串转为字符串流

    string word;
    while (ss >> word) { // 逐个提取空格分隔的部分
        cout << word << endl;
    }

    return 0;
}
```

**输出：**

```plaintext
123
456
789
```

#### 2. **字符串到数字的转换**

`stringstream` 可以将字符串中的数值转换为数字类型：

```cpp
#include <iostream>
#include <sstream>
using namespace std;

int main() {
    string line = "42";
    stringstream ss(line);

    int num;
    ss >> num; // 将字符串中的数字转换为整数
    cout << "Number: " << num << endl;

    return 0;
}
```

**输出：**

```plaintext
Number: 42
```

#### 3. **数字到字符串的转换**

将数字转换为字符串：

```cpp
#include <iostream>
#include <sstream>
using namespace std;

int main() {
    int num = 123;
    stringstream ss;
    ss << num; // 将数字插入字符串流
    string str = ss.str(); // 获取流中的字符串
    cout << "String: " << str << endl;

    return 0;
}
```

**输出：**

```plaintext
String: 123
```

---

### **用法解释**

1. **初始化字符串流**
    
    ```cpp
    stringstream ss(line);
    ```
    
    - 这里 `line` 是一个 `string` 类型变量。
    - `ss` 是一个字符串流对象，它存储了 `line` 的内容，可以像操作 `cin` 一样从中提取数据。
2. **提取数据**
    
    ```cpp
    ss >> word;
    ```
    
    - 从流中提取单个单词或数据段（以空格或其他分隔符为界）。
3. **数据回填**
    
    ```cpp
    ss << data;
    ```
    
    - 将数据写入流中，用于构造字符串。
4. **获取字符串内容**
    
    ```cpp
    ss.str();
    ```
    
    - 获取字符串流中的完整字符串。

---

### **在代码中的作用**

在 `stringstream ss(line);` 的上下文中，`line` 是从输入中读取的一行字符串，比如：

```
seven four + nine =
```

通过 `stringstream`，这行字符串可以分割成单独的单词：`"seven"`, `"four"`, `"+"`, `"nine"`, `"="`。

具体步骤如下：

1. **创建字符串流**： 将整行字符串存入流中，便于逐步解析。
    
    ```cpp
    stringstream ss(line);
    ```
    
2. **逐个读取单词**：
    
    ```cpp
    while (ss >> word) {
        // 每次提取一个单词
    }
    ```
    

这使得解析复杂输入变得简单、高效，尤其是在处理以空格或其他分隔符分隔的字符串时。

---

### **总结**

`stringstream` 是一个强大的工具，用于字符串的分割、数据提取，以及字符串与数字之间的转换。它在需要解析复杂输入格式时特别有用，比如当前问题中的解析输入行，将单词分离为各个部分以进一步处理。