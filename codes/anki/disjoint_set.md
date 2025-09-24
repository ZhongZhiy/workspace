# 算法

## 并查集的find()

<!-- notecardId: 1757756948228 -->


```
cpp
int find(int p){
	if(p != fa[p])
		fa[p] = find(fa[p]);
	return fa[p];
}
```

## 并查集的init()

<!-- notecardId: 1757757328604 -->
```cpp
void init() {
for(int i = 1;i <= n; ++i)
	fa[i] = i;
}
```

## 并查集的merge()

<!-- notecardId: 1757757328610 -->
```cpp
void merge(int x, int y){
	//sz[y]] += sz[x];  //把x的权值加在y上, 注意顺序
	fa(find(x)) = find(y);  //让x的祖先等于y
}
```

