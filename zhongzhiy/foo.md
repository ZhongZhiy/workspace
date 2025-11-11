# Hayagriva YAML 文件格式

Hayagriva 的 YAML 文件格式允许你向 Hayagriva 提供一组文献条目。它基于 [YAML 标准](https://en.wikipedia.org/wiki/YAML)。本文件档从概述开始，描述格式的结构、常用字段及数据类型，并给出示例和说明。

## 概述

从技术上讲，Hayagriva 文件是一个包含单个映射（mapping）的 YAML 文档，该映射的值本身也是映射。
或者更简单地说：每个文献条目需要通过某个名称（“键”）可识别，并具有描述该条目的若干属性（“字段”）。举例来说，文件可以像这样：

```yaml
harry:
    type: Book
    title: Harry Potter and the Order of the Phoenix
    author: Rowling, J. K.
    volume: 5
    page-total: 768
    date: 2003-06-21

electronic:
    type: Web
    title: Ishkur's Guide to Electronic Music
    serial-number: v2.5
    author: Ishkur
    url: http://www.techno.org/electronic-music-guide/
```

你可以看到它指代了两个条目：哈利·波特系列的第五卷（键：`harry`）和一个名为 “Ishkur's Guide to Electronic Music” 的网页（键：`electronic`）。键总是位于冒号前面……

有时候，字段的值可能不只是冒号后面的一段文本。如果一篇文章由多人合著，`author` 字段可以写成这样：

```yaml
author: ["Omarova, Saule", "Steele, Graham"]
```

或者也可以写成这种形式：

```yaml
author:
    - Omarova, Saule
    - Steele, Graham
```

`author` 字段可以是一个数组（列表），以便表示多个创作者。YAML 有两种表示列表的方式：第一种是紧凑的，使用方括号；第二种是使用连字符的块状表示法。

有时字段可以接受复合数据。例如，如果你想为 URL 保存访问日期，你需要 `url` 字段接受复合结构，可以这样表示：

```yaml
url:
    value: http://www.techno.org/electronic-music-guide/
    date: 2020-11-30
```

也有更紧凑的形式，如果你熟悉 JSON，会很像：

```yaml
url: { value: http://www.techno.org/electronic-music-guide/, date: 2020-11-30 }
```

到目前为止，你可能会认为需要大量字段来表示任何文献可能有的信息：例如，一篇文章可能有很多额外信息……

## 使用父条目表示出版情境

Hayagriva 的目标是尽量减少需要记住的字段数量，使格式更容易记忆并在不查阅文档的情况下编写。与其他一些文献管理格式不同，Hayagriva 使用“父级”（parents）的概念：许多文献是在其他媒介中发表（例如文章出现在期刊、博客、报纸等），当这些被引用的条目每次都重复相同的父级信息时会很繁琐。

我们改用父级概念：许多文献是在其他媒介中发布（例如：文章可以出现在期刊、博客、报纸……），当每次都重复父级信息时这很不方便。父级允许你在条目内部嵌套表示其所发表的更大容器条目，从而复用字段和结构。

实际例子：一篇科学期刊文章可以像这样表示：

```yaml
kinetics:
    type: Article
    title: Kinetics and luminescence of the excitations of a nonequilibrium polariton condensate
    author: ["Doan, T. D.", "Tran Thoai, D. B.", "Haug, Hartmut"]
    serial-number:
        doi: "10.1103/PhysRevB.102.165126"
    page-range: 165126-165139
    date: 2020-10-14
    parent:
        type: Periodical
        title: Physical Review B
        volume: 102
        issue: 16
        publisher: American Physical Society
```

这表示该文章发表在期刊“Physical Review B”第 102 卷第 16 期。注意 `title` 字段在文章和它的父条目中都可以使用 —— 每个字段在父子条目中是相互独立可用的。

要指定父条目信息，在顶层条目中写 `parent` 字段名后加冒号，然后在缩进的下一行写该父条目的所有字段。

字段 `type: Periodical` 也可以省略，因为每种条目类型都有一个默认的父类型（default parent），如果父条目没有显式 `type` 字段就会使用该默认父类型。

有时一个媒介可以以多种方式发布，也就是说单一父条目可能不足以完整描述发布情境。为了解决这种情况，`parent` 可以是一个列表：

```yaml
wwdc-network:
    type: Article
    author:  ["Mehta, Jiten", "Kinnear, Eric"]
    title: Boost Performance and Security with Modern Networking
    date: 2020-06-26
    parent:
        - type: Conference
          title: World Wide Developer Conference 2020
          organization: Apple Inc.
          location: Mountain View, CA
        - type: Video
          runtime: "00:13:42"
          url: https://developer.apple.com/videos/play/wwdc2020/10111/
```

该条目描述了一场在会议上发表并且可以通过视频获得的信息来源：一个演讲既是会议的一部分，也有可用的视频记录。

就像 `author` 字段一样，`parent` 也可以是一个列表。若是列表形式，连字符表示每个父条目的开始。

父条目也可以作为独立条目出现，并且它们自己也可以有父条目。这在你处理例如某个期刊属于一个系列，或者像下面的情形中很有用：

```yaml
plaque:
    type: Misc
    title: Informational plaque about Jacoby's 1967 photos
    publisher:
        name: Stiftung Reinbeckhallen
        location: Berlin, Germany
    date: 2020
    parent:
        type: Artwork
        date: 1967
        author: Jacoby, Max
        parent:
            type: Anthology
            title: Bleibtreustraße
            archive: Landesmuseum Koblenz
            archive-location: Koblenz, Germany
```

这个说明：该牌匾由博物馆为 Jacoby 的一张照片制作，照片属于一个系列，而该系列通常收藏在另一个博物馆。

## 参考

本节列出所有可能的字段及它们的数据类型说明。

### 字段

#### `type`

|           |                   |
| --------- | ----------------- |
| **数据类型：** | 条目类型（entry type）  |
| **说明：**   | 项目的媒介类型，通常决定引用的结构 |
| **示例：**   | `type: video`     |

#### `title`

|           |                                                                |
| --------- | -------------------------------------------------------------- |
| **数据类型：** | 可格式化字符串（formattable string）                                    |
| **说明：**   | 条目的标题                                                          |
| **示例：**   | `title: "Rick Astley: How An Internet Joke Revived My Career"` |

#### `author`

|                  |                                                           |
|------------------|-----------------------------------------------------------|
| **数据类型：**   | person / 人员列表                                         |
| **说明：**       | 对条目主要负责创作的人                                     |
| **示例：**       | `author: ["Klocke, Iny", "Wohlrath, Elmar"]`              |

#### `date`

|           |                 |
| --------- | --------------- |
| **数据类型：** | 日期（date）        |
| **说明：**   | 条目出版的日期         |
| **示例：**   | `date: 1949-05` |

#### `parent`

|                  |                                                           |
|------------------|-----------------------------------------------------------|
| **数据类型：**   | 条目（entry）                                             |
| **说明：**       | 条目发表于其中／与之强相关的容器条目                       |
| **示例：**       | <pre>parent:<br>    type: Anthology<br>    title: Automata studies<br>    editor: ["Shannon, C. E.", "McCarthy, J."]</pre> |

#### `abstract`

|           |                                                                               |
| --------- | ----------------------------------------------------------------------------- |
| **数据类型：** | 可格式化字符串                                                                       |
| **说明：**   | 条目的摘要（例如期刊文章的摘要）                                                              |
| **示例：**   | `abstract: The dominant sequence transduction models are based on complex...` |

#### `genre`

|                  |                                                           |
|------------------|-----------------------------------------------------------|
| **数据类型：**   | 可格式化字符串                                            |
| **说明：**       | 条目的类型、类别或子类型（例如论文类型、报告类型等），不要用于主题性描述或类别化标签 |
| **示例：**       | `genre: Doctoral dissertation` |

#### `editor`

|                  |                                                           |
|------------------|-----------------------------------------------------------|
| **数据类型：**   | person / 人员列表                                         |
| **说明：**       | 负责选择并修订条目内容的人                                 |
| **示例：**       | <pre>editor:<br>    - Stringer, Gary A.<br>    - Pebworth, Ted-Larry</pre> |

#### `affiliated`

|                  |                                                           |
|------------------|-----------------------------------------------------------|
| **数据类型：**   | 带角色的人员列表 / 带角色的人员列表的列表                  |
| **说明：**       | 与条目相关但不属于 `author` 或 `editor` 的相关人员         |
| **示例：**       | <pre>affiliated:<br>    - role: Director<br>      names: Cameron, James<br>    - role: CastMember<br>      names: ["Schwarzenegger, Arnold", "Hamilton, Linda", "Patrick, Robert"]</pre> |

#### `call-number`

|                  |                                                           |
|------------------|-----------------------------------------------------------|
| **数据类型：**   | 可格式化字符串                                            |
| **说明：**       | 项目在图书馆、机构或收藏中的编号。与 `archive` 一起使用。   |
| **示例：**       | `call-number: "F16 D14"`                                  |

#### `publisher`

|                  |                                                           |
|------------------|-----------------------------------------------------------|
| **数据类型：**   | 出版者（publisher）                                       |
| **说明：**       | 条目的出版者                                               |
| **示例：**       | <pre>publisher: Penguin Books</pre> 或 <pre>publisher:<br>    name: Penguin Books<br>    location: London</pre> |

#### `location`

|                  |                                                           |
|------------------|-----------------------------------------------------------|
| **数据类型：**   | 可格式化字符串                                            |
| **说明：**       | 条目实际所在或发生地点。若要表示出版地，请使用 `publisher`。|
| **示例：**       | `location: Lahore, Pakistan`                              |

#### `organization`

|                  |                                                           |
|------------------|-----------------------------------------------------------|
| **数据类型：**   | 可格式化字符串                                            |
| **说明：**       | 条目产生或有关联的机构                                     |
| **示例：**       | `organization: Technische Universität Berlin`             |

#### `issue`

|                  |                                                           |
|------------------|-----------------------------------------------------------|
| **数据类型：**   | 数字或字符串                                              |
| **说明：**       | 当父条目有多个期号时，表示该期号在序列中的位置。也用于表示电视节目的集数。 |
| **示例：**       | `issue: 5`                                                |

#### `volume`

|                  |                                                           |
|------------------|-----------------------------------------------------------|
| **数据类型：**   | 数字或字符串                                              |
| **说明：**       | 当父条目有多个卷/部分/季时，表示该条目所在的卷或部分         |
| **示例：**       | `volume: 2-3`                                             |

#### `volume-total`

|                  |                                                           |
|------------------|-----------------------------------------------------------|
| **数据类型：**   | 数字                                                      |
| **说明：**       | 表示该条目一共包含多少卷/部分/季                           |
| **示例：**       | `volume-total: 12`                                        |

#### `chapter`

|                  |                                                           |
|------------------|-----------------------------------------------------------|
| **数据类型：**   | 数字或字符串                                              |
| **说明：**       | 在所引用作品中该章节的编号。当章节本身就是被引用的条目（例如章节有独立标题）时，也可以用于标识章节。 |
| **示例：**       | `chapter: 4`                                              |

#### `edition`

|                  |                                                           |
|------------------|-----------------------------------------------------------|
| **数据类型：**   | 数字或字符串                                              |
| **说明：**       | 条目的出版版本                                             |
| **示例：**       | `edition: expanded and revised edition`                   |

#### `page-range`

|                  |                                                           |
|------------------|-----------------------------------------------------------|
| **数据类型：**   | 数字或字符串                                              |
| **说明：**       | 在父条目中的页码范围                                       |
| **示例：**       | `page-range: 812-847`                                     |

#### `page-total`

|                  |                                                           |
|------------------|-----------------------------------------------------------|
| **数据类型：**   | 数字                                                      |
| **说明：**       | 条目的总页数                                               |
| **示例：**       | `page-total: 1103`                                        |

#### `time-range`

|                  |                                                           |
|------------------|-----------------------------------------------------------|
| **数据类型：**   | 时间戳范围（timestamp range）                             |
| **说明：**       | 在父条目中该条目开始与结束的时间范围                       |
| **示例：**       | `time-range: 00:57-06:21`                                 |

#### `runtime`

|                  |                                                           |
|------------------|-----------------------------------------------------------|
| **数据类型：**   | 时间戳（timestamp）                                       |
| **说明：**       | 条目的总时长                                               |
| **示例：**       | `runtime: 01:42:21,802`                                   |

#### `url`

|                  |                                                           |
|------------------|-----------------------------------------------------------|
| **数据类型：**   | URL                                                       |
| **说明：**       | 条目的规范公共 URL，可以包含访问日期                       |
| **示例：**       | `url: { value: https://www.reddit.com/r/AccidentalRenaissance/comments/er1uxd/japanese_opposition_members_trying_to_block_the/, date: 2020-12-29 }` |

#### `serial-number`

|                  |                                                           |
|------------------|-----------------------------------------------------------|
| **数据类型：**   | 字符串或字符串字典（dictionary of strings）               |
| **说明：**       | 任意形式的序列号，包括文章编号。如果你有像 `doi` 这样的已知方案的序列号，应该将它们放在 `serial-number` 的字典中，例如示例所示。 |
| **示例：**       | `serial-number: 2003.13722` 或 <pre>serial-number:<br>    doi: "10.22541/au.148771883.35456290"<br>    arxiv: "1906.00356"<br>    serial: "8516"</pre> |

#### `language`

|                  |                                                           |
|------------------|-----------------------------------------------------------|
| **数据类型：**   | Unicode 语言标识符                                        |
| **说明：**       | 条目所用语言                                               |
| **示例：**       | `language: zh-Hans`                                       |

#### `archive`

|                  |                                                           |
|------------------|-----------------------------------------------------------|
| **数据类型：**   | 可格式化字符串                                            |
| **说明：**       | 存放该条目的机构/收藏名称                                   |
| **示例：**       | `archive: National Library of New Zealand`                |

#### `archive-location`

|                  |                                                           |
|------------------|-----------------------------------------------------------|
| **数据类型：**   | 可格式化字符串                                            |
| **说明：**       | 存放该条目的机构/收藏所在地                                 |
| **示例：**       | `archive-location: Wellington, New Zealand`               |

#### `note`

|                  |                                                           |
|------------------|-----------------------------------------------------------|
| **数据类型：**   | 可格式化字符串                                            |
| **说明：**       | 对条目的简短标注、装饰或注释（例如，用于表示某些版本包含在书评中） |
| **示例：**       | `microfilm version`                                       |

### 数据类型

#### Entry（条目）

条目是一组字段的集合，可以具有键（作为顶级条目映射的一个条目），也可以作为其他条目的 `parent` 字段中的值。

#### Entry Type（条目类型）

必须使用下列关键字之一：

- `article`。短篇文字，可能是新闻或学术性质，出现在某个更大的出版物中（默认父类型：`periodical`）。
- `chapter`。长篇作品的章节（默认父类型：`book`）。
- `entry`。关于某主题的短小条目。可能出现在参考书或数据集中（默认父类型：`reference`）。
- `anthos`。发表在文集（Anthology）中的文本（默认父类型：`anthology`）。
- `report`。由作者编写、可能隶属于某机构的报告文档，面向特定受众或用途。
- `thesis`。提交以获取高等教育学位的学术著作。
- `web`。网络原生内容（如动画、Web 应用或其他仅在互联网上出现的形式）。当引用传统网页或网站时，请谨慎选择条目类型。
- `scene`。节目的一个片段或演出的一部分，通常发生在同一地点（默认父类型：`video`）。
- `artwork`。艺术创作（默认父类型：`exhibition`）。
- `patent`。提交给政府机构的技术文件，用于对发明的复制权利进行限制。
- `case`。法院审理或拟审理的法律案件的引用。
- `newspaper`。某一特定日子出版的报纸期。
- `legislation`。法律文件或拟议法律草案（默认父类型：`anthology`）。
- `manuscript`。作为出版候选提交的手稿。
- `original`。条目在被重新出版之前的原始容器。
- `post`。微博或类似平台上的一条发布（如 Twitter），（默认父类型：`post`）。
- `misc`。不符合其他任何条目类型的项目。
- `performance`。现场艺术表演。
- `periodical`。定期出版、包含独特内容的出版物，包括学术期刊和新闻杂志。
- `proceedings`。会议的正式出版记录。
- `book`。以纸质装订形式出版的长篇作品。
- `blog`。网站上的自我出版文章集合。
- `reference`。参考著作，如手册或词典。
- `conference`。专业会议。该类型表示所引用的是会议本身。如果你想引用发表在会议出版物中的论文，请选择适当的条目类型（如 `proceedings` 或 `article`）。
- `anthology`。围绕某一主题或主题集合的文本集。
- `repository`。公开可见的源代码、论文或其他数据及其演化历史的存储库。
- `thread`。由原始帖触发的网络书面讨论，可以是论坛、社交网络或问答网站上的讨论串。
- `video`。任何形式的影像制品，可能伴随音频（默认父类型：`video`）。
- `audio`。任何类型的音频录制（默认父类型：`audio`）。
- `exhibition`。策展的艺术作品集合。

该字段不区分大小写。如果条目作为另一个定义了默认父类型的条目的父条目出现，且未显式指定 `type` 字段，则默认值为 `Misc` 或该默认父类型。

#### Formattable String（可格式化字符串）

可格式化字符串是在引用或引文中可能会经过文本大小写变换的字符串。你可以对字符串的某些片段或整个字符串禁用这些变换。

最简单的情况是提供一个可以被大小写折叠的字符串：

```yaml
publisher: UN World Food Programme
```

如果你想保留字符串的一部分原样，但希望其余部分按照样式的行为处理，可以用大括号将那部分包起来。注意如果使用大括号包含部分内容，则必须将整个字符串用引号包住：

```yaml
publisher: "{imagiNary} Publishing"
```

要完全禁用格式化并按源字符串的大小写原样保留，要把字符串放在 `value` 子字段中，并指定另一个子字段 `verbatim: true`：

```yaml
publisher:
    value: UN World Food Programme
    verbatim: true
```

如果你的条目将 `language` 设置为非英语，标题大小写或句子大小写的折叠将总是被禁用。

你也可以在字符串中包含由 [Typst](https://typst.app) 评估的数学标记，方法是用美元符号包裹它。

此外，每个可格式化字符串都可以包含一个短形式（short），引用样式可选择用短形式代替长形式渲染：

```yaml
journal:
    value: International Proceedings of Customs
    short: Int. Proc. Customs
```

#### Person（人名）

一个人由姓名组成，可选地包含名（given name）、前缀（prefix）和后缀（suffix）以及别名（alias）。通常你可以用一个字符串指定人的名字，格式如“姓, 名”或类似的表示法：

- `Doe, Janet`
- `Luther King, Martin, Jr.`
- `UNICEF`
- `von der Leyen, Ursula`

前缀与姓氏之间会使用与 BibTeX 相同的算法自动分割（参见 BibTeX 文档），这会影响首字母小写规则等。

通常这就足够了。但如果名字的一部分包含逗号，或者前缀不希望被小写，或需要指定别名，则可以使用映射形式详细指定：

```yaml
author:
    given-name: Gloria Jean
    name: Watkins
    alias: bell hooks
```

可用的子字段为 `name`、`given-name`、`prefix`、`suffix` 和 `alias`。`name` 字段为必需项。

#### List of persons with role（带角色的人员列表）

此数据类型需要一个包含两个字段的映射：`names`，其中包含一个或多个人人名；以及 `role`，指定他们在条目中的角色：

```yaml
role: ExecutiveProducer
names: ["Simon, David", "Colesberry, Robert F.", "Noble, Nina Kostroff"]
```

可能的 `role` 值（不区分大小写）包括但不限于：

- `translator`：译者。
- `afterword`：撰写后记。
- `foreword`：撰写前言。
- `introduction`：撰写引言。
- `annotator`：提供注释。
- `commentator`：撰写评论。
- `holder`：持有专利或类似权利的人。
- `compiler`：编辑文集的编者。
- `founder`：创办人。
- `collaborator`：合作者。
- `organizer`：组织者。
- `cast-member`：演出人员（演员）。
- `composer`：作曲者。
- `producer`：制片人。
- `executive-producer`：执行制片人（首席制片）。
- `writer`：作者（撰写文字）。
- `cinematography`：摄影（摄像）。
- `director`：导演。
- `illustrator`：插画者。
- `narrator`：朗读者或配音。

#### Date（日期）

日期遵循 ISO 8601。你应当以 `YYYY-MM-DD` 的形式指定完整日期，年份前可加正负号以表示公元前或远古年份。也可以使用缩短形式 `YYYY` 或 `YYYY-MM`。

#### Timestamp（时间戳）

时间戳表示媒体中的时间点。格式为字符串 `DD:HH:MM:SS,msms`，但除了 `MM:SS` 之外的部分都可以省略。通常需要用双引号包裹该字符串以避免解析问题。

最左边的时间单位允许在未指定更大单位时发生溢出。例如 `138:00` 被允许，表示 2 小时 18 分（当语义允许时）。

#### Timestamp range（时间戳范围）

范围由两个时间戳用连字符连接组成。第一个表示开始时间，第二个表示结束时间。通常也需要用引号包裹：

```yaml
time-range: "03:35:21-03:58:46"
```

#### String（字符串）

字符串是一系列字符作为字段值。大多数情况下你可以在冒号后直接写字符串，但如果字符串包含特殊字符（如 `:`, `{`, `}`, `[`, `]`, `,`, `&`, `*`, `#`, `?` 等）或以空格开头/结尾，或者跨行，可能需要引用或使用多行 YAML 语法。

#### Numeric（数值）

数值变量由一个或多个用逗号、与号或连字符分隔的整数构成。数值可以表示单个数字或一个范围，仅包含整数，但可以带有前缀或后缀的非数字字符。

```yaml
page-range: S10-15
```

#### Unicode Language Identifier（Unicode 语言标识符）

Unicode 语言标识符用于表示语言及其变体。最简单的形式是小写的两字母 ISO 语言代码（如 `en`, `zh`），也支持更复杂的变体标记、脚本和区域子标签。

请参考我们用于解析语言标识符的 Rust crate `unic-langid` 的文档以获取更多信息：
https://docs.rs/unic-langid/latest/unic_langid/index.html

``` 