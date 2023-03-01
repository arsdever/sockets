#pragma once

#include <stdint.h>
#include <string_view>

// Macros
// define NO_TEMPLATES to disable templates

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

#ifndef NO_TEMPLATES
    template <typename container_t>
    void send(const container_t& data) noexcept(false);

    template <typename container_t, size_t size>
    container_t recv() noexcept(false);
#endif

private:
    void send_all(const void* data, size_t size) noexcept(false);
    void recv_all(void* data, size_t size) noexcept(false);
    void init(socket_type type) noexcept(false);

private:
    int _native;
    socket_type _type;
};

#ifndef NO_TEMPLATES
template <typename container_t>
void socket::send(const container_t& data) noexcept(false)
{
    send_all(data.data(), data.size());
}

template <typename container_t, size_t size>
container_t socket::recv() noexcept(false)
{
    container_t data;
    data.resize(size);
    recv_all(data.data(), size);
    return data;
}
#endif

} // namespace ad::sockets
