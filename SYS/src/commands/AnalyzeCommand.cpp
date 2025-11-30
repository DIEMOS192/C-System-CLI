#include "../../include/commands/AnalyzeCommand.h"
#include "../../include/ColorUtils.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

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
            ColorUtils::printError("analyze: cannot open file '" + file + "'");
            return 2;
        }
        std::string line;
        size_t rows = 0;
        size_t cols = 0;
        std::vector<std::string> headers;
        struct Stat { 
            size_t count=0; 
            double sum=0; 
            double min=std::numeric_limits<double>::infinity(); 
            double max=-std::numeric_limits<double>::infinity(); 
            std::vector<double> values;
        };
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
                        st.count++; 
                        st.sum += v; 
                        if (v < st.min) st.min = v; 
                        if (v > st.max) st.max = v;
                        st.values.push_back(v);
                    }
                } catch (...) { /* non-numeric, ignore */ }
                ++idx;
            }
        }
        std::cout << ColorUtils::colorize("Analysis Report", ColorUtils::BOLD) << "\n";
        std::cout << "File: " << file << " | Rows: " << rows << " | Columns: " << cols << "\n\n";
        
        // print simple stats for numeric columns
        for (size_t i = 0; i < stats.size(); ++i) {
            auto &st = stats[i];
            if (st.count > 0) {
                std::string h = (i < headers.size() ? headers[i] : (std::string("col")+std::to_string(i+1)));
                double mean = st.sum / st.count;
                
                // Calculate Median
                double median = 0.0;
                std::sort(st.values.begin(), st.values.end());
                if (st.count % 2 == 0) {
                    median = (st.values[st.count/2 - 1] + st.values[st.count/2]) / 2.0;
                } else {
                    median = st.values[st.count/2];
                }

                // Calculate StdDev
                double varianceSum = 0.0;
                for (double val : st.values) {
                    varianceSum += (val - mean) * (val - mean);
                }
                double stdDev = std::sqrt(varianceSum / st.count);

                std::cout << ColorUtils::colorize("[" + h + "]", ColorUtils::CYAN) << "\n";
                std::cout << "  Count:  " << st.count << "\n";
                std::cout << "  Min:    " << st.min << "\n";
                std::cout << "  Max:    " << st.max << "\n";
                std::cout << "  Mean:   " << std::fixed << std::setprecision(2) << mean << "\n";
                std::cout << "  Median: " << std::fixed << std::setprecision(2) << median << "\n";
                std::cout << "  StdDev: " << std::fixed << std::setprecision(2) << stdDev << "\n\n";
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
