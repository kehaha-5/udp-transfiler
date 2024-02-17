#ifndef CONSTANT_H
#define CONSTANT_H

#include <string>
const int MAX_MSG_LENGTH = 1400;                                   // mtu affect udp 单个包最大大小
const int IP_V4_LEN = 16;                                          // ipv4 字符串长度
const int MAX_FILE_DATA_SIZE = 1300;                               //单个包中文件最大大小
const std::string INTERRUPTION_FILE_SUFFIX = ".udptranfiler.dat";  //文件中断下载后缀名
const int SEND_PACKAGE_TIMEOUT = 999;                               // udp 单个包超时时间 ms

#endif