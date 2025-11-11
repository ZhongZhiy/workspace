使用 Git 将代码远程推送到 GitHub 上，主要分为以下几个步骤：

---

## 🧩 一、准备工作

### 1. 安装 Git
如果你还没安装 Git，可以去官网下载安装：
- 官网：https://git-scm.com/

安装完成后，在命令行中输入以下命令查看是否安装成功：

```bash
git --version
```

---

### 2. 配置 Git 用户名和邮箱（只需设置一次）

```bash
git config --global user.name "你的GitHub用户名"
git config --global user.email "你的GitHub注册邮箱"
```

---

### 3. 创建 SSH 密钥（用于免密推送）

#### 检查是否存在 SSH 密钥：
```bash
ls -al ~/.ssh
```
如果存在 `id_rsa.pub` 或 `id_ed25519.pub` 等文件，说明你已经有密钥。

#### 如果没有，生成新的 SSH 密钥：
```bash
ssh-keygen -t ed25519 -C "你的邮箱@example.com"
# 或者旧版本系统使用 RSA：
ssh-keygen -t rsa -b 4096 -C "你的邮箱@example.com"
```
连续回车即可，默认保存路径为 `~/.ssh/id_ed25519`。

#### 添加 SSH 密钥到 GitHub：

1. 查看公钥内容：
   ```bash
   cat ~/.ssh/id_ed25519.pub
   ```
   复制输出的内容。

2. 登录 GitHub → Settings → SSH and GPG keys → New SSH key  
   把复制的公钥粘贴进去，保存即可。

---

## 📦 二、将本地项目上传到 GitHub

### 方法一：新建一个空的 GitHub 仓库，然后连接本地

#### 1. 在 GitHub 上新建一个空仓库（不要勾选 README、.gitignore、License）

比如地址是：`https://github.com/你的用户名/你的仓库名.git`

#### 2. 初始化本地 Git 仓库（已有可跳过）
```bash
cd 你的项目目录
git init
```

#### 3. 添加所有文件并提交
```bash
git add .
git commit -m "Initial commit"
```

#### 4. 添加远程仓库地址
```bash
git remote add origin git@github.com:你的用户名/你的仓库名.git
```

#### 5. 推送代码到 GitHub
```bash
git branch -M main
git push -u origin main
```

> 第一次推送时 `-u` 参数会把当前分支和远程分支绑定，之后就可以直接用 `git push`。

---

### 方法二：克隆已有的 GitHub 仓库到本地

如果你想先在 GitHub 上创建好仓库，再从那里开始开发：

```bash
git clone git@github.com:你的用户名/你的仓库名.git
cd 你的仓库名
# 然后添加文件、提交、推送即可
git add .
git commit -m "Add files"
git push
```

---

## ✅ 常用命令速览

| 命令 | 说明 |
|------|------|
| `git init` | 初始化一个新的 Git 仓库 |
| `git clone <url>` | 克隆远程仓库到本地 |
| `git add .` | 添加所有修改到暂存区 |
| `git commit -m "描述"` | 提交更改 |
| `git remote add origin <url>` | 添加远程仓库 |
| `git push -u origin main` | 推送代码并绑定远程分支 |
| `git status` | 查看当前状态 |
| `git log` | 查看提交历史 |

---

## 🧪 测试 SSH 是否连接成功

```bash
ssh -T git@github.com
```

如果提示：

```
Hi 你的用户名! You've successfully authenticated, but GitHub does not provide shell access.
```

说明 SSH 已配置成功！

---

如果你有具体的项目结构或错误信息，也可以告诉我，我可以帮你具体分析。欢迎继续提问 😊