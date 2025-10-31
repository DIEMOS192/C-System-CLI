#pragma once

#include "../ICommand.h"
#include <memory>

std::unique_ptr<ICommand> createAnalyzeCommand(const std::string& dataPath = "data/sample.csv");
