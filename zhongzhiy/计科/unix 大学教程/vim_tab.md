
## ✅ **Tab 相关操作**

### **关闭其他所有 Tab**

```vim
:tabonly
```

或简写：

```vim
:tabo
```

---

## 📌 **Tab 创建与切换**

### **新建 Tab**

```vim
:tabnew
```

或打开文件：

```vim
:tabnew filename
```

### **切换到下一个/上一个 Tab**

```vim
:tabnext   " 或 :tabn
:tabprevious  " 或 :tabp
```

### **跳到指定 Tab（按编号）**

```vim
:tabn 3   " 跳到第 3 个 tab
```

---

## 🗑️ **关闭 Tab**

### **关闭当前 Tab**

```vim
:tabclose
```

或：

```vim
:tabc
```

### **关闭指定 Tab**

```vim
:tabc 3
```

---

## 📁 **Tab 列表查看**

### **列出所有 tab**

```vim
:tabs
```

---

## 🎯 **窗口（split）相关（常与 tab 混用）**

虽然不是 Tab，但常一起使用：

### **关闭除当前窗口外的所有窗口**

```vim
:only
```
