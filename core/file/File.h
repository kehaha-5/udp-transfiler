#ifndef FIEL_FILE_H
#define FIEL_FILE_H

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

namespace file {
class File {
   public:
    File(std::string path);

   private:
    fs::path _filepathObj;
};
}  // namespace file

#endif