cmake_minimum_required(VERSION 3.16)

# Project name and version
project(MyCSFMLProject VERSION 1.0)

set(CMAKE_PREFIX_PATH "usr/local/lib/")
# Find the CSFML package
# find_package(CSFML 2.5.2 REQUIRED COMPONENTS system window graphics audio network)

# set(CSFML_DIR "/path/to/csfml/install")
# Add the executable target
add_executable(client
                network/client/udp_client.c
                network/md5.c
                network/create_payload.c           
                network/tools.c
                network/client/request.c
                network/client/handle_responce.c
                network/protocol/actions.c
                network/actions/move_player.c
                network/player.c
                network/protocol/request_id.c
                network/network_tools.c
                # yaml.c
                # read.c
                # map.c
                map/ground.c
                map/player_other.c
                map/player.c
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
                network/protocol/actions.c
                network/client/request.c
                network/protocol/request_id.c
                network/tools.c
                network/player.c
                network/actions/move_player.c
                network/network_tools.c
                map/ground.c
                map/wall.c)  # Update with your source files

target_compile_definitions(server PRIVATE SERVER)
target_link_libraries(server csfml-system crypto m)
# Link the required CSFML libraries to the executable
target_link_libraries(client csfml-system csfml-window csfml-graphics csfml-audio crypto m)

# Define the source directory for assets
set(ASSETS_DIR ${CMAKE_SOURCE_DIR}/assets)  # Update this with your assets directory

# Custom command to copy assets to the build directory after the build
add_custom_command(
    TARGET client
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_DIR} ${CMAKE_BINARY_DIR}/assets
    COMMENT "Copying assets to build directory..."
)