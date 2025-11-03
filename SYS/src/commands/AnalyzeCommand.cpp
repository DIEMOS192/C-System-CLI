#include "../../include/commands/AnalyzeCommand.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <vector>

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
        std::vector<std::string> headers;
        struct Stat { size_t count=0; double sum=0; double min=std::numeric_limits<double>::infinity(); double max=-std::numeric_limits<double>::infinity(); };
        std::vector<Stat> stats;
        bool headerParsed = false;
        while (std::getline(in, line)) {
            if (!headerParsed) {
                // first row as header
                std::stringstream ss(line);
                std::string cell;
                while (std::getline(ss, cell, ',')) headers.push_back(cell);
                cols = headers.size();
                stats.resize(cols);
                headerParsed = true;
                continue;
            }
            ++rows;
            std::stringstream ss(line);
            std::string cell; size_t idx=0;
            while (std::getline(ss, cell, ',')) {
                if (idx >= stats.size()) { stats.resize(idx+1); }
                // try parse number
                try {
                    if (!cell.empty()) {
                        double v = std::stod(cell);
                        auto &st = stats[idx];
                        st.count++; st.sum += v; if (v < st.min) st.min = v; if (v > st.max) st.max = v;
                    }
                } catch (...) { /* non-numeric, ignore */ }
                ++idx;
            }
        }
        std::cout << "analyze: file='" << file << "' rows=" << rows << " cols=" << cols << '\n';
        // print simple stats for numeric columns
        for (size_t i = 0; i < stats.size(); ++i) {
            const auto &st = stats[i];
            if (st.count > 0) {
                std::string h = (i < headers.size() ? headers[i] : (std::string("col")+std::to_string(i+1)));
                std::cout << "  [" << h << "] count=" << st.count
                          << " min=" << st.min << " max=" << st.max
                          << " mean=" << (st.sum / st.count) << '\n';
            }
        }
        return 0;
    }
private:
    std::string path_;
};

std::unique_ptr<ICommand> createAnalyzeCommand(const std::string& dataPath) {
    return std::make_unique<AnalyzeCommand>(dataPath);
}
