#ifndef UTILITIES_H
#define UTILITIES_H

#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

namespace utils{

    unordered_map<string, string> settingsParser(const string &filename);

    bool verifySettings(const unordered_map<string, string>& settings);

}



#endif // UTILITIES_H
