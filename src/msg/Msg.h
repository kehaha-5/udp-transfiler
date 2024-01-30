#ifndef MSG_COMMAND_H
#define MSG_COMMAND_H
#include <rapidjson/document.h>
#include <sys/types.h>

#include <cmath>
#include <cstring>
#include <string>
#include <vector>

#include "Constant.h"
#include "file/server/Directory.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
namespace msg {

const u_int EXTENT_INFO_LEN = sizeof(u_long) + (sizeof(u_int) * 3);
const u_int JSON_MARK_LEN = 20;  // 数据用json表示时，json字符串的标志位
const u_int PALYLOAD_LEN = MAX_MSG_LENGTH - EXTENT_INFO_LEN - JSON_MARK_LEN;

struct Msg {
    u_long ack;          // 标识唯一一个信息 信息可能会被分成很多包
    u_int order;         // 此包在信息中的位置 0,1,2,3,4,5
    u_int tatolPackges;  // 分包数量
    u_int tatolSzie;     // 整个信息的总长度
    char* data;          // json数据
    ~Msg() { delete[] data; }
};

struct lsMsg {
    lsMsg() { command = "ls"; };
    ~lsMsg() { files.clear(); }
    std::string command;
    file::server::filesInfo files = {};
    std::string jsonStr() {
        rapidjson::StringBuffer str;
        rapidjson::Writer<rapidjson::StringBuffer> writer(str);
        writer.StartObject();
        writer.Key("command");
        writer.String(command.c_str());
        writer.Key("files");
        writer.StartArray();
        for (auto it : files) {
            writer.StartObject();
            writer.Key("last_write_time");
            writer.String(it.last_write_time.c_str());
            writer.Key("name");
            writer.String(it.name.c_str());
            writer.Key("size");
            writer.String(it.size.c_str());
            writer.EndObject();
        }
        writer.EndArray();
        writer.EndObject();
        writer.Flush();
        return str.GetString();
    };

    void buildStruct(rapidjson::Document& _jsonMsg) {
        command = _jsonMsg["command"].GetString();
        files = {};
        for (auto& m : _jsonMsg["files"].GetArray()) {
            file::server::fileInfo file = {};
            if (m.HasMember("last_write_time")) {
                file.last_write_time = m["last_write_time"].GetString();
            }
            if (m.HasMember("size")) {
                file.size = m["size"].GetString();
            }
            if (m.HasMember("name")) {
                file.name = m["name"].GetString();
            }
            files.push_back(file);
        }
    };
};

struct errMsg {
    errMsg(std::string _msg, u_long _ack = 0) : msg(_msg){};
    std::string command = "error";
    std::string msg;
    std::string jsonStr() {
        rapidjson::StringBuffer str;
        rapidjson::Writer<rapidjson::StringBuffer> writer(str);
        writer.StartObject();
        writer.Key("err");
        writer.String(msg.c_str());
        writer.EndObject();
        return str.GetString();
    };
};

inline std::vector<Msg> getsubcontractInfo(std::string& jsonStr, u_long ack) {
    char data[jsonStr.size()];
    double tatolSzie = jsonStr.size();
    double tatolPackges = std::ceil(tatolSzie / PALYLOAD_LEN);
    std::vector<Msg> msgs;
    msgs.resize(tatolPackges);
    int startPos = 0;
    u_short order = 0;
    for (auto& it : msgs) {
        it.data = new char[PALYLOAD_LEN + 1];
        std::memset(it.data, '\0', PALYLOAD_LEN + 1);
        it.tatolPackges = tatolPackges;
        it.tatolSzie = tatolSzie;
        if ((PALYLOAD_LEN + startPos) <= tatolSzie) {
            std::strncpy(it.data, jsonStr.c_str() + startPos, PALYLOAD_LEN);
        } else {
            std::strncpy(it.data, jsonStr.c_str() + startPos, tatolSzie - startPos);
        }
        it.ack = ack;
        it.order = order;
        order++;
        startPos += PALYLOAD_LEN;
    }
    return msgs;
}
}  // namespace msg

#endif