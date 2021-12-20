#include "utilities.h"


pair<string, string> parseLine(const string& line, const string delimiter=" = ")
{
    auto end = line.find(delimiter);
    string first = line.substr(0, end);
    string second = line.substr(end+size(delimiter), size(line)-end+size(delimiter));
    return pair<string, string> {first, second};
}


std::unordered_map<std::string, std::string> utils::settingsParser(const string& filename)
{
    ifstream file(filename);
    if(!file.is_open()){
        cerr << "Can't open file " << filename << endl;
        // Return empty
        return unordered_map<string, string> {};
    }
    string line;
    unordered_map<string, string> settings;
    while(getline(file, line)){
        auto pair = parseLine(line);
        settings.insert(pair);

    }
    file.close();
    return settings;
}

bool utils::verifySettings(const unordered_map<string, string> &settings)
{
    auto hasSetting = [settings](const string& setting){
        return settings.find(setting) != settings.end();
    };

    return (hasSetting("ip-address") and hasSetting("port"));
}
