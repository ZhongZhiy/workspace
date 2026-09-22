## Web and HTTP
Web页: 由一些对象组成

URL格式: 协议名://用户:口令@主机名:端口号/路径名:端口

HTTP: 使用TCP, 无状态, 
  - 持久HTTP
    - 流水线: 发送多个请求, 服务器按顺序响应
    - 非流水线
  - 非持久HTTP
    - 响应时间模型: 2 个 RTT(往返时间round-trip-time) + 对象传输时间

#### HTTP 请求报文
请求: ASCII码
请求行: 方法(GET, POST, PUT, DELETE) URL HTTP/1.1

#### HTTP 响应状态码: 
1. 200 ok
2. 301 moved permanently
3. 400 bad request
4. 404 not found
5. 505 HTTP version not supported


### 用户-服务器状态 cookie


### Web 缓存(代理服务器)
- 缓存既是服务器又是客户端, 也可以是中间节点
- 通常由ISP 提供(企业或大学)

好处: 
- 对用户: 减少响应时间, 减少网络流量
- 对服务器: 减少负载, 减少网络流量
- 对网络: 减少网络流量


#### 条件 GET 方法
在头部添加 If-Modified-Since 或 If-None-Match 字段

