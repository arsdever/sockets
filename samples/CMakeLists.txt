find_package(spdlog REQUIRED)

add_executable(sample_app main.cpp)
target_link_libraries(sample_app sockets::lib spdlog::spdlog)
