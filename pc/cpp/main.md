# default

## [Linux] 

转义回车符怎么使用
---
多行命令可以使用`\`转义回车符

类似:
```sh
# 这是一个长命令，用 \ 拆成多行写，可读性极高
sudo docker run -d \
  --name my-web-server \
  -p 80:80 \
  nginx:latest
  ```

  ## [Linux] 

  用单引号/双引号会失去转义
  ---
  单引号


  ## [Linux] 

使用上一次使用的, 以`vim`开头的超长命令
---
`!vim` 就会使用上次以`vim` 开头的命令, 例如: `vim -b file.txt files.txt`

## [Linux]

显式最近使用的 10 条命令
---
`history 10`

## [Linux]

直接使用上一次使用的命令
---
`!!`

## [Linux] 

提取上一次命令的最后一个参数
---
`!$`

## [Linux] 

如果上一个命令输入错误, 例如 `vum file.txt`, 怎么修改使用
---
`^u^i`

## [Linux] 

搜索使用命令
---
`Ctrl-R`

## [Linux] 

创建别名 `ls` 为 `ls -l`, 解除别名
---
```sh
alias ls='ls -l'
unalias ls
```

## [Linux] 

登录 shell 会执行哪些加载命令
---
登录 shell 会依次加载 `/etc/profile -> ~/.bash_profile -> ~/.bashrc -> /etc/bashrc`

其中 `profile`文件是登录的时候加载, 具有继承性, 其中 `PATH`就在其中, 一般 ssh连接或 `su - root`切换的时候加载


## [Linux] 

非登录 shell 会执行哪些加载命令有什么用
---
非登录 shell 会直接加载 `~/.bashrc -> /etc/bashrc`, 

一般在每次打开一个终端会加载一次, 常用来写 `alias` 等非继承的函数


## [Linux] 

把`echo "hello" ` 重定向 覆盖/追加 到 `output.txt` 文件中
---
```sh
echo "hello" > output.txt  # 覆盖
echo "hello" >> output.txt  # 追加
```

## [Linux]

重定向错误输出流到 `output.txt` 中
---
三大标准管道:
1. `0` 是标准输入, 默认接入键盘
2. `1` 是标准输出, 默认接入屏幕
3. `2` 是标准错误
```sh
err 2> output.txt
```
