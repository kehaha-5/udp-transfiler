
#include <gtest/gtest.h>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <thread>
#include <vector>

#include "Logging.h"
#include "config/ServerConfig.h"
#include "file/server/Directory.h"

using namespace file::server;

class TestDir : public testing::Test {
   protected:
    void SetUp() {
        logConfig logconf = {logLever::debug, logAppender::console};
        Log::setConfig(logconf);
        auto currentPath = std::filesystem::current_path();
        std::cout << _currentPath << std::endl;
        currentPath.append(_filePath);
        _currentPath = currentPath;
        std::filesystem::create_directory(_currentPath);
        config::ServerConfig::getInstance().setConfigFilePath(_currentPath);
        Directory::getInstance().setFilePath();
        createFiles();
    }

    void TearDown() { fs::remove_all(_currentPath); }

   public:
    int _threadNum = 100;
    std::string _currentPath;
    std::vector<std::string> _existFileName = {"1.txt", "2.txt", "3.txt", "4.txt", "5.txt"};
    void createFiles() {
        for (auto it : _existFileName) {
            auto currentPath = std::filesystem::current_path();
            auto currFile = currentPath.append(_filePath).append(it);
            std::ofstream file(currFile);
            ASSERT_TRUE(file.is_open());
            file << "hello word file name is " << it.data() << std::endl;
            file.close();
        }
    }
    void multiplyThreadTest(std::function<void()> testFun) {
        try {
            std::vector<std::thread> threads;
            threads.resize(_threadNum);
            for (int i = 0; i < _threadNum; i++) {
                threads[i] = (std::thread(testFun));
            }
            for (int i = 0; i < _threadNum; i++) {
                if (threads[i].joinable()) {
                    threads[i].join();
                }
            }
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
            throw e;
        }
    }

   private:
    std::string _filePath = "TestDir";
};

TEST_F(TestDir, functionalTest) {
    debug_log("curr path is %s", _currentPath.c_str());
    debug_log("dir path is %s", Directory::getInstance().getFullPath().c_str());
    ASSERT_STREQ(_currentPath.c_str(), Directory::getInstance().getFullPath().c_str());
}

TEST_F(TestDir, multiplyThreadTest) {
    auto currPath = _currentPath;
    auto fun = std::bind([currPath]() {
        try {
            debug_log("curr path is %s", currPath.c_str());
            debug_log("dir path is %s", Directory::getInstance().getFullPath().c_str());
            ASSERT_STREQ(Directory::getInstance().getFullPath().c_str(), currPath.c_str());
            debug_log("thread exit~ !!!");
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
            throw e;
        }
    });
    multiplyThreadTest(fun);
}

TEST_F(TestDir, testLs) {
    ASSERT_GT(_existFileName.size(), 0);
    auto lsInfo = Directory::getInstance().ls();
    ASSERT_EQ(lsInfo.size(), _existFileName.size());
    for (auto it : lsInfo) {
        auto res = std::find(_existFileName.begin(), _existFileName.end(), it.name);
        ASSERT_TRUE(res != _existFileName.end());
    }
}

TEST_F(TestDir, multiplyThreadTestLs) {
    auto files = _existFileName;
    auto fun = std::bind([&files]() {
        try {
            ASSERT_GT(files.size(), 0);
            auto lsInfo = Directory::getInstance().ls();
            ASSERT_EQ(lsInfo.size(), files.size());
            for (auto it : lsInfo) {
                auto res = std::find(files.begin(), files.end(), it.name);
                ASSERT_TRUE(res != files.end());
            }
            info_log("thread run finish %lu", std::this_thread::get_id());
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
            throw e;
        }
    });
    multiplyThreadTest(fun);
}

TEST_F(TestDir, getFileInfoTest) {
    filesDownInfo data = {};
    std::string errMsg;
    ASSERT_TRUE(Directory::getInstance().getAllFileDownInfo(data, errMsg));
    ASSERT_EQ(data.size(), _existFileName.size());
    for (auto& it : data) {
        debug_log("file name is  %s  and hash is %s", it.name.c_str(), it.hash.c_str());
        auto findRes = std::find(_existFileName.begin(), _existFileName.end(), it.name);
        EXPECT_TRUE(findRes != _existFileName.end());
    }

    data = {};
    errMsg.clear();
    ASSERT_TRUE(Directory::getInstance().getSpecialFileDownInfo(data, _existFileName[1], errMsg));
    ASSERT_STREQ(data[0].name.c_str(), _existFileName[1].c_str());

    data = {};
    errMsg.clear();
    ASSERT_FALSE(Directory::getInstance().getSpecialFileDownInfo(data, "test.bin", errMsg));

    data = {};
    // TODO symlink file
    //  ASSERT_FALSE(file.getSpecialFileDownInfo(data, "testLink"));
    //  ASSERT_EQ(file.getErrMsg().code, errCode::fileTypeNotSupported);
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}