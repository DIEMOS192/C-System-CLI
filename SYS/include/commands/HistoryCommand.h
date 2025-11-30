#pragma once
#include "ICommand.h"
#include "../History.h"
#include <memory>

std::unique_ptr<ICommand> createHistoryCommand(const History& history);
