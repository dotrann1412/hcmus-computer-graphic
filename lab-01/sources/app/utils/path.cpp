#include "path.h"
#include <cstdarg>
#include <iostream>

std::string Path::join(int args_count, ...)
{
    std::filesystem::path path;
    std::va_list list; 
    va_start(list, args_count);
    for (int i = 0; i < args_count; ++i)
    {
		path /= va_arg(list, std::string);
    }
    va_end(list);

    return path.string();
}

std::string Path::join(const std::vector<std::string>& element)
{
    std::filesystem::path path;
    for (const std::string& e : element)
    {
        path /= e;
    }

    return path.string();
}

bool Path::exists(const std::string& path)
{
    return std::filesystem::exists(path);
}

std::vector<std::string> Path::listdir(const std::string& path)
{
    std::vector<std::string> result;
	for (const auto & entry : std::filesystem::directory_iterator(path)) {
		std::string hehe = entry.path().string();
		result.push_back({ hehe.begin() + path.size() + 1, hehe.end() });
	}
    return result;
}


bool Path::isFile(const std::string& path) 
{
    std::error_code ec;
    return std::filesystem::is_regular_file(std::filesystem::path(path), ec);
}
