---
tags:
  - vim
---
以下是对你上传的四个文件内容的完整中文翻译：

---

## 📄 Home.md（首页）

欢迎来到 nvimdots 的 Wiki！

这是一个使用 `Lua` 编写的 Neovim 配置，旨在提供一个易于使用和自定义的基础配置。

### 直接使用

请参考 [Wiki: 必要条件](https://github.com/ayamir/nvimdots/wiki/Prerequisites) 安装所需的软件包。

### 自定义使用

请查阅 [Wiki: 使用说明](https://github.com/ayamir/nvimdots/wiki/Usage)，了解如何根据你的具体需求调整此配置。

### 包含的插件

详情请参见 [Wiki: 插件列表](https://github.com/ayamir/nvimdots/wiki/Plugins)，其中包含所有集成插件的详细信息。

### 默认快捷键

查看 [Wiki: 快捷键](https://github.com/ayamir/nvimdots/wiki/Keybindings)，了解默认的快捷键设置。

### NixOS 支持

如需 NixOS 下的配置支持，请查阅 [Wiki: NixOS 支持](https://github.com/ayamir/nvimdots/wiki/NixOS-Support) 页面。

### 常见问题 FAQ

常见问题解答请参考 [Wiki: 问题汇总](https://github.com/ayamir/nvimdots/wiki/Issues)。

### 知识花园（Knowledge Garden）

更多高级技巧和知识，请查看 [Wiki: 知识花园](https://github.com/ayamir/nvimdots/wiki/Knowledge-Garden)。

再次感谢你使用这个配置！

---

## 📄 Issues.md（问题汇总）

### Windows 上剪贴板无法正常工作？

请参考 [Neovim 官方 FAQ](https://github.com/neovim/neovim/wiki/FAQ#how-to-use-the-windows-clipboard-from-wsl)，并确保 `win32yank.exe` 已添加到你的 `$PATH` 环境变量中。我们不使用 `clip.exe` 进行复制操作，因为它不能正确处理 UTF-8 编码字符串。

更多信息请参见此 issue：  
[https://github.com/ayamir/nvimdots/issues/762](https://github.com/ayamir/nvimdots/issues/762)

### LSP 服务器无法自动启动？

请查阅 [nvim-lspconfig 的服务器配置文档](https://github.com/neovim/nvim-lspconfig/blob/master/doc/server_configurations.md)，以确保你的项目目录能被识别为有效的根目录。例如对于 `gopls`（Go 语言服务器）来说，需要存在 `.mod` 文件等标识来触发 LSP 启动。

---

## 📄 Keybindings.md（快捷键绑定）

### Snippets（代码片段）相关快捷键

- **`lua/keymap/completion.lua`**  
  https://github.com/ayamir/nvimdots/blob/main/lua/keymap/completion.lua

- **`lua/modules/configs/completion/cmp.lua`**  
  用于补全相关的快捷键  
  https://github.com/ayamir/nvimdots/blob/main/lua/modules/configs/completion/cmp.lua

- **`lua/keymap/editor.lua`**  
  https://github.com/ayamir/nvimdots/blob/main/lua/keymap/editor.lua

- **`lua/keymap/lang.lua`**  
  https://github.com/ayamir/nvimdots/blob/main/lua/keymap/lang.lua

- **`lua/keymap/tool.lua`**  
  https://github.com/ayamir/nvimdots/blob/main/lua/keymap/tool.lua

---

## 📄 Knowledge-Garden.md（知识花园）

### 代码片段 Snippets 的配置

基础配置中包含了从 `friendly-snippets` 中直接复制的 `package.json` 文件，位于 `snips` 目录下。如果你需要更高级的使用方式，请参考 [LuaSnip 文档](https://github.com/L3MON4D3/LuaSnip/blob/master/DOC.md)。

#### 添加自己的 Snippet（以 Go 为例）：
1. 检查你的语言在 `package.json` 中定义的 snippet 文件位置。
2. 创建 `snippets/go.json` 文件，并填入如下格式的内容：

```json
{
  "func main": {
    "prefix": "main",
    "body": [
      "func main() {",
      "\t$0",
      "}"
    ],
    "description": "Go main function"
  }
}
```

### C/C++ 编译器依赖项

确保以下工具之一已安装并在你的 `$PATH` 中（根据你使用的语言决定）：
- `clang++`
- `clang`
- `gcc`
- `g++`

#### macOS 用户：
通常可以通过安装 LLVM 来解决这个问题，LLVM 包含了完整的工具链：

```bash
brew install llvm
```

如果你使用的是 `nix-darwin`，请将 `pkgs.llvm` 添加到 `environment.systemPackages` 中：

示例配置文件 `darwin-configuration.nix`：

```nix
{ config, pkgs, lib, ... }:
let
  inherit (pkgs) callPackage fetchFromGitHub;
  inherit (builtins) fetchTarball;
  homeDir = builtins.getEnv "HOME";
in
{
  environment.systemPackages = with pkgs; [
    llvmPackages
  ];

  # 将 nix 安装的 shell 加入 /etc/shells
  shells = with pkgs; [
    zsh
  ];

  # 设置环境变量传递给 zshrc
  variables = {
    PATH = "${pkgs.llvmPackages.out}/bin:$PATH";
  };

  services.nix-daemon.enable = true;
}
```

---

## 🐧 NixOS-Support.md（NixOS 支持）

### 关于 lazy-lock.json 的更新机制

当 `lazy-lock.fixed.json` 的哈希值发生变化时（即上游 `lazy-lock.json` 被修改），会创建一个新的 `lazy-lock.json` 文件，通过合并现有 `lazy-lock.json`（不受 `nix` 管理）和 `lazy-lock.fixed.json` 的内容生成。

在这种情况下，`lazy-lock.fixed.json` 中的版本优先级更高。这意味着：
- 已经由上游管理的插件将使用 `lazy-lock.fixed.json` 中的版本；
- 新增但尚未提交到上游的插件则会被保留。

---

### 示例 NixOS 配置

```nix
{ config, pkgs, lib, ... }:
{
  # 安装到用户作用域
  home.packages = with pkgs; [
    go
  ];

  programs.neovim = {
    # 仅对 Neovim 可见的包
    nvimdots = {
      # 构建所需依赖（include、lib、pkgconfig）
      extraDependentPackages = with pkgs; [ icu ];
      
      # Haskell 包可通过 nvimdots 选项轻松安装
      extraHaskellPackages = hs: with hs; [ ghcup ];
    };

    # 其他运行时依赖包
    extraPackages = with pkgs; [
      go
      # 某些语言需要使用 wrapper
      rWrapper.override {
        packages = with pkgs.rPackages; [
          # R 包列表
        ];
      }
    ];
  };
}
```

---

### Home Manager 配置（Nix 用户推荐）

```nix
home-manager = {
  url = "github:nix-community/home-manager";
  nixpkgs.follows = "nixpkgs";
};
```

### Flakes 支持

```nix
inputs = {
  nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  nvimdots.url = "github:ayamir/nvimdots";
  home-manager = {
    url = "github:nix-community/home-manager";
    nixpkgs.follows = "nixpkgs";
  };
};
```

---

### 静态链接与动态库检查

你可以使用 `ldd <binary>` 检查某个二进制文件所依赖的动态库。也可以通过构建日志（通过 `mason.nvim` 的 UI 查看）查看构建期间所需的依赖项。

如果这些依赖项存在于 `nixpkgs` 中，你可以通过查找对应的 `*.nix` 文件找到你需要的包。

如果你希望稳妥一些，这里列出了 `mason-registry` 中已注册的所有包所需的依赖项：
- `libamd` → https://github.com/zship/libamd
- `libc` → https://www.gnu.org/software/libc/

---

如需进一步帮助配置 Neovim + Mason + LSP 或 NixOS 支持，请告诉我！


以下是你上传的四个文件内容的完整中文翻译：

---

## 📄 NixOS-Support.md（NixOS 支持）

### lazy-lock.json 的更新机制

当 `lazy-lock.fixed.json` 的哈希值发生变化时（即上游的 `lazy-lock.json` 被修改），会创建一个新的 `lazy-lock.json` 文件。新文件是通过将现有的 `lazy-lock.json`（未被 `nix` 管理）与 `lazy-lock.fixed.json` 合并生成的。

在这种情况下，`lazy-lock.fixed.json` 中的版本优先级更高。这意味着：
- 已经由上游管理的插件将使用 `lazy-lock.fixed.json` 中的版本；
- 新增但尚未提交到上游的插件则会被保留。

---

### 如何添加依赖项？

你应该将构建此依赖所需的内容（包括 `include`、`lib` 和 `pkgconfig`）添加到 `programs.neovim.extraDependentPackages` 中。

例如，对于运行时依赖，你可以将对应的依赖项添加到 `home.packages` 或 `programs.neovim.extraPackages` 中。

> **注意**：  
`home.packages` 是用户作用域内的有效配置，而 `programs.neovim.extraPackages` 是 Neovim 作用域内的全局配置。某些语言可能还需要使用 wrapper，请参考下面的示例进行配置。

---

### 示例 NixOS 配置

```nix
{ config, pkgs, lib, ... }:
{
  # 安装到用户作用域
  home.packages = with pkgs; [
    go
  ];

  programs.neovim = {
    # 仅对 Neovim 可见的包
    nvimdots = {
      # 构建所需依赖（include、lib、pkgconfig）
      extraDependentPackages = with pkgs; [ icu ];
      
      # Haskell 包可通过 nvimdots 选项轻松安装
      extraHaskellPackages = hs: with hs; [ ghcup ];
    };

    # 其他运行时依赖包
    extraPackages = with pkgs; [
      go
      # 某些语言需要使用 wrapper
      rWrapper.override {
        packages = with pkgs.rPackages; [
          # R 包列表
        ];
      }
    ];
  };
}
```

---

### Home Manager 配置（Nix 用户推荐）

```nix
home-manager = {
  url = "github:nix-community/home-manager";
  nixpkgs.follows = "nixpkgs";
};
```

---

### Flakes 支持

```nix
inputs = {
  nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  nvimdots.url = "github:ayamir/nvimdots";
  home-manager = {
    url = "github:nix-community/home-manager";
    nixpkgs.follows = "nixpkgs";
  };
};
```

---

### NixOS 配置片段

```nix
{ config, pkgs, lib, ... }:
let
  inherit (pkgs) callPackage fetchFromGitHub;
  inherit (builtins) fetchTarball;
  homeDir = builtins.getEnv "HOME";
in
{
  # 自动垃圾回收
  nix = {
    gc = {
      automatic = true;
      options = "--max-freed $((25 * 1024**3 - 1024 * $(df -P -k /nix/store | tail -n 1 | awk '{ print $4 }')))";
    };
    package = pkgs.nixUnstable;
    # 启用 flake 和实验性命令
    extraOptions = ''
      auto-optimise-store = true
      experimental-features = nix-command flakes
      keep-outputs = true
      keep-derivations = true
      trusted-users = root

flakes
keep-outputs = true
keep-derivations = true
trusted-users = root ${username}
'' + lib.optionalString (pkgs.system == "aarch64-darwin") ''
extra-platforms = x86_64-darwin aarch64-darwin
'';
  };
  environment = {
    systemPackages = with pkgs; [
      llvmPackages
    ];

    # 将 nix 安装的 shell 加入 /etc/shells
    shells = with pkgs; [
      zsh
    ];

    # 设置环境变量传递给 zshrc
    variables = {
      PATH = "${pkgs.llvmPackages.out}/bin:$PATH";
    };
  };

  services = {
    # 自动升级 nix 包和守护进程
    nix-daemon.enable = true;
  };
}
```

---

## 📦 Plugins.md（插件列表）

### 插件依赖关系图

以下是部分插件之间的依赖关系（以 Graphviz 格式表示）：

```
"cmp-latex-symbols" -> "cmp-tabnine (opt)" [color="0.649 0.701 0.701" style="dashed"];
"cmp-tabnine (opt)" -> "codeium.nvim (opt)" [color="0.649 0.701 0.701" style="dashed"];
"nui.nvim (opt)" -> "codeium.nvim (opt)" [color="0.649 0.701 0.701" style="dashed"];
"codeium.nvim (opt)" -> "nvim-cmp" [color="0.649 0.701 0.701" style="dashed"];
"friendly-snippets" -> "LuaSnip" [color="0.649 0.701 0.701" style="dashed"];
CursorHold -> "Comment.nvim" [color="0.649 0.701 0.701"];
CursorHold -> "gitsigns.nvim" [color="0.649 0.701 0.701"];
CursorHold -> "which-key.nvim" [color="0.649 0.701 0.701"];
CursorHold -> "mini.align" [color="0.649 0.701 0.701"];
CursorHold -> "paint.nvim" [color="0.649 0.701 0.701"];
"mason-null-ls.nvim" -> "none-ls.nvim" [color="0.649 0.701 0.701" style="dashed"];
"plenary.nvim" -> "none-ls.nvim" [color="0.649 0.701 0.701" style="dashed"];
CursorHold -> "none-ls.nvim" [color="0.649 0.701 0.701"];
"mason-lspconfig.nvim" -> "mason.nvim" [color="0.649 0.701 0.701" style="dashed"];
"mason.nvim" -> "nvim-lspconfig" [color="0.649 0.701 0.701" style="dashed"];
"nvim-lspconfig" -> "lualine.nvim" [color="0.649 0.701 0.701"];
"nvim-lspconfig" -> "mason.nvim" [color="0.649 0.701 0.701"];
"lspsaga.nvim" -> "lualine.nvim" [color="0.649 0.701 0.701"];
LspAttach -> "neodim" [color="0.649 0.701 0.701"];
LspAttach -> "aerial.nvim" [color="0.649 0.701 0.701"];
LspAttach -> "glance.nvim" [color="0.649 0.701 0.701"];
LspAttach -> "fidget.nvim" [color="0.649 0.701 0.701"];
LspAttach -> "lsp-format-modifications.nvim" [color="0.649 0.701 0.701"];
"nvim-treesitter" -> "neodim" [color="0.649 0.701 0.701" style="dashed"];
"self-contained" -> "persisted.nvim" [color="0.649 0.701 0.701"];
"self-contained" -> "toggleterm.nvim" [color="0.649 0.701 0.701"];
"self-contained" -> "nvim-bufdel" [color="0.649 0.701 0.701"];
"self-contained" -> "nvim-bqf" [color="0.649 0.701 0.701"];
"fzf" -> "nvim-bqf" [color="0.649 0.701 0.701" style="dashed"];
"self-contained" -> "nvim-dap" [color="0.649 0.701 0.701"];
"nvim-dap" -> "nvim-dap-ui" [color="0.649 0.701 0.701" style="dashed"];
"plenary.nvim" -> "telescope-undo.nvim" [color="0.649 0.701 0.701" style="dashed"];
"telescope-undo.nvim" -> "telescope.nvim" [color="0.649 0.701 0.701" style="dashed"];
"telescope.nvim" -> "telescope-fzf-native.nvim" [color="0.649 0.701 0.701"];
"telescope-fzf-native.nvim" -> "search.nvim" [color="0.649 0.701 0.701" style="dashed"];
"search.nvim" -> "telescope-frecency.nvim" [color="0.649 0.701 0.701"];
```

---

### 插件分类

#### 补全相关
- **`neovim/nvim-lspconfig`**：Neovim 原生 LSP 配置
- **`williamboman/mason.nvim`**：用于管理 LSP/DAP 服务器、检查工具和格式化工具的包管理器
- **`williamboman/mason-lspconfig.nvim`**：结合 `nvim-lspconfig` 使用 `mason.nvim`
- **`folke/neoconf.nvim`**：用于管理全局和项目本地设置
- **`Jint-lzxy/lsp_signature.nvim`**：在补全函数参数时显示签名
- **`glepnir/lspsaga.nvim`**：提供更好的 LSP 功能体验
- **`nvim-tree/nvim-web-devicons`**：nerdfont 图标源
- **`stevearc/aerial.nvim`**：代码大纲窗口，便于浏览和快速导航

#### DAP（调试适配器协议）
- **`DNLHC/glance.nvim`**：预览、导航和编辑 LSP 位置
- **`joechrisellis/lsp-format-modifications.nvim`**：部分格式化修改的代码
- **`nvimtools/none-ls.nvim`**：通过 Lua 使用 Neovim 作为语言服务器
- **`vim-lua/plenary.nvim`**：Lua 函数集合
- **`jay-babu/mason-null-ls.nvim`**：结合 `null-ls` 使用 `mason.nvim`
- **`hrsh7th/nvim-cmp`**：Neovim 的自动补全插件
- **`L3MON4D3/LuaSnip`**：用于 `nvim-cmp` 的 snippets 引擎
- **`rafamadriz/friendly-snippets`**：`LuaSnip` 的 snippets 来源
- **`lukas-reineke/cmp-under-comparator`**：为 `nvim-cmp` 提供更好的排序支持

#### 编辑增强
- **`mfussenegger/nvim-treehopper`**：像 `hop.nvim` 一样选择文本对象
- **`nvim-treesitter/nvim-treesitter-textobjects`**：在文本对象之间移动
- **`windwp/nvim-ts-autotag`**：更快的 `vim-closetag`
- **`nvim-treesitter-context`**：显示当前缓冲区内容的上下文
- **`JoosepAlviste/nvim-ts-context-commentstring`**：基于上下文的注释字符串处理
- **`LangKevin/nvim-bqf`**：更强大的 quickfix 插件
- **`ray-x/go.nvim`**：Golang 插件
- **`mrcjkb/rustaceanvim`**：Rust 插件
- **`Saecki/crates.nvim`**：管理 `crates.io` 依赖
- **`iamcco/markdown-preview.nvim`**：渲染 Markdown 预览
- **`chrisbra/csv.vim`**：CSV 处理插件

#### 工具类
- **`nvim-treesitter`**：语法高亮和解析库
- **`lualine.nvim`**：状态栏插件
- **`local-highlight.nvim`**：局部高亮插件
- **`nvim-ts-autotag`**：自动闭合标签
- **`rainbow-delimiters.nvim`**：彩虹括号插件
- **`nvim-treesitter-textobjects`**：文本对象操作插件
- **`gitsigns.nvim`**：Git 行级标记
- **`Comment.nvim`**：智能注释插件
- **`which-key.nvim`**：快捷键提示插件
- **`mini.align`**：快速对齐插件
- **`paint.nvim`**：颜色主题绘制插件
- **`persisted.nvim`**：会话保存插件
- **`toggleterm.nvim`**：浮动终端插件
- **`nvim-bufdel`**：缓冲区删除插件
- **`nvim-bqf`**：改进的 quickfix 插件
- **`vim-cool`**：搜索后取消高亮插件
- **`vim-fugitive`**：Git 插件
- **`vim-matchup`**：匹配插件
- **`vim-rhubarb`**：GitHub 快捷方式
- **`vim-sleuth`**：自动检测缩进设置
- **`which-key.nvim`**：快捷键提示插件
- **`wilder.nvim`**：命令行增强插件

---

## ⚙️ Prerequisites.md（前置条件）

### Windows 上剪贴板问题

请参考 [Neovim 官方 FAQ](https://github.com/neovim/neovim/wiki/FAQ#how-to-use-the-windows-clipboard-from-wsl)，并确保 `win32yank.exe` 已添加到你的 `$PATH` 环境变量中。我们不使用 `clip.exe` 进行复制操作，因为它不能正确处理 UTF-8 编码字符串。

更多信息请参见此 issue：  
[https://github.com/ayamir/nvimdots/issues/762](https://github.com/ayamir/nvimdots/issues/762)

---

### macOS 编译器依赖项

请确保至少有一个以下工具存在于你的 `$PATH` 中（根据你使用的语言决定）：
- `clang++`
- `clang`
- `gcc`
- `g++`

#### macOS 用户：
通常可以通过安装 LLVM 来解决这个问题，LLVM 包含了完整的工具链：

```bash
brew install llvm
```

如果你使用的是 `nix-darwin`，请将 `pkgs.llvm` 添加到 `environment.systemPackages` 中：

示例配置文件 `darwin-configuration.nix`：

```nix
{ config, pkgs, lib, ... }:
let
  inherit (pkgs) callPackage fetchFromGitHub;
  inherit (builtins) fetchTarball;
  homeDir = builtins.getEnv "HOME";
in
{
  # 自动清理 Nix 存储
  nix = {
    gc = {
      automatic = true;
      options = "--max-freed $((25 * 1024**3 - 1024 * $(df -P -k /nix/store| tail -n 1| awk '{ print $4 }')))";

    };
    package = pkgs.nixUnstable;
    extraOptions = ''
      auto-optimise-store = true
      experimental-features = nix-command flakes
      keep-outputs = true
      keep-derivations = true
      trusted-users = root

flakes
keep-outputs = true
keep-derivations = true
trusted-users = root ${username}
'' + lib.optionalString (pkgs.system == "aarch64-darwin") ''
extra-platforms = x86_64-darwin aarch64-darwin
'';
  };
  environment = {
    systemPackages = with pkgs; [
      llvmPackages
    ];

    # 将 nix 安装的 shell 加入 /etc/shells
    shells = with pkgs; [
      zsh
    ];

    # 设置环境变量传递给 zshrc
    variables = {
      PATH = "${pkgs.llvmPackages.out}/bin:$PATH";
    };
  };

  services = {
    # 自动升级 nix 包和守护进程服务
    nix-daemon.enable = true;
  };
}
```

---

## ⚙️ Usage.md（使用说明）

### 修改配置

你可以在 `user/settings.lua` 中自定义配置：

#### 合并条目：

```lua
settings["lsp_deps"] = {
  "zls", -- Zig 语言服务器
}
```

结果如下：

```lua
{
  "bashls",
  "clangd",
  "html",
  "jsonls",
  "lua_ls",
  "pylsp",
  "zls"
}
```

#### 覆盖条目：

```lua
settings["lsp_deps"] = function(defaults)
  return {
    defaults[5], -- "lua_ls"
    defaults[6], -- "pylsp"
    "zls", -- Zig 语言服务器
  }
end
```

结果如下：

```lua
{
  "lua_ls",
  "pylsp",
  "zls"
}
```

---

### 主题与高亮覆盖

你可以通过 `require("modules.utils.icons").get(category, add_space?)` 获取图标。

图标列表可在此查看：  
[图标列表链接](https://github.com/ayamir/nvimdots/blob/main/lua/modules/utils/icons.lua)

#### 示例高亮覆盖：

```lua
highlight_overrides = {
  all = function(colors)
    return {
      NvimTreeNormal = { fg = colors.none },
      CmpBorder = { fg = "#3E4145" },
    }
  end,
  latte = function(latte)
    return {
      Normal = { fg = ucolors.darken(latte.base, 0.7, latte.mantle) },
    }
  end,
  frappe = function(frappe)
    return {
      ["@comment"] = { fg = frappe.surface2, style = { "italic" } },
    }
  end,
  macchiato = function(macchiato)
    return {
      LineNr = { fg = macchiato.overlay1 },
    }
  end,
  mocha = function(mocha)
    return {
      Comment = { fg = mocha.flamingo },
    }
  end,
}
```

---

如需进一步帮助配置 Neovim + Mason + LSP 或 NixOS 支持，请告诉我！



 