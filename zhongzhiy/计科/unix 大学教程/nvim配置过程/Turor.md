---
tags:
  - vim
---
以下是上传文件内容的中文翻译：

---

# 欢迎来到 Neovim 教程

Neovim 是一个非常强大的编辑器，它有许多命令，多到无法在这个教程中全部介绍。本教程旨在介绍足够多的命令，使你能够轻松地将 Neovim 用作一个通用的编辑器。

重要的是要记住，这个教程是通过实践来学习的。这意味着你需要动手练习才能正确掌握它们。如果你只是阅读文字，很快就会忘记最重要的内容！

现在，请确保你的 Caps-Lock 键关闭，并按下 `j`{normal} 键多次，直到 Lesson 0 完全填满屏幕。

## 第 0 课

注意：课程中的命令会修改文本，但这些更改不会被保存。不要担心搞砸了；只需记住按下 [<Esc>](<Esc>) 然后 [u](u) 就可以撤销最新更改。

本教程是交互式的，有一些你需要知道的事情：
- 单击链接 [像这样](holy-grail) 打开相关的帮助部分。
- 或者在任何单词上按下 [K](K) 查找其文档！
- 你可以通过 `:q`{vim} `<Enter>`{normal} 关闭此帮助窗口。

当左侧有一个 ✗ 标记时，你需要修改文本。一旦你正确完成了更改，左侧的 ✗ 标记将变为 ✓。我想你已经能想象到 Neovim 可以多么整洁。

有时候，你会被提示运行一个命令（我稍后会解释）：
    `:help`{vim} `<Enter>`{normal}
或者按下一系列按键：
~~~ normal
    <Esc>0f<Space>d3wP$P
~~~
尖括号 `<` 和 `>` 中的内容（如 `<Enter>`{normal}）描述了一个需要按下的键，而不是要输入的文本。

现在，移动到下一课（使用 `j`{normal} 键向下滚动）。

## 第 1.1 课：移动光标
** 要移动光标，请按下 `h`、`j`、`k`、`l` 键，如图所示。**
          ↑
          k         提示：`h`{normal} 键在左边并左移。
     ← h    l →           `l`{normal} 键在右边并右移。
         j                `j`{normal} 键看起来像下箭头。
         ↓
 1. 在屏幕上四处移动光标，直到你感到舒适。
 2. 按住下方向键 (`j`{normal}) 直到重复。
    现在你知道如何转到下一课了。
 3. 使用下方向键，移动到第 1.2 课。
注意：如果你对输入的内容不确定，请按下 <Esc> 进入正常模式。然后重新输入你想要的命令。
注意：光标键也应该工作。但是一旦你习惯了 hjkl，你会发现移动起来更快。

## 第 1.2 课：退出 Neovim
!! 注意：在执行以下任何步骤之前，请通读整个课程 !!
 1. 按下 <Esc> 键（确保你在正常模式下）。
 2. 输入：
    `:q!`{vim} `<Enter>`{normal}
    这将退出编辑器，并丢弃你所做的所有更改。
 3. 打开 Neovim 并通过执行让你进入这个教程的命令返回到这里。那可能是：
    `:Tutor`{vim} `<Enter>`{normal}
 4. 如果你已熟记这些步骤并且有信心，请执行步骤 1 到 3 来退出并重新进入编辑器。
注意：[:q!](:q) `<Enter>`{normal} 会丢弃你所做的任何更改。在几节课后你将学会如何将更改保存到文件中。
 5. 将光标向下移动到第 1.3 课。

## 第 1.3 课：文本编辑：删除
** 按下 `x`{normal} 删除光标下的字符。**
 1. 将光标移动到下面标记为 ✗ 的行。
 2. 要修复错误，请将光标移到要删除的字符上。
 3. 按下 [x 键](x) 删除不需要的字符。
 4. 重复步骤 2 到 4 直到句子正确。
The ccow jumpedd ovverr thhe mooon.
 5. 现在这行正确了，继续第 1.4 课。
注意：随着教程的进行，不要试图记住一切，你的 Neovim 词汇量会随着使用而扩展。考虑定期回到这个教程复习一下。

## 第 1.4 课：文本编辑：插入
** 按下 `i`{normal} 插入文本。**
 1. 将光标移动到下面标记为 ✗ 的第一行。
 2. 要使第一行与第二行相同，请将光标移到要插入文本的位置之后的第一个字符上。
 3. 按下 `i`{normal} 并输入必要的添加内容。
 4. 每次错误修正后，按下 `<Esc>`{normal} 返回正常模式。
    重复步骤 2 到 4 来纠正句子。
There is text misng this .
There is some text missing from this line.
 5. 当你熟练插入文本后，继续第 1.5 课。

## 第 1.5 课：文本编辑：追加
** 按下 `A`{normal} 追加文本。**
 1. 将光标移动到下面标记为 ✗ 的第一行。
    光标位于该行的哪个字符上无关紧要。
 2. 按下 [A](A) 并输入必要的添加内容。
 3. 文本追加完成后，按下 `<Esc>`{normal} 返回正常模式。
 4. 将光标移动到标记为 ✗ 的第二行并重复步骤 2 和 3 来纠正这句话。
There is some text missing from th
There is some text missing from this line.
There is also some text miss
There is also some text missing here.
 5. 当你熟练追加文本后，继续第 1.6 课。

## 第 1.6 课：编辑文件
** 使用 `:wq`{vim} 写入文件并退出。**
!! 注意：在执行以下任何步骤之前，请通读整个课程 !!
 1. 像第 1.2 课那样退出本教程：`:q!`{vim}
    或者，如果你有另一个终端访问权限，请在那里执行以下操作。
 2. 在 shell 提示符下输入以下命令：
~~~ sh
    $ nvim tutor
~~~
    'nvim' 是启动 Nvim 编辑器的命令，'tutor' 是你要编辑的文件名。使用一个可以更改的文件。
 3. 如前所学插入和删除文本。
 4. 保存文件并退出 Neovim：
~~~ cmd
    :wq
~~~
    注意你需要按下 `<Enter>` 来执行命令。
 5. 如果你在步骤 1 中退出了本教程，请重启并向下移动到以下摘要。
 6. 阅读并理解上述步骤后：执行它们。

## 第 1 课总结
 1. 使用箭头键或 hjkl 键移动光标。
     h (左)   j (下)       k (上)       l (右)
 2. 从 shell 提示符启动 Neovim 输入：
~~~ sh
    $ nvim FILENAME
~~~
 3. 退出 Neovim 输入：`<Esc>`{normal} `:q!`{vim} `<Enter>`{normal} 丢弃所有更改。
                或者输入：`<Esc>`{normal} `:wq`{vim} `<Enter>`{normal} 保存更改。
 4. 删除光标处的字符输入：`x`{normal}
 5. 插入或追加文本输入：
    `i`{normal} 插入文本 `<Esc>`{normal}     在光标前插入。
    `A`{normal} 追加文本 `<Esc>`{normal}     在行末追加。
注意：按下 `<Esc>`{normal} 将使你进入正常模式或取消不想要且未完成的命令。
现在继续第 2 课。

## 第 2.1 课：删除命令
** 输入 `dw`{normal} 删除一个词。**
 1. 按下 `<Esc>`{normal} 确保你在正常模式下。
 2. 将光标移动到下面标记为 ✗ 的行。
 3. 将光标移到需要删除的词的开头。
 4. 输入 [d](d)[w](w) 让这个词消失。
There are a some words fun that don't belong paper in this sentence.
 5. 重复步骤 3 和 4 直到句子正确并继续第 2.2 课。

## 第 2.2 课：更多删除命令
** 输入 `d$`{normal} 删除到行尾。**
 1. 按下 `<Esc>`{normal} 确保你在正常模式下。
 2. 将光标移动到下面标记为 ✗ 的行。
 3. 将光标移到正确行的末尾（第一个 . 之后）。
 4. 输入 `d$`{normal} 删除到行尾。
Somebody typed the end of this line twice. end of this line twice.
 5. 继续第 2.3 课以了解发生了什么。

## 第 2.3 课：关于操作符和动作
许多改变文本的命令由一个[操作符](operator)和一个[动作](navigation)组成。
带有 [d](d) 删除操作符的删除命令格式如下：
    d   motion
  其中：
    d      - 是删除操作符。
    motion - 是操作符将作用的对象（如下所列）。
  动作简短列表：
    [w](w) - 直到下一个词的开始，不包括其第一个字符。
    [e](e) - 到当前词的末尾，包括最后一个字符。
    [$]($) - 到行尾，包括最后一个字符。
因此输入 `de`{normal} 将从光标到词尾删除。
注意：在正常模式下仅输入动作而不带操作符将按指定方式移动光标。

## 第 2.4 课：使用计数进行动作
** 在动作前输入数字表示重复多少次。**
 1. 将光标移动到下面标记为 ✓ 的行开头。
 2. 输入 `2w`{normal} 将光标向前移动两个词。
 3. 输入 `3e`{normal} 将光标移动到第三个词的末尾。
 4. 输入 `0`{normal} ([零](0)) 移动到行首。
 5. 用不同的数字重复步骤 2 和 3。
This is just a line with words you can move around in.
 6. 继续第 2.5 课。

## 第 2.5 课：使用计数删除更多
** 输入数字与操作符组合重复操作。**
在上面提到的删除操作符和动作组合中，你在动作前插入一个数字以删除更多：
     d   number   motion
 1. 将光标移动到标记为 ✗ 的行中的第一个大写词。
 2. 输入 `d2w`{normal} 删除这两个大写词
 3. 用不同的数字重复步骤 1 和 2，一次命令删除连续的大写词
This ABC DE line FGHI JK LMN OP of words is Q RS TUV cleaned up.

## 第 2.6 课：操作行
** 输入 `dd`{normal} 删除整行。**
由于频繁删除整行，Vi 的设计者决定只需输入两个 d 即可删除一行。
 1. 将光标移动到下面短语的第二行。
 2. 输入 [dd](dd) 删除该行。
 3. 现在移动到第四行。
 4. 输入 `2dd`{normal} 删除两行，然后按下 `u`{normal} 两次撤销所有三行。
5)  Roses are red,
6)  Mud is fun,
7)  Violets are blue,
8)  I have a car,
9)  Clocks tell time,
10)  Sugar is sweet
11)  And so are you.

## 第 2.7 课：撤销命令
** 按下 `u`{normal} 撤销最后的命令，`U`{normal} 修复整行。**
 1. 将光标移动到下面标记为 ✗ 的行并将光标放在第一个错误上。
 2. 输入 `x`{normal} 删除第一个不需要的字符。
 3. 现在输入 `u`{normal} 撤销最后执行的命令。
 4. 这次用 `x`{normal} 命令修复行上的所有错误。
 5. 现在输入大写的 `U`{normal} 将行恢复到原始状态。
 6. 现在输入 `u`{normal} 几次撤销 `U`{normal} 和之前的命令。
 7. 现在输入几次 `<C-r>`{normal} (Control + R) 重做命令。
Fiix the errors oon thhis line and reeplace them witth undo.
 8. 这些是非常有用的命令。现在继续第 2 课总结。

## 第 2 课总结
 1. 从光标删除到下一个词输入：    `dw`{normal}
 2. 从光标删除到行尾输入：   `d$`{normal}
 3. 删除整行输入：                           `dd`{normal}
 4. 重复一个动作在其前面加上数字：           `2w`{normal}
 5. 改变命令的格式为：
        operator   [number]   motion
    其中：
        operator -   要做什么，例如 [d](d) 表示删除
        [number] -   可选的数字，用来重复动作
        motion   -   移动文本以操作，例如：
                        [w](w) (词),
                        [$]($) (行尾)，等。
 6. 移动到行首输入一个零： [0](0)
 7. 撤销以前的操作，输入：            `u`{normal}  (小写 u)
    撤销行上的所有更改，输入：   `U`{normal}  (大写 U)
    撤销撤销，输入：                   `<C-r>`{normal}

## 第 3.1 课：放置命令
** 输入 `p`{normal} 将先前删除的文本放在光标之后。**
 1. 将光标移动到下面标记为 ✓ 的第一行。
 2. 输入 `dd`{normal} 删除该行并将其存储在 Neovim 寄存器中。
 3. 将光标移动到 c) 行，在删除行应放的位置上方。
 4. 输入 `p`{normal} 将行放在光标下方。
 5. 重复步骤 2 到 4 将所有行按正确顺序放置。
d) Can you learn too?
b) Violets are blue,
c) Intelligence is learned,
a) Roses are red,
注意：你也可以用 `P`{normal}（大写 P）将文本放在光标之前。

## 第 3.2 课：替换命令
** 输入 `rx`{normal} 将光标处的字符替换为 x。**
 1. 将光标移动到下面标记为 ✗ 的第一行。
 2. 将光标移到第一个错误上。
 3. 输入 `r`{normal} 然后输入应该存在的字符。
 4. 重复步骤 2 和 3 直到第一行与第二行相同。
Whan this lime was tuoed in, someone presswd some wrojg keys!
When this line was typed in, someone pressed some wrong keys!
 5. 现在继续第 3.3 课。
注意：请记住你应该通过实践学习，而不是死记硬背。

## 第 3.3 课：更改操作符
** 更改到词尾，输入 `ce`{normal}。**
 1. 将光标移动到下面标记为 ✗ 的第一行。
 2. 将光标放在 "lubw" 中的 "u" 上。
 3. 输入 `ce`{normal} 和正确的词（在这种情况下，输入 "ine" ）。
 4. 按下 `<Esc>`{normal} 并移动到下一个需要更改的字符。
 5. 重复步骤 3 和 4 直到第一句与第二句相同。
This lubw has a few wptfd that mrrf changing usf the change operator.
This line has a few words that need changing using the change operator.
注意 [c](c)e 删除词并进入插入模式。

## 第 3.4 课：更多使用 `c`{normal} 的更改
** 更改操作符与删除使用的动作相同。**
 1. 更改操作符的工作方式与删除相同。格式为：
        c    [number]   motion
 2. 动作相同，如 `w`{normal}（词）和 `$`{normal}（行尾）。
 3. 移动到下面标记为 ✗ 的第一行。
 4. 将光标移到第一个错误。
 5. 输入 `c$`{normal} 并输入像第二行一样的行其余部分并按下 `<Esc>`{normal}。
The end of this line needs some help to make it like the second.
The end of this line needs to be corrected using the c$ command.
注意：在输入时可以使用退格键来纠正错误。

## 第 3 课总结
 1. 要放回刚删除的文本，输入 [p](p)。这会将删除的文本放在光标之后（如果删除了一行，它将放在光标行的下方）。
 2. 要替换光标下的字符，输入 [r](r) 然后输入你想有的字符。
 3. [更改操作符](c) 允许你从光标更改到动作带你去的地方。输入 `ce`{normal} 从光标更改到词尾，`c$`{normal} 更改到行尾等。
 4. 更改的格式为：
        c   [number]   motion
现在继续下一课。

## 第 4.1 课：光标位置和文件状态
** 输入 `<C-g>`{normal} 显示你在文件中的位置和文件状态。
 输入 `{count}G`{normal} 移动到文件中的某一行。**
注意：在执行这些步骤之前，请通读整个课程！！
 1. 按住 `<Ctrl>`{normal} 键并按下 `g`{normal}。我们称之为 `<C-g>`{normal}。
    页面底部会出现一条消息，显示文件名和文件中的位置。记住步骤 3 的行号。
注意：你可能会在屏幕右下角看到光标位置。这是当 ['ruler']('ruler') 选项设置时发生的情况。
 2. 按下 [G](G) 将你移动到文件底部。
    输入 [gg](gg) 将你移动到文件开头。
 3. 输入你所在的行号然后 `G`{normal}。这将把你带回第一次按下 `<C-g>`{normal} 时所在的行。
 4. 如果你有信心这样做，请执行步骤 1 到 3。

## 第 4.2 课：搜索命令
** 输入 `/`{normal} 后跟一个短语来搜索该短语。**
 1. 在正常模式下输入 `/`{normal} 字符。请注意它和光标出现在屏幕底部，就像 `:`{normal} 命令一样。
 2. 现在输入 'errroor' `<Enter>`{normal}。这是你想搜索的词。
 3. 要再次搜索同一短语，只需输入 [n](n)。
    要反向搜索同一短语，输入 [N](N)。
 4. 要反向搜索短语，请使用 [?](?) 而不是 `/`{normal}。
 5. 要返回你来的地方，请按下 `<C-o>`{normal}。
    （在按下字母 `o`{normal} 时保持 `<Ctrl>`{normal} 按下）。
    重复以进一步返回。`<C-i>`{normal} 向前移动。
"errroor" 不是拼写 error 的方法；errroor 是一个错误。
注意：当搜索到达文件末尾时，除非 ['wrapscan']('wrapscan') 选项被重置，否则它将继续从开头开始。

## 第 4.3 课：匹配括号搜索
** 输入 `%`{normal} 找到匹配的 ), ], 或 }。**
 1. 将光标放在下面标记为 ✓ 的行中的任意 (, [, 或 { 上。
 2. 现在输入 [%](%) 字符。
 3. 光标将移动到匹配的括号或方括号。
 4. 输入 `%`{normal} 将光标移动到另一个匹配的括号。
 5. 将光标移动到另一个 (, ), [, ], {, 或 } 上，看看 `%`{normal} 会做什么。
This ( is a test line with ('s, ['s, ] and {'s } in it. ))
注意：这在调试具有不匹配括号的程序时非常有用！

## 第 4.4 课：替换命令
** 输入 `:s/old/new/g` 替换 "new" 为 "old"。**
 1. 将光标移动到下面标记为 ✗ 的行。
 2. 输入
~~~ cmd
        :s/thee/the/
~~~
    注意：[:s](:s) 命令只更改了行中第一个匹配的 "thee"。
 3. 现在输入
~~~ cmd
        :s/thee/the/g
~~~
    添加 g [标志](:s_flags) 表示全局替换该行，更改行中所有出现的 "thee"。
Usually thee best time to see thee flowers is in thee spring.
 4. 要更改两行之间的每个出现的字符串，请输入
~~~ cmd
        :#,#s/old/new/g
~~~
    其中 # 是范围行号（即，`1,3` 表示从第 1 行到第 3 行，包括）。
    输入
~~~ cmd
        :%s/old/new/g
~~~
    更改整个文件中的每个出现。
    输入
~~~ cmd
        :%s/old/new/gc
~~~
    查找整个文件中的每个出现，并提示是否替换。
注意：你也可以先使用可视模式选择要替换的行。这将在未来的一课中更详细地解释。

## 第 4 课总结
 1. `<C-g>`{normal}     显示你的位置和文件状态。
    `G`{normal}         移动到文件末尾。
    number `G`{normal}  移动到该行号。
    `gg`{normal}        移动到第一行。
 2. 输入 `/`{normal} 后跟一个短语向前搜索该短语。
    输入 `?`{normal} 后跟一个短语向后搜索该短语。
    搜索后输入 `n`{normal} 找到同一方向的下一个出现，或输入 `N`{normal} 向相反方向搜索。
    `<C-o>`{normal} 带你回到旧位置，`<C-i>`{normal} 到新位置。
 3. 当光标在 (, ), [, ], {, 或 } 上时输入 `%`{normal} 转到其匹配项。
 4. 要替换行中第一个 old 为 new 输入
~~~ cmd
        :s/old/new
~~~
    要替换行中所有 olds 输入
~~~ cmd
        :s/old/new/g
~~~
    要替换两行之间的短语输入
~~~ cmd
        :#,#s/old/new/g
~~~
    要替换整个文件中的所有出现输入
~~~ cmd
        :%s/old/new/g
~~~
    要每次询问确认添加 'c'
~~~ cmd
        :%s/old/new/gc
~~~

## 第 5.1 课：如何执行外部命令
** 输入 `:!`{vim} 后跟一个外部命令来执行该命令。**
 1. 输入熟悉的命令 `:`{normal} 将光标设置在屏幕底部。这允许你输入命令行命令。
 2. 现在输入 [!](!cmd)（感叹号）字符。这允许你执行任何外部 shell 命令。
 3. 例如输入 "ls" 跟在 "!" 后面，然后按 `<Enter>`{normal}。
    这将显示你的目录列表，就像你在 shell 提示符下一样。
注意：可以通过这种方式执行任何外部命令，你可以包含参数。
注意：所有 `:`{vim} 命令在按下 `<Enter>`{normal} 后执行。

## 第 5.2 课：关于写文件的更多信息
** 要保存对文本所做的更改，输入 `:w`{vim} FILENAME。**
 1. 输入 `:!dir`{vim} 获取你的目录列表。
    你已经知道必须在此之后按下 `<Enter>`{normal}。
 2. 选择一个尚不存在的文件名，例如 TEST。
 3. 现在输入：
~~~ cmd
        :w TEST
~~~
    （其中 TEST 是你选择的文件名。）
 4. 这将当前文件保存为名称 TEST。
    要验证这一点，请再次输入 `:!dir`{vim} 查看你的目录。
注意：如果你退出 Neovim 并用 `nvim TEST` 重新启动，该文件将是保存时教程的精确副本。
 5. 现在通过输入：
~~~ cmd
        :!del TEST
~~~

## 第 5.3 课：选择要写入的文本
** 要保存文件的一部分，输入 `v`{normal} 动作 `:w FILENAME`{vim}。**
 1. 将光标移动到这一行。
 2. 按下 [v](v) 并将光标移动到下面的第五个项目。请注意，文本被高亮显示。
 3. 按下 `:`{normal} 字符。在屏幕底部
        `:'<,'>`{vim}
    将出现。
 4. 输入
        `w TEST`{vim}
    其中 TEST 是一个尚不存在的文件名。验证你看到
        `:'<,'>w TEST`{vim}
    在你按下 `<Enter>`{normal} 之前。
 5. Neovim 将选定的行写入文件 TEST。使用 `:!dir`{vim} 查看它。
    不要立即删除它！我们将在下一课中使用它。
注意：按下 [v](v) 开始 [可视选择](visual-mode)。你可以移动光标来增大或减小选择。然后你可以使用操作符对文本进行操作。例如，`d`{normal} 删除文本。

## 第 5.4 课：检索和合并文件
** 要检索文件内容，输入 `:r FILENAME`{vim}。**
 1. 将光标放在这一行上方。
注意：执行步骤 2 后你将看到第 5.3 课的文本。然后向下移动查看此课程。完成后按下 `u`{normal} 撤销。
 2. 现在使用命令检索你的 TEST 文件
        `:r TEST`{vim}
    其中 TEST 是你使用的文件名。
    检索的文件将放在光标行下方。
 3. 要验证文件已被检索，向上移动光标并注意现在有两个第 5.3 课的副本，原始的和检索的版本。
注意：你还可以读取外部命令的输出。例如，
        `:r !dir`{vim}
      读取 ls 命令的输出并将其放在光标下方。

## 第 5 课总结
 1. [:!command](:!cmd) 执行外部命令。
     一些有用的示例是：
     `:!dir`{vim}                   - 显示目录列表
     `:!del FILENAME`{vim}          - 删除文件 FILENAME
 2. [:w](:w) FILENAME              将当前 Neovim 文件写入磁盘，文件名为 FILENAME。
 3. [v](v)  动作  :w FILENAME   将可视选择的行保存到文件 FILENAME 中。
 4. [:r](:r) FILENAME              检索磁盘文件 FILENAME 并将其放在光标位置下方。
 5. [:r !dir](:r!)                  读取 dir 命令的输出并将其放在光标位置下方。

## 第 6.1 课：打开命令
** 输入 `o`{normal} 在光标下方打开一行并进入插入模式。**
 1. 将光标移动到下面标记为 ✓ 的行。
 2. 输入小写字母 `o`{normal} 在光标下方 [打开](o) 一行并进入插入模式。
 3. 现在输入一些文本并按下 `<Esc>`{normal} 退出插入模式。完成后删除你打开的行。
在输入 `o`{normal} 后，光标将放在打开的行中并处于插入模式。
 4. 要在光标上方打开一行，只需输入大写 O，而不是小写 `o`{normal}。在下面的行上尝试这个。完成后删除你打开的行。
在光标所在行上方输入 O 打开一行。

## 第 6.2 课：追加命令
** 输入 `a`{normal} 在光标后插入文本。**
 1. 将光标移动到下面标记为 ✗ 的行开头。
 2. 按下 `e`{normal} 直到光标在 "li" 的末尾。
 3. 输入小写字母 `a`{normal} [追加](a) 文本到光标后。
 4. 完成下面一行中的单词。按下 `<Esc>`{normal} 退出插入模式。
 5. 使用 `e`{normal} 移动到下一个不完整的单词并重复步骤 3 和 4。
This li will allow you to pract appendi text to a line.
This line will allow you to practice appending text to a line.
注意：[a](a), [bus（动态规划）](bus（动态规划）.md), 和 [A](A) 都进入相同的插入模式，唯一的区别是插入字符的位置不同。

## 第 6.3 课：另一种替换方式
** 输入大写 `R`{normal} 替换多个字符。**
 1. 将光标移动到下面标记为 ✗ 的第一行。将光标移动到第一个 "xxx" 的开头。
 2. 现在按下 `R`{normal} ([大写 R](R)) 并输入第二行下面的数字，使其替换 "xxx"。
 3. 按下 `<Esc>`{normal} 离开 [替换模式](mode-replace)。注意行的其余部分保持不变。
 4. 重复步骤替换剩余的 "xxx"。
Adding 123 to xxx gives you xxx.
Adding 123 to 456 gives you 579.
注意：替换模式类似于插入模式，但每个输入的字符都会替换现有字符。

## 第 6.4 课：复制和粘贴文本
** 使用 `y`{normal} 操作符复制文本，使用 `p`{normal} 粘贴它。**
 1. 转到下面标记为 ✓ 的行并将光标放在 "a)" 之后。
 2. 使用 `v`{normal} 开始可视模式并将光标移动到 "first" 之前。
 3. 输入 `y`{normal} [复制](yank) 高亮的文本。
 4. 将光标移动到下一行的末尾：`j$`{normal}
 5. 输入 `p`{normal} [粘贴](put) 文本。
 6. 按下 `a`{normal} 然后输入 "second"。按下 `<Esc>`{normal} 退出插入模式。
 7. 使用可视模式选择 "item."，用 `y`{normal} 复制它，移动到下一行末尾用 `j$`{normal} 并用 `p`{normal} 粘贴那里
a) This is the first item.
b)
注意：你可以使用 `y`{normal} 作为操作符：`yw`{normal} 复制一个词。
注意：你可以使用 `P`{normal} 在光标前粘贴，而不是在光标后。

## 第 6.5 课：设置选项
** 设置一个选项，使搜索和替换命令忽略大小写。**
Neovim 中有许多你可以配置的设置，以满足你的需求。
 1. 输入 `/ignore` 搜索 "ignore"。
    重复几次通过按下 `n`{normal}。
 2. 设置 'ic' (忽略大小写) 选项输入：
~~~ cmd
        :set ic
~~~
 3. 现在再次搜索 "ignore" 通过按下 `n`{normal}。
    注意 Ignore 和 IGNORE 现在也被找到了。
 4. 设置 'hlsearch' 和 'incsearch' 选项：
~~~ cmd
        :set hls is
~~~
 5. 现在再次输入搜索命令并查看结果：/ignore <Enter>
 6. 要禁用忽略大小写输入：
~~~ cmd
        :set noic
~~~
 7. 要反转设置值，在前面加上 "inv"：
~~~ cmd
        :set invic
~~~
注意：要移除匹配的高亮输入：
~~~ cmd
        :nohlsearch
~~~
注意：如果你想只为一次搜索命令忽略大小写，请在短语中使用 [\c](/\c)：
/ignore\c <Enter>

## 第 6 课总结
 1. 输入 `o`{normal} 在光标下方打开一行并开始插入模式。
    输入 `O`{normal} 在光标上方打开一行。
 2. 输入 `a`{normal} 在光标后插入文本。
    输入 `A`{normal} 在行尾后插入文本。
 3. `e`{normal} 命令移动到词尾。
 4. `y`{normal} 操作符复制文本，`p`{normal} 粘贴它。
 5. 输入大写 `R`{normal} 进入替换模式，直到按下 `<Esc>`{normal}。
 6. 输入 "[:set](:set) xxx" 设置选项 "xxx"。一些选项是：
        'ic' 'ignorecase'   搜索时忽略大小写
        'is' 'incsearch'    显示搜索短语的部分匹配
        'hls' 'hlsearch'    高亮所有匹配的短语
    你可以使用长选项名或短选项名。
 7. 在前面加上 "no" 来关闭选项：
~~~ cmd
        :set noic
~~~
 8. 在前面加上 "inv" 来反转选项：
~~~ cmd
        :set invic
~~~

## 第 7.1 课：获取帮助
** 使用在线帮助系统。**
Neovim 有一个全面的在线帮助系统。
要开始，请尝试以下两种之一：
  - 按下 `<F1>`{normal} 键（如果你有的话）
  - 输入 `:help`{vim}
阅读帮助窗口中的文本以了解帮助如何工作。
输入 `<C-w><C-w>`{normal} 从一个窗口跳到另一个窗口。
输入 `:q`{vim} 关闭帮助窗口。
你可以通过给 ":help" 命令提供参数找到几乎所有主题的帮助。尝试以下（别忘了按下 <Enter>）：
~~~ cmd
    :help w
    :help c_CTRL-D
    :help insert-index
    :help user-manual
~~~

## 第 7.2 课：补全
** 使用 `<C-d>`{normal} 和 `<Tab>`{normal} 进行命令行补全。**
 1. 列出当前目录的内容： `:!dir`{vim}
 2. 输入命令的开头： `:e`{vim}
 3. 按下 `<C-d>`{normal} Neovim 将显示以 "e" 开头的命令列表。
 4. 按下 `<Tab>`{normal} Neovim 将显示可能补全的菜单
    （或如果输入的命令是唯一的，例如：
    ":ed`<Tab>`{normal}" 将补全为 ":edit")。
 5. 使用 `<Tab>`{normal} 或 `<C-n>`{normal} 转到下一个匹配项。或使用
    `<S-Tab>`{normal} 或 `<C-p>`{normal} 转到上一个匹配项。
 6. 选择条目 `edit`{vim}。现在你可以看到 `edit`{vim}
    已经自动插入到命令行中。
 7. 现在添加一个空格和一个现有文件名的开头： `:edit FIL`{vim}
 8. 按下 `<Tab>`{normal}。Vim 将显示一个补全菜单，列出以 `FIL` 开头的文件名
注意：补全适用于许多命令。对于 `:help`{vim} 特别有用。

## 第 7.3 课：配置 Neovim
Neovim 是一个非常可配置的编辑器。你可以按照自己的喜好进行自定义。要开始使用更多功能，请创建一个 vimrc 文件，如果你想使用 Lua，可以是 "init.lua"，如果你想使用 Vimscript，可以是 "init.vim"。本课中我们将使用 "init.lua"。
 1. 开始编辑 "init.lua" 文件。
    `:exe 'edit' stdpath('config')..'/init.lua'`{vim}
 2. 将 Lua 示例配置复制到你的 "init.lua" 文件中。
    `:read $VIMRUNTIME/example_init.lua`{vim}
 3. 写入文件（也会创建任何缺失的父目录）：
    `:w ++p`{vim}
 4. 下次启动 Neovim 时，你可以快速打开这个 vimrc 文件：
    `:e $MYVIMRC`{vim}

## 第 7 课总结
 1. 输入 `:help`{vim}
    或按下 `<F1>`{normal} 或 `<Help>`{normal} 打开帮助窗口。
 2. 输入 `:help TOPIC`{vim} 查找有关 TOPIC 的帮助。
 3. 输入 `<C-w><C-w>`{normal} 跳转到另一个窗口
 4. 输入 `:q`{vim} 关闭帮助窗口
 5. 在命令模式下，按下 `<C-d>`{normal} 查看可能的补全。
    按下 `<Tab>`{normal} 使用补全菜单并选择一个匹配项。
 6. 创建你的配置文件以保存你的首选设置。你可以通过 `:e $MYVIMRC`{vim} 重新访问它。

## 接下来是什么？
运行 `:help nvim-quickstart`{vim} 以获取更多关于扩展 Nvim 的信息。

## 结论
本教程旨在简要介绍 Neovim 编辑器，足以让你轻松使用它。远远不够完整，因为 Neovim 有许多更多的命令。经常查阅帮助。

网上还有无数优秀的教程和视频可供参考。
这里有一堆推荐：
-Learn Vim Progressively*:
h ps://yannesposito.com/Scratch/en/blog/Learn-Vim-Progressively/
- *Learning Vim in 2014*:
h ps://benmccormick.org/learning-vim-in-2014/
- *Vimcasts*:
h p://vimcasts.org/
- *Vim Video-Tutorials by Derek Wyatt*:
h p://derekwyatt.org/vim/tutorials/
- *Learn Vimscript the Hard Way*:
h ps://learnvimscriptthehardway.stevelosh.com/
- *7 Habits of Effective Text Editing*:
h ps://www.moolenaar.net/habits.html
- *vim-galore*:
  https://github.com/mhinz/vim-galore
如果你喜欢书，《Practical Vim》by Drew Neil 经常被推荐（续集《Modern Vim》包含特定于 Neovim 的内容）。

本教程由 Michael C. Pierce 和 Robert K. Ware 编写，来自 Colorado School of Mines，使用 Charles Smith 提供的想法，Colorado State University。电子邮件：bware@mines.colorado.edu。
由 Bram Moolenaar 修改为 Vim。
由 Felipe Morales 修改为 vim-tutor-mode。
由 Rory Nesbitt 修改为 Neovim。

// vim: nowrap