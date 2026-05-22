# 找到所有 .jpg 图片并转换成 .png (需要安装 imagemagick)
    fd -e jpg -x convert {} {.}.png
    ```
    > `{}` 代表完整路径，`{.}` 代表去除扩展名的路径。这比 `find -exec` 的语法简单得多。

---

## 二、 fzf：模糊搜索的终极交互层

`fzf` 并不是一个搜索工具，它是一个**过滤器**。它从标准输入（stdin）接收列表，让你通过打字过滤，最后把选中的结果输出到标准输出（stdout）。

### 1. 核心交互逻辑

`fzf` 的精髓在于 **“模糊匹配”**。比如你想找 `src/main/resources/config.yaml`，你只需要输入 `smrcfg`，它就能通过字符间的跳转帮你精确定位。

### 2. 深度使用场景

*   **场景 1：环境变量与别名搜索**
    你是否经常忘记自己设过哪些 `alias`？
    ```bash
    alias | fzf
    ```
*   **场景 2：极速进程管理**
    比起手动输入 `kill -9 1234`，你可以通过这个组合命令实现“可视化点杀”：
    

    ps -ef | fzf --multi | awk '{print $2}' | xargs kill -9
    
    > `--multi` 允许你用 `Tab` 键勾选多个进程，一次性全部杀掉。

---

## 三、 梦幻联动：fd + fzf + bat + cd

将这些 Rust/Go 编写的工具组合起来，可以极大地改变你操作终端的习惯。

### 1. 打造“超级搜索器”
在你的配置文件（`.bashrc` 或 `.zshrc`）中放入这段进阶脚本：

# 使用 fd 搜索文件，fzf 展示列表，bat 预览内容
# 按下 Ctrl + P 即可触发
alias fp="fd --type f | fzf --preview 'bat --style=numbers --color=always --line-range :500 {}'"