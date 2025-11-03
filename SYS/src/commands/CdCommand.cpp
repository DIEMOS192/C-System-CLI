#include "../../include/commands/CdCommand.h"
#include <filesystem>
#include <iostream>

class CdCommand : public ICommand {
public:
    std::string name() const override { return "cd"; }
    std::string help() const override { return "Change current directory (cd <path>|-)"; }
    int execute(const std::vector<std::string>& args) override {
        if (args.empty()) {
            std::cerr << "cd: missing operand\n";
            return 1;
        }
        try {
            if (args[0] == "-") {
                if (prev_.empty()) {
                    std::cerr << "cd: no previous directory\n"; return 1;
                }
                auto cur = std::filesystem::current_path();
                std::filesystem::current_path(prev_);
                prev_ = cur;
            } else {
                auto cur = std::filesystem::current_path();
                std::filesystem::current_path(args[0]);
                prev_ = cur;
            }
        } catch (const std::exception& e) {
            std::cerr << "cd: " << e.what() << '\n';
            return 2;
        }
        return 0;
    }
private:
    std::filesystem::path prev_{};
};

std::unique_ptr<ICommand> createCdCommand() {
    return std::make_unique<CdCommand>();
}
