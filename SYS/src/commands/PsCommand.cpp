#include "../../include/commands/PsCommand.h"
#include <iostream>
#include <cstdlib>
#include <string>

class PsCommand : public ICommand {
public:
    std::string name() const override { return "ps"; }
    std::string help() const override { return "Show processes (ps [args...] -> tasklist/ps)"; }
    int execute(const std::vector<std::string>& args) override {
#if defined(_WIN32)
        // Use tasklist on Windows; pass through simple args
        std::string cmd = "tasklist";
        for (auto &a : args) { cmd += " "; cmd += a; }
        return std::system(cmd.c_str());
#else
        std::string cmd = "ps aux";
        for (auto &a : args) { cmd += " "; cmd += a; }
        return std::system(cmd.c_str());
#endif
    }
};

std::unique_ptr<ICommand> createPsCommand() {
    return std::make_unique<PsCommand>();
}
