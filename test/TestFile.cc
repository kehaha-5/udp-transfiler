
#include <gtest/gtest.h>

#include <filesystem>
#include <thread>
#include <vector>

#include "Logging.h"
#include "file/Directory.h"

using namespace file;

class TestFile : public testing::Test {
   protected:
    void SetUp() {
        logConfig logconf = {logLever::debug, logAppender::console};
        Log::setConfig(logconf);
        _currentPath = std::filesystem::current_path();
        std::cout << _currentPath << std::endl;
        _currentPath += _filePath;
        std::filesystem::create_directory(_currentPath);
        file::Directory::getInstance().setFilePath(_currentPath);
        
    }

    void TearDown() { fs::remove(_currentPath); }

   public:
    int _threadNum = 30;
    std::string _currentPath;

   private:
    std::string _filePath = "/testFile";
};

TEST_F(TestFile, functionalTest) {
    debug_log("curr path is %s", _currentPath.c_str());
    debug_log("dir path is %s", Directory::getInstance().getFullPath().c_str());
    ASSERT_STREQ(_currentPath.c_str(), Directory::getInstance().getFullPath().c_str());
}

TEST_F(TestFile, multiplyThreadTest) {
    try {
        std::vector<std::thread> threads;
        threads.resize(_threadNum);
        auto currPath = _currentPath;
        for (int i = 0; i < _threadNum; i++) {
            threads[i] = (std::thread(std::bind([currPath]() {
                try {
                    debug_log("curr path is %s", currPath.c_str());
                    debug_log("dir path is %s", Directory::getInstance().getFullPath().c_str());
                    ASSERT_STREQ(Directory::getInstance().getFullPath().c_str(), currPath.c_str());
                    debug_log("thread exit~ !!!");
                } catch (std::exception& e) {
                    std::cout << e.what() << std::endl;
                    throw e;
                }
            })));
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

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}