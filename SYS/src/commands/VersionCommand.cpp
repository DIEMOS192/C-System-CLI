#include "../../include/commands/VersionCommand.h"
#include <iostream>

#ifndef SYSCLI_VERSION
#define SYSCLI_VERSION "0.1.0"
#endif

class VersionCommand : public ICommand {
public:
    std::string name() const override { return "version"; }
    std::string help() const override { return "Show version"; }
    int execute(const std::vector<std::string>&) override {
        std::cout << "sys-cli version " << SYSCLI_VERSION << "\n";
        return 0;
    }
};

std::unique_ptr<ICommand> createVersionCommand() {
    return std::make_unique<VersionCommand>();
}
