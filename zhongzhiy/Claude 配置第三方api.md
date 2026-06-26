Claude Code 把“是否已完成首次引导”的状态死死地记录在主目录下的另一个隐藏文件 **`~/.claude.json`** 里

写入`'{ "hasCompletedOnboarding": true } | save -f ~/.claude.json`来重置引导

## 配置Claude
在`~/.claude/setting.json`中写入

```json
{
  "env": {
    "ANTHROPIC_BASE_URL": "https://api.siliconflow.cn/",
    "ANTHROPIC_AUTH_TOKEN": "你的_SILICONFLOW_API_KEY",
    "ANTHROPIC_MODEL": "Pro/zai-org/GLM-4.7",
    "ANTHROPIC_DEFAULT_SONNET_MODEL": "Pro/zai-org/GLM-4.7",
    "ANTHROPIC_DEFAULT_HAIKU_MODEL": "Pro/zai-org/GLM-4.7",
    "CLAUDE_CODE_DISABLE_NONESSENTIAL_TRAFFIC": "1"
  }
}
```

同时在shell中也写上相似的变量