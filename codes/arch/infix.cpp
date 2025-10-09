#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

ll qpow(ll base, ll q) {
    if (q == 0) return 1;  // 明确处理 q=0 的情况
    ll ans = 1;
    while(q) {
        if(q & 1) ans *= base;
        base *= base;
        q >>= 1;
    }
    return ans;
}

ll cal(ll a, ll b, char ch) {
    switch(ch) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) {
                cerr << "Error: division by zero" << endl;
                exit(1);
            }
            return a / b;
        case '^': return qpow(a, b);
    }
    return 0;
}

// 获取操作符优先级
int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    cin >> s;
    s += '#';  // 添加结束标记

    stack<ll> nb;
    stack<char> ch;
    
    for(int i = 0; i < s.size() - 1; ++i) {
        // ============== 修复1：处理负数 ==============
        if (s[i] == '-' && (i == 0 || s[i-1] == '(' || 
                            s[i-1] == '+' || s[i-1] == '-' || 
                            s[i-1] == '*' || s[i-1] == '/' || s[i-1] == '^')) {
            i++;  // 跳过 '-'
            ll tp = 0;
            while (i < s.size() && isdigit(s[i])) {
                tp = tp * 10 + s[i] - '0';
                i++;
            }
            i--;  // 抵消for循环的i++
            nb.push(-tp);
            continue;
        }
        // =====================================
        
        if(isdigit(s[i])) {
            ll tp = 0;
            while(i < s.size() && isdigit(s[i])) {
                tp = tp * 10 + s[i] - '0';
                i++;
            }
            i--;
            nb.push(tp);
        }
        else {
            if(s[i] == '(') {
                ch.push(s[i]);
            }
            else if(s[i] == ')') {
                // ============== 修复2：栈空检查 ==============
                while(!ch.empty() && ch.top() != '(') {
                    if (nb.size() < 2) {
                        cerr << "Error: insufficient operands before )" << endl;
                        return 1;
                    }
                    // =====================================
                    
                    ll b = nb.top(); nb.pop();
                    ll a = nb.top(); nb.pop();
                    ll tp = cal(a, b, ch.top());
                    ch.pop();
                    nb.push(tp);
                }
                if(!ch.empty() && ch.top() == '(') ch.pop();
                else {
                    cerr << "Error: mismatched parentheses" << endl;
                    return 1;
                }
            }
            else {
                // ============== 修复3：统一优先级处理 ==============
                while(!ch.empty() && ch.top() != '(' && 
                      precedence(ch.top()) >= precedence(s[i])) {
                    // ============== 修复4：栈空检查 ==============
                    if (nb.size() < 2) {
                        cerr << "Error: insufficient operands for operator " << s[i] << endl;
                        return 1;
                    }
                    // =====================================
                    
                    ll b = nb.top(); nb.pop();
                    ll a = nb.top(); nb.pop();
                    ll tp = cal(a, b, ch.top());
                    ch.pop();
                    nb.push(tp);
                }
                ch.push(s[i]);
                // =====================================
            }
        }
    }

    // ============== 修复5：处理剩余操作符 ==============
    while(!ch.empty()) {
        // ============== 修复6：栈空检查 ==============
        if (nb.size() < 2) {
            cerr << "Error: insufficient operands at end" << endl;
            return 1;
        }
        // =====================================
        
        ll b = nb.top(); nb.pop();
        ll a = nb.top(); nb.pop();
        ll tp = cal(a, b, ch.top());
        ch.pop();
        nb.push(tp);
    }
    // =====================================
    
    // ============== 修复7：最终结果检查 ==============
    if (nb.size() != 1) {
        cerr << "Error: invalid expression" << endl;
        return 1;
    }
    // =====================================
    
    cout << nb.top();

    return 0;
}
