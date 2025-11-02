# shell


如果您希望传递的参数中包含空格（例如一个名为 My Photos 的文件夹），您要么用**使用单引号**，双引号将其包裹起来，要么使用**转义符号 `\`** 进行处理（`My\ Photos`）。

#### shell怎么知道这个程序
>_环境变量_ `$PATH`，它会列出当 shell 接到某条指令时，进行程序搜索



#### 搜索while echo路径，
绝对路径，相对路径
pwd：print current working dir
### 命令
`cd`: change dir
special dir:
. and ..

**`ls`**:show list of this dir 
可以给一个路径

~:home dir
-:previous dir


参数
-l

### 在程序见创建连接
重定向`< file`和`> file`可以把程序的输入流和输出流重定向到文件
还可以使用`>>`来向一个文件追加内容

**管道**把前一个文件的输出作用于后一个文件
### 权限
对于目录的写入是指您是否被允许重命名、创建或删除
该目录中的文件，所以它仍然是正确的，但请注意，这意味着如果您对文件具有写权限，但您没有其目录的写权限，则不能删除该文件，您可以清空它，但不能删除它，因为这需要写入目录本身，最

mv 可以重命名
cp 
rm 

重定向文件
\>
但是

管道
|
把左侧的结果作为右侧的参数

root用户
sudo 程序

sudo su使用root使用shell

## 第二集
注意空格
变量赋值foo=bar之间不能有空格

单引号和双引号

美元符号$带有不同含义

！！替换？

通配符*, ?

tldr

## 第三节课
[编辑器 (Vim) · the missing semester of your cs education](https://missing-semester-cn.github.io/2020/editors/)






