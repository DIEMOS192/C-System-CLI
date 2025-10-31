# SYS CLI

Small example C++ CLI with a command registry and a few built-in commands.

How to build (from workspace root with bash on Windows):

```bash
mkdir -p SYS/build
cd SYS/build
cmake -G "Unix Makefiles" ..
cmake --build .
```

Usage:

```bash
./sys-cli            # prints available commands
./sys-cli ls         # list current directory
./sys-cli cd ..      # change directory
./sys-cli analyze    # analyze data/sample.csv
```

Notes:

- Uses C++17 filesystem.
