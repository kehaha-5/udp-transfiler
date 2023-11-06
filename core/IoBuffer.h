#ifndef IO_BUFFER_H
#define IO_BUFFER_H
#include <memory>
const int MAX_LENGTH = 65507;  // udp单个包最大大小

class MemPool;
typedef std::unique_ptr<MemPool> MemPoolPtr ;

class IoBuufer {
   public:
    IoBuufer();
    ~IoBuufer();

   private:
      MemPoolPtr menPool;      
};
#endif