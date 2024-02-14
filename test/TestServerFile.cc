#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <system_error>
#include <thread>

#include "Logging.h"
#include "file/server/File.h"

using namespace file::server;

class TestServerFile : public ::testing::Test {
   protected:
    void SetUp() {
        logConfig logconf = {logLever::debug, logAppender::console};
        Log::setConfig(logconf);
        _currentPath = std::filesystem::current_path();
        _currentPath.append("testFile");
        std::error_code ec;
        std::filesystem::create_directory(_currentPath, ec);
        ASSERT_FALSE(ec);
        // 在测试之前执行的设置
        // 在这里生成测试文件（文本和二进制文件）
        generateTextTestFile();
        generateBinaryTestFile();
        generateNotSupportFile();
    }

    void TearDown() { std::filesystem::remove_all(_currentPath); }

    void generateTextTestFile() {
        _textFile = _currentPath / "test.txt";
        std::ofstream file(_textFile);
        ASSERT_TRUE(file.is_open());

        for (char letter = 'a'; letter <= 'z'; ++letter) {
            _textFileContext += letter;
        }
        file.write(&_textFileContext[0], _textFileContext.size());
        file.close();
    }

    void generateBinaryTestFile() {
        // 生成二进制测试文件的代码
        _binFile = _currentPath / "test.bin";
        std::ofstream file(_binFile, std::ios::binary);
        ASSERT_TRUE(file.is_open());

        // 写入一些测试数据
        for (char letter = 'a'; letter <= 'z'; ++letter) {
            _binFileContext += letter;
        }
        file.write(&_binFileContext[0], _binFileContext.size());
        file.close();
    }

    void generateNotSupportFile() {
        _linkFile = _currentPath / "test.link.test";
        _linkFile2 = _currentPath / "testLink";
        std::ofstream linkFile(_linkFile);
        std::error_code ec;
        std::filesystem::create_symlink(_linkFile, _linkFile2, ec);
        if (ec) {
            debug_log("create_symlink code %i,msg %s", ec.value(), ec.message().c_str());
            ASSERT_TRUE(ec);
        }
        ASSERT_TRUE(std::filesystem::equivalent(_linkFile, _linkFile2));
        ASSERT_TRUE(std::filesystem::is_symlink(_linkFile2));
    }

   public:
    fs::path _currentPath;
    fs::path _textFile;
    std::string _textFileContext;
    fs::path _binFile;
    std::string _binFileContext;
    fs::path _linkFile;
    fs::path _linkFile2;
    int fileSize = 4;  //_textFile _binFile _linkFile _linkFile2
    int _threadNum = 30;
};

TEST_F(TestServerFile, functionalTestFile) {
    File file(_textFile);
    ASSERT_FALSE(file.hasError());

    File fileNotExist("not_exist_file.txt");
    ASSERT_TRUE(fileNotExist.hasError());
    auto notExitErrMsg = fileNotExist.getErrMsg();
    ASSERT_TRUE(notExitErrMsg.code == errCode::fileNotExist);

    // TODO symlink file
    //  File fileNotSupported(_linkFile2);
    //  ASSERT_TRUE(fileNotSupported.hasError());
    //  auto notSupportedMsg = fileNotSupported.getErrMsg();
    //  ASSERT_TRUE(notSupportedMsg.code == errCode::fileTypeNotSupported);
}


TEST_F(TestServerFile, ReadTextFile) {
    File file(_textFile);
    fileData testData;

    ASSERT_TRUE(file.getPosContext(0, 20, testData));
    EXPECT_EQ(testData.realSize, 20);  // 这里根据实际文件内容的长度进行修改
    EXPECT_STREQ(testData.data.c_str(), _textFileContext.substr(0, 20).c_str());

    // 测试文件读取到最后
    ASSERT_TRUE(file.getPosContext(0, 30, testData));
    EXPECT_EQ(testData.realSize, _textFileContext.size());
    EXPECT_STREQ(testData.data.c_str(), _textFileContext.c_str());

    // 测试文件 pos 位置大于文件可读位置
    ASSERT_FALSE(file.getPosContext(100, 1000, testData));
    ASSERT_TRUE(file.hasError());
    ASSERT_TRUE(file.getErrMsg().code == errCode::fileSzieOut);
}

TEST_F(TestServerFile, ReadBinaryFile) {
    // 测试二进制文件正常读取
    File file(_binFile);  // 请根据你的文件类构造函数进行修改
    fileData testData;

    ASSERT_TRUE(file.getPosContext(0, 20, testData));
    EXPECT_EQ(testData.realSize, 20);  // 这里根据实际文件内容的长度进行修改
    EXPECT_EQ(std::memcmp(testData.data.data(), _binFileContext.substr(0, 20).data(), 20), 0);

    // 测试文件读取到最后
    ASSERT_TRUE(file.getPosContext(0, 30, testData));
    EXPECT_EQ(testData.realSize, _binFileContext.size());
    EXPECT_EQ(memcmp(testData.data.data(), _binFileContext.data(), _binFileContext.size()), 0);

    // 测试文件 pos 位置大于文件可读位置
    ASSERT_FALSE(file.getPosContext(100, 1000, testData));
    ASSERT_TRUE(file.getErrMsg().code == errCode::fileSzieOut);
}

TEST_F(TestServerFile, RandomReadBinaryFile) {
    // 测试二进制文件正常读取
    File file(_binFile);  // 请根据你的文件类构造函数进行修改
    for (int i = 0; i < 26; i++) {
        for (int j = (i == 0) ? 1 : i; j < 26; j++) {
            fileData testData;
            auto res = file.getPosContext(i, j, testData);
            EXPECT_TRUE(res);
            if (!res) {
                debug_log("i is %i j is %i err is %s", i, j, file.getErrMsg().errMsg.c_str());
            }
            debug_log("i is %i j is %i ", i, j);
            ASSERT_STREQ(testData.data.c_str(), _binFileContext.substr(i, j).c_str());
        }
    }
}

TEST_F(TestServerFile, multiplyThreadReadTest) {
    std::vector<std::thread> threads;
    int _threadNum = 30;
    threads.resize(_threadNum);
    for (int i = 0; i < _threadNum; i++) {
        threads[i] = std::thread(std::bind([this]() {
            File file(_binFile);
            for (int i = 0; i < 26; i++) {
                for (int j = (i == 0) ? 1 : i; j < 26; j++) {
                    fileData testData;
                    auto res = file.getPosContext(i, j, testData);
                    EXPECT_TRUE(res);
                    if (!res) {
                        debug_log("i is %i j is %i err is %s", i, j, file.getErrMsg().errMsg.c_str());
                    }
                    debug_log("i is %i j is %i ", i, j);
                    ASSERT_STREQ(testData.data.c_str(), _binFileContext.substr(i, j).c_str());
                }
            }
        }));
    }
    for (int i = 0; i < _threadNum; i++) {
        threads[i].join();
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
