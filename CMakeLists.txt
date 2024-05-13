cmake_minimum_required(VERSION 3.16)

# Project name and version
project(MyCSFMLProject VERSION 1.0)

set(CMAKE_PREFIX_PATH "usr/local/lib/")
# Find the CSFML package
# find_package(CSFML 2.5.2 REQUIRED COMPONENTS system window graphics audio network)

set(CSFML_DIR "/path/to/csfml/install")
# Add the executable target
add_executable(client
                network/client/udp_client.c
                network/md5.c
                network/create_payload.c                

                # yaml.c
                # read.c
                # map.c
                map/ground.c
                map/wall.c)  # Update with your source files

add_executable(server
                network/server/server.c
                network/server/new_connection.c
                yaml.c
                read.c
                map.c
                network/md5.c
                network/create_map.c
                network/create_payload.c                
                network/protocol/id.c
                network/protocol/broadcast.c
                map/ground.c
                map/wall.c)  # Update with your source files

target_compile_definitions(server PRIVATE SERVER)
target_link_libraries(server csfml-system crypto)
# Link the required CSFML libraries to the executable
target_link_libraries(client csfml-system csfml-window csfml-graphics csfml-audio crypto)

# Define the source directory for assets
set(ASSETS_DIR ${CMAKE_SOURCE_DIR}/assets)  # Update this with your assets directory

# Custom command to copy assets to the build directory after the build
add_custom_command(
    TARGET client
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_DIR} ${CMAKE_BINARY_DIR}/assets
    COMMENT "Copying assets to build directory..."
)