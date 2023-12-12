#ifndef MSG_COMMAND_H
#define MSG_COMMAND_H
#include <string>
#include <utility>
#include <vector>

#include "file/Directory.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
namespace msg {

struct lsMsg {
    std::string command = "ls";
    file::filesInfo files = {};
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
            writer.Key("size");
            writer.Double(it.second);
            writer.Key("name");
            writer.String(it.first.c_str());
            writer.EndObject();
        }
        writer.EndArray();
        writer.EndObject();
        return str.GetString();
    };
};

struct errMsg {
    errMsg(std::string _msg) : msg(_msg){};
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

}  // namespace msg

#endif