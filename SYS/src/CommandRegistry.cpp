#include "../include/CommandRegistry.h"
#include <algorithm>

void CommandRegistry::registerCommand(std::unique_ptr<ICommand> cmd) {
    if (!cmd) return;
    std::string key = cmd->name();
    commands_[key] = std::move(cmd);
}

ICommand* CommandRegistry::get(const std::string& name) const {
    auto it = commands_.find(name);
    if (it == commands_.end()) return nullptr;
    return it->second.get();
}

std::vector<std::string> CommandRegistry::list() const {
    std::vector<std::string> out;
    out.reserve(commands_.size());
    for (auto const& p : commands_) out.push_back(p.first);
    std::sort(out.begin(), out.end());
    return out;
}
