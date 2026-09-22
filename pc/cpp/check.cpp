#include <iostream>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {
    cout << "正在编译中..." << endl;
    // 开启 O2 优化，提升暴力程序的运行速度
    if (system("g++ gen.cpp -o gen -O2") != 0 ||
        system("g++ toc.cpp -o my -O2") != 0 ||
        system("g++ main.cpp -o bf -O2") != 0) {
        cout << "❌ 编译失败！请检查源文件。" << endl;
        return 1;
    }
    cout << "✅ 编译成功，开始对拍！\n" << endl;

    int max_tests = 100000;
    for (int i = 1; i <= max_tests; ++i) {
        system("./gen > in.txt");

        // 可选：你甚至可以加入 time 或者利用 chrono 判断程序是否 TLE (超时)
        system("./bf < in.txt > bf.out");
        system("./my < in.txt > my.out");

        // if(i == 50){
        //     cout << "----------------------------------------" << endl;
        //     cout << i << "----------------------------------------" << endl;
        //     cout << "【输入数据 in.txt (由于太长可能只展示前20行)】:" << endl;
        //     system("cat in.txt");
        //     cout << "----------------------------------------" << endl;

        //     cout << "bf.out" << endl;
        //     system("cat bf.out");
        //     cout << "----------------------------------------" << endl;
        //     cout << "my.out" << endl;
        //     system("cat my.out");

        //     cout << "----------------------------------------" << endl;
        // }

        if (system("diff -Z bf.out my.out > /dev/null")) {
            cout << "\n\n❌ Wrong Answer on Test " << i << "!" << endl;

            cout << "----------------------------------------" << endl;
            cout << "【输入数据 in.txt (由于太长可能只展示前20行)】:" << endl;
            system("head -n 20 in.txt");
            cout << "----------------------------------------" << endl;
            cout << "【正确输出 bf.out】:" << endl;
            system("cat bf.out");
            cout << "----------------------------------------" << endl;
            cout << "【你的输出 my.out】:" << endl;
            system("cat my.out");
            cout << "----------------------------------------" << endl;
            // return 0; // 发现错误，立刻停止
        }
        cout << "\r✅ Accepted on Test " << i << " / " << max_tests << flush;
    }
    cout << "\n🎉 对拍结束，未发现问题！" << endl;
    return 0;
}
