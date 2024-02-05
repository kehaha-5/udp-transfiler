
#include <gtest/gtest.h>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <thread>
#include <vector>

#include "Logging.h"
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
        Directory::getInstance().setFilePath(_currentPath);
        createFiles();
    }

    void TearDown() { fs::remove_all(_currentPath); }

   public:
    int _threadNum = 100;
    std::string _currentPath;
    std::vector<std::string> _files = {};
    void createFiles() {
        std::vector<std::string> files = {"1.txt", "2.txt", "3.txt", "4.txt", "5.txt"};
        for (auto it : files) {
            auto currentPath = std::filesystem::current_path();
            auto currFile = currentPath.append(_filePath).append(it);
            std::ofstream file(currFile);
            if (file.is_open()) {
                file << "hello word file name is " << it.data() << std::endl;
                file.close();
                _files.push_back(it.data());
            }
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
    ASSERT_GT(_files.size(), 0);
    auto lsInfo = Directory::getInstance().ls();
    ASSERT_EQ(lsInfo.size(), _files.size());
    for (auto it : lsInfo) {
        auto res = std::find(_files.begin(), _files.end(), it.name);
        ASSERT_TRUE(res != _files.end());
    }
}

TEST_F(TestDir, multiplyThreadTestLs) {
    auto files = _files;
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

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}