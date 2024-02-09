

#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <ios>
#include <string>

#include "config/ClientConfig.h"
#include "config/ServerConfig.h"

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
        clientConfig << "downloadthreadNum=" << _clientConfig.downloadthreadNum << "\n";
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
        _clientConfig.downloadthreadNum = 10;
        _clientConfig.filePath = "./client_download";
        _clientConfig.ip = "127.0.0.1";
        _clientConfig.port = 23111;

        _serverConfig.ip = "127.0.0.1";
        _serverConfig.port = 23111;
        _serverConfig.filePath = "./server_upload";
        _serverConfig.threadNum = 5;
    }

   public:
    std::filesystem::path _currentPath;
    config::clientConfig _clientConfig;
    config::serverConfig _serverConfig;
    config::serverConfig _badServerConfig;
    std::filesystem::path _clientFilePath;
    std::filesystem::path _serverFilePath;
    std::filesystem::path _badServerFilePath;
};

TEST_F(TestConfig, functionalTest) {
    config::ServerConfig::getInstance().setConfigFile(_serverFilePath);
    auto serConf = config::ServerConfig::getInstance().getConfig();
    ASSERT_STREQ(serConf.filePath.c_str(), _serverConfig.filePath.c_str());
    ASSERT_STREQ(serConf.ip.c_str(), _serverConfig.ip.c_str());
    ASSERT_EQ(serConf.port, _serverConfig.port);
    ASSERT_EQ(serConf.threadNum, _serverConfig.threadNum);

    config::ClientConfig::getInstance().setConfigFile(_clientFilePath);
    auto clientConf = config::ClientConfig::getInstance().getConfig();
    ASSERT_STREQ(clientConf.filePath.c_str(), _clientConfig.filePath.c_str());
    ASSERT_STREQ(clientConf.ip.c_str(), _clientConfig.ip.c_str());
    ASSERT_EQ(clientConf.port, _clientConfig.port);
    ASSERT_EQ(clientConf.downloadthreadNum, _clientConfig.downloadthreadNum);
}

TEST_F(TestConfig, defualtValueTest) {
    auto serConf = config::ServerConfig::getInstance().getConfig();
    ASSERT_STREQ(serConf.filePath.c_str(), "./upload");
    ASSERT_STREQ(serConf.ip.c_str(), "0.0.0.0");
    ASSERT_EQ(serConf.port, 23111);
    ASSERT_EQ(serConf.threadNum, 5);

    auto clientConf = config::ClientConfig::getInstance().getConfig();
    ASSERT_STREQ(clientConf.filePath.c_str(), "./upload");
    ASSERT_STREQ(clientConf.ip.c_str(), "127.0.0.1");
    ASSERT_EQ(clientConf.port, 23111);
    ASSERT_EQ(clientConf.downloadthreadNum, 5);
}

TEST_F(TestConfig, getIntErrorTest) {
    config::ServerConfig::getInstance().setConfigFile(_serverFilePath);
    auto serConf = config::ServerConfig::getInstance().getConfig();
    ASSERT_STREQ(serConf.filePath.c_str(), _serverConfig.filePath.c_str());
    ASSERT_STREQ(serConf.ip.c_str(), _serverConfig.ip.c_str());
    ASSERT_EQ(serConf.port, 23111);
    ASSERT_EQ(serConf.threadNum, 5);
}