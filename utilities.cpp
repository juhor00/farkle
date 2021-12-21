#include "utilities.h"


std::pair<std::string, std::string> parseLine(const std::string& line, const std::string delimiter=" = ")
{
    auto end = line.find(delimiter);
    std::string first = line.substr(0, end);
    std::string second = line.substr(end+size(delimiter), size(line)-end+size(delimiter));
    return std::pair<std::string, std::string> {first, second};
}


std::unordered_map<std::string, std::string> utils::settingsParser(const std::string& filename)
{
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cerr << "Can't open file " << filename << std::endl;
        // Return empty
        return std::unordered_map<std::string, std::string> {};
    }
    std::string line;
    std::unordered_map<std::string, std::string> settings;
    while(getline(file, line)){
        auto pair = parseLine(line);
        settings.insert(pair);

    }
    file.close();
    return settings;
}

bool utils::verifySettings(const std::unordered_map<std::string, std::string> &settings)
{
    auto hasSetting = [settings](const std::string& setting){
        return settings.find(setting) != settings.end();
    };

    return (hasSetting("ip-address") and hasSetting("port"));
}

std::vector<std::string> utils::split(std::string s, std::string delimiter)
{
    std::vector<std::string> results;
    size_t pos = 0;
    std::string param;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        param = s.substr(0, pos);
        s.erase(0, pos + delimiter.length());
    }
    return results;
}
