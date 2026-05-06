# 算法
## 字典树的空间怎么开设? 

<!-- notecardId: 1767853954303 -->
节点最长个数, 每个需要开设26个子节点(数字就只有10个), 标记数组
```cpp
int node[N][26];
bool isEnd[N];
```

## 字典树的插入操作

<!-- notecardId: 1767853954317 -->
遍历这字符串的每个字符, 如果当前树上没有对应节点, 就开辟一个并且分配一个编号idx, 最后标记当前字符为单词末尾
```cpp
void insert(const string &s) {  //插入单词
    int p = 0;
    for(int i = 0; i < s.size(); ++i) {  //遍历单词的每个字符
        int ch = s[i] - 'a';
        if(!node[p][ch]) node[p][ch] = ++idx;   //如果当前节点没有这个字符，就新建一个节点
        p = node[p][ch];  //更新当前节点
    }
    isEnd[p] = true;  //标记单词结束
}
```
