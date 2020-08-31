[![GitHub release (latest by date)](https://img.shields.io/github/v/release/fmorgner/godot-cpp-dodge)](https://github.com/fmorgner/godot-cpp-dodge/releases/)
[![GitHub](https://img.shields.io/github/license/fmorgner/godot-cpp-dodge)](LICENSE)
[![C++17](https://img.shields.io/badge/c%2B%2B-17-orange)](https://en.cppreference.com/w/cpp/17)
[![Godot 3.2](https://img.shields.io/badge/Godot-3.2-blue)](https://godotengine.org/)
[![Linux](https://img.shields.io/badge/OS-Linux-green)](https://github.com/fmorgner/godot-cpp-dodge/releases/latest/download/Dodge.the.Creeps.Linux.64.tzst)
[![Windows](https://img.shields.io/badge/OS-Windows-green)](https://github.com/fmorgner/godot-cpp-dodge/releases/latest/download/Dodge.the.Creeps.Windows.64.zip)

# Dodge the Creeps!

This is an implementation of the Godot "Dodge the Creeps!" tutorial game using godot-cpp 3.2, with some additional features.

![In-Game Screenshot](screenshot.png)

## Running The Binary Packages

Packaged versions can be found on the [Releases](https://github.com/fmorgner/godot-cpp-dodge/releases/) page.
Recent releases support both Linux and Windows.

### Linux

After downloading and extracting the package, you may need to mark the `Dodge the Creeps!.x86_64` file, located in the folder `Dodge the Creeps! (Linux 64)` as executable.
Afterwards, simply launch the executable file.

### Windows

After downloading and extracting the package, you should be able execute the `Dodge the Creeps!.exe` executable.

## Building From Source

You may also build this project from source.
You will need the following tools, regardless of your target platform:

| Tool                                   | Tested Version| Description                                                            |
|----------------------------------------|---------------|------------------------------------------------------------------------|
| [Python](https://python.org)           | 3\.8          | Used to build [godot-cpp](https://github.com/fmorgner/conan-godot-cpp) |
| [Conan](https://conan.io)              | 1\.28         | Used to build [godot-cpp](https://github.com/fmorgner/conan-godot-cpp) |
| [CMake](https://cmake.org)             | 3\.14         | Used to build the game                                                 |
| [Git LFS](https://git-lfs.github.com/) | 2\.11         | Used to store and fetch game assets                                    |
| [Godot](https://godotengine.org/)      | 3\.2          | Used as the game engine                                                |

Compilation is currently supported on both Linux and Windows.
On Linux, you may install Godot either via your package manager, or via [Flatpak](https://flathub.org/apps/details/org.godotengine.Godot).
On Windows, you can use [Chocolatey](https://chocolatey.org/packages/godot) to install Godot.

Before running the game, you have to compile the *scripts* used in the implementation.
Follow the guides below to do so.
Of course you will also need to clone or download the source code before continuing.

> **NOTE**
> All commands have been tested in **bash** on Linux and **Powershell** on Windows.

### Building on Linux

In addition to the basic tools, you will need the at least GCC version 9.2 to build the project on Linux.
After installing gcc, you can build the project using the following commands from the root of the source:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### Building on Windows

Before starting the build process, make sure that the tools mentioned above are installed and accessible in your **PATH**.

When building on Windows, you will need to have a recent version of the Microsoft Builds Tools for Visual Studio.
Currently, all builds on Windows have only been tested with version the [Microsoft Builds Tools for Visual Studio 2019](https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2019)
After installing the build tools, you can use the following commands from the root of the source:

```powershell
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

## Packaging

The Godot game engine is capable of exporting a game so that it can easily be deployed.
Follow the instructions below to export the game for packaging.
Make sure you have compiled the *scripts* as described above.

> **NOTE**
> All commands have been tested in **bash** on Linux and **Powershell** on Windows.

### Packaging on Linux

To export the game for Linux, you can use the following command:

```bash
godot --path godot --export "Linux" '../pkg/Dodge the Creeps!.x86_64'
```

You will be left with an executable and a *script* library called `libdodgetc.so`.
To further bundle them, use the following command from the root folder of your clone:

```bash
tar -czf "Dodge.the.Creeps.Linux.64.tzst" --transform 's/pkg/Dodge the Creeps! (Linux 64)/' pkg/*
```

### Packaging on Windows

To export the game for Linux, you can use the following command:

```powershell
godot --path godot --export 'Windows Desktop' '../pkg/Dodge the Creeps!.exe'
```

You will be left with an executable and a *script* library called `dodgetc.dll`.
To further bundle them, use the following command from the root folder of your clone:

```powershell
New-Item -Path 'pkg\Dodge the Creeps! (Windows 64)' -ItemType Directory
Get-ChildItem -Path 'pkg\*' -Include '*.exe','*.dll' | Copy-Item -Destination 'pkg\Dodge the Creeps! (Windows 64)'
Compress-Archive -Path '.\pkg\Dodge the Creeps! (Windows 64)' -DestinationPath 'Dodge.the.Creeps.Windows.64.zip'
```

## Asset Licenses

All assets used in this project are licensed as follows:

| Asset Group            | Author                                                              | License Identifier                                          |
|------------------------|---------------------------------------------------------------------|-------------------------------------------------------------|
| Death Sparkle          | Felix Morgner                                                       | [CC-BY-SA-4.0](https://spdx.org/licenses/CC-BY-SA-4.0.html) |
| House In a Forest Loop | [HorrorPen](https://opengameart.org/content/loop-house-in-a-forest) | [CC-BY-3.0](https://spdx.org/licenses/CC-BY-3.0.html)       |
| Player and Mob Sprites | [kenney.nl](https://www.kenney.nl/assets/abstract-platformer)       | [CC0-1.0](https://spdx.org/licenses/CC0-1.0.html)           |
| Xolonium Font          | [Severin Meyer](gitlab.com/sev/xolonium)                            | [OFL-1.0](https://spdx.org/licenses/OFL-1.0.html)           |
| Godot Engine Logo      | Andrea Calabró                                                      | [CC-BY-3.0](https://spdx.org/licenses/CC-BY-3.0.html)       |
| Game Over Sound        | `<UNKNOWN>`                                                         | `<UNKNOWN>`                                                 |
| Coin Animation         | [DontMind8](https://opengameart.org/content/coin-animation)         | [CC-BY-4.0](https://spdx.org/licenses/CC-BY-4.0.html)       |