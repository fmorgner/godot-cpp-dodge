cmake_minimum_required(VERSION "3.14.0")

project("dodgetc_native"
  LANGUAGES CXX
  VERSION "1.0.0"
  DESCRIPTION "An implementation of the Godot \"Dodge the Creeps!\" tutorial game using godot-cpp"
)

include("FetchContent")

FetchContent_Declare(
  "Godot"
  GIT_REPOSITORY https://github.com/fmorgner/godot-cmake.git
)
FetchContent_MakeAvailable("Godot")

list(APPEND CMAKE_MODULE_PATH
  "${PROJECT_SOURCE_DIR}/cmake/Modules"
  "${PROJECT_BINARY_DIR}/_deps/godot-src/Modules"
)

include("Conan")
include("Godot")

conan_check(REQUIRED)
conan_add_remote(NAME "fmorgner" URL "https://api.bintray.com/conan/fmorgner/conan-public")
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
  INTERPROCEDURAL_OPTIMIZATION ON
  LINK_FLAGS_MINSIZEREL "-s"
  GODOT_BINARY_INSTALL_DIR "godot/bin"
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_definitions("dodgetc" PRIVATE "_USE_MATH_DEFINES")
endif()

godot_register_library("dodgetc")

godot_register_class("dodgetc" "HUD")
godot_register_class("dodgetc" "Main")
godot_register_class("dodgetc" "Mob")
godot_register_class("dodgetc" "Player")