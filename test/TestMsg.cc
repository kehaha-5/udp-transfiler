
#include <gtest/gtest.h>
#include <sys/types.h>

#include "Logging.h"
#include "log/Log.h"
#include "msg/Buffer.h"
#include "msg/Msg.h"
#include "msg/proto/command_msg.pb.h"
#include "msg/proto/package_msg.pb.h"
#include "transfiler/AckRandom.h"

class TestMsg : public testing::Test {
   protected:
    void SetUp() {
        logConfig logconf = {logLever::debug, logAppender::console};
        Log::setConfig(logconf);
    }

   public:
    int getRandomNumber(int lower, int upper) { return rand() % (upper - lower + 1) + lower; }
    void getLetterTableByBytesNum(u_int loop, std::string& data) {
        char letter = 'a';
        for (int i = 0; i < loop; i++) {
            data += letter;
            if (letter == 'z') {
                letter = 'a';
            } else {
                if (getRandomNumber(1, 2) == 1) {
                    letter++;
                }
            }
        }
    }
    void vailBufferToMsgData(msg::Command& orginMsg, msg::Buffer& buffer) {
        msg::Command buffToMsg;
        std::string errMsg;
        EXPECT_TRUE(buffToMsg.build(buffer.getData(), errMsg));
        if (!errMsg.empty()) {
            info_log("build error is %s ", errMsg.c_str());
        }
        ASSERT_EQ(buffToMsg.command, orginMsg.command);
        ASSERT_STREQ(buffToMsg.msg.c_str(), orginMsg.msg.c_str());
    }
};

TEST_F(TestMsg, subcontractTset) {
    int tatolFor = 20;
    for (int i = 1; i <= tatolFor; i++) {
        std::string data;
        getLetterTableByBytesNum(msg::PALYLOAD_LEN * i, data);
        auto ack = transfiler::AckRandom::getAck();
        auto msg = msg::getsubcontractInfo(data, ack, msg::proto::Command);
        ASSERT_EQ(msg.size(), i);
        for (int j = 0; j < msg.size(); j++) {
            ASSERT_EQ(msg[j].ack, ack);
            ASSERT_EQ(msg[j].order, j);

            debug_log("i is %i ,  j is %i , j*msg::PALYLOAD_LEN is %i", i, j, j * msg::PALYLOAD_LEN);
            debug_log("string size() - pos is %i ", data.size() - (j * msg::PALYLOAD_LEN));

            EXPECT_STREQ(msg[j].data.c_str(), data.substr((j * msg::PALYLOAD_LEN), msg::PALYLOAD_LEN).c_str());
        }
    }
}

TEST_F(TestMsg, bufferSimpleTest) {
    msg::Command msg = {};
    msg.command = msg::proto::COMMAND_ERRORMSG;
    getLetterTableByBytesNum(msg::PALYLOAD_LEN, msg.msg);
    std::string out;
    msg.serialized(&out);
    auto ack = transfiler::AckRandom::getAck();
    auto resMsg = msg::getsubcontractInfo(out, ack, msg::proto::Command);
    msg::Buffer buff;
    for (auto& it : resMsg) {
        buff.setData(it);
    }
    ASSERT_EQ(ack, buff.getAck());
    ASSERT_TRUE(buff.hasAllData());
    vailBufferToMsgData(msg, buff);
}

TEST_F(TestMsg, bufferTest) {
    int packNum = 2;
    msg::Command msg = {};
    msg.command = msg::proto::COMMAND_ERRORMSG;
    getLetterTableByBytesNum(msg::PALYLOAD_LEN * packNum, msg.msg);
    std::string out;
    msg.serialized(&out);
    auto ack = transfiler::AckRandom::getAck();
    auto resMsg = msg::getsubcontractInfo(out, ack, msg::proto::Command);
    ASSERT_EQ(resMsg.size(), packNum + 1);
    msg::Buffer buff;
    for (int i = 0; i < packNum; i++) {
        buff.setData(resMsg.at(i));
        ASSERT_FALSE(buff.hasAllData());
    }
    buff.setData(resMsg.at(packNum));
    ASSERT_TRUE(buff.hasAllData());
    vailBufferToMsgData(msg, buff);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}