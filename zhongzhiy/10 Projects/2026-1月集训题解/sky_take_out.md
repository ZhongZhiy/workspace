第一次使用 maven compile 失败, 是因为JDK版本太高了, 换成 17 的就可以了

compile 后运行不能和前端页面成功连接, 报错 `2026-06-15 20:22:22.037 ERROR 18652 --- [reate-885876140] com.alibaba.druid.pool.DruidDataSource   : create connection SQLException, url: jdbc:mysql://localhost:3306/sky_take_out?serverTimezone=Asia/Shanghai&useUnicode=true&characterEncoding=utf-8&zeroDateTimeBehavior=convertToNull&useSSL=false&allowPublicKeyRetrieval=true, errorCode 1045, state 28000`

是因为数据库的原因, 在`application-dev.yml`文件写的数据库用户密码和我本地的mysql用户密码不一致