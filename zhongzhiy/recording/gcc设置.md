下面我来逐项解释这个界面的各功能，并给出一个针对漫画／固定图像型 EPUB（你已提取成图片文件夹后）的推荐配置流程——让你一键生成最适合 Kindle 阅读的 MOBI/AZW3 文件。

---

## 一、主界面按钮

- **Add directory**：添加一个包含所有页面图片的文件夹（推荐用，自动按文件名顺序导入）
    
- **Add file**：添加单个文件（通常是 PDF/CBZ）
    
- **Clear list**：清除当前已添加的所有输入
    
- **Convert**：开始转换，你可以从下拉菜单里选转换成 **MOBI + EPUB**（双格式）或只要 MOBI／AZW3
    

---

## 二、目标设备选择

在界面上部，“Kindle Scribe” 下拉框里可以选你要适配的设备型号：

- **Kindle Scribe**（最新版）
    
- **Kindle Paperwhite／Oasis** 等旧机型
    

**→ 选对应你实际用的设备**，程序会自动优化页面大小和格式。

---

## 三、Metadata Editor

点这会弹出对话框，让你填写书名、作者、出版信息等，**会写入到最后生成文件的元数据**，方便在 Kindle 书架里显示。

---

## 四、模式与排版选项

|选项|含义及推荐设置|
|---|---|
|**Manga mode**|针对“右翻”日漫自动左右翻页；**中文/英文漫画可不启用**|
|**Spread splitter**|如果图片里是一张跨页大图，就把它拆成左右两页；**若所有页面都是单页**可关|
|**Panel View 4/2/HQ**|自动识别“分镜”并逐格查看；一般普通漫画不必要|
|**Webtoon mode**|纵向长条模式（Webtoon）；一般固定页不需要|
|**Stretch/Upscale**|对小图放大；若图片已是原尺寸，关掉以免失真|
|**Custom gamma**／**Gamma: Auto**|调整亮度曲线；默认 Auto 即可|
|**W/B margins**|自动加黑白边距；漫画通常不需要|
|**Cropping mode**|裁剪空白边（Auto/Manual/None），建议保持 **Auto**|
|**Cropping Power**|裁剪强度，默认 **1.00**|
|**Spread shift**|拆分跨页时微调上下偏移；通常不动|
|**1x4 to 2x2 strips**|Webtoon 的 1×4 分条改 2×2；固定页无需|
|**Color mode**|彩色／灰度转换；保留 **Color**|
|**JPEG/PNG/mozJpeg**|输出编码方式；**PNG 保无损**，JPEG 可选更小但有损|
|**Output split**|结果中是否再打包分卷；一般关|
|**Delete input**|转换成功后删除源文件夹；不推荐自动删|
|**Disable processing** / **No rotate**|跳过所有处理／禁止自动旋转；仅在故障排查时用|

---

## 四、一步到位的“最简”推荐配置

1. **Add directory** → 选你提取好图片的那个根文件夹
    
2. 设备选 **Kindle Scribe**（或你实际机型）
    
3. Metadata Editor 填上“书名”＋“作者”
    
4. 模式（Modes）一栏全部**关闭**：Manga mode / Spread splitter / Panel View / Webtoon mode / Stretch/Upscale
    
5. 保持 **Gamma: Auto**，Cropping mode 选 **Auto**，Cropping Power = **1.00**
    
6. Color mode 选 **Color**，输出格式选 **PNG**（若想更小可选 JPEG）
    
7. **不要**勾 “Delete input” / “Disable processing” / “No rotate”
    
8. 最后点击右上角 **Convert → MOBI + EPUB**
    

这样你会得到一个最适合 Kindle 的双格式文件：MOBI 给老 Kindle，EPUB 给新版 Kindle App/Scribe。如果你只需要 MOBI，也可以从下拉里单选。

---

### 五、转换完成后

- 直接用 USB 拷贝到 Kindle 的 `Documents` 文件夹
    
- 或者用「Send to Kindle」工具／邮箱投送
    

这样就能**无损、整页、逐页**地在 Kindle 上看漫画啦～