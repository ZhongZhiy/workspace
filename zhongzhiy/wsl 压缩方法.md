压缩 WSL2 的虚拟磁盘（`.vhdx` 文件）是一个释放硬盘空间的好办法。因为 WSL2 的虚拟磁盘默认是自动扩展的，但你在 Linux 里面删除文件后，Windows 上的 `.vhdx` 文件并不会自动变小。

下面为你提供两种最常用的压缩方法：**最快的方法（命令行）** 和 **最省事的方法（如果你装了 Docker）**。

## 方法一：使用 Windows 自带的 `diskpart` 工具（最推荐）

这是最标准、最彻底的方法。请按照以下步骤操作：

### 1. 关闭 WSL2 实例

首先，确保所有的 WSL 实例都已经完全关闭。打开 Windows Powershell（管理员身份），运行：

PowerShell

```
wsl --shutdown
```

### 2. 找到你的 `.vhdx` 虚拟磁盘路径

通常，默认安装的 Ubuntu 磁盘文件位于以下路径：

Plaintext

```
C:\Users\<你的Windows用户名>\AppData\Local\Packages\CanonicalGroupLimited.Ubuntu...（一长串）\LocalState\ext4.vhdx
```

> 💡 **小贴士：** 如果你找不到，可以在 Powershell 中运行 `cd $env:LOCALAPPDATA\Packages`，然后找包含 `Ubuntu` 或 `Debian` 的文件夹。**复制好 `ext4.vhdx` 的完整绝对路径**。

### 3. 使用 `diskpart` 进行压缩

在 Powershell 中依次输入以下命令：

1. 启动磁盘管理工具：
    
    PowerShell
    
    ```
    diskpart
    ```
    
2. 选择你的 WSL2 虚拟磁盘文件（**请把路径替换为你真实的路径**）：
    
    PowerShell
    
    ```
    select vdisk file="C:\Users\你的用户名\AppData\Local\Packages\...\LocalState\ext4.vhdx"
    ```
    
3. 以只读模式挂载它（为了安全）：
    
    PowerShell
    
    ```
    attach vdisk readonly
    ```
    
4. 开始压缩：
    
    PowerShell
    
    ```
    compact vdisk
    ```
    
    _(此时会显示进度条，等待完成到 100% 即可)_
    
5. 分离磁盘并退出：
    
    PowerShell
    
    ```
    detach vdisk
    exit
    ```
    

## 方法二：使用 Docker Desktop 自动压缩（最省事）

如果你平时都在用 **Docker Desktop**，并且通过它启用了 WSL2 后端，那可能正是 Docker 占用了大量空间。Docker 已经内置了非常方便的压缩功能：

1. 打开 **Docker Desktop**。
    
2. 点击右上角的 **齿轮图标 (Settings)** -> **Resources** -> **Advanced**（或者直接找到 Disk utilization）。
    
3. 或者是直接点击顶部菜单栏的 **Clean / Purge data**（垃圾桶图标），里面通常有一个 **Optimize disk space** 的选项。
    
4. 点击后，Docker 会自动帮你安全地压缩其关联的 WSL2 虚拟磁盘。
    

## 💡 进阶小技巧：在 Linux 内部先“填零”（可选）

如果你发现压缩后体积变化不大，是因为 Linux 删除了文件，但磁盘扇区上还有残留数据。在执行上面的 `diskpart` 之前，你可以先进入 WSL2 内部，把空闲空间“擦干净”：

1. 进入 WSL2，运行以下命令（这会把所有剩余空间填成 0，最后会提示空间不足，不用管它）：
    
    Bash
    
    ```
    dd if=/dev/zero of=/zero.small.file bs=1M
    rm /zero.small.file
    ```
    
2. 运行完后，再退出 WSL2，执行前面的 **方法一**，压缩效果会非常惊人！