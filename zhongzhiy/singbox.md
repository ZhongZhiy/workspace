# sing-box-subscribe

根据配置模板生成用于 sing-box 的 `config.json`。主要用于为使用 `clash_mode` 配置的用户添加订阅节点。

这不适合完全不熟悉 sing-box 配置文件的人使用。至少您需要了解 outbound、DNS 服务器、DNS 规则和路由规则。最好是[...]

请参考：[http://sing-box.sagernet.org/configuration](http://sing-box.sagernet.org/configuration/)

**默认不会解析 SSR 协议脚本。如果订阅链接包含 SSR 协议，将会报错！！！**

**vecel 服务器的处理时间上限为 10 秒。如果 clash 文件太大，会由于处理超时而失败！！！**

## 功能

**sing-box 网页解析器**

使用您搭建的网站实现实时配置更新，可以作为 sing-box 的远程链接

例如，我搭建的网站 [https://sing-box-subscribe.vercel.app](https://sing-box-subscribe.vercel.app)，在网站后面加 `/config/URL_LINK`，这里的 `URL_LINK` 指的是订阅链接：

```
https://xxxxxxx.vercel.app/config/https://xxxxxxsubscribe?token=123456&file=https://github.com/Toperlock/sing-box-subscribe/raw/main/config_template/config_template_groups_rule_set_tun.json
```

### 2024.2.16 更新：支持在链接后添加 `emoji`、`tag`、`prefix`、`ua`、`file`、`eps` 和 `enn` 参数。使用 `&` 连接多个参数。用法与参数相同[...]

`/config/URL_LINK&emoji=1&prefix=♥&ua=v2rayng&eps=vmess,hy2&enn=网站,剩余流量&file=https://xxxxxxxxx.json`

上述示例显示：启用 emoji，在节点名称前添加 ♥，使用 v2rayng 用户代理，并使用 `https://xxxxxxxxx.json` 作为生成的 sing-box 配置模板。

示例：https://sing-box-subscribe.vercel.app/config/https://gist.githubusercontent.com/Toperlock/b1ca381c32820e8c79669cbbd85b68ac/raw/dafae92fbe48ff36dae6e5172caa1cfd7914cda4/gistfile1.txt&file=http[...]

### 2023.11.04 更新：支持处理两个子链接，格式为：`/config/URL 编码`，`emoji`、`tag`、`prefix`、`UA` 参数不可写入（支持 2024.1.1 起的 3 个子链接）

使用 `|` 连接两个子链接，然后通过 [URL 编码](https://www.urlencoder.org/) 将其放置在 `config/` 之后，如图所示：

<div align="left">
  <img src="https://github.com/Toperlock/sing-box-subscribe/assets/86833913/5ed8e9de-3296-4dfc-ad65-2e181017829e" alt="如何使用" width="50%" />
</div>

示例：https://sing-box-subscribe.vercel.app/config/https%3A%2F%2Fgist.githubusercontent.com%2FToperlock%2Fb1ca381c32820e8c79669cbbd85b68ac%2Fraw%2Fdafae92fbe48ff36dae6e5172caa1cfd7914cda4%2Fgistfil[...]

### 2023.11.10 更新：`file` 参数可以简化为数字 `1` 或 `2`，表示使用 GitHub 仓库中提供的模板序号。

示例：https://sing-box-subscribe.vercel.app/config/https://gist.githubusercontent.com/Toperlock/b1ca381c32820e8c79669cbbd85b68ac/raw/dafae92fbe48ff36dae6e5172caa1cfd7914cda4/gistfile1.txt&file=2

### 演示视频

|网页解析订阅链接（v2/clash/sing-box）|
|-----------------------------|
|<video controls width="250" src="https://github.com/Toperlock/sing-box-subscribe/assets/86833913/a583c443-0c7b-454e-aaf2-f0a7159b276a"></video>|

## 目录

[操作视频](https://github.com/Toperlock/sing-box-subscribe/blob/main/instructions/README.md#-demonstration-video)

[参数意义](https://github.com/Toperlock/sing-box-subscribe/tree/main/instructions#providersjson-file)

[模板详细说明](https://github.com/Toperlock/sing-box-subscribe/tree/main/instructions#config-template-files)

[Windows 上运行 sing-box](https://github.com/Toperlock/sing-box-subscribe/tree/main/instructions#windows-sing-box-usage)

## 支持的协议

|  协议 | V2 订阅 | Clash 订阅 | 标准 URI 格式 | SingBox 格式 |
|  :----  | :----: | :----: | :----: | :----: |
| http  | ✅ | ✅ | ✅ | ✅ |
| socks5  | ✅ | ✅ | ✅ | ✅ |
| shadowsocks  | ✅ | ✅ | ✅ | ✅ |
| shadowsocksR  | ✅ | ✅ | ✅ | singbox 默认不支持 |
| vmess  | ✅ | ✅ | ✅ | ✅ |
| trojan  | ✅ | ✅ | ✅ | ✅ |
| vless  | ✅ | ✅ | ✅ | ✅ |
| tuic  | ✅ | ✅ | ✅ | ✅ |
| hysteria  | ✅ | ✅ | ✅ | ✅ |
| hysteria2  | ✅ | ✅ | ✅ | ✅ |
| wireguard  | ✅ | ✅ | ✅ | ✅ |

~目前不支持解析 clash 订阅~ 仅实现了对（**v2 或 clash 订阅格式**）中勾选协议分享链接的解析。您可以自行编写协议解析代码。

**此脚本仅供个人使用。我使用 [yacd](https://yacd.metacubex.one)（iOS 用户请使用 http://yacd.metacubex.one）管理节点切换（outbound 类型为 `urltest` 和 `selector`）和分流规则。**

**脚本可通过 vercel 服务器部署运行于网页，或者下载项目源码后本地运行。请使用您自己部署的网站生成 sing-box 配置文件。**

# I. 服务器部署

## 快速开始

1. 点击此项目右上角的 Fork 按钮，将此项目 Fork 到您的仓库；
2. 点击右侧按钮开始部署：
   [![通过 Vercel 部署](https://vercel.com/button)](https://vercel.com/new)，直接使用 GitHub 账号登录；[请参阅详细教程](../docs/vercel-en.md#how-to-create-a-new[...]
3. 部署完成后即可开始使用；
4. （可选）[绑定自定义域名](https://vercel.com/docs/concepts/projects/domains/add-a-domain)：某些地区 vercel 分配的域名 DNS 被污染，绑定自定义域名以便连接使用。

### 开启自动更新

> 如果遇到 Upstream Sync 执行错误，请手动点击 Sync Fork！

Fork 项目后，由于 GitHub 的限制，您需要手动进入 Fork 项目的 Actions 页面，启用 Workflows，并启用 Upstream Sync Action，如下图所示：

![AutoUpdate](https://github.com/Toperlock/ChatGPT-Next-Web/raw/main/docs/images/enable-actions.jpg)

![启用自动更新](https://github.com/Toperlock/ChatGPT-Next-Web/raw/main/docs/images/enable-actions-sync.jpg)

### 手动更新代码

如果想立即启用手动更新，请查阅 [GitHub 文档](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/working-with-forks/syncing-a-fork) 了解相关信息。

您可以 star/watch 项目或关注作者以获知新功能。

## 页面操作步骤

[示例网站](https://sing-box-subscribe.vercel.app/)。打开您部署的网站，编辑右侧 `编辑服务器 TEMP_JSON_DATA` 框的内容，点击 `保存`，选择配置[...]

iOS 使用快捷指令复制网页内容，或者内容太多时选择下载文件，自行解决文件后缀问题。👉🏻[快捷指令安装](ht[...]

Android 使用 Chrome 浏览器打开网页生成配置文件（请到浏览器设置 - 辅助功能中缩小网页），长按内容，全选后选择[...]

**注意保存后立即生成配置文件，否则您填写的内容会保留在网页上，其他人打开时可能会浏览到。**

<div align="left">
  <img src="https://github.com/Toperlock/sing-box-subscribe/assets/86833913/f794806c-edfc-4951-a216-6e38646f3791" alt="如何使用" width="50%" />
</div>


# II. 本地安装
### 在您的电脑上安装 [Python](https://www.python.org/) 3.10 或更高版本。确保将 Python 添加到系统环境变量中（可参考 Google 的安装步骤）。

<div align="left">
  <img src="https://github.com/Toperlock/sing-box-subscribe/assets/86833913/f387322b-a602-40df-b3b6-95561329f2f8" alt="安装" width="60%" />
</div>

### 在终端中输入以下命令安装依赖项（Mac 系统将 `pip` 替换为 `pip3`）：

```
pip install -r requirements.txt
```

<div align="left">
  <img src="https://github.com/Toperlock/sing-box-subscribe/assets/86833913/0fc03b49-4c57-4ef3-a4fc-044c1a108d75" alt="安装" width="60%" />
</div>

### 下载 `sing-box-subscribe` 项目并打开终端，导航到项目目录（您可以直接在文件路径中输入 `cmd`）。

<div align="left">
  <img src="https://github.com/Toperlock/sing-box-subscribe/assets/86833913/73f05ba8-105c-4f10-8e6c-16e27f26c084" alt="运行" width="60%" />
</div>

### 将您的订阅链接放入 `providers.json` 中，编辑 `config_template_groups_tun.json` 文件，并在编辑模板后使用以下命令运行脚本：

```
python main.py
```

或者您可以直接通过 `template_index` 选择模板，`0` 表示第一个模板（不支持 flask）。

```
python main.py --template_index=0
```

对于 Windows 系统，推荐将命令添加到批处理程序中以便执行。

在使用前，确保编辑 `providers.json` 文件以及 `config_template` 目录中的 `.json` 模板文件。

提供了一个懒人配置文件 `config_template_groups_rule_set_tun`，该文件允许基于不同类别筛选节点：
* 实现 `Openai` 路由规则
* 实现 `Youtube` 路由规则
* 实现 `Google` 路由规则
* 实现 `Github` 路由规则
* 实现 `Telegram` 路由规则
* 实现 `Twitter` 路由规则
* 实现 `Facebook` 路由规则
* 实现 `Instagram` 路由规则
* 实现 `Bilibili` 路由规则
* 实现 `Bahamut` 路由规则
* 实现 `Spotify` 路由规则
* 实现 `TikTok` 路由规则
* 实现 `Netflix` 路由规则
* 实现 `Disney+` 路由规则
* 实现 `Apple` 路由规则
* 实现 `Amazon` 路由规则
* 实现 `Microsoft` 路由规则
* 实现 `Game` 路由规则
* 实现 `Hbo` 路由规则
* 实现 `Prime Video` 路由规则

# providers.json 文件
在此文件中，您可以添加订阅链接和基本设置。
```json
{
    "subscribes":[
        {
            "url": "https://4gviet.com/api/v1/client/subscribe?token=xx",
            "tag": "airport1_tag", //可保持默认无需修改
            "enabled": true, //启用此链接的转换
            "emoji": 1, //添加国旗 emoji
            "subgroup": "",
            "prefix": "", //不添加节点名称前缀
            "ex-node-name": "网站|流量|过期", //过滤包含关键词的节点
            "User-Agent":"clashmeta" //设置浏览器 UA
        },
        {
            "url": "https://5gtocdocao.com/api/v1/client/subscribe?token=xx",
            "tag": "airport2_tag", //可保持默认无需修改
            "enabled": false, //禁用此链接的转换
            "emoji": 0, //不添加国旗 emoji
            "subgroup": "named", //命名订阅链接
            "prefix": "❤️node_name prefix - ", //添加节点名称前缀
            "User-Agent":"clashmeta" //设置浏览器 UA
        }
    ],
    "auto_set_outbounds_dns":{
        "proxy": "",
        "direct": ""
    },
    "save_config_path": "./config.json",
    "auto_backup": false,
    "exclude_protocol": "ssr", //不解析 ssr 节点！！！
    "config_template": "", //自定义正确的网页 json 配置模板链接
    "Only-nodes": false //输出完整的 sing-box 配置
}
```
- `url`：必填。

> 支持设置常规 V2 订阅链接（**内容为 base64 编码**）

> 支持设置 clash 订阅链接

> 支持设置 sing-box 订阅链接

> 支持设置本地文件路径（**内容为标准 URI 链接或 Clash 字段**）

    本地文件后缀为 `.txt` 的需要在文件中按行添加单个节点分享链接，例如以 `ss://` 开头（非订阅链接）。

    本地文件后缀为 `.yaml` 的，需要正确填写 clash proxies 字段。

    本地文件需保存在同一驱动器中。本地路径格式：`/Desktop/sing-box-subscribe/xx.txt` 或与 `main.py` 同文件夹的相对路径格式：`./xx.txt`。

- `tag`：必填。保持默认即可。

> 使用此 tag 填入配置模板以添加此订阅。此处的 "airport1_tag" 对应于配置模板中的 "{机场1}"。具体用法见配置模板部分。

<details>
      <summary>tag 截图参考</summary>

<div align="left">
  <img src="https://github.com/Toperlock/sing-box-subscribe/assets/86833913/781c5bb7-c5c5-467e-a6ae-05ff44a19973" alt="下载" width="65%" />
</div>

</details>




- `enabled`：可选。**设置为 false 时，此订阅将被忽略**。

- `emoji`：可选。**设置为 false 或 0 时，节点名称将不会包含国家旗帜 emoji**。

- `subgroup`：可选。为订阅链接命名并生成 outbound。

- `prefix`：可选。设置自定义前缀，会添加到节点名称的开头。如果未设置，则不添加前缀。

- `ex-node-name`：可选。过滤包含关键词的节点。多个关键词用 `|` 分隔。

- `User-Agent`：可选。您可以自定义 UA，例如将 UA 设置为 "clash.meta" 或 "sing-box"。

<details>
      <summary>prefix 效果参考</summary>
  
![Snipaste_2023-05-02_12-53-27](https://user-images.githubusercontent.com/21310130/235582317-6bb3d0a6-916f-445f-999b-f17b3db41eea.png)

</details>

- `auto_set_outbounds_dns`：可选。
> 包括 `proxy` 和 `direct` 设置。

> `proxy` 和 `direct` 应设置为配置模板文件中 `dns server` 的 `tag`。

> 设置此选项后，脚本会自动适配路由规则中的 DNS 规则。

> 路由规则中设置为 `direct` 的出站规则的 DNS 服务器将设置为指定的 `direct` 出站。

> 路由规则中需要代理的出站规则将设置为相应的 `proxy` 出站，脚本会自动为代理出站创建相应的 `dns server`。

- `save_config_path`：必填。设置生成的配置文件路径。

- `auto_backup`：可选。
> 当设置为 true 时，脚本会将当前使用的 sing-box 配置文件重命名为 `原文件名.当前时间.bak` 进行备份，以防生成了错误的配置文件。

- `exclude_protocol`：可选。
> 设置需要排除的协议，多个协议用逗号分隔，例如 ssr, vmess。

> 使用此设置中的协议的分享链接将被忽略。

> sing-box 发布程序不支持 ssr（需要额外参数构建），因此此设置可能有用。

- `config_template`：可选。输入正确的网页 json 配置模板链接，以从此模板生成 sing-box 配置。

- `Only-nodes`：可选。
> 设置为 true 或 1 时，仅输出订阅链接的 sing-box 格式的节点信息。

# 配置模板文件
脚本将搜索 `config_template` 目录中的 JSON 模板文件，您可以在脚本运行时选择使用哪个模板文件。

例如，目录中有 `tun.json` 和 `socks.json` 模板文件。

![Snipaste_2023-03-24_22-16-49](https://user-images.githubusercontent.com/21310130/227548643-ffbf3825-9304-4df7-9b65-82a935227aef.png)

脚本不会验证模板文件的正确性。如果模板文件不正确，将会发生错误，脚本也无法运行。

模板文件类似于 sing-box 配置，但添加了一些新参数，例如 `{all}`、`{机场tag}`（翻译为 `{airport_tag}`）、`filter`，这些仅适用于 `urltest` 和 `clash_mode` 模式：

```json
{
  "tag":"proxy",
  "type":"selector",
  "outbounds":[
    "auto",
    "{all}"//所有订阅的所有节点都会被添加到此 tag 的位置
  ],
  "filter":[
    //此过滤器会移除 airport1_tag 中包含 ˣ² 的节点
    {"action":"exclude","keywords":["ˣ²"],"for":["机场1"]}
  ]
},
{
  "tag":"netflix",
  "type":"selector",
  "outbounds":[
    "{机场1}",//带有 airport1_tag 的节点将被添加到此 tag 的位置
    "{机场2}"//带有 airport2_tag 的节点将被添加到此 tag 的位置
  ],
  "filter":[
    //如果 airport1_tag 和 airport2_tag 中的节点名称包含 'sg'、'新加坡'、'tw'、'台湾'，它们将共同构成 netflix 组
    {"action":"include","keywords":["sg|新加坡|tw|台湾"]},
    //“for” 设置为 airport1_tag，表示此规则仅适用于 airport1_tag
    {"action":"exclude","keywords":["ˣ²"],"for":["机场1"]}
    //此过滤器会移除 airport1_tag 中包含 ˣ² 的节点
  ]
}
```

- `{all}`：表示所有订阅中的所有节点。脚本会将所有节点添加到带有此标识的 `outbounds` 中。

- `{机场tag}`（翻译为 `{airport_tag}`）：在 `providers.json` 中设置的机场 `tag` 可在此处使用，表示此订阅中的所有节点。

- `filter`：可选。节点过滤器，是一个数组对象，您可以添加任意数量的规则，格式如下：
```json
"filter": [
    {"action": "include", "keywords": ["keyword1|keyword2"]},
    {"action": "exclude", "keywords": ["keyword1|keyword2"], "for": ["airport1_tag", "airport2_tag"]}
  ]
```

- **关键词区分大小写**

- `include`：添加要保留的关键词，使用 `|` 连接多个关键词。包含这些关键词的节点名称会被保留，其余节点会被删除。

- `exclude`：添加要排除的关键词，使用 `|` 连接多个关键词。包含这些关键词的节点名称会被删除，其余节点会被保留。

- `for`：可选。设置机场 `tag`，可以是多个。此规则仅适用于指定的机场，其他机场将忽略此规则。

多个规则按顺序执行。

# Windows sing-box 使用说明

1. 下载 Windows 客户端程序 [sing-box-windows-amd64.zip](https://github.com/SagerNet/sing-box/releases)。
2. 创建一个 `.bat` 批处理文件，内容为 `start /min sing-box.exe run`。
3. 参考 [客户端配置](https://github.com/chika0801/sing-box-examples/blob/main/Tun/config_client_windows.json) 示例，根据需要修改，并将文件名更改为 **config.json**，然后放置在与 sing-box 同一目录下。
4. 右键点击 **sing-box.exe**，选择属性，转到兼容性选项卡，选择以管理员身份运行程序。
5. 运行批处理文件，在弹出的用户账户控制对话框中选择是。

## 隐藏 Windows 运行 sing-box 时弹出的 cmd 窗口

> 使用 WinSW 将 sing-box.exe 设置为 Windows 服务，[WinSW 教程](https://github.com/winsw/winsw)

> 修改 XML 配置文件
```xml
<service>
  <id>sing-box</id>
  <name>sing-box</name>
  <description>sing-box 服务</description>
  <executable>./sing-box.exe</executable>
  <log mode="reset"></log>
  <arguments>run</arguments>
</service>
```
<details>
      <summary>Windows sing-box 文件夹内容</summary>
 
<div align="left">
  <img src="https://github.com/Toperlock/sing-box-subscribe/assets/86833913/c6a815bf-b542-43c6-aeb6-84020586a1f1" alt="下载" width="50%" />
</div>

</details>

## 在无图形界面的客户端中，操作时不使用 tun

例如，如果您在 Windows 上使用内核运行 sing-box，请删除 inbounds 中的 tun 字段：

```json
"inbounds": [
    {
      "type": "mixed",
      "listen": "127.0.0.1",
      "listen_port": 2080, //此端口必须与 Windows 代理端口一致
      "sniff": true,
      "set_system_proxy": true,
      "sniff_override_destination": false,
      "domain_strategy": "ipv4_only"
    }
  ]
```

<div align="left">
  <img src="https://github.com/Toperlock/sing-box-subscribe/assets/86833913/387f2077-b8b6-42ed-9658-361b28179db2" alt="下载" width="50%" />
</div>

<details>
      <summary><b>效果参考</b></summary>

具体效果取决于各自的出站和规则设置。

<div align="left">
  <img src="https://user-images.githubusercontent.com/21310130/227577941-01c80cfc-1cd9-4f95-a709-f5442a2a2058.png" alt="下载" width="50%" />
  <img src="https://user-images.githubusercontent.com/21310130/227577968-6747c7aa-db61-4f6c-b7cc-e3802e34cc3d.png" alt="下载" width="50%" />
  <img src="https://github.com/Toperlock/sing-box-subscribe/assets/86833913/955968d7-98e7-4bd2-a582-02576877dba1" alt="下载" width="50%" />
  <img src="https://github.com/Toperlock/sing-box-subscribe/assets/86833913/9e7c35ff-c6c4-46c4-a74b-624ff72c17ea" alt="下载" width="50%" />
</div>

</details>

# 致谢
- [xream](https://github.com/xream)
- [sing-box](https://github.com/SagerNet/sing-box)
- [yacd](https://github.com/haishanh/yacd)
- [clash](https://github.com/Dreamacro/clash)
- [sing-box-examples@chika0801](https://github.com/chika0801/sing-box-examples)

部分协议解析参考自 [convert2clash](https://github.com/waited33/convert2clash)。

部分 clash2v2ray 解析参考自 [clash2base64](https://github.com/yuanyiwei/toys/blob/master/DEPRECATED/clash/clash2base64.py)。

部分代码同步参考自 [ChatGPT-Next-Web](https://github.com/Yidadaa/ChatGPT-Next-Web)。

感谢 @SayRad 提供的越南语翻译。

