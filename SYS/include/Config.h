#pragma once
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>

class Config {
public:
    void load(const std::string& path) {
        std::ifstream in(path);
        if (!in) return;
        std::string line;
        while (std::getline(in, line)) {
            if (line.empty() || line[0] == '#') continue;
            auto pos = line.find('=');
            if (pos != std::string::npos) {
                std::string key = line.substr(0, pos);
                std::string val = line.substr(pos + 1);
                settings_[key] = val;
            }
        }
    }
    std::string get(const std::string& key, const std::string& def = "") const {
        auto it = settings_.find(key);
        return (it != settings_.end()) ? it->second : def;
    }
private:
    std::unordered_map<std::string, std::string> settings_;
};
