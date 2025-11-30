#include "../../include/commands/PsCommand.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>

class PsCommand : public ICommand {
public:
    std::string name() const override { return "ps"; }
    std::string help() const override { return "Show processes (ps [--filter <name>])"; }
    int execute(const std::vector<std::string>& args) override {
        std::string filterName;
        std::string extraArgs;

        for (size_t i = 0; i < args.size(); ++i) {
            if (args[i] == "--filter" && i + 1 < args.size()) {
                filterName = args[i+1];
                i++; // skip next arg
            } else {
                extraArgs += " " + args[i];
            }
        }

#if defined(_WIN32)
        std::string cmd = "tasklist";
        if (!filterName.empty()) {
            // If user didn't provide extension, assume .exe might be needed or just partial match
            // tasklist /FI "IMAGENAME eq name.exe"
            // But to be safe and simple, let's try to match what user typed.
            // If it doesn't have .exe, append * to make it a wildcard match if supported, 
            // but tasklist uses eq for exact. Let's use "IMAGENAME eq filterName"
            // If user types "chrome", tasklist expects "chrome.exe".
            if (filterName.find(".exe") == std::string::npos) {
                filterName += ".exe";
            }
            cmd += " /FI \"IMAGENAME eq " + filterName + "\"";
        }
        cmd += extraArgs;
        return std::system(cmd.c_str());
#else
        std::string cmd = "ps aux";
        if (!filterName.empty()) {
            cmd += " | grep " + filterName;
        }
        cmd += extraArgs;
        return std::system(cmd.c_str());
#endif
    }
};

std::unique_ptr<ICommand> createPsCommand() {
    return std::make_unique<PsCommand>();
}
