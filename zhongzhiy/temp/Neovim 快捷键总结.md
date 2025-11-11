# 🎯 Neovim 快捷键总结

## 📖 说明
- `<leader>` = 空格键 (Space)
- `<localleader>` = 空格键 (Space)
- 所有快捷键在 VSCode Neovim 和普通 Neovim 中都可用

---

## 🔧 基本编辑操作

### 模式切换
| 快捷键 | 功能 | 模式 |
|--------|------|------|
| `i` | 进入插入模式（光标位置） | Normal |
| `a` | 进入插入模式（光标后一位） | Normal |
| `o` | 新建下一行并进入插入模式 | Normal |
| `O` | 新建上一行并进入插入模式 | Normal |
| `Esc` | 返回普通模式 | Insert/Visual |
| `Esc` | 清除搜索高亮 | Normal |

### 移动
| 快捷键 | 功能 | 模式 |
|--------|------|------|
| `h` | 左移 | Normal |
| `j` | 下移 | Normal |
| `k` | 上移 | Normal |
| `l` | 右移 | Normal |
| `w` | 移动到下一个单词 | Normal |
| `b` | 移动到上一个单词 | Normal |

### 编辑
| 快捷键 | 功能 | 模式 |
|--------|------|------|
| `dd` | 删除整行 | Normal |
| `x` | 删除单个字符 | Normal |
| `u` | 撤销 | Normal |
| `Ctrl+r` | 重做 | Normal |
| `yy` | 复制行 | Normal |
| `p` | 粘贴 | Normal |

---

## 🪟 窗口和分割

### 窗口导航
| 快捷键 | 功能 | 描述 |
|--------|------|------|
| `Ctrl+h` | 移动到左侧窗口 | 分割窗口导航 |
| `Ctrl+l` | 移动到右侧窗口 | 分割窗口导航 |
| `Ctrl+j` | 移动到下方窗口 | 分割窗口导航 |
| `Ctrl+k` | 移动到上方窗口 | 分割窗口导航 |

### 终端模式
| 快捷键 | 功能 | 模式 |
|--------|------|------|
| `Esc Esc` | 退出终端模式 | Terminal |

---

## 🔍 搜索和文件

### Telescope 搜索 (Leader + s)
| 快捷键          | 功能           | 描述                  |
| ------------ | ------------ | ------------------- |
| `<leader>sh` | 搜索帮助         | Search Help         |
| `<leader>sk` | 搜索键映射        | Search Keymaps      |
| `<leader>sf` | 搜索文件         | Search Files        |
| `<leader>ss` | 选择 Telescope | Search Select       |
| `<leader>sw` | 搜索当前单词       | Search current Word |
| `<leader>sg` | 全局搜索         | Search by Grep      |
| `<leader>sd` | 搜索诊断         | Search Diagnostics  |
| `<leader>sr` | 恢复搜索         | Search Resume       |
| `<leader>s.` | 搜索最近文件       | Search Recent Files |
| `<leader>sn` | 搜索 Neovim 文件 | Search Neovim files |

### 缓冲区和快速操作
| 快捷键 | 功能 | 描述 |
|--------|------|------|
| `<leader><leader>` | 查找现有缓冲区 | Find existing buffers |
| `<leader>/` | 当前缓冲区模糊搜索 | Fuzzy search in buffer |
| `<leader>s/` | 在打开文件中搜索 | Search in Open Files |

---

## 🔧 LSP 功能

### 代码导航
| 快捷键 | 功能 | 描述 |
|--------|------|------|
| `gd` | 跳转到定义 | Go to Definition |
| `gr` | 跳转到引用 | Go to References |
| `gi` | 跳转到实现 | Go to Implementation |
| `grt` | 跳转到类型定义 | Go to Type Definition |
| `K` | 显示悬停信息 | Show Hover |

### 代码操作
| 快捷键 | 功能 | 描述 |
|--------|------|------|
| `grn` | 重命名符号 | Rename |
| `<leader>ca` | 代码操作 | Code Action |
| `<leader>f` | 格式化文档 | Format buffer |

### 诊断
| 快捷键 | 功能 | 描述 |
|--------|------|------|
| `<leader>q` | 打开诊断快速修复列表 | Diagnostic Quickfix |
| `<leader>th` | 切换内联提示 | Toggle Inlay Hints |

---

## 🌳 Neo-tree 文件树

### 基本操作
| 快捷键 | 功能 | 描述 |
|--------|------|------|
| `<leader>e` | 切换侧边栏 | Toggle Sidebar |
| `Enter` | 打开文件/文件夹 | Open |
| `S` | 水平分割打开 | Open Split |
| `s` | 垂直分割打开 | Open VSplit |
| `t` | 新标签页打开 | Open in Tab |

### 文件操作
| 快捷键 | 功能 | 描述 |
|--------|------|------|
| `a` | 添加文件 | Add File |
| `A` | 添加目录 | Add Directory |
| `d` | 删除 | Delete |
| `r` | 重命名 | Rename |
| `c` | 复制 | Copy |
| `m` | 移动 | Move |
| `y` | 复制到剪切板 | Copy to Clipboard |
| `x` | 剪切到剪切板 | Cut to Clipboard |
| `p` | 从剪切板粘贴 | Paste from Clipboard |

### 导航
| 快捷键 | 功能 | 描述 |
|--------|------|------|
| `<bs>` | 向上导航 | Navigate Up |
| `.` | 设置根目录 | Set Root |
| `H` | 切换隐藏文件 | Toggle Hidden |
| `/` | 模糊查找 | Fuzzy Finder |
| `?` | 显示帮助 | Show Help |
| `q` | 关闭窗口 | Close Window |
| `R` | 刷新 | Refresh |

---

## 🔀 Git 操作

### Git Signs (在缓冲区中)
| 快捷键 | 功能 | 描述 |
|--------|------|------|
| `]c` | 下一个 Git 更改 | Next Git Change |
| `[c` | 上一个 Git 更改 | Previous Git Change |

### Neo-tree Git 状态
| 快捷键 | 功能 | 描述 |
|--------|------|------|
| `A` | Git 添加所有 | Git Add All |
| `gu` | Git 取消暂存 | Git Unstage |
| `ga` | Git 添加文件 | Git Add File |
| `gr` | Git 恢复文件 | Git Revert File |
| `gc` | Git 提交 | Git Commit |
| `gp` | Git 推送 | Git Push |
| `gg` | Git 提交并推送 | Git Commit and Push |

---

## 💻 C++ 开发

### 编译运行
| 快捷键 | 功能 | 描述 |
|--------|------|------|
| `<F6>` | 编译并运行 C++ 文件 | Compile and Run C++ |
| `<F5>` | 启动调试 | Start Debug (VSCode) |

---

## 🎛️ VSCode 特定功能

### 文件操作 (VSCode 模式)
| 快捷键 | 功能 | 描述 |
|--------|------|------|
| `<leader>ff` | 快速打开文件 | Quick Open Files |
| `<leader>fg` | 在文件中查找 | Find in Files |
| `<leader>fr` | 打开最近文件 | Open Recent |
| `<leader>ft` | 选择主题 | Select Theme |

### 窗口管理 (VSCode 模式)
| 快捷键 | 功能 | 描述 |
|--------|------|------|
| `<leader>w` | 保存文件 | Save File |
| `<leader>q` | 关闭编辑器 | Close Editor |
| `<leader>bd` | 删除缓冲区 | Delete Buffer |
| `<leader>sv` | 垂直分割 | Split Vertical |
| `<leader>sh` | 水平分割 | Split Horizontal |

### 编辑操作 (VSCode 模式)
| 快捷键 | 功能 | 描述 |
|--------|------|------|
| `<leader>rn` | 重命名符号 | Rename Symbol |
| `<leader>ca` | 代码操作 | Code Action |
| `<leader>f` | 格式化文档 | Format Document |
| `gcc` | 切换行注释 | Toggle Line Comment |
| `gc` | 切换行注释 | Toggle Line Comment (Visual) |
| `gbc` | 切换块注释 | Toggle Block Comment |

### 终端 (VSCode 模式)
| 快捷键 | 功能 | 描述 |
|--------|------|------|
| `<leader>tt` | 切换终端 | Toggle Terminal |
| `<leader>tn` | 新建终端 | New Terminal |

### 命令和搜索 (VSCode 模式)
| 快捷键 | 功能 | 描述 |
|--------|------|------|
| `<leader>p` | 命令面板 | Command Palette |
| `<leader>/` | 在文件中查找 | Find in Files |

### Git (VSCode 模式)
| 快捷键 | 功能 | 描述 |
|--------|------|------|
| `<leader>gs` | Git 状态 | Git Status |
| `<leader>gc` | Git 提交 | Git Commit |
| `<leader>gp` | Git 推送 | Git Push |

### 诊断 (VSCode 模式)
| 快捷键 | 功能 | 描述 |
|--------|------|------|
| `<leader>xx` | 显示问题 | Show Problems |
| `]d` | 下一个诊断 | Next Diagnostic |
| `[d` | 上一个诊断 | Previous Diagnostic |

---

## 🔗 快捷键组

### `<leader>s` - 搜索组
- **f**: 文件搜索
- **g**: 全局搜索
- **h**: 帮助搜索
- **k**: 键映射搜索
- **w**: 单词搜索
- **d**: 诊断搜索
- **r**: 恢复搜索
- **.**: 最近文件

### `<leader>t` - 切换组
- **h**: 内联提示切换
- **t**: 终端切换
- **n**: 新终端

### `<leader>g` - Git 组
- **s**: Git 状态
- **c**: Git 提交
- **p**: Git 推送

---

## 📝 补全和代码片段

### Blink.cmp 自动补全
| 快捷键 | 功能 | 模式 |
|--------|------|------|
| `Ctrl+Space` | 打开菜单或文档 | Insert |
| `Ctrl+n` / `Down` | 选择下一项 | Insert |
| `Ctrl+p` / `Up` | 选择上一项 | Insert |
| `Ctrl+e` | 隐藏菜单 | Insert |
| `Ctrl+k` | 切换签名帮助 | Insert |
| `Tab` / `Shift+Tab` | 代码片段导航 | Insert |

---

## 🎨 Which-key 显示

按下 `<leader>` 键后会显示可用的快捷键组：
- `s` - 搜索功能
- `t` - 切换功能
- `g` - Git 操作
- `h` - Git 块操作 (Visual 模式)

---

## 💡 提示

1. **学习路径**: 先熟悉基本的 `hjkl` 移动和 `i`, `o`, `a` 插入模式
2. **常用组合**: `<leader>sf` (搜索文件) 和 `<leader>sg` (全局搜索) 是最常用的
3. **C++ 开发**: `<F6>` 可以快速编译运行当前 C++ 文件
4. **Git 工作流**: 使用 Neo-tree 的 Git 功能进行版本控制
5. **VSCode 集成**: 在 VSCode 中所有功能都通过 VSCode API 调用，保持一致性

## 🔄 环境检测

配置会自动检测运行环境：
- **VSCode 环境**: 加载 `vscode_config.lua`，使用 VSCode API
- **普通 Neovim**: 加载完整的 kickstart.nvim 配置

---

**记住**: 空格键是你的 `<leader>` 键，大部分复杂操作都从空格键开始！

