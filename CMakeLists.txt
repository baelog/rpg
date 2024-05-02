cmake_minimum_required(VERSION 3.16)

# Project name and version
project(MyCSFMLProject VERSION 1.0)

set(CMAKE_PREFIX_PATH "usr/local/lib/")
# Find the CSFML package
# find_package(CSFML 2.5.2 REQUIRED COMPONENTS system window graphics audio network)

set(CSFML_DIR "/path/to/csfml/install")
# Add the executable target
add_executable(rpg
                main.c
                yaml.c
                read.c
                map.c
                map/ground.c
                map/wall.c)  # Update with your source files

# Link the required CSFML libraries to the executable
target_link_libraries(rpg csfml-system csfml-window csfml-graphics csfml-audio csfml-network)

# Define the source directory for assets
set(ASSETS_DIR ${CMAKE_SOURCE_DIR}/assets)  # Update this with your assets directory

# Custom command to copy assets to the build directory after the build
add_custom_command(
    TARGET rpg
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_DIR} ${CMAKE_BINARY_DIR}/assets
    COMMENT "Copying assets to build directory..."
)