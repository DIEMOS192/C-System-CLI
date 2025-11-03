#pragma once

#include "../ICommand.h"
#include <memory>

std::unique_ptr<ICommand> createPwdCommand();
