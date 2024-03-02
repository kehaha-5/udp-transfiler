# udp-transfiler

## 功能
1. 查看指定目录中的文件信息
2. 下载指定文件夹中的文件 
    - size小于0将不会被下载
    - 只能下载 `regular_file` 类型的文件 
        - [what is regular_file](https://en.cppreference.com/w/cpp/filesystem#:~:text=regular%20file%3A%20a%20directory%20entry%20that%20associates%20a%20name%20with%20an%20existing%20file%20(i.e.%20a%20hard%20link).%20If%20multiple%20hard%20links%20are%20supported%2C%20the%20file%20is%20removed%20after%20the%20last%20hard%20link%20to%20it%20is%20removed.)

## 特点
1. 基于UDP协议进行数据传输并针对本项目实现了可靠性传输
2. 使用 [protobuf](https://protobuf.dev/) 作为序列化协议
3. 使用 [gtest](https://google.github.io/googletest/) 来对主要功能进行单元测试
    - 消息分包和重组
    - 定时器
    - 文件目录访问和文件读写
    - 消息唯一标识生成
    - 配置文件读取
4. 利用 one loop per thread 实现服务端核心功能
    - eventloop + threadPool

## 配置说明
- 配置分为服务端和客户端 
    - 服务端默认采用当前目录下的 `server_config.ini`
    - 客户端默认采用当前目录下的 `client_config.ini`
    - 可以使用 `--config` 命令来指定配置文件
    - 若无指定或配置不可用则采用默认配置

    ### 服务端

    ```ini
    ip=0.0.0.0 #默认监听ip
    port=23111 #默认端口
    filePath=./upload #默认可以访问的文件目录
    threadNum=15 #默认工作线程数量
    ```

    ### 客户端
    ```ini
   ip=127.0.0.1 #默认连接ip
   port=23111 #默认端口
   filePath=./downloadfile #默认下载目录
   downloadThreadNum=1 #下载线程
   maxResendPacketsNum=500 #下载时最多同时可以重发的包数量
   maxDownloadSpeeds=1073741824 #最大下载速度 单位B
   packetsTimerOut=1000 #包超时重发时间 单位ms
    ```

    ### 配置优化

    - 客户端配置中的 `maxResendPacketsNum` 配置作用，即在重发次数到此数量时，无法再发送新包
        - 因为重发包的作业和接收处理数据包的作业都是在同一个线程池中的，若重发包的作业有很多了，就会导致没有线程可以马上去处理接收数据的作业，而导致不断地触发超时重发
        - 这个配置若配置太小了，也会对下载速度有一定影响
        - 同时也可以通过这个配置去适配服务端的性能


