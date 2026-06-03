> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [pkmer.cn](https://pkmer.cn/Pkmer-Docs/10-obsidian/obsidian%E7%A4%BE%E5%8C%BA%E6%8F%92%E4%BB%B6/pdf-plus/)

> Obsidian PDF++ 是一个用于更好的 PDF 体验的 [Obsidian.md](https://obsidian.md) 插件。

obsidian 社区插件

* * *

插件 ID：pdf-plus pdf-plus pdf plus：Obsidian 的一款好用的 PDF 标注增强插件，很适合用来做读书笔记。

Obsidian PDF++ 是一个用于更好的 PDF 体验的 [Obsidian.md](https://obsidian.md) 插件。它允许你将文本链接的反向链接转换为高亮注释，即你可以 ** 通过链接到文本选择来用高亮注释 PDF 文件 **。此外，它还为内置的 PDF 查看器和 PDF 嵌入添加了许多 ** 便利功能 **。PDF++ 不仅仅是一个 PDF 注释工具，它还可以作为一个 ** 独立的 PDF 注释工具 **，你可以无缝地使用 Obsidian 的丰富 markdown 编辑器来注释你的 PDF 文件，而无需在 Obsidian 和外部应用程序之间切换。此外，PDF++ 还提供了许多高度可定制的复制格式。你可以从 Obsidian 的社区插件浏览器中安装这个插件。

> ***   注意**
> 
> 由于 PDF++ 插件本体的设置和功能太多，太复杂，所以本篇不会详细的一点点描述，只会着重讲讲笔者的使用习惯与方法。
> 
> 当前文章可用于 0.39.23 版本的 PDF++。

[](#%E6%8F%92%E4%BB%B6%E4%BB%8B%E7%BB%8D)插件介绍
---------------------------------------------

PDF++ 是一种针对 Obsidian 的原生 PDF 注释和编辑工具，显著提升了 Obsidian 的 PDF 支持能力。

*   功能概览
    *   **高亮注释**：将 PDF 文件中的反向链接转换为高亮注释，允许通过链接文本选择来注释 PDF。
    *   **注释同步**：支持将注释直接添加到 PDF 文件中，以便在 Obsidian 之外也可见。
    *   **查看器增强**：为内置的 PDF 查看器和嵌入功能添加了便利性改进，即使不用于注释，也能提升用户体验。
*   特点
    *   **与 Obsidian 原生查看器集成**：补充而非替代 Obsidian 的本机查看器，注释以纯 Markdown 保存，确保持久性。
    *   **独立注释工具**：无需在 Obsidian 和外部应用程序之间切换，即可使用丰富的 Markdown 编辑器注释 PDF。
    *   **分布式注释**：支持将单个 PDF 的注释分布在整个 vault 中。
    *   **轻量级依赖**：除可选的 `&color=...`/`&rect=...` 链接表示法外，不引入插件依赖的语法。

[](#%E6%8F%92%E4%BB%B6%E8%AE%BE%E7%BD%AE%E6%8E%A8%E8%8D%90)插件设置推荐
-----------------------------------------------------------------

### [](#editing-pdf-files)Editing PDF files

首先，这个设置不要开！！！

解释一下这个设置的意思：开启 PDF 编辑。简而言之，就是把注释、高亮等，写入 PDF 文件中。当你用其它软件打开该 PDF 文件时（比如 Sumatra PDF），你依然可以看到自己做的注释，摆脱对 Obsidian 的依赖。

这个功能非常好，奈何不靠谱，有损坏文件的风险。之前在群聊中有看到群友的 PDF 文件因此被损坏了，作者也标黄了一段文字示警，所以极不推荐打开。

### [](#backlink-highlighting)Backlink highlighting

这部份重点看 Colors 部份的设置。

这部份可以设定你想在 PDF 中用哪几种颜色标注，标注的颜色、含意全部都能自定义，也可以选择其中一个作为默认的标注颜色。

除此以外，我还作了如下更改：

*   打开了 `Highlight backlinks inPDF embeds` 项，使高亮在嵌入中也可以看到；
*   打开了 `Highlight backlinks in hover popover previews` 项，使高亮在悬浮小窗中也能看到；
*   把 `How to open the markdown file when no markdown file is opened` 设为了 `Split left`，这样在打开注释文件时，会在左侧打开，而不是右侧。

### [](#rectangular-selection-embeds)Rectangular selection embeds

当前部份是用于设定框选嵌入笔记的，推荐默认。

个人感觉这部份功能不全，等更新全了再推荐设置吧。

### [](#pdf-callouts)PDF++ callouts

默认设置就很好，没有什么需要更改的。

### [](#pdf-toolbar)PDF toolbar

该项用于设置 PDF 页面上方工具栏的内容，要注意一下其中的 `Default color selected in color palette`。

后面可看到如何用快捷键快速引用注释，这时，会使用工具栏中选中的颜色新建注释，而上面说的那项设置，正是决定打开 PDF 文件时，默认选中哪个颜色的。

除此以外，我还作了以下更改：

*   关闭了 `Show zoom level box` 项，隐藏了尺寸缩放的控件，因为我用不着；
*   关闭了 `Show "without specifying color" button in the color palette` 项，隐藏了默认颜色选项，反正默认颜色又不是不显示，用不着。

### [](#viewer-options)Viewer options

默认设置就很好，没有什么需要更改的。

这里决定了你选中要注释的部份后的右键菜单，不过基本没什么要改的。

我只关闭了其中的 `Customize menu..`，用不着。

### [](#copying-links-via-hotkeys)Copying links via hotkeys

这里没有设置，只是提供了一个通往快捷键设置的按钮。

推荐给命令中的 `PDF++: Copy link to selection or annotation` 添加一个快捷键，后面可以通过按这个快捷键快速添加注释。

### [](#other-shortcut-commands)Other shortcut commands

这里也是快捷键，没什么要改的。

### [](#link-copy-templates)Link copy templates

这里是重点，用于决定添加的注释的样式，即：为注释设定模版。想要自定义该区域的样式，需要一点点的 Markdown 语法知识，如果不会，按下面照抄就行了。

*   在 `Display text format` 设置中，把 `Page` 右侧的 `p.{{pageLabel}}` 改为 `Page.{{pageLabel}}`；
    
*   在 `Default display text format` 中选择 `Page`；
    
*   在 `Custom link copy formats` 设置中，点击 `+` 加号，新增一行，在下面新增的一行在左侧填入 `Quote in callout`，在右侧填入下列代码：
    
    ```
    > [!{{calloutType}}|{{color}}] {{linkWithDisplay}}
    > > {{text}}
    > 
    >
    ```
    
*   开启 `Use another template when no text is selected` 项；
    
*   在 `Link copy template used when no text is selected` 项中，填入 `{{linkToPageWithDisplay}}`。
    

### [](#auto-copy-auto-focus-auto-paste)Auto-copy / auto-focus / auto-paste

#### [](#auto-copy)Auto-copy

关闭即可，这是 “自动复制”，也就是选中文本后会自动复制。个人认为用不上，且会污染剪贴板。

#### [](#auto-focus)Auto-focus

这个也一样，用于 “自动聚焦”，但在 auto-paste 中已经有了，不需要这个。

#### [](#auto-paste)Auto-paste

可用快捷键触发（就是上面设置的快捷键），会自动将选中文本的注释加到某个指定的 Markdown 文件中，它的默认设置就很好。

#### [](#general)General

这项设置很重要。

*   将 `How to open target markdown file when not opened` 项设为 `Split left`，使指定的 Markdown 文件在左侧打开，而不是右侧；
    
*   关闭 `Always open in editing view` 项，不然每次打开 Markdown 注释文件时，都会处于编辑状态；
    
*   在 `Command to execute` 中填入 `PDF++: Create new note for auto-focus or auto-paste`，这样就会为每个 PDF 文件自动新建一个对应的 Markdown 文件，用于存放注释；
    
*   `New note title format` 是用来设置新建的 Markdown 文件位置与名称的，我的设置为 `Notes/{{ file.basename }}.md`；
    
*   `Template file path` 可用于为新建的 Markdown 文件指定模版，需要先在库中手动建一个 Markdown 模版文件，然后在模版文件中输入模版，再将模版文件的路径写入到该设置中，模版内容推荐用下面这个：
    
    ```
    ---
    PDF: "[[{{ file.path }}|{{ file.basename }}]]"
    ---
    
    # {{ file.basename }}
    ```
    

### [](#pdf-annotations)PDF Annotations

这项不用管，这与最开始说的 `Editing PDF files` 有关。

### [](#pdf-internal-links)PDF internal links

没有需要修改的，默认就好。

### [](#citationsin-pdf-experimental)Citationsin PDF experimental

这是实验性内容，我不用，所以不讲。

### [](#external-links-in-pdf)External links in PDF

我把这项关了。如果开启的话，需要按下 Ctrl 才能用悬浮小窗预览，否则不需要。

没有需要修改的，默认就好。

### [](#pdf-outline-table-of-contents)PDF outline (table of contents)

没有需要修改的，默认就好。

### [](#pdf-thumbnails)PDF thumbnails

没有需要修改的，默认就好。

### [](#pdf-page-composer-experimental)PDF page composer (experimental)

实验性内容，而且与最开始说的 `Editing PDF files` 有关，不用管。

### [](#opening-links-to-pdf-files)Opening links to PDF files

本设置决定了 “当在 PDF 对应的 Markdown 文件中点击 PDF 链接时，如何打开该 PDF 文件”。

以下是我的更改：

*   将 `How to open PDF links when there is no open PDF file` 项改为 `Split right`，保证 PDF 文件在左侧，对应的 Markdown 文件在右侧；
*   关闭 `Ignore "height" parameter in popover preview` 项，使高度参数在悬浮小窗中有效。

### [](#embedding-pdf-files)Embedding PDF files

此处是有关 PDF 文件嵌入相关的设置，推荐开启 `Make PDF embeds with a page specified unscrollable`，使嵌入后的页面无法滚动。

### [](#backlinks-pane-for-pdf-files)Backlinks pane for PDF files

此处是有关 PDF 文件的反链的设置，其实就是 PDF 高亮。本插件通过 PDF 文件的反链指向的文本与位置，来高亮对应的文本与位置。

### [](#search-from-links)Search from links

我用不着，就没看了。

### [](#integration-with-external-apps-desktop-only)Integration with external apps (desktop-only)

将内容全部关闭就好，用不着。

### [](#view-sync)View Sync

用于和 View Sync 插件配合使用的，我用不着。

### [](#misc)Misc

其他设置，没什么要改的。

### [](#style-settings)Style settings

用于和 Style settings 插件配合使用的，我用不着。

[](#%E4%BD%BF%E7%94%A8%E6%96%B9%E6%B3%95)使用方法
---------------------------------------------

每个 PDF 文件都对应着一个 Markdown 文件。

打开一个 PDF 文件，点击左侧 Obsidian 自带的工具栏中的 `PDF++: Toggle auto-paste` 按钮，用以开启自动粘贴功能。

可以选中一段文本，按下之前设好的快捷键，就会将该文本按照设置好的模版，和上方工具栏里选中的颜色，自动粘贴到对应的 Markdown 文件中。

也可以在选中文本后，直接右键，更自由的选择颜色与其它模版（如果看不懂，试试就明白了）。

如果对应的 Markdown 文件不存在，会自动按照前文设置好的模版与路径来自动创建，然后再粘贴。

可以右键 PDF 文件中高亮的部份，重新选择高亮颜色。

[](#%E5%B0%8F%E5%A3%B0%E5%8F%A8%E5%8F%A8)小声叨叨
---------------------------------------------

这插件好用是好用，但这设置也太多了吧？放弃全部详细说明了，还是只把我咋设置，以及这些设置都是啥意思讲讲吧。

[](#%E5%85%B6%E4%BB%96%E7%9B%B8%E5%85%B3%E6%96%87%E7%AB%A0)其他相关文章
-----------------------------------------------------------------

[如何让 mousewheel-image-zoom 插件适配 pdf++ 嵌入块](https://pkmer.cn/Pkmer-Docs/10-obsidian/obsidian%E4%BD%BF%E7%94%A8%E6%8A%80%E5%B7%A7/huajin/%E5%A6%82%E4%BD%95%E8%AE%A9mousewheel-image-zoom%E6%8F%92%E4%BB%B6%E9%80%82%E9%85%8Dpdf++%E5%B5%8C%E5%85%A5%E5%9D%97)

[](#%E5%85%BC%E5%AE%B9%E6%80%A7)兼容性
-----------------------------------

PDF++ 与以下插件兼容：

*   [obsidian-hover-editor](https://pkmer.cn/Pkmer-Docs/10-obsidian/obsidian%E7%A4%BE%E5%8C%BA%E6%8F%92%E4%BB%B6/obsidian-hover-editor)
*   [Better Search Views](https://github.com/ivan-lednev/better-search-views)

以下插件跟 PDF++ 冲突：

*   [close-similar-tabs](https://pkmer.cn/Pkmer-Docs/10-obsidian/obsidian%E7%A4%BE%E5%8C%BA%E6%8F%92%E4%BB%B6/close-similar-tabs)

> **讨论**
> 
> 若阁下有独到的见解或新颖的想法，诚邀您在文章下方留言，与大家共同探讨。