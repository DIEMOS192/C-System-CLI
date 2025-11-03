# SYS CLI

Small example C++ CLI with a command registry and a few built-in commands.

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

## Usage

```bash
./sys-cli                 # prints usage with hint to help
./sys-cli help            # list commands
./sys-cli help ls         # show help for a command
./sys-cli version         # show version

# Filesystem
./sys-cli ls              # list current directory
./sys-cli ls -a           # include dot files
./sys-cli ls -l           # long format with sizes and timestamps
./sys-cli ls path/to/dir  # list given path
./sys-cli pwd             # print working directory
./sys-cli cd ..           # change directory
./sys-cli cd -            # toggle back to previous directory

# Processes
./sys-cli ps              # delegates to tasklist (Windows) or ps aux (Unix)
./sys-cli ps /FI "IMAGENAME eq conhost.exe"  # pass-through args

# CSV analysis
./sys-cli analyze                     # analyze data/sample.csv by default
./sys-cli analyze path/to/file.csv    # analyze given file
```

### Analyze output

- Prints row/column counts
- Computes numeric stats per column (min/max/mean) ignoring non-numeric values

## Notes

- Requires a C++17 compiler (uses `<filesystem>`)
- On Windows, `ps` uses `tasklist`; on Unix-like systems it uses `ps aux`
