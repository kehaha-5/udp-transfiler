

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
    bool isShowResLog;
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

struct strangeServerConfig {
    std::string ip;
    std::string port;
    std::string filePath;
    std::string threadNum;
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
        _strangeServerConfigFilePath = _currentPath / "strangeServerConfig.ini";
        initConfig();
        createFiles();
    }

    // void TearDown() { std::filesystem::remove_all(_currentPath); }
    void createFiles() {
        std::ofstream serverConfig(_serverFilePath, std::ios_base::out);
        ASSERT_TRUE(serverConfig.good());
        serverConfig << "ip=" << _serverConfig.ip << "\n";
        serverConfig << "port=" << _serverConfig.port << "# 我是注释\n";
        serverConfig << "filePath=" << _serverConfig.filePath << "# 我是注释\n";
        serverConfig << "threadNum=" << _serverConfig.threadNum << "# 我是注释\n";
        serverConfig << "isShowResLog=" << std::boolalpha << _serverConfig.isShowResLog << "# 我是注释\n";
        serverConfig.close();

        std::ofstream clientConfig(_clientFilePath, std::ios_base::out);
        ASSERT_TRUE(clientConfig.good());
        clientConfig << "ip=" << _clientConfig.ip << "\n";
        clientConfig << "port=" << _clientConfig.port << "\n";
        clientConfig << "filePath=" << _clientConfig.filePath << "\n";
        clientConfig << "downloadThreadNum=" << _clientConfig.downloadThreadNum << "\n";
        clientConfig << "maxResendPacketsNum=" << _clientConfig.maxAckSet << "\n";
        clientConfig << "maxDownloadSpeeds=" << _clientConfig.maxDownloadSpeeds << "\n";
        clientConfig << "packetsTimerOut=" << _clientConfig.packetsTimerOut << "\n";
        clientConfig.close();

        std::ofstream badServerFilePath(_badServerFilePath, std::ios_base::out);
        ASSERT_TRUE(badServerFilePath.good());
        badServerFilePath << "ip=" << _serverConfig.ip << "\n";
        badServerFilePath << "port"
                          << "\n";
        badServerFilePath << "filePath=" << _serverConfig.filePath << "\n";
        badServerFilePath << "threadNum"
                          << "threadNum"
                          << "\n";
        badServerFilePath.close();

        std::ofstream strangeServerConfigFilePath(_strangeServerConfigFilePath, std::ios_base::out);
        ASSERT_TRUE(strangeServerConfigFilePath.good());
        strangeServerConfigFilePath << "ip=" << _strangeServerConfig.ip << "\n";
        strangeServerConfigFilePath << "port" << _strangeServerConfig.port << "\n";
        strangeServerConfigFilePath << "filePath=" << _strangeServerConfig.filePath << "\n";
        strangeServerConfigFilePath << "threadNum" << _strangeServerConfig.threadNum << "\n";
        strangeServerConfigFilePath.close();
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
        _serverConfig.isShowResLog = true;

        _strangeServerConfig.ip = "123is not ip format";
        _strangeServerConfig.port = "123";
        _strangeServerConfig.filePath = "";
        _strangeServerConfig.threadNum = "你好";
    }

   public:
    std::filesystem::path _currentPath;
    clientConfig _clientConfig;
    serverConfig _serverConfig;
    strangeServerConfig _strangeServerConfig;
    std::filesystem::path _clientFilePath;
    std::filesystem::path _serverFilePath;
    std::filesystem::path _badServerFilePath;
    std::filesystem::path _strangeServerConfigFilePath;
};

TEST_F(TestConfig, functionalTest) {
    config::ServerConfig::getInstance().setConfigFile(_serverFilePath);
    ASSERT_STREQ(config::ServerConfig::getInstance().getFilepath().c_str(), _serverConfig.filePath.c_str());
    ASSERT_STREQ(config::ServerConfig::getInstance().getIp().c_str(), _serverConfig.ip.c_str());
    ASSERT_EQ(config::ServerConfig::getInstance().getPort(), _serverConfig.port);
    ASSERT_EQ(config::ServerConfig::getInstance().getThreadNum(), _serverConfig.threadNum);
    ASSERT_EQ(config::ServerConfig::getInstance().getIsShowResLog(), _serverConfig.isShowResLog);

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
    ASSERT_EQ(config::ServerConfig::getInstance().getThreadNum(), 10);
}

TEST_F(TestConfig, testStrangeConfig) {
    serverConfig defaultConfig = {config::ServerConfig::getInstance().getIp(), config::ServerConfig::getInstance().getPort(),
                                  config::ServerConfig::getInstance().getFilepath(), config::ServerConfig::getInstance().getThreadNum()};
    config::ServerConfig::getInstance().setConfigFile(_strangeServerConfigFilePath);
    ASSERT_STREQ(config::ServerConfig::getInstance().getFilepath().c_str(), defaultConfig.filePath.c_str());
    ASSERT_STREQ(config::ServerConfig::getInstance().getIp().c_str(), defaultConfig.ip.c_str());
    ASSERT_EQ(config::ServerConfig::getInstance().getPort(), defaultConfig.port);
    ASSERT_EQ(config::ServerConfig::getInstance().getThreadNum(), defaultConfig.threadNum);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}