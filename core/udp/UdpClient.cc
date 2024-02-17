#include <arpa/inet.h>
#include <fcntl.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cassert>
#include <string>

#include "Constant.h"
#include "Logging.h"
#include "UdpClient.h"

using namespace udp;

UdpClient::UdpClient(evenPtr even, std::string &host, __uint16_t port) {
    _socketfd = socket(AF_INET, SOCK_DGRAM | SOCK_CLOEXEC, IPPROTO_UDP);
    exit_if(_socketfd == -1, "create socket error");

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    int ret = inet_aton(host.c_str(), &servaddr.sin_addr);
    exit_if(ret == 0, "client host format %s ", host.c_str());
    servaddr.sin_port = htons(port);
    int res = connect(_socketfd, (const struct sockaddr *)&servaddr, sizeof servaddr);
    exit_if(res == -1, "connect error ip %s port %d", host.c_str(), port);

    _serveraddr = servaddr;

    debug_log("connect ip %s port %d", host.c_str(), port);

    setNonBlocking();
}

void UdpClient::sendMsg(std::string &msg) {
    int res = sendto(_socketfd, msg.c_str(), msg.size(), 0, (const struct sockaddr *)&_serveraddr, sizeof(_serveraddr));
    exit_if(res == -1, "sendMsg");
}

std::string UdpClient::rev() {
    std::string data(MAX_MSG_LENGTH, '\0');
    struct sockaddr_in serveraddr = {};
    socklen_t serverLen = sizeof(serveraddr);
    long res = recvfrom(_socketfd, &data[0], MAX_MSG_LENGTH, 0, (struct sockaddr *)&serveraddr, &serverLen);
    if (res == -1) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return std::string();
        }
        exit_log("recvfrom");
    }
    if (res == 0) {
        return std::string();
    }
    assert(res <= MAX_MSG_LENGTH);
    data.resize(res);
    return data;
}

void UdpClient::setNonBlocking() {
    int flags = fcntl(_socketfd, F_GETFL);
    exit_if(flags == -1, "set non-blocking F_GETFL");

    int res = fcntl(_socketfd, F_SETFL, flags | O_NONBLOCK);
    exit_if(res == -1, "set non-blocking F_GETFL");
}
