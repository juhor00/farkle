#ifndef UTILITIES_H
#define UTILITIES_H

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

namespace utils{

    std::unordered_map<std::string, std::string> settingsParser(const std::string &filename);

    bool verifySettings(const std::unordered_map<std::string, std::string>& settings);

    std::vector<std::string> split(std::string s, std::string delimiter = " ");

    std::string join(const std::vector<std::string> v, const std::string delimiter = " ");
    std::string join(const std::unordered_set<std::string> s, const std::string delimiter = " ");

    std::unordered_set<int> toInt(const std::unordered_set<std::string>& s);
    std::unordered_map<int, int> toInt(const std::unordered_map<std::string, std::string>& s);
    int toInt(const std::string& s);

    std::unordered_set<std::string> toString(const std::unordered_set<int>& i);
    std::unordered_map<std::string, std::string> toString(const std::unordered_map<int, int>& i);
    std::string toString(const int& i);
}



#endif // UTILITIES_H
