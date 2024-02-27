#ifndef CONSTANT_H
#define CONSTANT_H

#include <string>

const int MAX_MSG_LENGTH = 1400;                                                            // mtu affect udp 单个包最大大小
const int IP_V4_LEN = 16;                                                                   // ipv4 字符串长度
const int MAX_FILE_DATA_SIZE = 1300;                                                        //单个包中文件最大大小
const int LARGE_FILE_SIZE = 1024 * 1024 * 500;                                              //大文件读取使用mmap读取 单位B
const std::string INTERRUPTION_FILE_SUFFIX = ".udptranfiler.dat";                           //文件中断下载后缀名
const std::string DOWNLOAD_ING_FILE_SUFFIX = ".downloading.dat";                            //文件下载中保存的文件名
const int SEND_THREAD_WAIT_FOR_ACK_SET_MS = 50;  //当ack到达最大重发次数后进行等待，最好不要用锁，防止因为服务端错误一直无法解锁
#endif