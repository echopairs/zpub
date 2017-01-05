### zpub
The pub/sub network framework base on  zeromq and protobuf
### Introduction
```
  zpub
  |- bin/               项目构建生成的二进制输出目录（排除在版本控制库之外）
  |- build/             项目构建的工作目录 （排除在版本控制库之外）
  |- include/           发布需要的头文件目录
  |- release/           使用发布脚本发布的二进制文件保存目录 （排除在版本控制库之外）
  |- src/               项目源代码目录
  |   |- common/		模块公用文件
  |   |- pub/           pub模块(发送消息)
  |   |- sub/           sub模块(订阅处理消息模块)
  |   |- zpbs			*.proto文件目录
  |- tools/             构建/发布/测试等相关脚本
```
### Requirements
依赖
#### Tools
  cmake >= 3.2 
#### Dependent libs
 zeromq
 protobuf
### Build


