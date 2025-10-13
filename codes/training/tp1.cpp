#include <iostream>
#include <cstring>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Node {
    double arg; 
    int fat;    
    int l, r;   
} node[1000];

int head = -1;
int idx = 0;

void insertNode(double a, int f) {
    node[idx].arg = a;
    node[idx].fat = f;
    node[idx].l = node[idx].r = -1;
    if (head == -1) {
        head = idx;
    } else {
        int p = head;
        while (node[p].r != -1) p = node[p].r;
        node[p].r = idx;
        node[idx].l = p;
    }
    idx++;
}

void sortNode() {
    for (int i = 0; i < idx - 1; ++i) {
        for (int j = i + 1; j < idx; ++j) {
            if (node[i].fat < node[j].fat) {
                swap(node[i], node[j]);
            }
        }
    }
}

int main() {
    char s[1000];
    cin.getline(s, 1000);

    char *p = strtok(s, " ");
    while (p) {
        double a;
        int f;
        sscanf(p, "%lf,%d", &a, &f);
        if (a == 0 && f == 0) break;
        insertNode(a, f);
        p = strtok(nullptr, " ");
    }

    if (idx == 0) {
        cout << "f(X)=0.0";
        return 0;
    }

    sortNode();

    cout << "f(X)=";
    bool first = true, allZero = true;
    for (int i = 0; i < idx; ++i) {
        double c = node[i].arg;
        int e = node[i].fat;
        if (c == 0) continue;
        allZero = false;
        if (!first && c > 0) cout << "+";

        if (e == 0)
            cout << fixed << setprecision(1) << c;
        else if (e == 1) {
            if (c == 1) cout << "X";
            else if (c == -1) cout << "-X";
            else cout << fixed << setprecision(1) << c << "X";
        } else {
            if (c == 1) cout << "X^" << e;
            else if (c == -1) cout << "-X^" << e;
            else cout << fixed << setprecision(1) << c << "X^" << e;
        }
        first = false;
    }
    if (allZero) cout << "0.0";
    cout << endl;
    return 0;
}
