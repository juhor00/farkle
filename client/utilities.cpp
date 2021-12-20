#include "utilities.h"


std::unordered_map<std::string, std::string> util::settingsParser(string filename)
{
    ifstream file;
    file.open(filename);
    if(!file){
        cerr << "Can't open file " << filename << endl;
        // Return empty
        return unordered_map<string, string> {};
    }
    string line;
    while(getline(file, line)){
        cout << line << endl;
    }
    file.close();
    return unordered_map<string, string> {};
}
