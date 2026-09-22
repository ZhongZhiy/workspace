#import "@preview/codly:1.3.0": *
#import "@preview/codly-languages:0.1.1": *
#show: codly-init.with()
#set page(paper: "a4", margin: 2cm)
#set text(
  size: 8pt
)

= 对拍板子(windows)
== 随机数生成器
```cpp

#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

// 随机数生成器
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// 生成 [l, r] 范围内的随机整数
long long rnd(long long l, long long r) {
    if (l > r) swap(l, r);
    return uniform_int_distribution<long long>(l, r)(rng);
}

int main() {
    // 比赛常忘了写这一行，导致多组数据读入错位！
    int t = 1;
    cout << t << "\n"; // 输出组数 T。如果你的程序不需要读入 T，请把它删掉

    while (t--) {
        int n = rnd(1, 100); // 随机生成数组长度 N
        cout << n << "\n";

        // 输出长度为 N 的随机数组
        for(int i = 0; i < n; i++) {
            long long val = rnd(1, 100000);
            cout << val << (i == n - 1 ? "" : " ");
        }
        cout << "\n";
    }

    return 0; // 一定要 return 0，否则系统认为你的 gen 崩溃了
}
```

== check函数

```cpp
#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
    cout << "正在编译中 (Windows环境)..." << endl;

    // Windows 下生成 .exe 可执行文件
    if (system("g++ gen.cpp -o gen.exe -O2") != 0 ||
        system("g++ my.cpp -o my.exe -O2") != 0 ||
        system("g++ bf.cpp -o bf.exe -O2") != 0) {
        cout << "❌ 编译失败！请检查源文件。" << endl;
        return 1;
    }
    cout << "✅ 编译成功，开始对拍！\n" << endl;

    int max_tests = 100000;
    for (int i = 1; i <= max_tests; ++i) {
        // 直接运行 .exe，不要加 ./
        system("gen.exe > in.txt");

        // 获取程序返回值，非 0 说明程序发生了越界、除零死机等运行时错误 (RTE)
        int status_bf = system("bf.exe < in.txt > bf.out");
        int status_my = system("my.exe < in.txt > my.out");

        if (status_my != 0) {
            cout << "\n❌ 你的待测程序 (my.exe) 发生运行时崩溃 (RE/越界/段错误)!" << endl;
            return 1;
        }
        if (status_bf != 0) {
            cout << "\n❌ 你的暴力程序 (bf.exe) 发生运行时崩溃 (RE/越界/段错误)!" << endl;
            return 1;
        }

        // 使用 Windows 独有的 fc 命令比对文件，/W 表示忽略由于回车或多余空格造成的差异
        // > nul 用于隐藏 fc 本身冗长的对比输出
        if (system("fc /W bf.out my.out > nul")) {
            cout << "\n\n❌ Wrong Answer on Test " << i << "!" << endl;

            cout << "----------------------------------------" << endl;
            cout << "【输入数据 in.txt】:" << endl;
            system("type in.txt"); // Windows 的打印文件内容命令是 type
            cout << "----------------------------------------" << endl;
            cout << "【正确输出 bf.out】:" << endl;
            system("type bf.out");
            cout << "----------------------------------------" << endl;
            cout << "【你的输出 my.out】:" << endl;
            system("type my.out");
            cout << "----------------------------------------" << endl;
            return 0; // 发现错误，立刻停止
        }
        // \r 控制光标回到行首，实现不刷屏的动态刷新
        cout << "\r✅ Accepted on Test " << i << " / " << max_tests << flush;
    }

    cout << "\n🎉 对拍结束，未发现问题！" << endl;
    return 0;
}
```
