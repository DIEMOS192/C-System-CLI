#include "../../include/commands/HistoryCommand.h"
#include <iostream>

class HistoryCommand : public ICommand {
public:
    explicit HistoryCommand(const History& history) : history_(history) {}
    std::string name() const override { return "history"; }
    std::string help() const override { return "Show command history"; }
    int execute(const std::vector<std::string>&) override {
        const auto& hist = history_.get();
        for (size_t i = 0; i < hist.size(); ++i) {
            std::cout << (i + 1) << ": " << hist[i] << "\n";
        }
        return 0;
    }
private:
    const History& history_;
};

std::unique_ptr<ICommand> createHistoryCommand(const History& history) {
    return std::make_unique<HistoryCommand>(history);
}
