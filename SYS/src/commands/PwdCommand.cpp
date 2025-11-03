#include "../../include/commands/PwdCommand.h"
#include <iostream>
#include <filesystem>

class PwdCommand : public ICommand {
public:
    std::string name() const override { return "pwd"; }
    std::string help() const override { return "Print current directory"; }
    int execute(const std::vector<std::string>&) override {
        std::cout << std::filesystem::current_path().string() << "\n";
        return 0;
    }
};

std::unique_ptr<ICommand> createPwdCommand() {
    return std::make_unique<PwdCommand>();
}
