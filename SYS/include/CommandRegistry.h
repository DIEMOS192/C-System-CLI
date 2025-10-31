#pragma once

#include "ICommand.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class CommandRegistry {
public:
    void registerCommand(std::unique_ptr<ICommand> cmd);
    ICommand* get(const std::string& name) const;
    std::vector<std::string> list() const;
private:
    std::unordered_map<std::string, std::unique_ptr<ICommand>> commands_;
};
