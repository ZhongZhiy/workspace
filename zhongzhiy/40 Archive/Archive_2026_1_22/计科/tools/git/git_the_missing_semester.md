## 配置
配置文件在`～/.gitconfig`
配置传递`--local`就是对当前仓库，使用`--global`就是对所有仓库起作用
使用`git --list`查看所有配置
使用`git --list --show-origin`查看配置所在的文件
`git config --global user.name "username"`
`git config --global user.email 123@jkd`
可以通过输入 `git config <key>` 来检查 Git 的某一项配置

## 获得帮助
若你使用 Git 时需要获取帮助，有三种等价的方法可以找到 Git 命令的综合手册（manpage）：

```console
$ git help <verb>
$ git <verb> --help
$ man git-<verb>
```

如果你不需要全面的手册，只需要可用选项的快速参考，那么可以用 `-h` 选项获得更简明的 `help` 输出


## 获取 Git 仓库

通常有两种获取 Git 项目仓库的方式：

1. 将尚未进行版本控制的本地目录转换为 Git 仓库；
    
2. 从其它服务器 **克隆** 一个已存在的 Git 仓库。

## 底层和上层命令
### 向git存入，取出内容
```console
$ echo 'test content' | git hash-object -w --stdin
```
底层命令 `git hash-object` 来演示上述效果——该命令可将任意数据保存于 `.git/objects` 目录（即 **对象数据库**），并返回指向该数据对象的唯一的键。`-w` 选项会指示该命令不要只返回键，还要将该对象写入数据库中。 最后，`--stdin` 选项则指示该命令从标准输入读取内容；若不指定此选项，则须在命令尾部给出待存储文件的路径。

校验和的前两个字符用于命名子目录，余下的 38 个字符则用作文件名。
#### 取出
一旦你将内容存储在了对象数据库中，那么可以通过 `cat-file` 命令从 Git 那里取回数据
为 `cat-file` 指定 `-p` 选项可指示该命令自动判断内容的类型，并为我们显示大致的内容

文本对象被称为**数据对象（blob objiect）**


![|289x214](git_the_missing_semester-1752564244871.webp)

### 树对象
git根据某一时刻的暂存区的内容创建对应的树对象

`git uodate-index --add --cacheinfo `创建一个暂存区，指定 `--add` 选项，因为此前该文件并不在暂存区中（我们甚至都还没来得及创建一个暂存区呢）； 同样必需的还有 `--cacheinfo` 选项，因为将要添加的文件位于 Git 数据库中，而不是位于当前目录下

文件模式`1006441普通文件
`1007551`可执行文件
`120000`符号链接


## 使用
### 文件只有已跟踪/未跟踪
`git add` 命令使用文件或目录的路径作为参数；如果参数是目录的路径，该命令将递归地跟踪该目录下的所有文件。

`git add` 命令。：可以用它开始跟踪新文件，或者把已跟踪的文件放到暂存区，还能用于合并时把有冲突的文件标记为已解决状态等

如果你使用 `git status -s` 命令或 `git status --short` 命令，你将得到一种格式更为紧凑的输出。
- **左栏（第1列）**：表示“暂存区”（staging area）的状态
- **右栏（第2列）**：表示“工作区”（working directory）的状态
 - **??**：未被跟踪（untracked），就是新文件，还没被 git 记录管理。
- **A**：已添加到暂存区（Added）
- **M**：已修改（Modified）
- **D**：已删除（Deleted）
- **R**：重命名（Renamed）
- **C**：复制（Copied）
### 忽略文件
们可以创建一个名为 `.gitignore` 的文件，列出要忽略的文件的模式

文件 `.gitignore` 的格式规范如下：

- 所有空行或者以 `#` 开头的行都会被 Git 忽略。
    
- 可以使用标准的 glob 模式匹配，它会递归地应用在整个工作区中。
    
- 匹配模式可以以（`/`）开头防止递归。
    
- 匹配模式可以以（`/`）结尾指定目录。
    
- 要忽略指定模式以外的文件或目录，可以在模式前加上叹号（`!`）取反。
所谓的 glob 模式是指 shell 所使用的简化了的正则表达式。 星号（`*`）匹配零个或多个任意字符；`[abc]` 匹配任何一个列在方括号中的字符 （这个例子要么匹配一个 a，要么匹配一个 b，要么匹配一个 c）； 问号（`?`）只匹配一个任意字符；如果在方括号中使用短划线分隔两个字符， 表示所有在这两个字符范围内的都可以匹配（比如 `[0-9]` 表示匹配所有 0 到 9 的数字）。 使用两个星号（`**`）表示匹配任意中间目录，比如 `a/**/z` 可以匹配 `a/z` 、 `a/b/z` 或 `a/b/c/z` 等。


it diff 本身只显示尚未暂存的改动，而不是自上次提交以来所做的所有改动。

Git 提供了一个跳过使用暂存区域的方式， 只要在提交的时候，给 `git commit` 加上 `-a` 选项，Git 就会自动把所有已经跟踪过的文件暂存起来一并提交，从而跳过 `git add` 步骤

### 文件模式 `100644`

这个数字代表文件的**模式 (mode)**，它由两部分组成：文件类型 和 文件权限。这沿用了 Unix/Linux 系统的文件模式表示法。

- **前面的 `100`**: 代表文件类型。
    
    - `100`: 表示这是一个**普通文件 (regular file)**。
    - `120`: 表示这是一个**符号链接 (symbolic link)**。
    - `040`: 表示这是一个**目录 (directory)** (在 Git 中由 Tree 对象表示)。
    - `160`: 表示这是一个 **gitlink**，用于指向一个子模块 (submodule) 的特定提交。
- **后面的 `644`**: 代表文件的**权限 (permissions)**，使用标准的 Unix 权限八进制表示法。
    
    - `6` (所有者权限): `4` (读) + `2` (写) = `rw-`
    - `4` (用户组权限): `4` (读) = `r--`
    - `4` (其他用户权限): `4` (读) = `r--`

所以，`100644` 的完整意思是：**“这是一个普通的、非可执行的文件”。**

### git diff
`git diff` this command compares my **workding directory** with **the staged files**, this will show **the changes i haven't yet staged**

`git diff --staged`will show the differents between **your staged** and **last commit** ,(`--staged` and `--cached` are synonyms)

Run `git difftool --tool-help` to see what is available on your system.
commit records the snapshot set up in your **staging area**

use `git commit -a`can skip `git add`step to commit,but only for all file that were tracked, untracked file would not be commited

remove file from staging area and working directory
`git rm file`
and `git rm --cached file`only remove file from staging area but not your working directory

rename file by `git mv oldfile newfile`

### git log
list the commits incluing  SHA-1, author, date, messages
`git log -p ` will show the differnce in each commit 
`git log --stat` will show an abbreviated summary for each commit
`git log --pretty=online` also `=short=full=fuller`
`git log --pretty=format:%h - %an, %ar : %s`show log in specific format

Table 1. Useful specifiers for `git log --pretty=format`  

|Specifier|Description of Output|
|---|---|
|`%H`|Commit hash|
|`%h`|Abbreviated commit hash|
|`%T`|Tree hash|
|`%t`|Abbreviated tree hash|
|`%P`|Parent hashes|
|`%p`|Abbreviated parent hashes|
|`%an`|Author name|
|`%ae`|Author email|
|`%ad`|Author date (format respects the `--date=option`)|
|`%ar`|Author date, relative|
|`%cn`|Committer name|
|`%ce`|Committer email|
|`%cd`|Committer date|
|`%cr`|Committer date, relative|
|`%s`|Subject|
`git log --graph`show a nice little ASCII graph

Table 2. Common options to `git log`  

| Option            | Description                                                                                                                                        |
| ----------------- | -------------------------------------------------------------------------------------------------------------------------------------------------- |
| `-p`              | Show the patch introduced with each commit.                                                                                                        |
| `--stat`          | Show statistics for files modified in each commit.                                                                                                 |
| `--shortstat`     | Display only the changed/insertions/deletions line from the `--stat` command.                                                                      |
| `--name-only`     | Show the list of files modified after the commit information.                                                                                      |
| `--name-status`   | Show the list of files affected with added/modified/deleted information as well.                                                                   |
| `--abbrev-commit` | Show only the first few characters of the SHA-1 checksum instead of all 40.                                                                        |
| `--relative-date` | Display the date in a relative format (for example, “2 weeks ago”) instead of using the full date format.                                          |
| `--graph`         | Display an ASCII graph of the branch and merge history beside the log output.                                                                      |
| `--pretty`        | Show commits in an alternate format. Option values include `oneline`, `short`, `full`, `fuller`, and `format` (where you specify your own format). |
| `--oneline`       | Shorthand for `--pretty=oneline --abbrev-commit` used together.                                                                                    |
|                   |                                                                                                                                                    |

Table 3. Options to limit the output of `git log`  

| Option                | Description                                                                                                                     |
| --------------------- | ------------------------------------------------------------------------------------------------------------------------------- |
| `-<n>`                | Show only the last n commits.                                                                                                   |
| `--since`, `--after`  | Limit the commits to those made after the specified date.                                                                       |
| `--until`, `--before` | Limit the commits to those made before the specified date.                                                                      |
| `--author`            | Only show commits in which the author entry matches the specified string.                                                       |
| `--committer`         | Only show commits in which the committer entry matches the specified string.                                                    |
| `--grep`              | Only show commits with a commit message containing the string.(**add --all-match** to limit output to convery all the keywords) |
| `-S`                  | Only show commits adding or removing code matching the string.                                                                  |
`git log -- path/to/file` put in the last to limit the file path


## undo things
`git commit --amend` to overwrite the latest commit , but not the push

`git reset HEAD file` to unstage
`git restore --staged file` equal to `reset`

`git checkout -- file` unmodify the modified file, this is replace the file with the last staged or committed version
`git restore file` is equal to `checkout -- file` 

## remote
`git remote` show your remote branch, if you clone from remote, you will have an **origin** branch by default
`git remote -v` show all the url and shortname that you can pull or fetch
`git remote add <shortname> <url>`add remote
`git fetch <remote> `get data from remote and get all the references of all the branches to merge in ot inspect
`git push <remote> <branch>` if somebody pushed before, you must pull first before push 
`git remote show <remote>`show more information about a particular remote
`git remote rename oldname newname` this will change all your remote-tracking branch names

