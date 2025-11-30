#include "../include/CommandRegistry.h"
#include "../include/commands/LsCommand.h"
#include "../include/commands/CdCommand.h"
#include "../include/commands/PsCommand.h"
#include "../include/commands/AnalyzeCommand.h"
#include "../include/commands/HelpCommand.h"
#include "../include/commands/VersionCommand.h"
#include "../include/commands/PwdCommand.h"
#include "../include/Utils.h"
#include <iostream>
#include <memory>
#include <vector>
#include <string>

int main(int argc, char** argv) {
    CommandRegistry registry;

    // register built-in commands
    registry.registerCommand(createLsCommand());
    registry.registerCommand(createCdCommand());
    registry.registerCommand(createPwdCommand());
    registry.registerCommand(createPsCommand());
    registry.registerCommand(createAnalyzeCommand("data/sample.csv"));
    registry.registerCommand(createVersionCommand());
    registry.registerCommand(createHelpCommand(registry));

    if (argc < 2) {
        std::cout << "SYS CLI Interactive Mode\n";
        std::cout << "Type 'exit' or 'quit' to leave.\n";

        std::string line;
        while (true) {
            std::cout << "> ";
            if (!std::getline(std::cin, line)) break;
            if (line.empty()) continue;

            auto parts = SYSUtils::split(line);
            if (parts.empty()) continue;

            std::string cmd = parts[0];
            if (cmd == "exit" || cmd == "quit") break;

            std::vector<std::string> args;
            for (size_t i = 1; i < parts.size(); ++i) args.push_back(parts[i]);

            auto *c = registry.get(cmd);
            if (!c) {
                std::cerr << "Unknown command: " << cmd << "\n";
            } else {
                c->execute(args);
            }
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
