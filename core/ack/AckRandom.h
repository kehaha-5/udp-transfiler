#ifndef CORE_ACK_ACK_RANDOM_H
#define CORE_ACK_ACK_RANDOM_H

#include <sys/types.h>

#include <mutex>
#include <unordered_set>
namespace ack {
typedef std::unordered_set<u_long> unqiueAck;
class AckRandom {
   public:
    static u_long getAck();
    static int releasesAck(u_long ack);
    static int getAckMapSzie() { return _set.size(); }

   private:
    static bool insertMap(u_long ack);
    static unqiueAck _set;
    static std::mutex _setLock;
};
}  // namespace acksss

#endif