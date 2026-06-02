import os
from pathlib import Path


def batch_merge_markdowns(input_folder="all_markdowns", batch_size=20):
    # 1. 初始化路径
    input_path = Path(input_folder)

    if not input_path.exists():
        print(f"错误：找不到文件夹 '{input_folder}'")
        return

    # 2. 获取所有 .md 文件并排序
    md_files = sorted(list(input_path.glob("*.md")))
    total_files = len(md_files)

    if total_files == 0:
        print("文件夹内没有找到 .md 文件。")
        return

    print(f"找到 {total_files} 个文件，准备每 {batch_size} 个合并为一个文件...")

    # 3. 分批次处理
    for i in range(0, total_files, batch_size):
        # 获取当前批次的文件列表
        batch = md_files[i : i + batch_size]
        batch_num = (i // batch_size) + 1
        output_filename = f"merged_part_{batch_num}.md"

        print(f"正在生成: {output_filename} (包含 {len(batch)} 个文件)")

        with open(output_filename, "w", encoding="utf-8") as outfile:
            for file_path in batch:
                with open(file_path, "r", encoding="utf-8") as infile:
                    content = infile.read()

                    # 写入来源标记（可选）
                    outfile.write(f"\n\n\n")

                    # 写入正文
                    outfile.write(content)

                    # 确保文件之间有换行，防止格式错乱
                    if not content.endswith("\n"):
                        outfile.write("\n")

                    # 可以在每个文件结尾加个分割线
                    outfile.write("\n---\n")

    print("-" * 30)
    print(
        f"全部完成！共生成了 {(total_files + batch_size - 1) // batch_size} 个合并文件。"
    )

    print(f"全部完成！共生成了 { (total_files + batch_size - 1) // batch_size } 个合并文件。")

if __name__ == "__main__":
    # 你可以修改 batch_size 来调整每个合并包的文件数量
    batch_merge_markdowns(input_folder="all_markdowns", batch_size=20)
