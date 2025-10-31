#include "../../include/commands/CdCommand.h"
#include <filesystem>
#include <iostream>

class CdCommand : public ICommand {
public:
    std::string name() const override { return "cd"; }
    std::string help() const override { return "Change current directory"; }
    int execute(const std::vector<std::string>& args) override {
        if (args.empty()) {
            std::cerr << "cd: missing operand\n";
            return 1;
        }
        try {
            std::filesystem::current_path(args[0]);
        } catch (const std::exception& e) {
            std::cerr << "cd: " << e.what() << '\n';
            return 2;
        }
        return 0;
    }
};

std::unique_ptr<ICommand> createCdCommand() {
    return std::make_unique<CdCommand>();
}
