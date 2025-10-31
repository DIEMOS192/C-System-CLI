#include "../../include/commands/AnalyzeCommand.h"
#include <fstream>
#include <iostream>
#include <string>

class AnalyzeCommand : public ICommand {
public:
    AnalyzeCommand(std::string path) : path_(std::move(path)) {}
    std::string name() const override { return "analyze"; }
    std::string help() const override { return "Run a basic analysis on a CSV file"; }
    int execute(const std::vector<std::string>& args) override {
        std::string file = path_;
        if (!args.empty()) file = args[0];
        std::ifstream in(file);
        if (!in) {
            std::cerr << "analyze: cannot open file '" << file << "'\n";
            return 2;
        }
        std::string line;
        size_t rows = 0;
        size_t cols = 0;
        while (std::getline(in, line)) {
            ++rows;
            if (rows == 1) {
                // count columns by commas
                size_t c = 1;
                for (char ch : line) if (ch == ',') ++c;
                cols = c;
            }
        }
        std::cout << "analyze: file='" << file << "' rows=" << rows << " cols=" << cols << '\n';
        return 0;
    }
private:
    std::string path_;
};

std::unique_ptr<ICommand> createAnalyzeCommand(const std::string& dataPath) {
    return std::make_unique<AnalyzeCommand>(dataPath);
}
