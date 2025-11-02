#!/bin/zsh

# --- 修正开始 ---

# 1. 明确地进入你的 Git 仓库目录
cd /home/saber/bakulman || exit

# 2. 使用 git 命令的绝对路径 (请用 `which git` 的输出来替换)
GIT_CMD="/usr/bin/git"

# 3. 为了调试，暂时将日志输出到文件，而不是 /dev/null
#    当你确认脚本能成功运行后，再改回 /dev/null
LOG_FILE="/home/saber/bakulman/ob_sync.log"

# --- 脚本核心逻辑 ---

# 执行 git 命令，并将所有输出（标准输出和错误输出）追加到日志文件
echo "--- Starting sync at $(date) ---" >> ${LOG_FILE}

# 确保 cron 使用正确的 SSH 密钥
# 如果你的密钥在 ~/.ssh/id_rsa，并且没有密码，通常不需要特殊设置。
# 如果有密码或在其他位置，可能需要配置 GIT_SSH_COMMAND
# export GIT_SSH_COMMAND="ssh -i /home/saber/.ssh/your_private_key"

${GIT_CMD} add . >> ${LOG_FILE} 2>&1
# 检查 add 是否成功
if ${GIT_CMD} diff-index --quiet HEAD --; then
    echo "No changes to commit." >> ${LOG_FILE} 2>&1
else
    ${GIT_CMD} commit -m "sync: auto-sync at $(date)" >> ${LOG_FILE} 2>&1
    ${GIT_CMD} push origin main >> ${LOG_FILE} 2>&1 # 假设你的分支是 main
fi

echo "--- Sync finished at $(date) ---" >> ${LOG_FILE}
echo "" >> ${LOG_FILE}

# --- 修正结束 ---
