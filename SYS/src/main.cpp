#include "../include/CommandRegistry.h"
#include "../include/commands/LsCommand.h"
#include "../include/commands/CdCommand.h"
#include "../include/commands/PsCommand.h"
#include "../include/commands/AnalyzeCommand.h"
#include <iostream>
#include <memory>
#include <vector>
#include <string>

int main(int argc, char** argv) {
    CommandRegistry registry;

    // register built-in commands
    registry.registerCommand(createLsCommand());
    registry.registerCommand(createCdCommand());
    registry.registerCommand(createPsCommand());
    registry.registerCommand(createAnalyzeCommand("data/sample.csv"));

    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <command> [args...]\n";
        std::cout << "Available commands:\n";
        for (auto &name : registry.list()) {
            auto *c = registry.get(name);
            std::cout << "  " << name << " - " << (c ? c->help() : "") << "\n";
        }
        return 0;
    }

    std::string cmd = argv[1];
    std::vector<std::string> args;
    for (int i = 2; i < argc; ++i) args.emplace_back(argv[i]);

    auto *c = registry.get(cmd);
    if (!c) {
        std::cerr << "Unknown command: " << cmd << "\n";
        return 127;
    }

    return c->execute(args);
}
