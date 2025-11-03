#include "../../include/commands/HelpCommand.h"
#include "../../include/CommandRegistry.h"
#include <iostream>

class HelpCommand : public ICommand {
public:
    explicit HelpCommand(CommandRegistry& reg) : reg_(reg) {}
    std::string name() const override { return "help"; }
    std::string help() const override { return "Show help (help [command])"; }
    int execute(const std::vector<std::string>& args) override {
        if (args.empty()) {
            std::cout << "Available commands:\n";
            for (auto &name : reg_.list()) {
                auto *c = reg_.get(name);
                std::cout << "  " << name << " - " << (c ? c->help() : "") << "\n";
            }
            return 0;
        } else {
            auto *c = reg_.get(args[0]);
            if (!c) { std::cerr << "help: unknown command '" << args[0] << "'\n"; return 1; }
            std::cout << args[0] << ": " << c->help() << "\n";
            return 0;
        }
    }
private:
    CommandRegistry& reg_;
};

std::unique_ptr<ICommand> createHelpCommand(CommandRegistry& registry) {
    return std::make_unique<HelpCommand>(registry);
}
