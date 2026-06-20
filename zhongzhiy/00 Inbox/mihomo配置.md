直接使用[通用配置](https://github.com/HenryChiao/MIHOMO_YAMLS/blob/main/THEYAMLS/General_Config)
然后`systemctl enable mihomo --new`启动
使用web UI [zashboard](https://board.zash.run.place/#/setup)设置

### 给 Mihomo 赋予网络权限（解决 TUN 模式权限）

TUN 模式需要操作系统的网络核心权限。我们可以利用 Linux 的 `capabilities` 机制，给 `mihomo` 这个二进制程序单独“发一张特权准入证”，这样它就能以普通用户身份创建 TUN 网卡。

在终端运行以下命令：

Bash

```
sudo setcap cap_net_admin,cap_net_bind_service=+ep $(which mihomo)
```

- **`cap_net_admin`**：允许程序配置网卡和路由表（启动 TUN 必备）。
    
- **`cap_net_bind_service`**：允许程序占用 1024 以下的特权端口（如果你的配置里有用到低端口的话）。
    
- **`$(which mihomo)`**：自动找到你系统里 `mihomo` 命令的实际安装路径（通常在 `/usr/bin/mihomo`）。