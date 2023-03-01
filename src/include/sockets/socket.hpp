#pragma once

#include <stdint.h>
#include <string_view>

namespace ad::sockets
{

class socket
{
private:
    enum class socket_type { undefined, server, client };

public:
    socket() noexcept;
    ~socket() noexcept;

    socket(const socket&) = delete;
    socket& operator=(const socket&) = delete;

    socket(socket&& other) noexcept;
    socket& operator=(socket&& other) noexcept;

    void bind(std::string_view address, uint16_t port) noexcept(false);
    void listen(int backlog) noexcept(false);
    socket accept() noexcept(false);
    void connect(std::string_view address, uint16_t port) noexcept(false);

    void close() noexcept;

    void send(std::string_view data) noexcept(false);
    std::string recv() noexcept(false);

private:
	void init(socket_type type) noexcept(false);

private:
    int _native;
    socket_type _type;
};

} // namespace ad::sockets
