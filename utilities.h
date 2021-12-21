#ifndef UTILITIES_H
#define UTILITIES_H

#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>

namespace utils{

    std::unordered_map<std::string, std::string> settingsParser(const std::string &filename);

    bool verifySettings(const std::unordered_map<std::string, std::string>& settings);

    std::vector<std::string> split(std::string s, std::string delimiter = " ");

    std::string join(const std::vector<std::string> v, const std::string delimiter = " ");
}



#endif // UTILITIES_H
