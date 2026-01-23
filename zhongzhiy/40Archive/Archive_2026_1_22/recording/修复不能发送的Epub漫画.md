# 1.将epub书拆为图片
使用python脚本把文件夹里的书拆解为一个个图片文件夹
好的喵！以下是一个 **Python 脚本**，它会自动处理一个目录下的所有 `.epub` 文件：

---

## ✅ 脚本功能

- 遍历某个文件夹，找到所有 `.epub` 文件
    
- 解压每本 `.epub` 为临时目录
    
- 提取其中 `image/` 目录的图片（自动适配路径）
    
- 每本书的图片输出到独立的子文件夹，按书名命名
    
- 支持中文路径，无损提取 PNG/JPG 图像
    

---

## 🐍 脚本代码（Python 3）

```python
import os
import zipfile
import shutil

# 设置路径：这是存放 .epub 的文件夹
epub_dir = "你的/epub/目录"
output_dir = "你的/输出目录"

# 遍历 epub 文件
for filename in os.listdir(epub_dir):
    if filename.endswith(".epub"):
        book_name = os.path.splitext(filename)[0]
        epub_path = os.path.join(epub_dir, filename)

        # 解压到临时目录
        temp_dir = os.path.join(epub_dir, "__temp__")
        if os.path.exists(temp_dir):
            shutil.rmtree(temp_dir)
        os.makedirs(temp_dir)

        with zipfile.ZipFile(epub_path, 'r') as zip_ref:
            zip_ref.extractall(temp_dir)

        # 寻找图片目录（通常是 item/image 或 OEBPS/image）
        image_dir = None
        for root, dirs, files in os.walk(temp_dir):
            if 'image' in root.lower():
                image_dir = root
                break

        if not image_dir:
            print(f"[!] 未找到图像文件夹：{filename}")
            continue

        # 输出目录
        book_output_dir = os.path.join(output_dir, book_name)
        os.makedirs(book_output_dir, exist_ok=True)

        # 拷贝图像文件
        for img_file in os.listdir(image_dir):
            if img_file.lower().endswith(('.png', '.jpg', '.jpeg')):
                src = os.path.join(image_dir, img_file)
                dst = os.path.join(book_output_dir, img_file)
                shutil.copy2(src, dst)

        print(f"[✓] 处理完成：{book_name}")

# 清理
shutil.rmtree(temp_dir, ignore_errors=True)
```

---

## 📌 使用说明

1. 替换脚本中的：
    
    ```python
    epub_dir = "你的/epub/目录"
    output_dir = "你的/输出目录"
    ```
    
    路径可以用 `r"C:\路径"` 或 `/home/user/路径`
    
2. 确保系统已安装 Python（推荐 3.7+）
    
3. 然后运行这个脚本即可。
    

---

## 🐾 补充建议

- 如果你只处理一两本书，也可以改写成逐本处理的 GUI 脚本。
    
- 如果你有 `.cbz` 或 `.zip` 格式漫画，也可以轻松扩展。
    

需要我改成 **一键图形界面工具（.exe）** 或 **支持批量打包成 PDF** 的版本吗？喵～

# 使用gcc生成mobi文件
把含有漫画图片的文件夹的文件夹命名为漫画名字，直接添加进gcc，打开[[gcc设置]]的out split
