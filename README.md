# SYS CLI

A robust, cross-platform C++ CLI tool with an interactive REPL, command history, and colorized output.

## Build

With CMake + Ninja (CLion default):

```bash
cmake -S . -B cmake-build-debug -G Ninja
cmake --build cmake-build-debug
```

Or with Makefiles:

```bash
cmake -S . -B build -G "Unix Makefiles"
cmake --build build
```

The binary is `sys-cli` (or `sys-cli.exe` on Windows) inside the chosen build folder.

## Interactive Mode (REPL)

Run the program without arguments to enter the interactive shell:

```bash
./sys-cli
```

Features in interactive mode:

- **Colorized Prompt**: Shows current working directory.
- **Command History**: Use `history` to view past commands.
- **Quick Recall**: Use `!!` to re-run the last command.
- **Persistent State**: `cd` commands persist between lines.

## Commands

### General

- `help`: List all commands or get help for a specific one.
- `version`: Show current version (0.2.0).
- `history`: Show session command history.
- `exit` / `quit`: Exit the shell.

### Filesystem

- `ls`: List files with **color coding** (Blue for dirs, Green for executables).
  - `ls -a`: Include hidden files.
  - `ls -l`: Long format with sizes and timestamps.
- `pwd`: Print working directory.
- `cd <path>`: Change directory.
- `cd -`: Toggle back to previous directory.

### Processes

- `ps`: List running processes.
  - `ps --filter <name>`: Filter processes by name (e.g., `ps --filter chrome`).

### Data Analysis

- `analyze [file]`: Analyze a CSV file.
  - Computes **Count, Min, Max, Mean, Median, and StdDev** for numeric columns.
  - Generates a colorized report.

## Configuration

Create a `.sysclirc` file in the working directory to customize settings:

```ini
prompt_color=GREEN
```

Supported colors: `RED`, `GREEN`, `BLUE`, `CYAN` (default).

## Notes

- Requires a C++17 compiler (uses `<filesystem>`).
- Cross-platform support for Windows and Linux/macOS.
