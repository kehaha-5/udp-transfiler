
#include <gtest/gtest.h>
#include <sys/types.h>

#include "Logging.h"
#include "log/Log.h"
#include "msg/Msg.h"
#include "transfiler/AckRandom.h"

class TestMsg : public testing::Test {
   protected:
    void SetUp() {
        logConfig logconf = {logLever::debug, logAppender::console};
        Log::setConfig(logconf);
    }

   public:
    int getRandomNumber(int lower, int upper) { return rand() % (upper - lower + 1) + lower; }
    void getLetterTableByBytesNum(u_int loop, std::string &data) {
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
};

TEST_F(TestMsg, subcontractTset) {
    int tatolFor = 20;
    for (int i = 1; i <= tatolFor; i++) {
        std::string data;
        getLetterTableByBytesNum(msg::PALYLOAD_LEN * i, data);
        auto ack = transfiler::AckRandom::getAck();
        auto msg = msg::getsubcontractInfo(data, ack);
        ASSERT_EQ(msg.size(), i);
        for (int j = 0; j < msg.size(); j++) {
            ASSERT_EQ(msg[j].ack, ack);
            ASSERT_EQ(msg[j].order, j);

            debug_log("i is %i ,  j is %i , j*msg::PALYLOAD_LEN is %i", i, j, j * msg::PALYLOAD_LEN);
            debug_log("string size() - pos is %i ", data.size() - (j * msg::PALYLOAD_LEN));

            EXPECT_STREQ(msg[j].data, data.substr((j * msg::PALYLOAD_LEN), msg::PALYLOAD_LEN).c_str());
        }
    }
}
