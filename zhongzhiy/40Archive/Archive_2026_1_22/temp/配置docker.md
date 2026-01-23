恭喜！将服务器变成一个**网站服务器（Web Server）**是学习服务器运维最经典、也最有成就感的一步。

为了保持 Arch Linux 系统的整洁，我们采用 **Docker + Nginx** 的方案。这种方案不仅部署快，而且以后你想迁移到其他服务器时，直接拷贝文件夹就能走。

---

### 第一阶段：快速上线“你好，世界”

我们要利用之前安装好的 Docker，几分钟内跑起你的第一个网页。

#### 1. 创建项目目录

在 **fate (Arch)** 上，建立一个存放网站文件的文件夹：

Bash

```
mkdir -p ~/my_website/html
cd ~/my_website
```

#### 2. 准备网页内容

创建一个简单的 HTML 文件：

Bash

```
nano html/index.html
```

在编辑器里输入以下内容（按 `Ctrl+O` 保存，`Ctrl+X` 退出）：

HTML

```
<!DOCTYPE html>
<html>
<head>
    <title>Saber's Castle</title>
    <style>
        body { font-family: sans-serif; text-align: center; margin-top: 100px; background: #f4f4f4; }
        h1 { color: #333; }
    </style>
</head>
<body>
    <h1>欢迎来到我的 Arch Linux 服务器！</h1>
    <p>这是通过 Tailscale + Docker 部署的网站。</p>
</body>
</html>
```

#### 3. 编写 Docker Compose 配置文件

这是管理网站的“说明书”：

Bash

```
nano docker-compose.yml
```

输入以下内容：

YAML

```
services:
  web_server:
    image: nginx:alpine
    container_name: my_nginx
    ports:
      - "80:80"  # 将服务器的 80 端口映射到容器的 80 端口
    volumes:
      - ./html:/usr/share/nginx/html:ro  # 将刚才创建的 html 文件夹挂载进去
    restart: always
```

#### 4. 启动网站

Bash

```
docker compose up -d
```

---

### 第二阶段：在 Windows 上访问它

现在，你的网站已经运行在 `fate` 机器的 80 端口上了。

1. 打开 Windows 浏览器。
    
2. 在地址栏输入你的 Tailscale IP：`http://100.108.238.122`
    
3. **大功告成！** 你应该能看到刚才写的网页了。
    

---

### 第三阶段：让全世界看到（Tailscale Funnel）

现在的网站只有你自己（在 Tailscale 网络内）能看。如果你想发给没装 Tailscale 的朋友看，或者在外面用手机看，可以使用 **Tailscale Funnel**。

这是 Tailscale 最神奇的功能：它能帮你内网穿透，并自动搞定 **HTTPS 证书**。

#### 1. 在 Arch 上开启 Funnel

运行以下命令：

Bash

```
sudo tailscale serve --bg 80
sudo tailscale funnel 80 on
```

#### 2. 获取你的公网网址

运行：

Bash

```
tailscale status
```

你会看到类似 `https://fate.xxxx.ts.net` 的域名。

现在，你可以把这个域名发给任何人，他们都能在互联网上安全地访问你的 Arch 网站了！

---

### 进阶：如何更方便地改网页？

既然你已经学会了 `scp` 和 VS Code 远程连接：

- **方法 A**：在 Windows 用 VS Code 打开远程文件夹 `~/my_website/html`，直接编辑 `index.html`，保存即生效。
    
- **方法 B**：在本地写好漂亮的网页模板，用 `scp -r` 整个文件夹传到服务器。
    

---

### 下一步建议

网站已经跑起来了，接下来你想往哪个方向发展？

- **想要一个更漂亮的个人博客？** 我可以教你部署 **Halo** 或 **WordPress**。
    
- **想要一个私有云盘？** 我们可以部署 **Alist**，把你的硬盘变成像百度网盘一样的网页界面。
    
- **想要监控服务器流量？** 我们可以给网站加一个仪表盘（Dashboard）。
    

**你想先尝试把网页变漂亮，还是部署一个更有功能的“云盘”系统？**