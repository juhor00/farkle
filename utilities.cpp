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
        results.push_back(param);
        s.erase(0, pos + delimiter.length());
    }
    results.push_back(s.substr(0, size(s)));
    return results;
}

std::string utils::join(const std::vector<std::string> v, const std::string delimiter)
{
    std::string result = "";
    for(std::vector<std::string>::size_type i=0;i<size(v); i++){
        std::string param = v.at(i);
        result += param;
        if(i != size(v)-1){
            result += " ";
        }
    }
    return result;
}

std::string utils::join(const std::unordered_set<std::string> s, const std::string delimiter)
{
    std::vector<std::string> r(s.size());
    std::copy(s.begin(), s.end(), r.begin());
    return join(r, delimiter);
}
