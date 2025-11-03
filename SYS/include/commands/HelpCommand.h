#pragma once

#include "../ICommand.h"
#include <memory>
#include <string>

class CommandRegistry; // fwd decl

std::unique_ptr<ICommand> createHelpCommand(CommandRegistry& registry);
