#include <iostream>

#include "Logging.h"
int main(int, char **) {
    info_log("this is a test and %s", "test");
    std::cout << "Hello!\n";
}
