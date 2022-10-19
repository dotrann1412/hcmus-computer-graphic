#ifndef _PATH_H_
#define _PATH_H_

#include <string>
#include <filesystem>
#include <vector>

class Path
{
public:
    static std::string join(int, ...);
    static std::string join(const std::vector<std::string>&);
    static bool exists(const std::string& path);
    static std::vector<std::string> listdir(const std::string&);
    static bool isFile(const std::string& path);
};

#endif