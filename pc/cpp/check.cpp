// checker.cpp
#include <iostream>
#include <cstdlib> // 包含 system()

using namespace std;

int main() {
    // 1. 编译其他三个文件 (如果是 Windows，去掉 -o 及后面的部分，或者保留也可以)
    // Linux / macOS 编译命令
    system("g++ gen.cpp -o gen");
    system("g++ main.cpp -o my");
    system("g++ bf.cpp -o bf");

    int test_cases = 10000; // 设置对拍次数
    for (int i = 1; i <= test_cases; ++i) {
        // 2. 运行生成器，将输出重定向到 in.txt
        system("./gen > in.txt");  // Windows 系统请把 ./gen 改成 gen.exe

        // 3. 将 in.txt 喂给暴力程序和待测程序
        system("./bf < in.txt > bf.out"); // Windows: bf.exe < in.txt > bf.out
        system("./my < in.txt > my.out"); // Windows: my.exe < in.txt > my.out

        // 4. 对比输出文件
        // Windows 系统请使用命令: system("fc bf.out my.out > nul")
        // Linux / macOS 请使用命令: system("diff -Z bf.out my.out > /dev/null")
        if (system("diff -Z bf.out my.out > /dev/null")) {
            cout << "❌ Wrong Answer on Test " << i << "!" << endl;
            cout << "Input data saved in in.txt" << endl;
            break; // 发现错误，立刻停止
        }

        cout << "✅ Accepted on Test " << i << endl;
    }
    return 0;
}
