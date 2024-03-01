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
4. 利用 one loop per thread 实现服务端核心功能


