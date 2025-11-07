# gitpro
---

## Git 本质是什么？

<!-- notecardId: 1760405016340 -->

Git 是一个 **内容寻址文件系统（content-addressable filesystem）**。

---

## Git 对象存储的唯一性和完整性由什么保证？

<!-- notecardId: 1760405016345 -->

由对象内容计算出的 **哈希（SHA-1 或 SHA-256）** 保证。

---

## Git 中有哪些主要对象类型？

<!-- notecardId: 1760405016349 -->

Blob、Tree、Commit、Tag 四种。

---

## Blob 对象的作用是什么？

<!-- notecardId: 1760405016354 -->

存储文件内容，不包含文件名。

---

## Tree 对象的作用是什么？

<!-- notecardId: 1760405016360 -->

存储目录结构，包含权限、文件名及指向 blob 或子 tree 的哈希。

---

## Commit 对象的主要内容包括哪些？

<!-- notecardId: 1760405016365 -->

指向根 tree 的指针、父提交指针、作者、提交者和提交信息。

---

## Commit 对象的本质是什么？

<!-- notecardId: 1760405016370 -->

对某个 **tree 快照** 的引用。

---

## Tag 对象的作用是什么？

<!-- notecardId: 1760405016375 -->

为 commit、tree 或 blob 添加命名标签。

---

## Git 的配置文件按优先级分为哪三层？

<!-- notecardId: 1760405016380 -->

1. `/etc/gitconfig`（系统级）
2. `~/.gitconfig` 或 `~/.config/git/config`（用户级）
3. `.git/config`（仓库级）

---

## 查看所有 Git 配置及来源的命令？

<!-- notecardId: 1760405016386 -->

`$ git config --list --show-origin $`

---

## 如何设置用户身份信息？

<!-- notecardId: 1760405016391 -->

```bash
git config --global user.name "name"
git config --global user.email "email@mail.com"
```

---

## 如何设置 Git 默认编辑器？

<!-- notecardId: 1760405016397 -->

`$ git config --global core.editor vim $`

---

## 如何设置默认分支名称为 main？

<!-- notecardId: 1760405016401 -->

`$ git config --global init.defaultBranch main $`

---

## 获取 Git 命令帮助的三种方式？

<!-- notecardId: 1760405016406 -->

`git help <verb>`、`git <verb> --help`、`man git-<verb>`。

---

## 克隆仓库时如何设置新的本地目录名？

<!-- notecardId: 1760405016411 -->

`git clone URL newname`

---

## `git add` 的作用？

<!-- notecardId: 1760405016416 -->

跟踪文件，添加到暂存区。

---

## `git status` 的常用选项及含义？

<!-- notecardId: 1760405016423 -->

`git status` 显示仓库状态；
`git status -s` 或 `--short` 显示简短状态。

---

## `.gitignore` 文件中 `!pattern` 的作用？

<!-- notecardId: 1760405016429 -->

取消忽略某个匹配的模式。

---

## `.gitignore` 中 `**` 的作用？

<!-- notecardId: 1760405016434 -->

匹配多级（嵌套）目录。

---

## 比较未暂存修改的命令？

<!-- notecardId: 1760405016438 -->

`git diff`

---

## 比较已暂存修改与上次提交差异的命令？

<!-- notecardId: 1760405016443 -->

`git diff --staged` 或 `--cached`

---

## 提交暂存区更改的命令？

<!-- notecardId: 1760405016447 -->

`git commit`

---

## 跳过暂存区直接提交所有修改的命令？

<!-- notecardId: 1760405016451 -->

`git commit -a`

---

## 修改上一次提交的命令？

<!-- notecardId: 1760405016456 -->

`git commit --amend`

---

## 从暂存区和工作区删除文件的命令？

<!-- notecardId: 1760405016461 -->

`git rm file`

---

## 仅从暂存区移除文件（保留本地文件）的命令？

<!-- notecardId: 1760405016465 -->

`git rm --cached file`

---

## 移动或重命名文件的 Git 命令？

<!-- notecardId: 1760405016470 -->

`git mv old new`

---

## `git log` 的默认输出内容？

<!-- notecardId: 1760405016474 -->

提交历史：作者、时间、提交信息。

---

## 查看最近两次提交的改动？

<!-- notecardId: 1760405016479 -->

`git log -p -2`

---

## 格式化输出 Git 提交日志的命令？

<!-- notecardId: 1760405016484 -->

`git log --pretty=format:"%n - %an, %ar : %s"`

---

## 可视化分支合并历史的命令？

<!-- notecardId: 1760405016491 -->

`git log --graph`

---

## 回退文件到上次提交状态的命令？

<!-- notecardId: 1760405016496 -->

`git reset HEAD <file>`

---

## 撤销最近提交但保留修改的命令？

<!-- notecardId: 1760405016501 -->

`git reset --soft <commit>`

---

## 完全回退到某次提交的命令？

<!-- notecardId: 1760405016505 -->

`git reset --hard <commit>`

---

## 丢弃工作区修改的命令？

<!-- notecardId: 1760405016510 -->

`git checkout -- <file>`

---

## 创建并切换到新分支的命令？

<!-- notecardId: 1760405016515 -->

`git checkout -b <newbranchname>`

---

## 使用新命令切换分支？

<!-- notecardId: 1760405016520 -->

`git switch <branch>`

---

## 撤销已暂存但保留修改的命令？

<!-- notecardId: 1760405016524 -->

`git restore --staged <file>`

---

## 撤销文件修改的命令？

<!-- notecardId: 1760405016528 -->

`git restore <file>`

---

## 查看远程仓库名的命令？

<!-- notecardId: 1760405016532 -->

`git remote`

---

## 查看远程仓库详细信息的命令？

<!-- notecardId: 1760405016536 -->

`git remote show <remote>`

---

## 添加远程仓库并设置简称的命令？

<!-- notecardId: 1760405016540 -->

`git remote add <shortname> <url>`

---

## 从远程仓库获取数据的命令？

<!-- notecardId: 1760405016543 -->

`git fetch <remote>`

---

## 推送本地 master 分支到远程的命令？

<!-- notecardId: 1760405016546 -->

`git push origin master`

---

## 推送标签到远程的命令？

<!-- notecardId: 1760405016550 -->

`git push origin v1.5` 或 `git push origin --tags`

---

## 删除远程标签的命令？

<!-- notecardId: 1760405016555 -->

`git push origin --delete <tagname>`

---

## 列出所有标签的命令？

<!-- notecardId: 1760405016560 -->

`git tag`

---

## 创建带注释的标签命令？

<!-- notecardId: 1760405016564 -->

`git tag -a v1.0.0 -m "First stable release"`

---

## 显示标签详细信息的命令？

<!-- notecardId: 1760405016569 -->

`git show v1.0.0`

---

## 删除标签的命令？

<!-- notecardId: 1760405016573 -->

`git tag -d <tagname>`

---

## 创建新分支的命令？

<!-- notecardId: 1760405016578 -->

`git branch <branchname>`

---

## 删除本地分支的命令？

<!-- notecardId: 1760405016582 -->

`git branch -d <branch>`

---

## 查看已合并分支的命令？

<!-- notecardId: 1760405016595 -->

`git branch --merged`

---

## 合并分支的命令？

<!-- notecardId: 1760405016600 -->

`git merge <branch>`

---

## 解决合并冲突的步骤？

<!-- notecardId: 1760405016603 -->

1. 运行 `$ git status $` 检查冲突文件；
2. 手动修改冲突；
3. 运行 `$ git add <file> $` 标记为已解决。

---
