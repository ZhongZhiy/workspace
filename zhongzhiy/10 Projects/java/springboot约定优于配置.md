---
tags:
  - java
---

标注目录结构:
```plantext
src/main/java/com/example/demo/
├── DemoApplication.java (主启动类)
│
├── controller/   (控制层：放 Controller)
├── service/      (业务逻辑层：接口 + 实现类)
├── repository/   (持久层/数据访问层：放 Mapper 或 DAO)
├── entity/       (实体层：放 POJO/数据库映射类)
├── dto/          (数据传输对象：给前端传数据用的)
└── config/       (配置层：放自定义配置类)
```