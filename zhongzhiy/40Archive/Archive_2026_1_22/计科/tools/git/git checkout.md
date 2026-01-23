您提出了一个非常深刻且实际的问题！这正好触及了 Git 团队决定引入 `git switch` 和 `git restore` 的核心原因。

简单来说，您观察得完全正确。`git checkout` 命令功能过于强大和混杂，像一把“瑞士军刀”，既能切换分支，又能恢复文件，还能进入分离头指针状态，这让初学者非常困惑。

因此，Git 2.23 版本引入了两个新的、功能更专一的命令来分担它的工作：
*   `git switch`: **只负责分支的切换**。
*   `git restore`: **只负责文件的恢复**。

现在我们来回答您的两个核心问题。

### 1. 既然有了 `git switch`，`git checkout` 还有什么用？

虽然 `git switch` 和 `git restore` 是官方推荐的新方式，但 `git checkout` 作为一个历史悠久的命令，仍然可以完成所有这些工作。它的主要“剩余价值”在于：

**A. 恢复工作区的文件（这个功能现在更推荐用 `git restore`）**

这是 `git switch` 完全不具备的功能。`git checkout` 依然是撤销文件修改的强大工具。

*   **场景1：撤销对某个文件的所有本地修改**
    ```bash
    # 比如你把 app.py 改乱了，想恢复到上次提交时的样子
    git checkout -- app.py 
    
    # 新的、更清晰的命令是：
    git restore app.py 
    ```

*   **场景2：从过去某次提交中拉取一个文件的版本**
    ```bash
    # 从某个旧的commit中，只把 app.py 这个文件拉回来
    git checkout <commit-hash> -- app.py

    # 新的、更清晰的命令是：
    git restore --source=<commit-hash> app.py
    ```

**B. 向后兼容性与个人习惯**

对于无数的老用户和现存的脚本、教程来说，`git checkout` 已经根深蒂固。Git 团队保留它，确保了向后兼容性，老用户也无需立刻改变自己的习惯。

**总结：** 在现代 Git 工作流中，`git checkout` 的核心功能已经被 `git switch` 和 `git restore` 更清晰地替代了。您可以把它看作一个“遗留命令”，虽然还能用，但**对于新项目和新学习者，强烈建议直接学习和使用 `switch` 与 `restore`**。

---

### 2. 怎么用 `git switch` 回到之前的版本？

这个问题非常好！我们知道 `git checkout <commit-hash>` 可以让我们像“时光旅行”一样回到过去某个提交点，进入一个叫做 **“分离头指针 (detached HEAD)”** 的状态。

`git switch` 同样可以做到这一点，但它使用了一个专门的标志 `--detach` 来清晰地表达这个意图。

**回到过去某个版本的操作：**

假设您想回到哈希值为 `a1b2c3d` 的那个版本进行查看或测试。

*   **旧的方式：**
    ```bash
    git checkout a1b2c3d
    ```

*   **新的、推荐的方式：**
    ```bash
    git switch --detach a1b2c3d
    ```
    或者使用缩写：
    ```bash
    git switch -d a1b2c3d
    ```

使用 `git switch --detach` 的好处是，命令本身就**明确地告诉**你：“我正准备进入一个不属于任何分支的‘分离’状态”，这避免了初学者意外进入该状态而感到困惑。

当你在这个“分离”状态下完成了代码检查或测试，想回到你之前所在的分支（比如 `main`），可以这样做：

```bash
# 切换回 main 分支
git switch main

# 或者，如果你忘了之前在哪个分支，可以用 `-` 切换回上一个分支
git switch - 
```

### 命令对比一览表

| 任务 (Task) | 旧命令 (`checkout`) | 新命令 (`switch`/`restore`) | 推荐 |
| :--- | :--- | :--- | :--- |
| 切换到已存在的分支 | `git checkout feature` | `git switch feature` | ✅ `switch` |
| 创建并切换到新分支 | `git checkout -b new-feature` | `git switch -c new-feature` | ✅ `switch` |
| 回到上一个分支 | `git checkout -` | `git switch -` | ✅ `switch` |
| **回到某个历史版本 (分离HEAD)** | `git checkout <hash>` | `git switch --detach <hash>` | ✅ `switch --detach` |
| **撤销对文件的本地修改** | `git checkout -- <file>` | `git restore <file>` | ✅ `restore` |
| **从历史版本恢复文件** | `git checkout <hash> -- <file>` | `git restore --source=<hash> <file>` | ✅ `restore --source` |

希望这个解释能帮助您彻底理解这几个命令之间的关系！