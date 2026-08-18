---
created: 2026-07-05T16:34:23 (UTC +08:00)
tags: []
source: https://git.sr.ht/~foosoft/anki-connect
author: 
---

# ~foosoft/anki-connect - 用于创建闪卡远程 API 的 Anki 插件 - sourcehut git

> ## 摘录
> Anki-Connect 使外部应用程序（如 Yomichan）能够通过简单的 HTTP API 与 Anki 进行通信。其功能包括对用户牌组执行查询、自动创建新卡片等。Anki-Connect 兼容 Anki 最新的稳定版（2.1.x）；旧版本（2.0.x 及以下）已不再支持。

---
Anki-Connect 使外部应用程序（如 Yomichan）能够通过简单的 HTTP API 与 [Anki](https://apps.ankiweb.net/) 进行通信。其功能包括对用户牌组执行查询、自动创建新卡片等。Anki-Connect 兼容 Anki 最新的稳定版（2.1.x）；旧版本（2.0.x 及以下）已不再支持。

### [#](https://git.sr.ht/~foosoft/anki-connect#installation)安装

安装过程与其他 Anki 插件类似，可分为三个步骤完成：

1.  在 Anki 中选择 `工具` | `加载项` | `获取加载项...` 打开`安装加载项`对话框。
2.  在标有`代码`的文本框中输入 [2055492159](https://ankiweb.net/shared/info/2055492159)，然后按下`确定`按钮继续。
3.  按照提示重启 Anki 以完成 Anki-Connect 的安装。

为了其他应用程序能够使用 Anki-Connect，必须保持 Anki 在后台运行。您可以通过浏览器访问 `localhost:8765` 随时验证 Anki-Connect 是否正在运行。如果服务器正在运行，您将在浏览器窗口中看到 `Anki-Connect` 消息。

#### [#](https://git.sr.ht/~foosoft/anki-connect#notes-for-windows-users)Windows 用户须知

Windows 用户在启动 Anki 时可能会看到防火墙提示对话框出现。这是因为 Anki-Connect 运行了一个本地 HTTP 服务器以便其他应用程序可以连接它。要使此插件正常工作，必须解除对主机应用程序 Anki 的阻止。

#### [#](https://git.sr.ht/~foosoft/anki-connect#notes-for-macos-users)macOS 用户须知

从 [Mac OS X Mavericks](https://en.wikipedia.org/wiki/OS_X_Mavericks) 开始，操作系统引入了一个名为_App Nap_的功能。此功能会将某些已打开（但不可见）的应用程序置于挂起状态。由于这种行为会导致 Anki-Connect 在您有其他窗口在前台时停止工作，因此应为 Anki 禁用 App Nap：

1.  启动终端应用程序。
2.  在终端窗口中执行以下命令：
    
    ```
    defaults write net.ankiweb.dtop NSAppSleepDisabled -bool true
    defaults write net.ichi2.anki NSAppSleepDisabled -bool true
    defaults write org.qt-project.Qt.QtWebEngineCore NSAppSleepDisabled -bool true
    
    ```
    
3.  重启 Anki。

### [#](https://git.sr.ht/~foosoft/anki-connect#application-interface-for-developers)开发者应用接口

Anki-Connect 通过一个易于使用的 API 向外部应用程序暴露 Anki 的内部功能。安装后，每次启动 Anki 时，此插件将在端口 8765 上启动一个 HTTP 服务器。其他应用程序（包括浏览器扩展）然后通过 HTTP 请求与其通信。

默认情况下，Anki-Connect 仅将 HTTP 服务器绑定到 `127.0.0.1` IP 地址，因此您只能从其运行的同一主机上访问它。如果需要通过网络访问，可以在配置中更改绑定地址。转到 工具->加载项->AnkiConnect->配置 并更改 "webBindAddress" 值。例如，您可以将其设置为 `0.0.0.0` 以绑定到主机上的所有网络接口。这也需要重启 Anki。

#### [#](https://git.sr.ht/~foosoft/anki-connect#sample-invocation)示例调用

每个请求由一个 JSON 编码的对象组成，包含 `action`、`version`、上下文 `params` 以及用于身份验证的 `key` 值（可选，默认可省略）。Anki-Connect 将返回一个包含两个字段的对象：`result` 和 `error`。`result` 字段包含已执行 API 的返回值，`error` 字段是 API 执行期间抛出的任何异常的描述（如果执行成功则使用 `null` 值）。

_成功响应示例：_

```
{"result": ["Default", "Filtered Deck 1"], "error": null}

```

_失败响应示例：_

```
{"result": null, "error": "unsupported action"}

```

```
{"result": null, "error": "guiBrowse() got an unexpected keyword argument 'foobar'"}

```

为了与旨在与旧版本 Anki-Connect 配合使用的客户端兼容，如果在请求中未提供 `version` 字段，则版本将默认为 4。此外，当提供的版本号为 4 或更低时，API 响应将只包含 `result` 的值；没有 `error` 字段可用于错误处理。

您可以使用任何喜欢的语言或工具向 Anki-Connect 发出请求，但下面包含了一些简单的示例供参考。

##### [#](https://git.sr.ht/~foosoft/anki-connect#curl)Curl

```
curl localhost:8765 -X POST -d '{"action": "deckNames", "version": 6}'

```

##### [#](https://git.sr.ht/~foosoft/anki-connect#powershell)Powershell

```
(Invoke-RestMethod -Uri http://localhost:8765 -Method Post -Body '{"action": "deckNames", "version": 6}').result

```

##### [#](https://git.sr.ht/~foosoft/anki-connect#python)Python

```
import json
import urllib.request

def request(action, **params):
    return {'action': action, 'params': params, 'version': 6}

def invoke(action, **params):
    requestJson = json.dumps(request(action, **params)).encode('utf-8')
    response = json.load(urllib.request.urlopen(urllib.request.Request('http://127.0.0.1:8765', requestJson)))
    if len(response) != 2:
        raise Exception('response has an unexpected number of fields')
    if 'error' not in response:
        raise Exception('response is missing required error field')
    if 'result' not in response:
        raise Exception('response is missing required result field')
    if response['error'] is not None:
        raise Exception(response['error'])
    return response['result']

invoke('createDeck', deck='test1')
result = invoke('deckNames')
print('got list of decks: {}'.format(result))

```

##### [#](https://git.sr.ht/~foosoft/anki-connect#javascript)JavaScript

```
function invoke(action, version, params={}) {
    return new Promise((resolve, reject) => {
        const xhr = new XMLHttpRequest();
        xhr.addEventListener('error', () => reject('failed to issue request'));
        xhr.addEventListener('load', () => {
            try {
                const response = JSON.parse(xhr.responseText);
                if (Object.getOwnPropertyNames(response).length != 2) {
                    throw 'response has an unexpected number of fields';
                }
                if (!response.hasOwnProperty('error')) {
                    throw 'response is missing required error field';
                }
                if (!response.hasOwnProperty('result')) {
                    throw 'response is missing required result field';
                }
                if (response.error) {
                    throw response.error;
                }
                resolve(response.result);
            } catch (e) {
                reject(e);
            }
        });

        xhr.open('POST', 'http://127.0.0.1:8765');
        xhr.send(JSON.stringify({action, version, params}));
    });
}

await invoke('createDeck', 6, {deck: 'test1'});
const result = await invoke('deckNames', 6);
console.log(`got list of decks: ${result}`);

```

#### [#](https://git.sr.ht/~foosoft/anki-connect#authentication)身份验证

Anki-Connect 支持要求身份验证才能发出 API 请求。此功能默认_禁用_，但可以通过将 Anki-Config 的设置（工具->加载项->AnkiConnect->配置）中的 `apiKey` 字段设置为期望的字符串来启用。如果您已这样做，您应该会看到 [`requestPermission`](https://git.sr.ht/~foosoft/anki-connect#requestpermission) API 请求返回 `requireApiKey` 为 `true`。然后您必须在后续的任何 API 请求体中包含一个名为 `key` 的额外参数，其值必须与配置的 API 密钥匹配。

#### [#](https://git.sr.ht/~foosoft/anki-connect#hey-could-you-add-a-new-action-to-support-feature)嘿，你能添加一个新的 action 来支持 $FEATURE 吗？

Anki-Connect 的主要目标是支持从 Yomichan 浏览器扩展实时创建闪卡。当前的 API 提供了实现此功能所需的所有操作。我认识到 Anki-Connect 的角色已从最初的设计演变，我很乐意审查新功能请求。

话虽如此，_本项目采用自助服务模式_。如果您需要新功能，请创建 PR。我会审查它，如果看起来不错，就会合并。_不带附带拉取请求的新功能请求将不会被处理_。确保您的拉取请求满足以下条件：

-   尝试匹配周围代码的风格。
-   附有带示例的文档。
-   附有验证操作的测试。
-   实现在其他应用程序中有用的功能。

### [#](https://git.sr.ht/~foosoft/anki-connect#supported-actions)支持的 Action

当前支持的 action 文档按类别划分并在下方引用。请注意，尽管已弃用的 API 不会在此页面列出，但只要您的请求标记了 API 可用时对应的版本号，它们将继续正常运行。搜索参数会传递给 Anki，更多详情请查阅文档：[https://docs.ankiweb.net/searching.html](https://docs.ankiweb.net/searching.html)

- [卡片操作](https://git.sr.ht/~foosoft/anki-connect#card-actions)
- [牌组操作](https://git.sr.ht/~foosoft/anki-connect#deck-actions)
- [图形界面操作](https://git.sr.ht/~foosoft/anki-connect#graphical-actions)
- [媒体操作](https://git.sr.ht/~foosoft/anki-connect#media-actions)
- [杂项操作](https://git.sr.ht/~foosoft/anki-connect#miscellaneous-actions)
- [模型操作](https://git.sr.ht/~foosoft/anki-connect#model-actions)
- [笔记操作](https://git.sr.ht/~foosoft/anki-connect#note-actions)
- [统计操作](https://git.sr.ht/~foosoft/anki-connect#statistic-actions)

___

#### [#](https://git.sr.ht/~foosoft/anki-connect#card-actions)卡片操作

##### [#](https://git.sr.ht/~foosoft/anki-connect#codegeteasefactorscode)`getEaseFactors`

-   返回给定每张卡片的难易度因子数组（顺序相同）。
    
    _示例请求：_
    
    ```
    {
        "action": "getEaseFactors",
        "version": 6,
        "params": {
            "cards": [1483959291685, 1483959293217]
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": [4100, 3900],
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeseteasefactorscode)`setEaseFactors`

-   通过卡片 ID 设置卡片的难易度因子；如果成功（所有卡片都存在）返回 `true`，否则返回 `false`。
    
    _示例请求：_
    
    ```
    {
        "action": "setEaseFactors",
        "version": 6,
        "params": {
            "cards": [1483959291685, 1483959293217],
            "easeFactors": [4100, 3900]
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": [true, true],
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codesetspecificvalueofcardcode)`setSpecificValueOfCard`

-   设置单个卡片的特定值。鉴于修改卡片的某些值可能会对数据库造成破坏，部分键需要将参数 "warning_check" 设置为 True。此操作可用于设置卡片的标记、更改其难易因子、在筛选牌组中更改复习顺序以及更改 "data" 列（目前 Anki 似乎未使用它），以及许多其他值。值的列表及其各自用途的解释可在 [AnkiDroid 的 wiki](https://github.com/ankidroid/Anki-Android/wiki/Database-Structure) 中找到。
    
    _示例请求：_
    
    ```
    {
        "action": "setSpecificValueOfCard",
        "version": 6,
        "params": {
            "card": 1483959291685,
            "keys": ["flags", "odue"],
            "newValues": ["1", "-100"]
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": [true, true],
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codesuspendcode)`suspend`

-   通过卡片 ID 暂停卡片；如果成功（至少有一张卡片未被暂停）返回 `true`，否则返回 `false`。
    
    _示例请求：_
    
    ```
    {
        "action": "suspend",
        "version": 6,
        "params": {
            "cards": [1483959291685, 1483959293217]
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": true,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeunsuspendcode)`unsuspend`

-   通过卡片 ID 取消暂停卡片；如果成功（至少有一张卡片之前被暂停）返回 `true`，否则返回 `false`。
    
    _示例请求：_
    
    ```
    {
        "action": "unsuspend",
        "version": 6,
        "params": {
            "cards": [1483959291685, 1483959293217]
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": true,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codesuspendedcode)`suspended`

-   检查卡片是否被暂停。返回 `true` 表示已暂停，`false` 表示未暂停。
    
    _示例请求：_
    
    ```json
    {
        "action": "suspended",
        "version": 6,
        "params": {
            "card": 1483959293217
        }
    }
    
    ```
    _示例结果：_
    
    ```json
    {
        "result": true,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codearesuspendedcode)`areSuspended`

-   返回一个数组，指示每张给定卡片是否被暂停（顺序相同）。如果卡片不存在则返回 `null`。
    
    _示例请求：_
    
    ```
    {
        "action": "areSuspended",
        "version": 6,
        "params": {
            "cards": [1483959291685, 1483959293217, 1234567891234]
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": [false, true, null],
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeareduecode)`areDue`

-   返回一个数组，指示每张给定卡片是否到期（顺序相同）。_注意_：学习队列中间隔较长（超过 20 分钟）的卡片被视为未到期，直到其间隔时间已过，以匹配 Anki 在复习时的处理方式。
    
    _示例请求：_
    
    ```
    {
        "action": "areDue",
        "version": 6,
        "params": {
            "cards": [1483959291685, 1483959293217]
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": [false, true],
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codegetintervalscode)`getIntervals`

-   返回每张给定卡片 ID 的最新间隔数组，当 `complete` 为 `true` 时返回包含每张给定卡片 ID 所有间隔的二维数组。负数间隔以秒为单位，正数间隔以天为单位。
    
    _示例请求 1：_
    
    ```
    {
        "action": "getIntervals",
        "version": 6,
        "params": {
            "cards": [1502298033753, 1502298036657]
        }
    }
    
    ```
    _示例结果 1：_
    
    ```
    {
        "result": [-14400, 3],
        "error": null
    }
    
    ```
    _示例请求 2：_
    
    ```
    {
        "action": "getIntervals",
        "version": 6,
        "params": {
            "cards": [1502298033753, 1502298036657],
            "complete": true
        }
    }
    
    ```
    _示例结果 2：_
    
    ```
    {
        "result": [
            [-120, -180, -240, -300, -360, -14400],
            [-120, -180, -240, -300, -360, -14400, 1, 3]
        ],
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codefindcardscode)`findCards`

-   返回给定查询的卡片 ID 数组。功能上与 `guiBrowse` 相同，但不使用 GUI 以获得更好的性能。
    
    _示例请求：_
    
    ```
    {
        "action": "findCards",
        "version": 6,
        "params": {
            "query": "deck:current"
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": [1494723142483, 1494703460437, 1494703479525],
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codecardstonotescode)`cardsToNotes`

-   返回给定卡片 ID 的不有序笔记 ID 数组。对于具有相同笔记的卡片，ID 仅在数组中出现一次。
    
    _示例请求：_
    
    ```
    {
        "action": "cardsToNotes",
        "version": 6,
        "params": {
            "cards": [1502098034045, 1502098034048, 1502298033753]
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": [1502098029797, 1502298025183],
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codecardsmodtimecode)`cardsModTime`

-   返回一个对象列表，包含每张卡片 ID 的修改时间。此函数比执行 `cardsInfo` 快约 15 倍。
    
    _示例请求：_
    
    ```
    {
        "action": "cardsModTime",
        "version": 6,
        "params": {
            "cards": [1498938915662, 1502098034048]
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": [
            {
                "cardId": 1498938915662,
                "mod": 1629454092
            }
        ],
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codecardsinfocode)`cardsInfo`

-   返回一个对象列表，包含每张卡片 ID 的卡片字段、正反面（含 CSS）、笔记类型、所属笔记、牌组名称、最后修改时间戳以及难易度和间隔。
    
    _示例请求：_
    
    ```
    {
        "action": "cardsInfo",
        "version": 6,
        "params": {
            "cards": [1498938915662, 1502098034048]
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": [
            {
                "answer": "back content",
                "question": "front content",
                "deckName": "Default",
                "modelName": "Basic",
                "fieldOrder": 1,
                "fields": {
                    "Front": {"value": "front content", "order": 0},
                    "Back": {"value": "back content", "order": 1}
                },
                "css":"p {font-family:Arial;}",
                "cardId": 1498938915662,
                "interval": 16,
                "note":1502298033753,
                "ord": 1,
                "type": 0,
                "queue": 0,
                "due": 1,
                "reps": 1,
                "lapses": 0,
                "left": 6,
                "mod": 1629454092
            },
            {
                "answer": "back content",
                "question": "front content",
                "deckName": "Default",
                "modelName": "Basic",
                "fieldOrder": 0,
                "fields": {
                    "Front": {"value": "front content", "order": 0},
                    "Back": {"value": "back content", "order": 1}
                },
                "css":"p {font-family:Arial;}",
                "cardId": 1502098034048,
                "interval": 23,
                "note":1502298033753,
                "ord": 1,
                "type": 0,
                "queue": 0,
                "due": 1,
                "reps": 1,
                "lapses": 0,
                "left": 6
            }
        ],
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeforgetcardscode)`forgetCards`

-   遗忘卡片，使卡片变为新的。
    
    _示例请求：_
    
    ```
    {
        "action": "forgetCards",
        "version": 6,
        "params": {
            "cards": [1498938915662, 1502098034048]
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#coderelearncardscode)`relearnCards`

-   使卡片进入"重新学习"状态。
    
    _示例请求：_
    
    ```
    {
        "action": "relearnCards",
        "version": 6,
        "params": {
            "cards": [1498938915662, 1502098034048]
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeanswercardscode)`answerCards`

-   回答卡片。难易度介于 1（再次）和 4（简单）之间。将在回答前立即启动计时器。如果卡片存在返回 `true`，否则返回 `false`。
    
    _示例请求：_
    
    ```
    {
        "action": "answerCards",
        "version": 6,
        "params": {
            "answers": [
                {
                    "cardId": 1498938915662,
                    "ease": 2
                },
                {
                    "cardId": 1502098034048,
                    "ease": 4
                }
            ]
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": [true, true],
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codesetduedatecode)`setDueDate`

-   设置到期日期。将卡片转换为复习卡片（如果它们是新的），并使它们在特定日期到期。
    
    -   0 = 今天
    -   1! = 明天 + 将间隔改为 1
    -   3-7 = 随机选择 3-7 天
    
    _示例请求：_
    
    ```
    {
        "action": "setDueDate",
        "version": 6,
        "params": {
            "cards": [1498938915662, 1502098034048],
            "days": "3-7"
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": true,
        "error": null
    }
    
    ```
    

___

#### [#](https://git.sr.ht/~foosoft/anki-connect#deck-actions)牌组操作

##### [#](https://git.sr.ht/~foosoft/anki-connect#codedecknamescode)`deckNames`

-   获取当前用户的完整牌组名称列表。
    
    _示例请求：_
    
    ```
    {
        "action": "deckNames",
        "version": 6
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": ["Default"],
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codedecknamesandidscode)`deckNamesAndIds`

-   获取当前用户的完整牌组名称及其相应 ID 列表。
    
    _示例请求：_
    
    ```
    {
        "action": "deckNamesAndIds",
        "version": 6
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": {"Default": 1},
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codegetdeckscode)`getDecks`

-   接受卡片 ID 数组，返回一个对象，每个牌组名称作为键，其值为属于该牌组的给定卡片数组。
    
    _示例请求：_
    
    ```
    {
        "action": "getDecks",
        "version": 6,
        "params": {
            "cards": [1502298036657, 1502298033753, 1502032366472]
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": {
            "Default": [1502032366472],
            "Japanese::JLPT N3": [1502298036657, 1502298033753]
        },
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codecreatedeckcode)`createDeck`

-   创建一个新的空牌组。不会覆盖已存在的同名牌组。
    
    _示例请求：_
    
    ```
    {
        "action": "createDeck",
        "version": 6,
        "params": {
            "deck": "Japanese::Tokyo"
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": 1519323742721,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codechangedeckcode)`changeDeck`

-   将给定 ID 的卡片移动到其他牌组，如果目标牌组不存在则创建。
    
    _示例请求：_
    
    ```
    {
        "action": "changeDeck",
        "version": 6,
        "params": {
            "cards": [1502098034045, 1502098034048, 1502298033753],
            "deck": "Japanese::JLPT N3"
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codedeletedeckscode)`deleteDecks`

-   删除给定名称的牌组。参数 `cardsToo` _必须_ 指定并设置为 `true`。
    
    _示例请求：_
    
    ```
    {
        "action": "deleteDecks",
        "version": 6,
        "params": {
            "decks": ["Japanese::JLPT N5", "Easy Spanish"],
            "cardsToo": true
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codegetdeckconfigcode)`getDeckConfig`

-   获取给定牌组的配置组对象。
    
    _示例请求：_
    
    ```
    {
        "action": "getDeckConfig",
        "version": 6,
        "params": {
            "deck": "Default"
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": {
            "lapse": {
                "leechFails": 8,
                "delays": [10],
                "minInt": 1,
                "leechAction": 0,
                "mult": 0
            },
            "dyn": false,
            "autoplay": true,
            "mod": 1502970872,
            "id": 1,
            "maxTaken": 60,
            "new": {
                "bury": true,
                "order": 1,
                "initialFactor": 2500,
                "perDay": 20,
                "delays": [1, 10],
                "separate": true,
                "ints": [1, 4, 7]
            },
            "name": "Default",
            "rev": {
                "bury": true,
                "ivlFct": 1,
                "ease4": 1.3,
                "maxIvl": 36500,
                "perDay": 100,
                "minSpace": 1,
                "fuzz": 0.05
            },
            "timer": 0,
            "replayq": true,
            "usn": -1
        },
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codesavedeckconfigcode)`saveDeckConfig`

-   保存给定的配置组，成功返回 `true`，如果配置组 ID 无效（例如不存在）则返回 `false`。
    
    _示例请求：_
    
    ```
    {
        "action": "saveDeckConfig",
        "version": 6,
        "params": {
            "config": {
                "lapse": {
                    "leechFails": 8,
                    "delays": [10],
                    "minInt": 1,
                    "leechAction": 0,
                    "mult": 0
                },
                "dyn": false,
                "autoplay": true,
                "mod": 1502970872,
                "id": 1,
                "maxTaken": 60,
                "new": {
                    "bury": true,
                    "order": 1,
                    "initialFactor": 2500,
                    "perDay": 20,
                    "delays": [1, 10],
                    "separate": true,
                    "ints": [1, 4, 7]
                },
                "name": "Default",
                "rev": {
                    "bury": true,
                    "ivlFct": 1,
                    "ease4": 1.3,
                    "maxIvl": 36500,
                    "perDay": 100,
                    "minSpace": 1,
                    "fuzz": 0.05
                },
                "timer": 0,
                "replayq": true,
                "usn": -1
            }
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": true,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codesetdeckconfigidcode)`setDeckConfigId`

-   将给定牌组的配置组更改为给定 ID 的配置组。成功返回 `true`，如果给定的配置组或任何给定牌组不存在则返回 `false`。
    
    _示例请求：_
    
    ```
    {
        "action": "setDeckConfigId",
        "version": 6,
        "params": {
            "decks": ["Default"],
            "configId": 1
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": true,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeclonedeckconfigidcode)`cloneDeckConfigId`

-   使用给定名称创建新的配置组，从给定 ID 的组克隆，如果未指定则从默认组克隆。返回新配置组的 ID，如果要克隆的指定组不存在则返回 `false`。
    
    _示例请求：_
    
    ```
    {
        "action": "cloneDeckConfigId",
        "version": 6,
        "params": {
            "name": "Copy of Default",
            "cloneFrom": 1
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": 1502972374573,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#coderemovedeckconfigidcode)`removeDeckConfigId`

-   删除给定 ID 的配置组，成功返回 `true`，如果尝试删除默认配置组（ID = 1）或不存在的配置组则返回 `false`。
    
    _示例请求：_
    
    ```
    {
        "action": "removeDeckConfigId",
        "version": 6,
        "params": {
            "configId": 1502972374573
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": true,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codegetdeckstatscode)`getDeckStats`

-   获取给定牌组的统计信息，如总卡片数和待复习卡片数。
    
    _示例请求：_
    
    ```
    {
        "action": "getDeckStats",
        "version": 6,
        "params": {
            "decks": ["Japanese::JLPT N5", "Easy Spanish"]
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": {
            "1651445861967": {
                "deck_id": 1651445861967,
                "name": "Japanese::JLPT N5",
                "new_count": 20,
                "learn_count": 0,
                "review_count": 0,
                "total_in_deck": 1506
            },
            "1651445861960": {
                "deck_id": 1651445861960,
                "name": "Easy Spanish",
                "new_count": 26,
                "learn_count": 10,
                "review_count": 5,
                "total_in_deck": 852
            }
        },
        "error": null
    }
    
    ```
    

___

#### [#](https://git.sr.ht/~foosoft/anki-connect#graphical-actions)图形界面操作

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeguibrowsecode)`guiBrowse`

-   调用_卡片浏览器_对话框并搜索给定查询。返回找到的卡片标识符数组。查询语法[在此记录](https://docs.ankiweb.net/searching.html)。
    
    可选地，可以提供 `reorderCards` 属性以重新排序_卡片浏览器_中显示的卡片。这是一个包含 `order` 和 `columnId` 对象的数组。`order` 可以是 `ascending` 或 `descending`，而 `columnId` 可以是多个列标识符之一（如[Anki 源代码](https://github.com/ankitects/anki/blob/main/rslib/src/browser_table.rs)中记录的）。指定的列需要在_卡片浏览器_中可见。
    
    _示例请求：_
    
    ```
    {
        "action": "guiBrowse",
        "version": 6,
        "params": {
            "query": "deck:current",
            "reorderCards": {
                "order": "descending",
                "columnId": "noteCrt"
            }
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": [1494723142483, 1494703460437, 1494703479525],
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeguiselectcardcode)`guiSelectCard`

-   找到打开的_卡片浏览器_对话框实例并选择给定卡片标识符的卡片。如果_卡片浏览器_打开返回 `true`，否则返回 `false`。
    
    _示例请求：_
    
    ```
    {
        "action": "guiSelectCard",
        "version": 6,
        "params": {
            "card": 1494723142483
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": true,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeguiselectednotescode)`guiSelectedNotes`

-   找到打开的_卡片浏览器_对话框实例并返回选中笔记的标识符数组。如果浏览器未打开则返回空列表。
    
    _示例请求：_
    
    ```
    {
        "action": "guiSelectedNotes",
        "version": 6
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": [1494723142483, 1494703460437, 1494703479525],
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeguiaddcardscode)`guiAddCards`

-   调用_添加卡片_对话框，使用给定的牌组和模板预设笔记，并填入提供的字段值及标签。多次调用此功能会关闭旧窗口，并根据新提供的值重新打开窗口。调用添加卡片对话框，使用给定的牌组和模板预设笔记，并填入提供的字段值及标签。 多次调用此功能会关闭旧窗口，并根据新提供的值重新打开窗口。
    
    音频、视频和图片文件可以分别通过 audio、video 和 picture 键嵌入到字段中。关于这些字段的具体说明，请参考 addNote 和 storeMediaFile 的文档。音频、视频和图片文件可以分别通过audio、video和picture键嵌入到字段中。 关于这些字段的具体说明，请参考addNote和storeMediaFile的文档。
    
    如果用户确认"添加卡片"对话框，则结果为将添加笔记的 ID。如果用户确认"添加卡片"对话框，则结果为将添加笔记的ID。
    
    _示例请求：_
    
    ```
    {
        "action": "guiAddCards",
        "version": 6,
        "params": {
            "note": {
                "deckName": "Default",
                "modelName": "Cloze",
                "fields": {
                    "Text": "The capital of Romania is {{c1::Bucharest}}",
                    "Extra": "Romania is a country in Europe"
                },
                "tags": [
                  "countries"
                ],
                "picture": [{
                    "url": "https://upload.wikimedia.org/wikipedia/commons/thumb/1/13/EU-Romania.svg/285px-EU-Romania.svg.png",
                    "filename": "romania.png",
                    "fields": [
                        "Extra"
                    ]
                }]
            }
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": 1496198395707,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeguieditnotecode)`guiEditNote`

-   用对应于给定笔记 ID 的笔记打开_编辑_对话框。该对话框类似于_编辑当前_对话框，但：
    
    -   有预览按钮可预览笔记的卡片
    -   有浏览按钮可在浏览器中打开这些卡片
    -   有上一个/后退按钮可导航对话框历史
    -   没有包含关闭按钮的工具栏
    
    _示例请求：_
    
    ```
    {
        "action": "guiEditNote",
        "version": 6,
        "params": {
            "note": 1649198355435
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeguiaddnotesetdatacode)`guiAddNoteSetData`

-   在_添加笔记_对话框中设置字段、标签、牌组和笔记类型（模板）。可选择性地追加到字段/标签而不是替换它们。
    
    -   如果添加笔记对话框未打开，则返回错误。
    -   设置牌组/模板始终替换当前值。
    -   设置字段/标签时，如果 `append` 为 true 则追加，否则替换。
    -   还支持通过笔记对象导入媒体（图片/音频）。
    
    _示例请求（替换）：__
    
    ```
    {
        "action": "guiAddNoteSetData",
        "version": 6,
        "params": {
            "note": {
                "deckName": "Default",
                "modelName": "Basic",
                "fields": {"Front": "Hello", "Back": "World"},
                "tags": ["new", "api"]
            }
        }
    }
    
    ```
    _示例请求（追加）：__
    
    ```
    {
        "action": "guiAddNoteSetData",
        "version": 6,
        "params": {
            "note": {
                "fields": {"Front": " more text"},
                "tags": ["extra"]
            },
            "append": true
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": true,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeguicurrentcardcode)`guiCurrentCard`

-   返回当前卡片的信息，如果不在复习模式下则返回 `null`。
    
    _示例请求：_
    
    ```
    {
        "action": "guiCurrentCard",
        "version": 6
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": {
            "answer": "back content",
            "question": "front content",
            "deckName": "Default",
            "modelName": "Basic",
            "fieldOrder": 0,
            "fields": {
                "Front": {"value": "front content", "order": 0},
                "Back": {"value": "back content", "order": 1}
            },
            "template": "Forward",
            "cardId": 1498938915662,
            "buttons": [1, 2, 3],
            "nextReviews": ["<1m", "<10m", "4d"]
        },
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeguistartcardtimercode)`guiStartCardTimer`

-   启动或重置当前卡片的 `timerStarted` 值。这对于延迟计时器启动时间直到通过 API 显示卡片非常有用，使得调用 `guiAnswerCard` 时记录的答题时间更加准确。
    
    _示例请求：_
    
    ```
    {
        "action": "guiStartCardTimer",
        "version": 6
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": true,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeguishowquestioncode)`guiShowQuestion`

-   显示当前卡片的问题文本；如果在复习模式下返回 `true`，否则返回 `false`。
    
    _示例请求：_
    
    ```
    {
        "action": "guiShowQuestion",
        "version": 6
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": true,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeguishowanswercode)`guiShowAnswer`

-   显示当前卡片的答案文本；如果在复习模式下返回 `true`，否则返回 `false`。
    
    _示例请求：_
    
    ```
    {
        "action": "guiShowAnswer",
        "version": 6
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": true,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeguianswercardcode)`guiAnswerCard`

-   回答当前卡片；如果成功返回 `true`，否则返回 `false`。注意，当前卡片的答案必须先显示，Anki 才能接受任何答案。
    
    _示例请求：_
    
    ```
    {
        "action": "guiAnswerCard",
        "version": 6,
        "params": {
            "ease": 1
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": true,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeguiundocode)`guiUndo`

-   撤销最后一个操作/卡片；如果成功返回 `true`，否则返回 `false`。
    
    _示例请求：_
    
    ```
    {
        "action": "guiUndo",
        "version": 6
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": true,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeguideckoverviewcode)`guiDeckOverview`

-   打开给定名称牌组的_牌组概览_对话框；如果成功返回 `true`，否则返回 `false`。
    
    _示例请求：_
    
    ```
    {
        "action": "guiDeckOverview",
        "version": 6,
        "params": {
            "name": "Default"
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": true,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeguideckbrowsercode)`guiDeckBrowser`

-   打开_牌组浏览器_对话框。
    
    _示例请求：_
    
    ```
    {
        "action": "guiDeckBrowser",
        "version": 6
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeguideckreviewcode)`guiDeckReview`

-   开始给定名称牌组的复习；如果成功返回 `true`，否则返回 `false`。
    
    _示例请求：_
    
    ```
    {
        "action": "guiDeckReview",
        "version": 6,
        "params": {
            "name": "Default"
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": true,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeguiimportfilecode)`guiImportFile`

-   调用_导入...（Ctrl+Shift+I）_对话框，可选择文件路径。弹出对话框让用户审查导入。支持 Anki 支持的所有文件格式。如果未提供路径则打开文件对话框。在 Windows 上路径中必须使用正斜杠。仅支持 Anki 2.1.52+。
    
    _示例请求：_
    
    ```
    {
        "action": "guiImportFile",
        "version": 6,
        "params": {
            "path": "C:/Users/Desktop/cards.txt"
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeguiexitankicode)`guiExitAnki`

-   安排请求以优雅关闭 Anki。此操作是异步的，因此它将立即返回，不会等待 Anki 进程实际终止。
    
    _示例请求：_
    
    ```
    {
        "action": "guiExitAnki",
        "version": 6
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeguicheckdatabasecode)`guiCheckDatabase`

-   请求数据库检查，但立即返回而不等待检查完成。因此，即使数据库检查期间检测到错误，操作也将始终返回 `true`。
    
    _示例请求：_
    
    ```
    {
        "action": "guiCheckDatabase",
        "version": 6
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": true,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeguiplayaudiocode)`guiPlayAudio`

-   播放当前卡片当前侧面的任何音频；如果成功返回 `true`，否则返回 `false`。
    
    _示例请求：_
    
    ```
    {
        "action": "guiPlayAudio",
        "version": 6
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": true,
        "error": null
    }
    
    ```
    

___

#### [#](https://git.sr.ht/~foosoft/anki-connect#media-actions)媒体操作

##### [#](https://git.sr.ht/~foosoft/anki-connect#codestoremediafilecode)`storeMediaFile`

-   在媒体文件夹中存储具有指定 base64 编码内容的文件。或者，您可以指定绝对文件路径，或从中下载文件的 URL。如果提供了 `data`、`path` 和 `url` 中的多个，则优先使用 `data` 字段，然后是 `path`，最后是 `url`。为了防止 Anki 删除未被任何卡片使用的文件（例如配置文件），请在文件名前加上下划线。这些文件仍会同步到 AnkiWeb。默认情况下，任何同名现有文件将被删除。设置 `deleteExisting` 为 false 以防止这种情况[让 Anki 为新文件分配非冲突名称](https://github.com/ankitects/anki/blob/aeba725d3ea9628c73300648f748140db3fdd5ed/rslib/src/media/files.rs#L194)。
    
    _示例请求（相对路径）：__
    
    ```
    {
        "action": "storeMediaFile",
        "version": 6,
        "params": {
            "filename": "_hello.txt",
            "data": "SGVsbG8sIHdvcmxkIQ=="
        }
    }
    
    ```
    
    `_hello.txt` 文件内容：
    
    ```
    Hello world!
    ```
    _示例结果（相对路径）：__
    
    ```
    {
        "result": "_hello.txt",
        "error": null
    }
    
    ```
    _示例请求（绝对路径）：__
    
    ```
    {
        "action": "storeMediaFile",
        "version": 6,
        "params": {
            "filename": "_hello.txt",
            "path": "/path/to/file"
        }
    }
    
    ```
    _示例结果（绝对路径）：__
    
    ```
    {
        "result": "_hello.txt",
        "error": null
    }
    
    ```
    _示例请求（URL）：__
    
    ```
    {
        "action": "storeMediaFile",
        "version": 6,
        "params": {
            "filename": "_hello.txt",
            "url": "https://url.to.file"
        }
    }
    
    ```
    _示例结果（URL）：__
    
    ```
    {
        "result": "_hello.txt",
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#coderetrievemediafilecode)`retrieveMediaFile`

-   检索指定文件的 base64 编码内容，如果文件不存在则返回 `false`。
    
    _示例请求：_
    
    ```
    {
        "action": "retrieveMediaFile",
        "version": 6,
        "params": {
            "filename": "_hello.txt"
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": "SGVsbG8sIHdvcmxkIQ==",
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codegetmediafilesnamescode)`getMediaFilesNames`

-   获取匹配模式的媒体文件名称。默认返回所有名称。
    
    _示例请求：_
    
    ```
    {
        "action": "getMediaFilesNames",
        "version": 6,
        "params": {
            "pattern": "_hell*.txt"
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": ["_hello.txt"],
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codegetmediadirpathcode)`getMediaDirPath`

-   获取当前打开配置文件的 `collection.media` 文件夹的完整路径。
    
    _示例请求：_
    
    ```
    {
        "action": "getMediaDirPath",
        "version": 6
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": "/home/user/.local/share/Anki2/Main/collection.media",
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codedeletemediafilecode)`deleteMediaFile`

-   删除媒体文件夹中的指定文件。
    
    _示例请求：_
    
    ```
    {
        "action": "deleteMediaFile",
        "version": 6,
        "params": {
            "filename": "_hello.txt"
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

___

#### [#](https://git.sr.ht/~foosoft/anki-connect#miscellaneous-actions)杂项操作

##### [#](https://git.sr.ht/~foosoft/anki-connect#coderequestpermissioncode)`requestPermission`

-   请求使用此插件公开的 API 的权限。此方法不需要 API 密钥，是唯一一个接受来自任何来源的请求的方法；其他方法仅接受来自可信来源的请求，这些来源列在加载项配置中的 `webCorsOriginList` 下。`localhost` 默认受信任。
    
    从不受信任的来源调用此方法将在 Anki 中显示一个弹出窗口，询问用户是否允许您的来源使用 API；来自受信任来源的调用将返回结果而不显示弹出窗口。拒绝权限时，用户还可以选择忽略来自该来源的进一步权限请求。这些来源最终进入 `ignoreOriginList`，可通过加载项配置进行编辑。
    
    结果始终包含 `permission` 字段，其中包含字符串 `granted` 或 `denied`，对应于您的来源是否受信任。如果您的来源受信任，还将返回 `requireApiKey`（如果需要则为 `true`）和 `version` 字段。
    
    这应该是您进行的第一个调用，以确保您的应用程序和 Anki-Connect 能够正确相互通信。新版本的 Anki-Connect 向后兼容；只要您使用的是报告中的 Anki-Connect 版本或更早版本中可用的 action，一切应该都能正常工作。
    
    _示例请求：_
    
    ```
    {
        "action": "requestPermission",
        "version": 6
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": {
            "permission": "granted",
            "requireApiKey": false,
            "version": 6
        },
        "error": null
    }
    
    ```
    
    ```
    {
        "result": {
            "permission": "denied"
        },
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeversioncode)`version`

-   获取此插件公开的 API 版本。目前定义了版本 `1` 到 `6`。
    
    _示例请求：_
    
    ```
    {
        "action": "version",
        "version": 6
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": 6,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeapireflectcode)`apiReflect`

-   获取关于可用 AnkiConnect API 的信息。请求支持以下参数：
    
    -   `scopes` - 要获取反射信息的范围数组。目前唯一支持的值是 `"actions"`。
    -   `actions` - 可以是 `null` 或 API 方法名数组。如果值为 `null`，结果将列出所有可用的 API action。如果值是字符串数组，结果将仅包含此数组中的 action。
    
    结果将包含已使用的范围列表以及每个范围的值。例如，`"actions"` 范围将包含一个 `"actions"` 属性，其中包含支持的 action 名称列表。
    
    _示例请求：_
    
    ```
    {
        "action": "apiReflect",
        "version": 6,
        "params": {
            "scopes": ["actions", "invalidType"],
            "actions": ["apiReflect", "invalidMethod"]
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": {
            "scopes": ["actions"],
            "actions": ["apiReflect"]
        },
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codesynccode)`sync`

-   将本地 Anki 集合与 AnkiWeb 同步。
    
    _示例请求：_
    
    ```
    {
        "action": "sync",
        "version": 6
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codegetprofilescode)`getProfiles`

-   获取配置文件列表。
    
    _示例请求：_
    
    ```
    {
        "action": "getProfiles",
        "version": 6
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": ["User 1"],
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codegetactiveprofilecode)`getActiveProfile`

-   获取当前活动的配置文件。
    
    _示例请求：_
    
    ```
    {
        "action": "getActiveProfile",
        "version": 6
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": "User 1",
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeloadprofilecode)`loadProfile`

-   选择请求中指定的配置文件。
    
    _示例请求：_
    
    ```
    {
        "action": "loadProfile",
        "version": 6,
        "params": {
            "name": "user1"
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": true,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codemulticode)`multi`

-   在一个请求中执行多个 action，返回包含每个 action 响应的数组（按给定顺序）。
    
    _示例请求：_
    
    ```
    {
        "action": "multi",
        "version": 6,
        "params": {
            "actions": [
                {
                    "action": "deckNames"
                },
                {
                    "action": "deckNames",
                    "version": 6
                },
                {
                    "action": "invalidAction",
                    "params": {"useless": "param"}
                },
                {
                    "action": "invalidAction",
                    "params": {"useless": "param"},
                    "version": 6
                }
            ]
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": [
            ["Default"],
            {"result": ["Default"], "error": null},
            {"result": null, "error": "unsupported action"},
            {"result": null, "error": "unsupported action"}
        ],
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeexportpackagecode)`exportPackage`

-   以 `.apkg` 格式导出给定牌组。如果成功返回 `true`，否则返回 `false`。可以指定可选属性 `includeSched`（默认为 `false`）以包含卡片的调度数据。
    
    _示例请求：_
    
    ```
    {
        "action": "exportPackage",
        "version": 6,
        "params": {
            "deck": "Default",
            "path": "/data/Deck.apkg",
            "includeSched": true
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": true,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeimportpackagecode)`importPackage`

-   将 `.apkg` 格式的文件导入到集合中。如果成功返回 `true`，否则返回 `false`。注意，文件路径是相对于 Anki 的 collection.media 文件夹，而不是客户端。
    
    _示例请求：_
    
    ```
    {
        "action": "importPackage",
        "version": 6,
        "params": {
            "path": "/data/Deck.apkg"
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": true,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codereloadcollectioncode)`reloadCollection`

-   告诉 Anki 从数据库重新加载所有数据。
    
    _示例请求：_
    
    ```
    {
        "action": "reloadCollection",
        "version": 6
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

___

#### [#](https://git.sr.ht/~foosoft/anki-connect#model-actions)模型操作

##### [#](https://git.sr.ht/~foosoft/anki-connect#codemodelnamescode)`modelNames`

-   获取当前用户的完整模板名称列表。
    
    _示例请求：_
    
    ```
    {
        "action": "modelNames",
        "version": 6
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": ["Basic", "Basic (and reversed card)"],
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codemodelnamesandidscode)`modelNamesAndIds`

-   获取当前用户的完整模板名称及其对应 ID 列表。
    
    _示例请求：_
    
    ```
    {
        "action": "modelNamesAndIds",
        "version": 6
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": {
            "Basic": 1483883011648,
            "Basic (and reversed card)": 1483883011644,
            "Basic (optional reversed card)": 1483883011631,
            "Cloze": 1483883011630
        },
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codefindmodelsbyidcode)`findModelsById`

-   从当前用户获取提供模型 ID 的模板列表。
    
    _示例请求：_
    
    ```
    {
        "action": "findModelsById",
        "version": 6,
        "params": {
            "modelIds": [1704387367119, 1704387398570]
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": [
          {
            "id": 1704387367119,
            "name": "Basic",
            "type": 0,
            "mod": 1704387367,
            "usn": -1,
            "sortf": 0,
            "did": null,
            "tmpls": [
              {
                "name": "Card 1",
                "ord": 0,
                "qfmt": "{{Front}}",
                "afmt": "{{FrontSide}}\n\n<hr id=answer>\n\n{{Back}}",
                "bqfmt": "",
                "bafmt": "",
                "did": null,
                "bfont": "",
                "bsize": 0,
                "id": 9176047152973362695
              }
            ],
            "flds": [
              {
                "name": "Front",
                "ord": 0,
                "sticky": false,
                "rtl": false,
                "font": "Arial",
                "size": 20,
                "description": "",
                "plainText": false,
                "collapsed": false,
                "excludeFromSearch": false,
                "id": 2453723143453745216,
                "tag": null,
                "preventDeletion": false
              },
              {
                "name": "Back",
                "ord": 1,
                "sticky": false,
                "rtl": false,
                "font": "Arial",
                "size": 20,
                "description": "",
                "plainText": false,
                "collapsed": false,
                "excludeFromSearch": false,
                "id": -4853200230425436781,
                "tag": null,
                "preventDeletion": false
              }
            ],
            "css": ".card {\n    font-family: arial;\n    font-size: 20px;\n    text-align: center;\n    color: black;\n    background-color: white;\n}\n",
            "latexPre": "\\documentclass[12pt]{article}\n\\special{papersize=3in,5in}\n\\usepackage[utf8]{inputenc}\n\\usepackage{amssymb,amsmath}\n\\pagestyle{empty}\n\\setlength{\\parindent}{0in}\n\\begin{document}\n",
            "latexPost": "\\end{document}",
            "latexsvg": false,
            "req": [
              [
                0,
                "any",
                [
                  0
                ]
              ]
            ],
            "originalStockKind": 1
          },
          {
            "id": 1704387398570,
            "name": "Basic (and reversed card)",
            "type": 0,
            "mod": 1704387398,
            "usn": -1,
            "sortf": 0,
            "did": null,
            "tmpls": [
              {
                "name": "Card 1",
                "ord": 0,
                "qfmt": "{{Front}}",
                "afmt": "{{FrontSide}}\n\n<hr id=answer>\n\n{{Back}}",
                "bqfmt": "",
                "bafmt": "",
                "did": null,
                "bfont": "",
                "bsize": 0,
                "id": 1689886528158874152
              },
              {
                "name": "Card 2",
                "ord": 1,
                "qfmt": "{{Back}}",
                "afmt": "{{FrontSide}}\n\n<hr id=answer>\n\n{{Front}}",
                "bqfmt": "",
                "bafmt": "",
                "did": null,
                "bfont": "",
                "bsize": 0,
                "id": -7839609225644824587
              }
            ],
            "flds": [
              {
                "name": "Front",
                "ord": 0,
                "sticky": false,
                "rtl": false,
                "font": "Arial",
                "size": 20,
                "description": "",
                "plainText": false,
                "collapsed": false,
                "excludeFromSearch": false,
                "id": -7787837672455357996,
                "tag": null,
                "preventDeletion": false
              },
              {
                "name": "Back",
                "ord": 1,
                "sticky": false,
                "rtl": false,
                "font": "Arial",
                "size": 20,
                "description": "",
                "plainText": false,
                "collapsed": false,
                "excludeFromSearch": false,
                "id": 6364828289839985081,
                "tag": null,
                "preventDeletion": false
              }
            ],
            "css": ".card {\n    font-family: arial;\n    font-size: 20px;\n    text-align: center;\n    color: black;\n    background-color: white;\n}\n",
            "latexPre": "\\documentclass[12pt]{article}\n\\special{papersize=3in,5in}\n\\usepackage[utf8]{inputenc}\n\\usepackage{amssymb,amsmath}\n\\pagestyle{empty}\n\\setlength{\\parindent}{0in}\n\\begin{document}\n",
            "latexPost": "\\end{document}",
            "latexsvg": false,
            "req": [
              [
                0,
                "any",
                [
                  0
                ]
              ],
              [
                1,
                "any",
                [
                  1
                ]
              ]
            ],
            "originalStockKind": 1
          }
        ],
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codefindmodelsbynamecode)`findModelsByName`

-   从当前用户获取提供模板名称的模板列表。
    
    _示例请求：_
    
    ```
    {
        "action": "findModelsByName",
        "version": 6,
        "params": {
            "modelNames": ["Basic", "Basic (and reversed card)"]
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": [
          {
            "id": 1704387367119,
            "name": "Basic",
            "type": 0,
            "mod": 1704387367,
            "usn": -1,
            "sortf": 0,
            "did": null,
            "tmpls": [
              {
                "name": "Card 1",
                "ord": 0,
                "qfmt": "{{Front}}",
                "afmt": "{{FrontSide}}\n\n<hr id=answer>\n\n{{Back}}",
                "bqfmt": "",
                "bafmt": "",
                "did": null,
                "bfont": "",
                "bsize": 0,
                "id": 9176047152973362695
              }
            ],
            "flds": [
              {
                "name": "Front",
                "ord": 0,
                "sticky": false,
                "rtl": false,
                "font": "Arial",
                "size": 20,
                "description": "",
                "plainText": false,
                "collapsed": false,
                "excludeFromSearch": false,
                "id": 2453723143453745216,
                "tag": null,
                "preventDeletion": false
              },
              {
                "name": "Back",
                "ord": 1,
                "sticky": false,
                "rtl": false,
                "font": "Arial",
                "size": 20,
                "description": "",
                "plainText": false,
                "collapsed": false,
                "excludeFromSearch": false,
                "id": -4853200230425436781,
                "tag": null,
                "preventDeletion": false
              }
            ],
            "css": ".card {\n    font-family: arial;\n    font-size: 20px;\n    text-align: center;\n    color: black;\n    background-color: white;\n}\n",
            "latexPre": "\\documentclass[12pt]{article}\n\\special{papersize=3in,5in}\n\\usepackage[utf8]{inputenc}\n\\usepackage{amssymb,amsmath}\n\\pagestyle{empty}\n\\setlength{\\parindent}{0in}\n\\begin{document}\n",
            "latexPost": "\\end{document}",
            "latexsvg": false,
            "req": [
              [
                0,
                "any",
                [
                  0
                ]
              ]
            ],
            "originalStockKind": 1
          },
          {
            "id": 1704387398570,
            "name": "Basic (and reversed card)",
            "type": 0,
            "mod": 1704387398,
            "usn": -1,
            "sortf": 0,
            "did": null,
            "tmpls": [
              {
                "name": "Card 1",
                "ord": 0,
                "qfmt": "{{Front}}",
                "afmt": "{{FrontSide}}\n\n<hr id=answer>\n\n{{Back}}",
                "bqfmt": "",
                "bafmt": "",
                "did": null,
                "bfont": "",
                "bsize": 0,
                "id": 1689886528158874152
              },
              {
                "name": "Card 2",
                "ord": 1,
                "qfmt": "{{Back}}",
                "afmt": "{{FrontSide}}\n\n<hr id=answer>\n\n{{Front}}",
                "bqfmt": "",
                "bafmt": "",
                "did": null,
                "bfont": "",
                "bsize": 0,
                "id": -7839609225644824587
              }
            ],
            "flds": [
              {
                "name": "Front",
                "ord": 0,
                "sticky": false,
                "rtl": false,
                "font": "Arial",
                "size": 20,
                "description": "",
                "plainText": false,
                "collapsed": false,
                "excludeFromSearch": false,
                "id": -7787837672455357996,
                "tag": null,
                "preventDeletion": false
              },
              {
                "name": "Back",
                "ord": 1,
                "sticky": false,
                "rtl": false,
                "font": "Arial",
                "size": 20,
                "description": "",
                "plainText": false,
                "collapsed": false,
                "excludeFromSearch": false,
                "id": 6364828289839985081,
                "tag": null,
                "preventDeletion": false
              }
            ],
            "css": ".card {\n    font-family: arial;\n    font-size: 20px;\n    text-align: center;\n    color: black;\n    background-color: white;\n}\n",
            "latexPre": "\\documentclass[12pt]{article}\n\\special{papersize=3in,5in}\n\\usepackage[utf8]{inputenc}\n\\usepackage{amssymb,amsmath}\n\\pagestyle{empty}\n\\setlength{\\parindent}{0in}\n\\begin{document}\n",
            "latexPost": "\\end{document}",
            "latexsvg": false,
            "req": [
              [
                0,
                "any",
                [
                  0
                ]
              ],
              [
                1,
                "any",
                [
                  1
                ]
              ]
            ],
            "originalStockKind": 1
          }
        ],
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codemodelfieldnamescode)`modelFieldNames`

-   获取提供模板名称的完整字段名称列表。
    
    _示例请求：_
    
    ```
    {
        "action": "modelFieldNames",
        "version": 6,
        "params": {
            "modelName": "Basic"
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": ["Front", "Back"],
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codemodelfielddescriptionscode)`modelFieldDescriptions`

-   获取提供模板名称的完整字段描述列表（在 GUI 编辑器中字段为空时看到的文本）。
    
    _示例请求：_
    
    ```
    {
        "action": "modelFieldDescriptions",
        "version": 6,
        "params": {
            "modelName": "Basic"
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": ["", ""],
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codemodelfieldfontscode)`modelFieldFonts`

-   获取完整的字体及其字体大小列表。
    
    _示例请求：_
    
    ```
    {
        "action": "modelFieldFonts",
        "version": 6,
        "params": {
            "modelName": "Basic"
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": {
            "Front": {
                "font": "Arial",
                "size": 20
            },
            "Back": {
                "font": "Arial",
                "size": 20
            }
        },
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codemodelfieldsontemplatescode)`modelFieldsOnTemplates`

-   返回一个对象，指示给定模板名称的每张卡片模板的问题和答案侧的字段。每个数组中首先给出的是问题侧。
    
    _示例请求：_
    
    ```
    {
        "action": "modelFieldsOnTemplates",
        "version": 6,
        "params": {
            "modelName": "Basic (and reversed card)"
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": {
            "Card 1": [["Front"], ["Back"]],
            "Card 2": [["Back"], ["Front"]]
        },
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codecreatemodelcode)`createModel`

-   创建一个新的用于 Anki 的模板。用户必须提供要在模板中使用的 `modelName`、`inOrderFields` 和 `cardTemplates`。有可选字段 `css` 和 `isCloze`。如果未指定，`css` 将使用默认 Anki CSS，`isCloze` 将等于 `false`。如果 `isCloze` 为 `true`，则模板将作为 Cloze 创建。
    
    可选地为 `cardTemplates` 中的每个条目提供 `Name` 字段。默认情况下，卡片名称将为 `Card 1`、`Card 2` 等。
    
    _示例请求：_
    
    ```
    {
        "action": "createModel",
        "version": 6,
        "params": {
            "modelName": "newModelName",
            "inOrderFields": ["Field1", "Field2", "Field3"],
            "css": "Optional CSS with default to builtin css",
            "isCloze": false,
            "cardTemplates": [
                {
                    "Name": "My Card 1",
                    "Front": "Front html {{Field1}}",
                    "Back": "Back html  {{Field2}}"
                }
            ]
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result":{
            "sortf":0,
            "did":1,
            "latexPre":"\\documentclass[12pt]{article}\n\\special{papersize=3in,5in}\n\\usepackage[utf8]{inputenc}\n\\usepackage{amssymb,amsmath}\n\\pagestyle{empty}\n\\setlength{\\parindent}{0in}\n\\begin{document}\n",
            "latexPost":"\\end{document}",
            "mod":1551462107,
            "usn":-1,
            "vers":[
    
            ],
            "type":0,
            "css":".card {\n font-family: arial;\n font-size: 20px;\n text-align: center;\n color: black;\n background-color: white;\n}\n",
            "name":"TestApiModel",
            "flds":[
                {
                    "name":"Field1",
                    "ord":0,
                    "sticky":false,
                    "rtl":false,
                    "font":"Arial",
                    "size":20,
                    "media":[
    
                    ]
                },
                {
                    "name":"Field2",
                    "ord":1,
                    "sticky":false,
                    "rtl":false,
                    "font":"Arial",
                    "size":20,
                    "media":[
    
                    ]
                }
            ],
            "tmpls":[
                {
                    "name":"My Card 1",
                    "ord":0,
                    "qfmt":"",
                    "afmt":"This is the back of the card {{Field2}}",
                    "did":null,
                    "bqfmt":"",
                    "bafmt":""
                }
            ],
            "tags":[
    
            ],
            "id":1551462107104,
            "req":[
                [
                    0,
                    "none",
                    [
    
                    ]
                ]
            ]
        },
        "error":null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codemodeltemplatescode)`modelTemplates`

-   返回一个对象，指示连接到提供模板名称的每张卡片的模板内容。
    
    _示例请求：_
    
    ```
    {
        "action": "modelTemplates",
        "version": 6,
        "params": {
            "modelName": "Basic (and reversed card)"
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": {
            "Card 1": {
                "Front": "{{Front}}",
                "Back": "{{FrontSide}}\n\n<hr id=answer>\n\n{{Back}}"
            },
            "Card 2": {
                "Front": "{{Back}}",
                "Back": "{{FrontSide}}\n\n<hr id=answer>\n\n{{Front}}"
            }
        },
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codemodelstylingcode)`modelStyling`

-   获取提供模板名称的 CSS 样式。
    
    _示例请求：_
    
    ```
    {
        "action": "modelStyling",
        "version": 6,
        "params": {
            "modelName": "Basic (and reversed card)"
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": {
            "css": ".card {\n font-family: arial;\n font-size: 20px;\n text-align: center;\n color: black;\n background-color: white;\n}\n"
        },
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeupdatemodeltemplatescode)`updateModelTemplates`

-   按名称修改现有模板的模板。仅指定卡片和指定侧面将被修改。如果现有卡片或侧面未在请求中包含，则保持不变。
    
    _示例请求：_
    
    ```
    {
        "action": "updateModelTemplates",
        "version": 6,
        "params": {
            "model": {
                "name": "Custom",
                "templates": {
                    "Card 1": {
                        "Front": "{{Question}}?",
                        "Back": "{{Answer}}!"
                    }
                }
            }
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeupdatemodelstylingcode)`updateModelStyling`

-   按名称修改现有模板的 CSS 样式。
    
    _示例请求：_
    
    ```
    {
        "action": "updateModelStyling",
        "version": 6,
        "params": {
            "model": {
                "name": "Custom",
                "css": "p { color: blue; }"
            }
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codefindandreplaceinmodelscode)`findAndReplaceInModels`

-   按模板名称在现有模板中查找并替换字符串。通过设置为 true/false 自定义替换正面、背面或 CSS。
    
    _示例请求：_
    
    ```
    {
        "action": "findAndReplaceInModels",
        "version": 6,
        "params": {
            "model": {
                "modelName": "",
                "findText": "text_to_replace",
                "replaceText": "replace_with_text",
                "front": true,
                "back": true,
                "css": true
            }
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": 1,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codemodeltemplaterenamecode)`modelTemplateRename`

-   重命名现有模板中的模板。
    
    _示例请求：_
    
    ```
    {
        "action": "modelTemplateRename",
        "version": 6,
        "params": {
            "modelName": "Basic",
            "oldTemplateName": "Card 1",
            "newTemplateName": "Card 1 renamed"
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codemodeltemplaterepositioncode)`modelTemplateReposition`

-   重新定位现有模板中的模板。
    
    `index` 的值从 0 开始。例如，索引 `0` 将模板放在第一位，索引 `2` 将模板放在第三位。
    
    _示例请求：_
    
    ```
    {
        "action": "modelTemplateReposition",
        "version": 6,
        "params": {
            "modelName": "Basic",
            "templateName": "Card 1",
            "index": 1
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codemodeltemplateaddcode)`modelTemplateAdd`

-   按名称向现有模板添加模板。如果要更新现有模板，请使用 `updateModelTemplates`。
    
    _示例请求：_
    
    ```
    {
        "action": "modelTemplateAdd",
        "version": 6,
        "params": {
            "modelName": "Basic",
            "template": {
                "Name": "Card 3",
                "Front": "Front html {{Field1}}",
                "Back": "Back html {{Field2}}"
            }
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codemodeltemplateremovecode)`modelTemplateRemove`

-   从现有模板中删除模板。
    
    _示例请求：_
    
    ```
    {
        "action": "modelTemplateRemove",
        "version": 6,
        "params": {
            "modelName": "Basic",
            "templateName": "Card 1"
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codemodelfieldrenamecode)`modelFieldRename`

-   重命名给定模板的字段名称。
    
    _示例请求：_
    
    ```
    {
        "action": "modelFieldRename",
        "version": 6,
        "params": {
            "modelName": "Basic",
            "oldFieldName": "Front",
            "newFieldName": "FrontRenamed"
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codemodelfieldrepositioncode)`modelFieldReposition`

-   重新定位给定模板字段列表中字段的位置。
    
    `index` 的值从 0 开始。例如，索引 `0` 将字段放在第一位，索引 `2` 将字段放在第三位。
    
    _示例请求：_
    
    ```
    {
        "action": "modelFieldReposition",
        "version": 6,
        "params": {
            "modelName": "Basic",
            "fieldName": "Back",
            "index": 0
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codemodelfieldaddcode)`modelFieldAdd`

-   在给定模板内创建新字段。
    
    可选地，可以提供 `index` 值，其工作方式与 `modelFieldReposition` 中的索引完全相同。默认情况下，字段将添加到字段列表末尾。
    
    _示例请求：_
    
    ```
    {
        "action": "modelFieldAdd",
        "version": 6,
        "params": {
            "modelName": "Basic",
            "fieldName": "NewField",
            "index": 0
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codemodelfieldremovecode)`modelFieldRemove`

-   删除给定模板内的字段。
    
    _示例请求：_
    
    ```
    {
        "action": "modelFieldRemove",
        "version": 6,
        "params": {
            "modelName": "Basic",
            "fieldName": "Front"
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codemodelfieldsetfontcode)`modelFieldSetFont`

-   设置给定模板中字段的字体。
    
    _示例请求：_
    
    ```
    {
        "action": "modelFieldSetFont",
        "version": 6,
        "params": {
            "modelName": "Basic",
            "fieldName": "Front",
            "font": "Courier"
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codemodelfieldsetfontsizecode)`modelFieldSetFontSize`

-   设置给定模板中字段的字体大小。
    
    _示例请求：_
    
    ```
    {
        "action": "modelFieldSetFontSize",
        "version": 6,
        "params": {
            "modelName": "Basic",
            "fieldName": "Front",
            "fontSize": 10
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codemodelfieldsetdescriptioncode)`modelFieldSetDescription`

-   设置给定模板中字段的描述（在 GUI 编辑器中字段为空时看到的文本）。
    
    旧版本的 Anki（2.1.49 及以下）没有字段描述。在这种情况下，这将返回 `false`。
    
    _示例请求：_
    
    ```
    {
        "action": "modelFieldSetDescription",
        "version": 6,
        "params": {
            "modelName": "Basic",
            "fieldName": "Front",
            "description": "example field description"
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": true,
        "error": null
    }
    
    ```
    

___

#### [#](https://git.sr.ht/~foosoft/anki-connect#note-actions)笔记操作

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeaddnotecode)`addNote`

-   使用给定的牌组和模板，以及提供的字段值和标签创建笔记。成功时返回创建的笔记的标识符，失败时返回 `null`。
    
    Anki-Connect 可以下载音频、视频和图片文件并将其嵌入到新创建的笔记中。相应的 `audio`、`video` 和 `picture` 笔记成员是可选的，可以省略。如果选择包含其中任何一个，它们应包含一个带有必填 `filename` 字段和一个 `data`、`path` 或 `url` 的对象或对象数组。有关这些字段的说明，请参考 `storeMediaFile` 的文档。可以选择性地提供 `skipHash` 字段以跳过包含与提供值匹配的 MD5 哈希的文件。这对于避免保存错误页面和存根文件非常有用。`fields` 成员是要在其中插入媒体的字段名称列表。如果不需此功能可以省略。`options` 组内的 `allowDuplicate` 成员可以设置为 true 以启用添加重复卡片。通常不能添加重复卡片并会触发异常。
    
    `options` 内的 `duplicateScope` 成员可用于指定检查重复的范围。`"deck"` 值仅检查目标牌组中的重复项；任何其他值将检查整个集合。
    
    `duplicateScopeOptions` 对象可用于指定一些附加设置：
    
    -   `duplicateScopeOptions.deckName` 将指定用于检查重复的牌组。如果未定义或为 `null`，将使用目标牌组。
    -   `duplicateScopeOptions.checkChildren` 将改变是否在子牌组中检查重复卡片。默认值为 `false`。
    -   `duplicateScopeOptions.checkAllModels` 指定是否在所有笔记类型上执行重复检查。默认值为 `false`。
    
    _示例请求：_
    
    ```
    {
        "action": "addNote",
        "version": 6,
        "params": {
            "note": {
                "deckName": "Default",
                "modelName": "Basic",
                "fields": {
                    "Front": "front content",
                    "Back": "back content"
                },
                "options": {
                    "allowDuplicate": false,
                    "duplicateScope": "deck",
                    "duplicateScopeOptions": {
                        "deckName": "Default",
                        "checkChildren": false,
                        "checkAllModels": false
                    }
                },
                "tags": [
                    "yomichan"
                ],
                "audio": [{
                    "url": "https://assets.languagepod101.com/dictionary/japanese/audiomp3.php?kanji=猫&kana=ねこ",
                    "filename": "yomichan_ねこ_猫.mp3",
                    "skipHash": "7e2c2f954ef6051373ba916f000168dc",
                    "fields": [
                        "Front"
                    ]
                }],
                "video": [{
                    "url": "https://cdn.videvo.net/videvo_files/video/free/2015-06/small_watermarked/Contador_Glam_preview.mp4",
                    "filename": "countdown.mp4",
                    "skipHash": "4117e8aab0d37534d9c8eac362388bbe",
                    "fields": [
                        "Back"
                    ]
                }],
                "picture": [{
                    "url": "https://upload.wikimedia.org/wikipedia/commons/thumb/c/c7/A_black_cat_named_Tilly.jpg/220px-A_black_cat_named_Tilly.jpg",
                    "filename": "black_cat.jpg",
                    "skipHash": "8d6e4646dfae812bf39651b59d7429ce",
                }]
            }
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": 1496198395707,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeaddnotescode)`addNotes`

-   使用给定的牌组和模板，以及提供的字段值和标签创建多个笔记。返回创建的笔记标识符数组。如果出现任何错误，将收集并返回所有错误。
    
-   请参阅 `addNote` 的文档以了解 `notes` 数组中的对象说明。
    
    _示例请求：_
    
    ```
    {
       "action":"addNotes",
       "version":6,
       "params":{
          "notes":[
             {
                "deckName":"College::PluginDev",
                "modelName":"non_existent_model",
                "fields":{
                   "Front":"front",
                   "Back":"bak"
                }
             },
             {
                "deckName":"College::PluginDev",
                "modelName":"Basic",
                "fields":{
                   "Front":"front",
                   "Back":"bak"
                }
             }
          ]
       }
    }
    
    ```
    _示例结果：_
    
    ```
    {
       "result":null,
       "error":"['model was not found: non_existent_model']"
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codecanaddnotescode)`canAddNotes`

-   接受定义候选笔记参数的对象数组（参见 `addNote`），并返回一个布尔值数组，指示相应索引处的参数是否可以用于创建新笔记。
    
    _示例请求：_
    
    ```
    {
        "action": "canAddNotes",
        "version": 6,
        "params": {
            "notes": [
                {
                    "deckName": "Default",
                    "modelName": "Basic",
                    "fields": {
                        "Front": "front content",
                        "Back": "back content"
                    },
                    "tags": [
                        "yomichan"
                    ]
                }
            ]
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": [true],
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codecanaddnoteswitherrordetailcode)`canAddNotesWithErrorDetail`

-   接受定义候选笔记参数的对象数组（参见 `addNote`），并返回一个包含 `canAdd` 和 `error` 字段的对象数组。
    
    -   `canAdd` 指示相应索引处的参数是否可以用于创建新笔记。
    -   `error` 包含无法添加笔记的原因说明。
    
    _示例请求：_
    
    ```
    {
        "action": "canAddNotesWithErrorDetail",
        "version": 6,
        "params": {
            "notes": [
                {
                    "deckName": "Default",
                    "modelName": "Basic",
                    "fields": {
                        "Front": "front content",
                        "Back": "back content"
                    },
                    "tags": [
                        "yomichan"
                    ]
                },
                {
                    "deckName": "Default",
                    "modelName": "Basic",
                    "fields": {
                        "Front": "front content 2",
                        "Back": "back content 2"
                    },
                    "tags": [
                        "yomichan"
                    ]
                }
            ]
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": [
            {
                "canAdd": false,
                "error": "cannot create note because it is a duplicate"
            },
            {
                "canAdd": true
            }
        ],
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeupdatenotefieldscode)`updateNoteFields`

-   修改现有笔记的字段。您还可以包含音频、视频或图片文件，它们将通过可选的 `audio`、`video` 或 `picture` 属性添加到笔记中。请参阅 `addNote` 的文档以了解 `audio`、`video` 或 `picture` 数组中的对象说明。
    
    > **警告**：您不能在 Anki 浏览器中查看正在更新的笔记，否则字段将不会更新。有关更多详细信息，请参阅[此问题](https://github.com/FooSoft/anki-connect/issues/82)。
    
    _示例请求：_
    
    ```
    {
        "action": "updateNoteFields",
        "version": 6,
        "params": {
            "note": {
                "id": 1514547547030,
                "fields": {
                    "Front": "new front content",
                    "Back": "new back content"
                },
                "audio": [{
                    "url": "https://assets.languagepod101.com/dictionary/japanese/audiomp3.php?kanji=猫&kana=ねこ",
                    "filename": "yomichan_ねこ_猫.mp3",
                    "skipHash": "7e2c2f954ef6051373ba916f000168dc",
                    "fields": [
                        "Front"
                    ]
                }]
            }
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeupdatenotecode)`updateNote`

-   修改现有笔记的字段和/或标签。换句话说，结合了 `updateNoteFields` 和 `updateNoteTags`。请参阅它们的文档以了解所有属性的说明。
    
    `fields` 或 `tags` 属性可以省略而不影响另一个。因此，对 `updateNoteFields` 的有效请求也适用于 `updateNote`。笔记必须具有 `fields` 属性才能更新可选的音频、视频或图片对象。
    
    如果未提供 `fields` 和 `tags`，该方法将失败。首先更新字段，如果更新标签失败则不会回滚。如果更新字段失败，则不更新标签。
    
    > **警告** 您不能在 Anki 浏览器中查看正在更新的笔记，否则字段将不会更新。有关更多详细信息，请参阅[此问题](https://github.com/FooSoft/anki-connect/issues/82)。
    
    _示例请求：_
    
    ```
    {
        "action": "updateNote",
        "version": 6,
        "params": {
            "note": {
                "id": 1514547547030,
                "fields": {
                    "Front": "new front content",
                    "Back": "new back content"
                },
                "tags": ["new", "tags"]
            }
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeupdatenotemodelcode)`updateNoteModel`

-   更新现有笔记的模板、字段和标签。这允许您更改笔记的模板，使用新内容更新其字段，并设置新标签。
    
    _示例请求：_
    
    ```
    {
        "action": "updateNoteModel",
        "version": 6,
        "params": {
            "note": {
                "id": 1514547547030,
                "modelName": "NewModel",
                "fields": {
                    "NewField1": "new field 1",
                    "NewField2": "new field 2",
                    "NewField3": "new field 3"
                },
                "tags": ["new", "updated", "tags"]
            }
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeupdatenotetagscode)`updateNoteTags`

-   通过笔记 ID 设置笔记的标签。旧标签将被移除。
    
    _示例请求：_
    
    ```
    {
        "action": "updateNoteTags",
        "version": 6,
        "params": {
            "note": 1483959289817,
            "tags": ["european-languages"]
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codegetnotetagscode)`getNoteTags`

-   通过笔记 ID 获取笔记的标签。
    
    _示例请求：_
    
    ```
    {
        "action": "getNoteTags",
        "version": 6,
        "params": {
            "note": 1483959289817
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": ["european-languages"],
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeaddtagscode)`addTags`

-   通过笔记 ID 向笔记添加标签。
    
    _示例请求：_
    
    ```
    {
        "action": "addTags",
        "version": 6,
        "params": {
            "notes": [1483959289817, 1483959291695],
            "tags": "european-languages"
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#coderemovetagscode)`removeTags`

-   通过笔记 ID 从笔记中移除标签。
    
    _示例请求：_
    
    ```
    {
        "action": "removeTags",
        "version": 6,
        "params": {
            "notes": [1483959289817, 1483959291695],
            "tags": "european-languages"
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codegettagscode)`getTags`

-   获取当前用户的完整标签列表。
    
    _示例请求：_
    
    ```
    {
        "action": "getTags",
        "version": 6
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": ["european-languages", "idioms"],
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeclearunusedtagscode)`clearUnusedTags`

-   清除当前用户笔记中所有未使用的标签。
    
    _示例请求：_
    
    ```
    {
        "action": "clearUnusedTags",
        "version": 6
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codereplacetagscode)`replaceTags`

-   通过笔记 ID 替换笔记中的标签。
    
    _示例请求：_
    
    ```
    {
        "action": "replaceTags",
        "version": 6,
        "params": {
            "notes": [1483959289817, 1483959291695],
            "tag_to_replace": "european-languages",
            "replace_with_tag": "french-languages"
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codereplacetagsinallnotescode)`replaceTagsInAllNotes`

-   替换当前用户所有笔记中的标签。
    
    _示例请求：_
    
    ```
    {
        "action": "replaceTagsInAllNotes",
        "version": 6,
        "params": {
            "tag_to_replace": "european-languages",
            "replace_with_tag": "french-languages"
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codefindnotescode)`findNotes`

-   返回给定查询的笔记 ID 数组。查询语法[在此记录](https://docs.ankiweb.net/searching.html)。
    
    _示例请求：_
    
    ```
    {
        "action": "findNotes",
        "version": 6,
        "params": {
            "query": "deck:current"
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": [1483959289817, 1483959291695],
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codenotesinfocode)`notesInfo`

-   返回一个对象列表，包含每个笔记 ID 的笔记字段、标签、笔记类型、修改时间、属于该笔记的卡片以及创建该笔记的配置文件。
    
    _示例请求（笔记 ID）：__
    
    ```
    {
        "action": "notesInfo",
        "version": 6,
        "params": {
            "notes": [1502298033753]
        }
    }
    
    ```
    _示例请求（查询）：__
    
    ```
    {
        "action": "notesInfo",
        "version": 6,
        "params": {
            "query": "deck:current"
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": [
            {
                "noteId":1502298033753,
                "profile": "User_1",
                "modelName": "Basic",
                "tags":["tag","another_tag"],
                "fields": {
                    "Front": {"value": "front content", "order": 0},
                    "Back": {"value": "back content", "order": 1}
                },
                "mod": 1718377864,
                "cards": [1498938915662]
            }
        ],
        "error": null
    }
    
    ```
    s

##### [#](https://git.sr.ht/~foosoft/anki-connect#codenotesmodtimecode)`notesModTime`

-   返回一个对象列表，包含每个笔记 ID 的修改时间。
    
    _示例请求：_
    
    ```
    {
        "action": "notesModTime",
        "version": 6,
        "params": {
            "notes": [1502298033753]
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": [
            {
                "noteId": 1498938915662,
                "mod": 1629454092
            }
        ],
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codedeletenotescode)`deleteNotes`

-   删除给定 ID 的笔记。如果笔记有多个关联的卡片，所有关联的卡片都将被删除。
    
    _示例请求：_
    
    ```
    {
        "action": "deleteNotes",
        "version": 6,
        "params": {
            "notes": [1502298033753]
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#coderemoveemptynotescode)`removeEmptyNotes`

-   移除当前用户的所有空笔记。
    
    _示例请求：_
    
    ```
    {
        "action": "removeEmptyNotes",
        "version": 6
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```
    

___

#### [#](https://git.sr.ht/~foosoft/anki-connect#statistic-actions)统计操作

##### [#](https://git.sr.ht/~foosoft/anki-connect#codegetnumcardsreviewedtodaycode)`getNumCardsReviewedToday`

-   获取当天（以用户在 Anki 中配置的日期起始时间为准）已复习的卡片数量
    
    _示例请求：_
    
    ```
    {
        "action": "getNumCardsReviewedToday",
        "version": 6
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": 0,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codegetnumcardsreviewedbydaycode)`getNumCardsReviewedByDay`

-   获取已复习卡片数量，以 `(日期字符串, 数量)` 对列表形式返回。
    
    _示例请求：_
    
    ```
    {
        "action": "getNumCardsReviewedByDay",
        "version": 6
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result":  [
            ["2021-02-28", 124],
            ["2021-02-27", 261]
        ],
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codegetcollectionstatshtmlcode)`getCollectionStatsHTML`

-   获取集合统计报告。
    
    _示例请求：_
    
    ```
    {
        "action": "getCollectionStatsHTML",
        "version": 6,
        "params": {
            "wholeCollection": true
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": "<center> lots of HTML here </center>",
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codecardreviewscode)`cardReviews`

-   请求指定牌组在某个时间之后的所有卡片复习记录。`startID` 是不包含在结果中的最新 Unix 时间。返回 9 元组 `(复习时间, 卡片 ID, usn, 按下的按钮, 新区间, 前一个区间, 新因子, 复习持续时间, 复习类型)` 列表。
    
    _示例请求：_
    
    ```
    {
        "action": "cardReviews",
        "version": 6,
        "params": {
            "deck": "default",
            "startID": 1594194095740
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": [
            [1594194095746, 1485369733217, -1, 3,   4, -60, 2500, 6157, 0],
            [1594201393292, 1485369902086, -1, 1, -60, -60,    0, 4846, 0]
        ],
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codegetreviewsofcardscode)`getReviewsOfCards`

-   请求每张卡片 ID 的所有卡片复习记录。返回将每张卡片 ID 映射到字典列表的字典，格式为：
    
    ```
    {
        "id": reviewTime,
        "usn": usn,
        "ease": buttonPressed,
        "ivl": newInterval,
        "lastIvl": previousInterval,
        "factor": newFactor,
        "time": reviewDuration,
        "type": reviewType,
    }
    ```
    
    使用这些键值而不是更具描述性的对应值的原因是，这些是 Anki 数据库中使用的确切键值。
    
    _示例请求：_
    
    ```
    {
        "action": "getReviewsOfCards",
        "version": 6,
        "params": {
            "cards": [
                "1653613948202"
            ]
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": {
            "1653613948202": [
                {
                    "id": 1653772912146,
                    "usn": 1750,
                    "ease": 1,
                    "ivl": -20,
                    "lastIvl": -20,
                    "factor": 0,
                    "time": 38192,
                    "type": 0
                },
                {
                    "id": 1653772965429,
                    "usn": 1750,
                    "ease": 3,
                    "ivl": -45,
                    "lastIvl": -20,
                    "factor": 0,
                    "time": 15337,
                    "type": 0
                }
            ]
        },
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codegetlatestreviewidcode)`getLatestReviewID`

-   返回给定牌组的最新复习的 Unix 时间。如果从未为该牌组进行过复习则返回 0。
    
    _示例请求：_
    
    ```
    {
        "action": "getLatestReviewID",
        "version": 6,
        "params": {
            "deck": "default"
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": 1594194095746,
        "error": null
    }
    
    ```
    

##### [#](https://git.sr.ht/~foosoft/anki-connect#codeinsertreviewscode)`insertReviews`

-   将给定的复习记录插入数据库。所需格式：9 元组 `(复习时间, 卡片 ID, usn, 按下的按钮, 新区间, 前一个区间, 新因子, 复习持续时间, 复习类型)` 列表。
    
    _示例请求：_
    
    ```
    {
        "action": "insertReviews",
        "version": 6,
        "params": {
            "reviews": [
                [1594194095746, 1485369733217, -1, 3,   4, -60, 2500, 6157, 0],
                [1594201393292, 1485369902086, -1, 1, -60, -60,    0, 4846, 0]
            ]
        }
    }
    
    ```
    _示例结果：_
    
    ```
    {
        "result": null,
        "error": null
    }
    
    ```

