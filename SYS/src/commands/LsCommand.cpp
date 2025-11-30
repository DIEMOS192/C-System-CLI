#include "../../include/commands/LsCommand.h"
#include "../../include/ColorUtils.h"
#include <filesystem>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>
using std::uintmax_t;

class LsCommand : public ICommand {
public:
    std::string name() const override { return "ls"; }
    std::string help() const override { return "List files (ls [-a] [-l] [path])"; }
    static std::string humanSize(uintmax_t bytes) {
        const char* suffix[] = {"B","KB","MB","GB","TB"};
        double count = static_cast<double>(bytes);
        int i = 0;
        while (count >= 1024.0 && i < 4) { count /= 1024.0; ++i; }
        std::ostringstream oss; oss<< std::fixed << std::setprecision((i==0)?0:1) << count << suffix[i];
        return oss.str();
    }
    int execute(const std::vector<std::string>& args) override {
        bool all = false; // -a show dotfiles
        bool longfmt = false; // -l long listing
        std::filesystem::path p = std::filesystem::current_path();
        // parse simple flags
        for (const auto& a : args) {
            if (!a.empty() && a[0] == '-') {
                if (a.find('a') != std::string::npos) all = true;
                if (a.find('l') != std::string::npos) longfmt = true;
            } else {
                p = a;
            }
        }
        try {
            for (auto &entry : std::filesystem::directory_iterator(p)) {
                auto name = entry.path().filename().string();
                if (!all && !name.empty() && name[0] == '.') continue;

                std::string displayName = name;
                if (entry.is_directory()) {
                    displayName = ColorUtils::colorize(name + "/", ColorUtils::BLUE);
                } else if (name.size() > 4 && name.substr(name.size()-4) == ".exe") {
                    displayName = ColorUtils::colorize(name, ColorUtils::GREEN);
                }

                if (!longfmt) {
                    std::cout << displayName << "\n";
                } else {
                    uintmax_t sz = 0; std::error_code ec;
                    if (entry.is_regular_file(ec)) sz = entry.file_size(ec);
                    auto ftime = entry.last_write_time(ec);
                    auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
                        ftime - decltype(ftime)::clock::now() + std::chrono::system_clock::now());
                    std::time_t cftime = std::chrono::system_clock::to_time_t(sctp);
                    std::tm* tm = std::localtime(&cftime);
                    char buf[20]{}; if (tm) std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", tm);
                    std::cout << std::setw(10) << humanSize(sz) << "  " << buf << "  " << displayName << "\n";
                }
            }
        } catch (const std::exception& e) {
            ColorUtils::printError("ls: " + std::string(e.what()));
            return 2;
        }
        return 0;
    }
};

std::unique_ptr<ICommand> createLsCommand() {
    return std::make_unique<LsCommand>();
}
