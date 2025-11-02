```lua
-- =============================================================================
-- 可开关的 Fcitx5 输入法自动切换 (V6 - 终极版)
--
-- 核心逻辑：
-- 1. 采纳您的成功发现：移除了在 InsertEnter 中对 vim.fn.mode() 的检查。
-- 2. 引入了专门处理替换模式(R)的逻辑，防止其错误地切换为中文。
-- 3. 确保了在任何情况下，Normal 模式都保持英文输入法。
--
-- 依然根据您的系统定制：
-- `!fcitx5-remote -o` --> 英文
-- `!fcitx5-remote -c` --> 中文
-- =============================================================================

-- 开关，默认设置为 false (禁用)
vim.g.auto_im_switch_enabled = false

local commands = {
  to_english = 'silent !fcitx5-remote -o',
  to_chinese = 'silent !fcitx5-remote -c',
}

local fcitx5_group = vim.api.nvim_create_augroup('Fcitx5ToggleableSwitch', { clear = true })

-- 当离开插入/替换模式时，切换回英文
vim.api.nvim_create_autocmd('InsertLeave', {
  group = fcitx5_group,
  pattern = '*',
  callback = function()
    if vim.g.auto_im_switch_enabled then
      vim.cmd(commands.to_english)
    end
  end,
})

-- [[ 核心修正 ]]
-- 当进入插入模式时，直接切换
-- (根据您的发现，移除了不可靠的 vim.fn.mode() 检查)
vim.api.nvim_create_autocmd('InsertEnter', {
  group = fcitx5_group,
  pattern = '*',
  callback = function()
    if vim.g.auto_im_switch_enabled then
      vim.cmd(commands.to_chinese)
    end
  end,
})

-- [[ 替换模式(R)问题的最终解决方案 ]]
-- 当我们即将进入替换模式时，临时禁用一次自动切换
vim.api.nvim_create_autocmd('ModeChanged', {
  group = fcitx5_group,
  -- 模式从 "n" (Normal) 变为 "R" (Replace) 时触发
  pattern = 'n:R',
  callback = function()
    -- 如果总开关是开的，就临时把它关掉
    if vim.g.auto_im_switch_enabled then
      vim.g.auto_im_switch_enabled = false
      -- 然后，我们设置一个一次性的命令，在离开替换模式后，再把开关重新打开
      vim.api.nvim_create_autocmd('InsertLeave', {
        group = fcitx5_group,
        once = true, -- 这个命令只执行一次就自动销毁
        callback = function()
          vim.g.auto_im_switch_enabled = true
        end,
      })
    end
  end,
})

-- 切换开关的函数 (无需改动)
local function toggle_im_switch()
  vim.g.auto_im_switch_enabled = not vim.g.auto_im_switch_enabled
  if vim.g.auto_im_switch_enabled then
    vim.notify("✅ 输入法自动切换已开启", vim.log.levels.INFO)
  else
    vim.notify("❌ 输入法自动切换已禁用 (英文模式)", vim.log.levels.INFO)
    vim.cmd(commands.to_english)
  end
end

-- 创建命令和快捷键 (无需改动)
vim.api.nvim_create_user_command('ToggleIMSwitch', toggle_im_switch, {})
vim.keymap.set('n', '<Leader>im', toggle_im_switch, { noremap = true, silent = true, desc = "切换输入法自动切换" })

-- 启动时确保初始状态是英文
vim.cmd(commands.to_english)
vim.notify("输入法切换已加载 (默认禁用)，使用 <Leader>im 或 :ToggleIMSwitch 开启中文模式", vim.log.levels.INFO)
```