#include "../../include/commands/LsCommand.h"
#include <filesystem>
#include <iostream>

class LsCommand : public ICommand {
public:
    std::string name() const override { return "ls"; }
    std::string help() const override { return "List files in current directory"; }
    int execute(const std::vector<std::string>& args) override {
        std::filesystem::path p = std::filesystem::current_path();
        if (!args.empty()) p = args[0];
        try {
            for (auto &entry : std::filesystem::directory_iterator(p)) {
                std::cout << entry.path().filename().string();
                if (entry.is_directory()) std::cout << "/";
                std::cout << "\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "ls: " << e.what() << '\n';
            return 2;
        }
        return 0;
    }
};

std::unique_ptr<ICommand> createLsCommand() {
    return std::make_unique<LsCommand>();
}
