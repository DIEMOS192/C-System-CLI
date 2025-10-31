#include "../../include/commands/PsCommand.h"
#include <iostream>
#include <cstdlib>

class PsCommand : public ICommand {
public:
    std::string name() const override { return "ps"; }
    std::string help() const override { return "Show processes (delegates to platform 'ps' / 'tasklist')"; }
    int execute(const std::vector<std::string>& args) override {
#if defined(_WIN32)
        // Use tasklist on Windows
        return std::system("tasklist");
#else
        return std::system("ps aux");
#endif
    }
};

std::unique_ptr<ICommand> createPsCommand() {
    return std::make_unique<PsCommand>();
}
