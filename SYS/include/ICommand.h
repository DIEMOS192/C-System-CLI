#pragma once

#include <string>
#include <vector>

class ICommand {
public:
    virtual ~ICommand() = default;
    // command name (e.g. "ls")
    virtual std::string name() const = 0;
    // short help
    virtual std::string help() const = 0;
    // execute with args (argv style excluding program and command)
    // return exit code (0 success)
    virtual int execute(const std::vector<std::string>& args) = 0;
};
