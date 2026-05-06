---
tags:
  - java
---
Maven使用`pom.xml`定义项目内容，并使用预设的目录结构
一个maven项目使用`groupId`, `artifactId`和`version`作为唯一**标识符**

通过[search.maven.org](https://search.maven.org/)搜索关键字，找到对应的组件
maven定义了四种依赖关系, 用在依赖的`scoop`中: compile, test, runtime, provided

maven的生命周期由一系列phase构成, 运行命令`mvn clean`就是运行`default`生命周期知道指定的phase

模块间通过`pom.xml`来拆分和组合
