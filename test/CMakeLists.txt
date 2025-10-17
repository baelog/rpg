# set(CMAKE_PREFIX_PATH "usr/local/lib/")
include_directories(/usr/local/include/unity)

add_executable("test-bin"
                ../network/md5.c
                ../network/protocol/message.c
                mainTest.c
                packets/helper.c
                packets/TestPacketList.c
                packets/TestSequencesList.c)


target_link_libraries("test-bin" unity m crypto)
