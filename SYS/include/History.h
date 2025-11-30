#pragma once
#include <vector>
#include <string>

class History {
public:
    void add(const std::string& cmd) {
        if (cmd.empty()) return;
        history_.push_back(cmd);
    }
    const std::vector<std::string>& get() const { return history_; }
    std::string last() const {
        if (history_.empty()) return "";
        return history_.back();
    }
    void clear() { history_.clear(); }
private:
    std::vector<std::string> history_;
};
