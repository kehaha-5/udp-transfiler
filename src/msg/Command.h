#ifndef MSG_COMMAND_H
#define MSG_COMMAND_H
#include <rapidjson/document.h>
#include <sys/types.h>

#include <string>

#include "file/Directory.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
namespace msg {

struct lsMsg {
    lsMsg() { command = "ls"; };
    ~lsMsg() { files.clear(); }
    std::string command;
    file::filesInfo files = {};
    u_long ack;
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
        writer.Key("ack");
        writer.Uint64(ack);
        writer.EndObject();
        writer.Flush();
        return str.GetString();
    };

    lsMsg static getStruct(rapidjson::Document& _jsonMsg) {
        lsMsg msg;
        msg.ack = _jsonMsg["ack"].GetUint64();
        msg.command = _jsonMsg["command"].GetString();
        msg.files = {};
        for (auto& m : _jsonMsg["files"].GetArray()) {
            file::fileInfo file = {};
            if (m.HasMember("last_write_time")) {
                file.last_write_time = m["last_write_time"].GetString();
            }
            if (m.HasMember("size")) {
                file.size = m["size"].GetString();
            }
            if (m.HasMember("name")) {
                file.name = m["name"].GetString();
            }
            msg.files.push_back(file);
        }
        return msg;
    };
};

struct errMsg {
    errMsg(std::string _msg, u_long _ack = 0) : msg(_msg), ack(_ack){};
    std::string command = "error";
    std::string msg;
    u_long ack = 0;
    std::string jsonStr() {
        rapidjson::StringBuffer str;
        rapidjson::Writer<rapidjson::StringBuffer> writer(str);
        writer.StartObject();
        writer.Key("err");
        writer.String(msg.c_str());
        if (ack != 0) {
            writer.Key("ack");
            writer.Uint64(ack);
        }
        writer.EndObject();
        return str.GetString();
    };
};

}  // namespace msg

#endif