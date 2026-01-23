## 查找命令帮助
`whatis` and `info`查命令用法
`man`查命令详细
`which`查找命令位置

### man目录分类
man页面所属的分类标识(常用的是分类1和分类3)

1) 、用户可以操作的命令或者是可执行文件
2) 、系统核心可调用的函数与工具等
3) 、一些常用的函数与数据库
4) 、设备文件的说明
5) 、设置文件或者某些文件的格式
6) 、游戏
7) 、惯例与协议等。例如Linux标准文件系统、网络协议、ASCⅡ，码等说明内容
8) 、系统管理员可用的管理条令
9) 、与内核有关的文件



## [2.1. 创建和删除](https://linuxtools-rst.readthedocs.io/zh-cn/latest/base/02_file_manage.html#id15)[](https://linuxtools-rst.readthedocs.io/zh-cn/latest/base/02_file_manage.html#id3 "永久链接至标题")

- 创建：mkdir
- 删除：rm
- 删除非空目录：rm -rf file目录
- 删除日志 rm *log (等价: $find ./ -name “*log” -exec rm {} ;)
- 移动：mv
- 复制：cp (复制目录：cp -r )

## [2.2. 目录切换](https://linuxtools-rst.readthedocs.io/zh-cn/latest/base/02_file_manage.html#id16)[](https://linuxtools-rst.readthedocs.io/zh-cn/latest/base/02_file_manage.html#id4 "永久链接至标题")

- 找到文件/目录位置：cd
- 切换到上一个工作目录： cd -
- 切换到home目录： cd or cd ~
- 显示当前路径: pwd
- 更改当前工作路径为path: $cd path

## [2.3. 列出目录项](https://linuxtools-rst.readthedocs.io/zh-cn/latest/base/02_file_manage.html#id17)[](https://linuxtools-rst.readthedocs.io/zh-cn/latest/base/02_file_manage.html#id5 "永久链接至标题")
- 显示当前目录下的文件 ls
- 按时间排序，以列表的方式显示目录项 ls -lrt

## [2.4. 查找目录及文件 find/locate](https://linuxtools-rst.readthedocs.io/zh-cn/latest/base/02_file_manage.html#id18)[](https://linuxtools-rst.readthedocs.io/zh-cn/latest/base/02_file_manage.html#find-locate "永久链接至标题")
在 Linux 中，`find` 和 `locate` 是两个非常常用的**文件查找命令**，它们各有特点，适用于不同场景。下面我会详细讲解这两个命令的常用用法和区别。

---

## 🟢 一、`find` 命令

### ✅ 特点：
- 实时搜索（扫描文件系统）
- 精确匹配
- 支持复杂的条件表达式（按名、类型、大小、权限、时间等）
- 可以对找到的结果执行操作（如删除、移动）

### 🔧 基本语法：

```bash
find [路径] [表达式]
```

---

### 📌 常见用法示例：

#### 1. 按名称查找文件（区分大小写）：

```bash
find /home/user -name "example.txt"
```

#### 2. 按名称查找（不区分大小写）：

```bash
find /home/user -iname "example.txt"
```

#### 3. 查找所有 `.log` 文件：

```bash
find /var/log -name "*.log"
```

#### 4. 查找目录：

```bash
find /etc -type d -name "network*"
```

> `-type` 类型说明：
> - `f`：普通文件  
> - `d`：目录  
> - `l`：符号链接  
> - `c`：字符设备  
> - `b`：块设备

#### 5. 查找大于某个大小的文件（+表示大于）：

```bash
find /home/user -size +100M
```

> 单位说明：
> - `c` 字节
> - `k` 千字节
> - `M` 兆字节
> - `G` 吉字节  
> 示例：`+10k`, `-50M`, `+2G`

#### 6. 查找最近修改过的文件（例如7天内）：

```bash
find /var/log -mtime -7
```

> - `-mtime n`：n 天前修改的文件  
> - `-atime`：访问时间  
> - `-ctime`：状态更改时间

#### 7. 查找并删除：

```bash
find /tmp -name "*.tmp" -delete
```

或者使用 `-exec` 执行任意命令：

```bash
find /tmp -name "*.tmp" -exec rm {} \;
```

> `{}` 表示当前查找到的文件  
> `\;` 表示结束符

#### 8. 查找并列出详细信息：

```bash
find /home/user -name "*.txt" -exec ls -l {} \;
```

---

## 🟡 二、`locate` 命令

### ✅ 特点：
- 快速查找（依赖数据库 `updatedb`）
- 不实时更新（需要手动更新数据库）
- 更适合模糊查找、快速定位

### 更新数据库：

```bash
sudo updatedb
```

---

### 📌 常见用法示例：

#### 1. 查找包含关键字的文件：

```bash
locate example.txt
```

#### 2. 模糊查找：

```bash
locate .bashrc
```

#### 3. 显示匹配数量：

```bash
locate -c .bashrc
```

#### 4. 忽略大小写：

```bash
locate -i ".pdf"
```

#### 5. 只显示前10个结果：

```bash
locate -n 10 ".jpg"
```

---


- 如果你需要 **精确查找当前存在的文件**，推荐使用 `find`
- 如果你要 **快速模糊查找文件名或路径**，可以先运行一次 `updatedb`，然后使用 `locate`
- `locate` 的数据库通常保存在 `/var/lib/mlocate/mlocate.db`（具体位置因系统而异）






