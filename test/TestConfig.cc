

#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <ios>
#include <string>

#include "config/ClientConfig.h"
#include "config/ServerConfig.h"

struct serverConfig {
    std::string ip;
    u_short port;
    std::string filePath;
    u_short threadNum;
};

struct clientConfig {
    std::string ip;
    u_short port;
    std::string filePath;
    u_short downloadThreadNum;
    u_short packetsTimerOut;
    uint maxDownloadSpeeds;
    uint maxAckSet;
};

class TestConfig : public testing::Test {
   protected:
    void SetUp() {
        auto _currentPath = std::filesystem::current_path();
        _currentPath.append("testConfig");
        std::filesystem::create_directory(_currentPath);
        _clientFilePath = _currentPath / "clientConfig.ini";
        _serverFilePath = _currentPath / "serverConfig.ini";
        _badServerFilePath = _currentPath / "badServerConfig.ini";
        initConfig();
        createFiles();
    }

    void TearDown() { std::filesystem::remove_all(_currentPath); }
    void createFiles() {
        std::ofstream serverConfig(_serverFilePath, std::ios_base::out);
        ASSERT_TRUE(serverConfig.good());
        serverConfig << "ip=" << _serverConfig.ip << "\n";
        serverConfig << "port=" << _serverConfig.port << "\n";
        serverConfig << "filePath=" << _serverConfig.filePath << "\n";
        serverConfig << "threadNum=" << _serverConfig.threadNum << "\n";
        serverConfig.close();

        std::ofstream clientConfig(_clientFilePath, std::ios_base::out);
        ASSERT_TRUE(clientConfig.good());
        clientConfig << "ip=" << _clientConfig.ip << "\n";
        clientConfig << "port=" << _clientConfig.port << "\n";
        clientConfig << "filePath=" << _clientConfig.filePath << "\n";
        clientConfig << "downloadThreadNum=" << _clientConfig.downloadThreadNum << "\n";
        clientConfig << "maxAckSet=" << _clientConfig.maxAckSet << "\n";
        clientConfig << "maxDownloadSpeeds=" << _clientConfig.maxDownloadSpeeds << "\n";
        clientConfig << "packetsTimerOut=" << _clientConfig.packetsTimerOut << "\n";
        clientConfig.close();

        std::ofstream badServerFilePath(_badServerFilePath, std::ios_base::out);
        ASSERT_TRUE(serverConfig.good());
        badServerFilePath << "ip=" << _serverConfig.ip << "\n";
        badServerFilePath << "port="
                          << "port"
                          << "\n";
        badServerFilePath << "filePath=" << _serverConfig.filePath << "\n";
        badServerFilePath << "threadNum="
                          << "threadNum"
                          << "\n";
        badServerFilePath.close();
    }
    void initConfig() {
        _clientConfig.downloadThreadNum = 10;
        _clientConfig.filePath = "./client_download";
        _clientConfig.ip = "127.0.0.1";
        _clientConfig.port = 23111;
        _clientConfig.maxAckSet = 100;
        _clientConfig.maxDownloadSpeeds = 1024 * 1024 * 1024;
        _clientConfig.packetsTimerOut = 500;

        _serverConfig.ip = "127.0.0.1";
        _serverConfig.port = 23111;
        _serverConfig.filePath = "./server_upload";
        _serverConfig.threadNum = 5;
    }

   public:
    std::filesystem::path _currentPath;
    clientConfig _clientConfig;
    serverConfig _serverConfig;
    serverConfig _badServerConfig;
    std::filesystem::path _clientFilePath;
    std::filesystem::path _serverFilePath;
    std::filesystem::path _badServerFilePath;
};

TEST_F(TestConfig, functionalTest) {
    config::ServerConfig::getInstance().setConfigFile(_serverFilePath);
    ASSERT_STREQ(config::ServerConfig::getInstance().getFilepath().c_str(), _serverConfig.filePath.c_str());
    ASSERT_STREQ(config::ServerConfig::getInstance().getIp().c_str(), _serverConfig.ip.c_str());
    ASSERT_EQ(config::ServerConfig::getInstance().getPort(), _serverConfig.port);
    ASSERT_EQ(config::ServerConfig::getInstance().getThreadNum(), _serverConfig.threadNum);

    config::ClientConfig::getInstance().setConfigFile(_clientFilePath);
    ASSERT_STREQ(config::ClientConfig::getInstance().getFilepath().c_str(), _clientConfig.filePath.c_str());
    ASSERT_STREQ(config::ClientConfig::getInstance().getIp().c_str(), _clientConfig.ip.c_str());
    ASSERT_EQ(config::ClientConfig::getInstance().getPort(), _clientConfig.port);
    ASSERT_EQ(config::ClientConfig::getInstance().getDownloadThreadNum(), _clientConfig.downloadThreadNum);
    ASSERT_EQ(config::ClientConfig::getInstance().getMaxDownloadSpeeds(), _clientConfig.maxDownloadSpeeds);
    ASSERT_EQ(config::ClientConfig::getInstance().getPacketsTimerOut(), _clientConfig.packetsTimerOut);
    ASSERT_EQ(config::ClientConfig::getInstance().getMaxAckSet(), _clientConfig.maxAckSet);
}

TEST_F(TestConfig, getIntErrorTest) {
    config::ServerConfig::getInstance().setConfigFile(_badServerFilePath);
    ASSERT_STREQ(config::ServerConfig::getInstance().getFilepath().c_str(), _serverConfig.filePath.c_str());
    ASSERT_STREQ(config::ServerConfig::getInstance().getIp().c_str(), _serverConfig.ip.c_str());
    ASSERT_EQ(config::ServerConfig::getInstance().getPort(), 23111);
    ASSERT_EQ(config::ServerConfig::getInstance().getThreadNum(), 5);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}