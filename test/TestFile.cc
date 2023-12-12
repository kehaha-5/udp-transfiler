
#include <thread>
#include <vector>

#include "Logging.h"
#include "file/Directory.h"
#include "log/Log.h"

using namespace file;

const int threadNum = 10;

void getDir() { Directory* dir = Directory::getInstance(); }

int main(int, char**) {
    Directory* dir = Directory::getInstance("./testFile");
    std::vector<std::thread> threads;
    threads.resize(threadNum);
    for (int i = 0; i < threadNum; i++) {
        threads[i] = std::thread(*getDir);
    }
    for (int i = 0; i < threadNum; i++) {
        threads[i].join();
    }
}
