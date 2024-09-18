cmake_minimum_required(VERSION 3.16)

# Project name and version
project(MyCSFMLProject VERSION 1.0)

IF (WIN32)
    set(CMAKE_PREFIX_PATH "C:/lib")
    IF (WIN32)
    add_library(csfml-system STATIC IMPORTED)
    set_target_properties(csfml-system PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_PREFIX_PATH}/CSFML/include"
        IMPORTED_LOCATION "${CMAKE_PREFIX_PATH}/CSFML/lib/msvc/csfml-system.lib"
    )
    add_library(csfml-window STATIC IMPORTED)
    set_target_properties(csfml-window PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_PREFIX_PATH}/CSFML/include"
        IMPORTED_LOCATION "${CMAKE_PREFIX_PATH}/CSFML/lib/msvc/csfml-window.lib"
    )
    add_library(csfml-graphics STATIC IMPORTED)
    set_target_properties(csfml-graphics PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_PREFIX_PATH}/CSFML/include"
        IMPORTED_LOCATION "${CMAKE_PREFIX_PATH}/CSFML/lib/msvc/csfml-graphics.lib"
    )
    add_library(csfml-audio STATIC IMPORTED)
    set_target_properties(csfml-audio PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_PREFIX_PATH}/CSFML/include"
        IMPORTED_LOCATION "${CMAKE_PREFIX_PATH}/CSFML/lib/msvc/csfml-audio.lib"
    )

    add_library(crypto STATIC IMPORTED)
    set_target_properties(crypto PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_PREFIX_PATH}/OpenSSL-Win64/include"
        IMPORTED_LOCATION "${CMAKE_PREFIX_PATH}/OpenSSL-Win64/lib/VC/x64/MD/libcrypto.lib"
    )
ENDIF()
  # set stuff for windows
ELSE()
  # set stuff for other systems
  set(CMAKE_PREFIX_PATH "usr/local/lib/")
ENDIF()
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
                map/wall.c)

add_executable(server
                network/server/server.c
                network/server/update.c
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
                map/wall.c
                map/player.c)

target_compile_definitions(server PRIVATE SERVER)

target_link_libraries(server csfml-system crypto)
# Link the required CSFML libraries to the executable
target_link_libraries(client csfml-system csfml-window csfml-graphics csfml-audio crypto)


IF (WIN32)
  target_link_libraries(server Ws2_32.lib)
  target_link_libraries(client Ws2_32.lib)
ENDIF()

IF (NOT WIN32)
  target_link_libraries(server m)
  target_link_libraries(client m)
ENDIF()

# Define the source directory for assets
set(ASSETS_DIR ${CMAKE_SOURCE_DIR}/assets)  # Update this with your assets directory

# Custom command to copy assets to the build directory after the build
add_custom_command(
    TARGET client
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_DIR} ${CMAKE_BINARY_DIR}/assets
    COMMENT "Copying assets to build directory..."
)