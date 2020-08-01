cmake_minimum_required(VERSION "3.17.0")

project("dodgetc_native"
  LANGUAGES CXX
)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules")
set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/godot")

include("Conan")
include("Godot")

conan_check(REQUIRED)
conan_cmake_run(CONANFILE "conanfile.txt"
  OUTPUT_QUIET
  BASIC_SETUP
  CMAKE_TARGETS
  BUILD "missing"
  NO_OUTPUT_DIRS
)

add_library("dodgetc" SHARED
  "source/godot_native_library.cpp"
  "source/HUD.cpp"
  "source/Main.cpp"
  "source/Mob.cpp"
  "source/Player.cpp"
  "source/Rng.cpp"
)

target_include_directories("dodgetc" PRIVATE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

target_link_libraries("dodgetc" PRIVATE
  "CONAN_PKG::godot-cpp"
)

set_target_properties("dodgetc" PROPERTIES
  CXX_STANDARD "17"
  CXX_STANDARD_REQUIRED YES
)

godot_register_library("dodgetc")
godot_register_class("dodgetc" "HUD")
godot_register_class("dodgetc" "Main")
godot_register_class("dodgetc" "Mob")
godot_register_class("dodgetc" "Player")

install(TARGETS "dodgetc"
  LIBRARY DESTINATION "bin/linux"
)