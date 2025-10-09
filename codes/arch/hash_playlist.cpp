//hash模板，对应playlist
#include<bits/stdc++.h>
using namespace std;
#define PLEASE_AC return 0
typedef long long ll;

const int MAXN = 2e5 + 100;
const int HASH_SIZE = 4e5 + 100;  // 增大容量，避免冲突
const int M = 199999;

struct HashTable{
    struct Node{
        int next, key, val;
        Node(){next = key = val = 0;}
        Node(int next, int key, int val):next(next), key(key), val(val){}
    }data[HASH_SIZE];

    int head[M];
    int size;

    HashTable() {
        memset(head, 0, sizeof(head));
        size = 0;
    }

    int f(int val){return (val % M + M) % M;}

    int get(int key) {
        for(int p = head[f(key)]; p; p = data[p].next) {
            if(data[p].key == key) {
                return data[p].val;
            }
        }
        return 0;
    }

    void adddata(int idx, int key, int val) {
        data[idx] = {head[f(key)], key, val};
        head[f(key)] = idx;
    }

    void modify(int key, int delta) {
        for(int p = head[f(key)]; p; p = data[p].next) {
            if(data[p].key == key) {
                data[p].val += delta;
                return;
            }
        }
        // 不存在则添加
        if(size < HASH_SIZE - 1) {  // 防止越界
            size++;
            adddata(size, key, delta);
        }
    }
};

int arr[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    HashTable mp;

    int n;
    cin >> n;

    for(int i = 1; i <= n; ++i) {
        cin >> arr[i];
    }

    int l = 1, r = 1, max_ans = 0;
    while(r <= n) {
        mp.modify(arr[r], 1);
        
        while(mp.get(arr[r]) > 1) {
            mp.modify(arr[l], -1);
            l++;
        } 
        
        max_ans = max((long long)(r - l + 1), (long long)max_ans);
        r++;
    }

    cout << max_ans;
    PLEASE_AC;
}
