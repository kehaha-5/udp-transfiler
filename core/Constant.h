#ifndef CONSTANT_H
#define CONSTANT_H

#include <cmath>
#include <string>
const int MAX_MSG_LENGTH = 1400;                                   // mtu affect udp 单个包最大大小
const int IP_V4_LEN = 16;                                          // ipv4 字符串长度
const int MAX_FILE_DATA_SIZE = 1300;                               //单个包中文件最大大小
const std::string INTERRUPTION_FILE_SUFFIX = ".udptranfiler.dat";  //文件中断下载后缀名
const std::string DOWNLOAD_ING_FILE_SUFFIX = ".downloading.dat";   //文件下载中保存的文件名
const int SEND_PACKAGE_TIMEOUT = 1000;                             // udp 单个包超时时间 ms
const int MAX_DOWNLOAD_SPPED = 1024 * 1024 * 5;                   //每秒最大下载速度 单位B
const int MAX_SEND_PACKETS =
    (std::ceil(MAX_DOWNLOAD_SPPED / MAX_FILE_DATA_SIZE) == 0
         ? 1
         : std::ceil(MAX_DOWNLOAD_SPPED /
                     MAX_FILE_DATA_SIZE));  //在下载时最多每秒发送多少个包
                                            // MAX_SEND_PACKETS_NUM_PEER_SECONDE*MAX_FILE_DATA_SIZE等于大概下载速度 还要考虑下载线程数量 MAX_ACK_SET_SIZE数量
const int MAX_ACK_SET_SIZE =
    1000;  //可以处理最大的重发次数，在重发次数上升时，线程池的线程主要都去处理重发数据，导致没有人处理接受数据，导致更多的数据超时重发，当重发次数大于此数时，无法再发送新包
#endif