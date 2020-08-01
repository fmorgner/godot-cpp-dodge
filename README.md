# Dodge the Creeps!

This is an implementation of the Godot "Dodge the Creeps!" tutorial game using godot-cpp 3.2.

## Running the packaged version

After downloading and extracting the package, you will most likely need to mark the `Dodge the Creeps!.x86_64` file, located in the folder `Dodge the Creeps! (Linux 64)` as executable.
Afterwards, simply launch the executable file.

## Compiling

Before you can use the "script" implementations in Godot, you will need to compile the shared library.
You will need the following:

* Conan
* CMake >= 3.14
* GCC >= 9.2

If you have installed the required tools, issue the following commands from the root folder of your clone:

```
$ cmake -S . -B build
$ cmake --build build
```

If the compilation succeeds, you can now open the project in the Godot editor.

## Packaging

To export the Godot project, simply issue the following commands from the root folder of your clone:

```
mkdir -p pkg
godot --path godot --export "Linux" '../pkg/Dodge the Creeps!.x86_64'
```

You will be left with an executable and the "script" library.
To further bundle them, use the following command from the root folder of your clone:

```
tar -czf 'Dodge the Creeps! (Linux 64).tzst' --transform 's/pkg/Dodge the Creeps! (Linux 64)/' pkg/*
```