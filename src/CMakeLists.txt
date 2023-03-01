add_library(sockets_interface INTERFACE)
target_sources(sockets_interface INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/sockets/socket.hpp)
target_include_directories(sockets_interface INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(sockets::interface ALIAS sockets_interface)

add_library(sockets_lib STATIC socket.cpp)
add_library(sockets::lib ALIAS sockets_lib)
target_link_libraries(sockets_lib PUBLIC sockets::interface)
