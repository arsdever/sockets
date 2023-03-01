#include <iostream>
#include <optional>
#include <spdlog/spdlog.h>
#include <string>
#include <unordered_map>

#include "sockets/socket.hpp"

// parse arguments
std::unordered_map<std::string, std::optional<std::string>> parse_args(
    int argc, char** argv
)
{
    std::unordered_map<std::string, std::optional<std::string>> args;
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[ i ];
        auto eq = arg.find_first_of("=");
        if (eq != std::string::npos) {
            auto key = arg.substr(0, eq);
            auto value = arg.substr(eq + 1);
            args[ key ] = value;
        } else {
            args[ arg ] = std::nullopt;
        }
    }
    return args;
}

// run as client
void run_as_client()
{
    ad::sockets::socket sock;
    sock.connect("127.0.0.1", 8080);
    sock.send("Hello");
    std::string response = sock.recv();
    spdlog::info("Response: {}", response);
    sock.close();
    spdlog::info("Closed socket (client side)");
}

// run as server
void run_as_server() { spdlog::info("Running as server"); }

int main(int argc, char** argv)
{
    auto args = parse_args(argc, argv);

    if (args.find("client") != args.end()) {
        spdlog::info("Running as client");
        try {
            run_as_client();
        } catch (std::exception& e) {
            spdlog::error("Exception: {}", e.what());
        }
        return 0;
    }

    if (args.find("server") != args.end()) {
        spdlog::info("Running as server");
        run_as_server();
        return 0;
    }

    return 0;
}
