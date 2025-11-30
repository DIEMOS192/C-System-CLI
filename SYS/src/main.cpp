#include "../include/CommandRegistry.h"
#include "../include/commands/LsCommand.h"
#include "../include/commands/CdCommand.h"
#include "../include/commands/PsCommand.h"
#include "../include/commands/AnalyzeCommand.h"
#include "../include/commands/HelpCommand.h"
#include "../include/commands/VersionCommand.h"
#include "../include/commands/PwdCommand.h"
#include "../include/commands/HistoryCommand.h"
#include "../include/Utils.h"
#include "../include/ColorUtils.h"
#include "../include/History.h"
#include "../include/Config.h"
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <filesystem>

int main(int argc, char** argv) {
    // Enable ANSI colors on Windows
    ColorUtils::setupConsole();

    CommandRegistry registry;
    History history;
    Config config;
    config.load(".sysclirc");

    // register built-in commands
    registry.registerCommand(createLsCommand());
    registry.registerCommand(createCdCommand());
    registry.registerCommand(createPwdCommand());
    registry.registerCommand(createPsCommand());
    registry.registerCommand(createAnalyzeCommand("data/sample.csv"));
    registry.registerCommand(createVersionCommand());
    registry.registerCommand(createHelpCommand(registry));
    registry.registerCommand(createHistoryCommand(history));

    if (argc < 2) {
        std::cout << ColorUtils::colorize("SYS CLI Interactive Mode", ColorUtils::BOLD) << "\n";
        std::cout << "Type 'exit' or 'quit' to leave.\n";

        std::string line;
        while (true) {
            std::string cwd = std::filesystem::current_path().string();
            
            // Use config for prompt color, default to CYAN
            std::string pColor = config.get("prompt_color", ColorUtils::CYAN);
            // If user provided a raw ANSI code or a name, we might need mapping. 
            // For simplicity, let's assume they provide the ANSI code or we map simple names.
            // But since ColorUtils constants are strings, we can't easily map "RED" to ColorUtils::RED without a map.
            // Let's just stick to default CYAN for now unless I add a map.
            // Actually, let's just use CYAN as default and ignore config for color mapping complexity for now, 
            // or just check a few values.
            if (config.get("prompt_color") == "RED") pColor = ColorUtils::RED;
            else if (config.get("prompt_color") == "GREEN") pColor = ColorUtils::GREEN;
            else if (config.get("prompt_color") == "BLUE") pColor = ColorUtils::BLUE;

            std::cout << ColorUtils::colorize(cwd, pColor) << " > ";
            
            if (!std::getline(std::cin, line)) break;
            if (line.empty()) continue;

            // Handle history expansion
            if (line == "!!") {
                std::string last = history.last();
                if (last.empty()) {
                    ColorUtils::printError("No previous command");
                    continue;
                }
                line = last;
                std::cout << line << "\n";
            }

            history.add(line);

            auto parts = SYSUtils::split(line);
            if (parts.empty()) continue;

            std::string cmd = parts[0];
            if (cmd == "exit" || cmd == "quit") break;

            std::vector<std::string> args;
            for (size_t i = 1; i < parts.size(); ++i) args.push_back(parts[i]);

            auto *c = registry.get(cmd);
            if (!c) {
                ColorUtils::printError("Unknown command: " + cmd);
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
