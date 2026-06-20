---
date: 2026-06-08
title: alacritty简单配置
tags:
  - alacritty
  - Linux
  - shell
---

[Alacritty](https://alacritty.org/config-alacritty.html#s12)是使用 rust 语言编写的跨平台终端模拟器, 得益于 rust 语言的高性能, alacritty 号称是[最快的终端模拟器]. alacritty 虽然自带开箱即用的配置, 但是折腾折腾让终端更好看可以显著提高使用体验, [alacritty配置文档](https://alacritty.org/config-alacritty.html#s12)内容不多, 所以配置起来也相当简单, 只用挑选需要的内容, 同时直接使用 [alacritty-theme](https://github.com/alacritty/alacritty-theme)搭配颜色就够了. 

我的配置文件:

```toml
# windous 系统配置文件放在 ~/AppData/Roaming/alacritty/alacritty.toml
[general]
# 引入theme
import = [
"C:\\Users\\zzy20\\AppData\\Roaming\\alacritty\\alacritty-theme\\themes\\dark_pastels.toml"
]

[window]
# 窗口大小和位置, 凭感觉调
dimensions = {columns = 100, lines = 40}
position = {x = 800, y = 200}

decorations = "Full"       # 窗口状态栏, 显示, 如果使用None 就不方便实时调整窗口大小
opacity = 0.8              # 背景透明度
startup_mode = "Windowed"  # 启动状态为默认窗口模式
dynamic_title = true       # 窗口状态栏, 动态显示工作目录
padding = {x = 3, y = 3}   # 窗口四周间距, 凭感觉调

[font]
normal = { family = "JetBrainsMono NF" }  # 字体, 随便选个等宽字体就不错

[selection]
save_to_clipboard = true    # 把终端选中复制到剪切板


[terminal]
shell = "C:\\Users\\zzy20\\scoop\\apps\\nu\\current\\nu.exe"  # 默认shell

[cursor]
style = { shape = "block", blinking = "off" }  # 光标形态和状态
```