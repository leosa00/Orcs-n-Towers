cmake_minimum_required(VERSION 3.10)

project(YourProjectName)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

# Add your source files
file(GLOB_RECURSE SOURCES "src/*.cpp" "include/*.hpp" "fonts/*.ttf" "textures/*.png")

# Create executable
add_executable(YourExecutable ${SOURCES})

# Link SFML
target_link_libraries(YourExecutable PRIVATE sfml-graphics sfml-audio)

# Set include directories
target_include_directories(YourExecutable PRIVATE include)