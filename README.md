LateBit Template
---

A template to get started with the [LateBit](https://github.com/latebit/latebit-engine) game engine.

## How to use this template?

```sh
# Clone the repository
git clone https://github.com/latebit/latebit-template.git

# Go in the directory
cd latebit-template

# Configure
cmake -B build

# Build and run the demo
cmake --build build -t run
```

## Dependencies

To run the commands above you would need the following dependencies

  * A C++ compiler that supports C++20 (for example, [LLVM/Clang](https://releases.llvm.org/): `>=14`)
  * [cmake](https://cmake.org/download/): `>=3.28.1`

## What's included?

* [latebit](https://github.com/latebit/latebit-engine) with all the setup required for your IDE
* A `CMakeLists.txt` template to build your game natively and on WASM
* Example assets (sprites, audio) and configuration to see how to work with `latebit`