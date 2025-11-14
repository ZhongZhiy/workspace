# WSABuilds &nbsp; &nbsp; <img src="https://img.shields.io/github/downloads/MustardChef/WSABuilds/total?label=Total%20Downloads&style=for-the-badge"/> &nbsp; 


## 指南：将 Windows Subsystem For Android™ (WSA) 移动/安装到另一个分区或磁盘

### 前言：
##### WSA 可能占用大量存储空间，因此你可能想把它移动到容量更大的分区或磁盘。 本指南介绍一种方法，可从另一个分区或磁盘安装 WSA 并将其数据放置在目标位置，以节省系统盘空间。

### 先决条件：
- 你要移动/安装 Windows Subsystem For Android™ 的分区/磁盘 **必须** 为 **NTFS**
- 建议 C:/ 与你想要安装（或移动）WSA 的磁盘/分区均为 SSD
    - HDD 可能可用，但会出现性能问题
- 具备基础的命令提示符（CMD）使用知识
- 目标磁盘/分区必须有足够的可用空间（建议 20GB，因为 VHDX 文件可能会非常大）

> [!NOTE] 
> 
> 如果你想保留数据，请备份 %LOCALAPPDATA%\Packages\MicrosoftCorporationII.WindowsSubsystemForAndroid_8wekyb3d8bbwe\LocalCache\userdata.vhdx 文件。在卸载之前建议先备份此文件以防丢失。

## 步骤：

- ### 第 1 步：移除所有先前通过 WSABuilds 或官方 WSA 发布安装的 WSA
    - 要移除通过 WSABuild 安装的 WSA：

        - **1.)** 确保 Windows Subsystem For Android™ 未在运行
        - **2.)** 使用 Windows 自带的搜索或“添加或删除程序”搜索并卸载 “Windows Subsystem For Android™ Settings”
        - **3.)** 删除你解压并运行 Run.bat 来安装 WSA 的文件夹（例如 MagiskOnWSA 文件夹）
        - **4.)** 进入 %LOCALAPPDATA%/Packages/ 并删除名为 MicrosoftCorporationII.WindowsSubsystemForAndroid_8wekyb3d8bbwe 的文件夹
            
            - 如果删除时出现无法删除文件的错误，请确保 WSA 已关闭
     
    - 要移除从 Microsoft Store 安装的 WSA：
        
        - **1.)** 使用 Windows 自带的搜索或“添加或删除程序”搜索并卸载 “Windows Subsystem For Android™ Settings”


- ### 第 2 步：从目标分区安装 WSA
    - **1.)** 根据 Windows 版本和 CPU 架构，从 [Downloads](https://github.com/MustardChef/WSABuilds#downloads) 下载最新的 WSA 构建
    - **2.)** 解压到你想要的分区或驱动器
    - 使用 [Installation](https://github.com/MustardChef/WSABuilds#--installation) 中详细说明的相同步骤进行安装
    - **3.)** 打开解压后的文件夹并运行 Run.bat
 

- ### 第 3 步：将 AppData（VHDX + 数据）从 Windows 驱动器（C:\）移动到目标分区/驱动器
     - **1.)** 进入 %LOCALAPPDATA%\Packages\ 并将名为 MicrosoftCorporationII.WindowsSubsystemForAndroid_8wekyb3d8bbwe 的文件夹复制到目标驱动器/分区，复制完成并确认无误后可删除原始文件夹
     
     - **2.)** 以管理员身份打开命令提示符（通过 Windows Terminal (Admin) 或直接以管理员运行），执行命令：
     ```shell
     mklink /J "%LOCALAPPDATA%\Packages\MicrosoftCorporationII.WindowsSubsystemForAndroid_8wekyb3d8bbwe" "Location_Of_Folder_In_Other_Drive"
     ```
     将 Location_Of_Folder_In_Other_Drive 替换为你在其他驱动器上复制的 MicrosoftCorporationII.WindowsSubsystemForAndroid_8wekyb3d8bbwe 文件夹的实际路径。


- ### 第 4 步：检测是否一切正常
    - 运行 Windows Subsystem For Android™ Settings
        - 如果程序崩溃，说明在按照本指南操作时出现错误。请检查步骤并重试。
    
    
### 如果你卡住了或对指南中的步骤不理解，请加入 Discord 并在这里询问：
[<img src="https://invidget.switchblade.xyz/2thee7zzHZ" style="width: 400px;"/>](https://discord.gg/2thee7zzHZ) 
          