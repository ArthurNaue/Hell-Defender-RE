# 🎮 Hell Defender RE

A reworked version of the [Hell Defender](https://github.com/ArthurNaue/Hell-Defender) game, written in C using [Raylib](https://www.raylib.com/).

## 📁 Project Structure

```
Hell-Defender-RE/
├── assets/             # Game assets (textures, sounds, etc.)
├── include/            # Header files (.h)
├── src/                # Main source code (.c)
├── libraries/
│   └── raylib/         # Raylib as a local subdirectory
├── CMakeLists.txt      # Build script using CMake
└── README.md           # This file
```

## 🧩 Prerequisites

Make sure you have the following packages installed:

### 🐧 Linux (Ubuntu/Debian)

```bash
sudo apt update
sudo apt install build-essential cmake libasound2-dev libpulse-dev libx11-dev libxcursor-dev libxrandr-dev libxi-dev libgl1-mesa-dev libxinerama-dev
```

### 🍎 macOS

```bash
brew install cmake
```

### 🪟 Windows

```bash
- Install:
  - MINGW or MSYS2
  - CMAKE
- Make sure the compiler is added to your PATH
```

## 🚀 How to Properly Clone the Project

This repository uses **Raylib as a Git submodule**, so you should clone it with the `--recursive` flag:

```bash
git clone --recursive https://github.com/ArthurNaue/Hell-Defender-RE.git
cd Hell-Defender-RE
```

If you already cloned it without `--recursive`, run:

```bash
git submodule update --init --recursive
```

## 🛠️ How to Build

### 🔧 Using CMake in the terminal:

```bash
mkdir build
cd build
cmake ..
make
```

## 🎮 How to Run the Game

After building, inside the `build` folder, run:

```bash
./HellDefender
```

On Windows, the executable will be `HellDefender.exe`.

## 📝 Notes

- The `assets/` folder will be automatically copied to the executable directory.
- The project is configured to **use Raylib locally**, so there's **no need to install Raylib separately**.

## 👨‍💻 Author

Arthur Naue  
[GitHub](https://github.com/ArthurNaue)
