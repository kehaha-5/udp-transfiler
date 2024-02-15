#include <gtest/gtest.h>
#include <sys/types.h>

#include <filesystem>
#include <fstream>

#include "config/ClientConfig.h"
#include "file/client/File.h"

namespace fs = std::filesystem;

class TestClientFile : public ::testing::Test {
   protected:
    void SetUp() {
        config::ClientConfig::getInstance().setConfigFilePath(fs::current_path().append("testClient"));
        _currfile = config::ClientConfig::getInstance().getFilepath();
    }

    void getLetterTableByBytesNum(u_int loop, std::string& data) {
        char letter = 'a';
        for (int i = 0; i < loop; i++) {
            data += letter;
            if (letter == 'z') {
                letter = 'a';
            }
            letter++;
        }
    }

    u_long getFileSzie(std::string& name) {
        auto currFile = config::ClientConfig::getInstance().getFilepath() / name;
        return fs::file_size(currFile);
    }

    std::string getFileContext(std::string name, int pos, int size) {
        std::ifstream file(_currfile.append(name));
        file.seekg(pos);
        std::string data(size, 0);
        file.read(&data[0], size);
        return data;
    }

    void TearDown() { fs::remove_all(_currfile); }

   public:
    fs::path _currfile;
};

TEST_F(TestClientFile, functionalTest) {
    std::string fileName = "test.bin";
    file::client::File file(_currfile / fileName, 2048);
    file.init();
    std::string data;
    getLetterTableByBytesNum(1024, data);
    file.write(1024, data, 1024);
    ASSERT_EQ(getFileSzie(fileName), 2048);
    ASSERT_STREQ(data.c_str(), getFileContext(fileName, 1024, 1024).c_str());
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}