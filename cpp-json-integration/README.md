# C++ JSON Integration Example

This minimal example shows how to read and write JSON in C++ using the header-only [nlohmann/json](https://github.com/nlohmann/json) library. It reads from `input.json`, updates a few fields, and writes a summary to `output.json`.

## Build (Windows)

Requirements:
- CMake 3.16+
- A C++17 compiler (MSVC/Clang/GCC)

From PowerShell in the `cpp-json-integration` folder:

```powershell
# Configure and build
New-Item -ItemType Directory -Force build | Out-Null
Push-Location build
cmake -S .. -B . -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
Pop-Location

# Run (path may differ depending on generator)
# For MSVC multi-config:
.\build\Release\cpp-json-integration.exe
# For single-config (Ninja/Makefile):
.\build\cpp-json-integration.exe
```

The program will:
- Read `input.json` (create a default one if missing)
- Increment a `visits` counter and add a skill
- Write a pretty-printed `output.json`

## Files
- `main.cpp`: Example code using `nlohmann::json`
- `CMakeLists.txt`: Fetches and wires the JSON library
- `input.json`: Sample input
- `output.json`: Generated on run
