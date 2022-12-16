#include "path.h"
#include <cstdarg>
#include <iostream>
#include <fstream>

using namespace std;

std::string Path::join(int args_count, ...)
{
    filesystem::path path;
    std::va_list list; 
    va_start(list, args_count);
    for (int i = 0; i < args_count; ++i)
    {
		path /= va_arg(list, const char*);
    }
    va_end(list);

    return path.string();
}

std::string Path::join(const std::vector<std::string>& element)
{
    filesystem::path path;
    for (const std::string& e : element)
    {
        path /= e;
    }

    return path.string();
}

bool Path::exists(const std::string& path)
{
    return filesystem::exists(path);
}

std::vector<std::string> Path::listdir(const std::string& path)
{
    std::vector<std::string> result;
	for (const auto & entry : filesystem::directory_iterator(path)) {
		std::string hehe = entry.path().string();
		result.push_back({ hehe.begin() + path.size() + 1, hehe.end() });
	}
    return result;
}


bool Path::isFile(const std::string& path) 
{
    std::error_code ec;
    return filesystem::is_regular_file(filesystem::path(path), ec);
}
